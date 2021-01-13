
#include "RegistrationWindow.h"
#include "Client.h"
#include "ui_registrationwindow.h"
#include "OtherFunctions.h"

// Metodi pubblici
RegistrationWindow::RegistrationWindow(QWidget *parent, Client *client, QString username): QDialog(parent), client(client) {
	ui = QSharedPointer<Ui::RegistrationWindow>::create();
	ui->setupUi(this);
	
	adjustGraphics(username);
	createConnections();
	
	ui->NameEdit->setFocus();
	this->show();
}

void RegistrationWindow::readResponse(QJsonObject jSobject) {
    auto body = jSobject["body"].toString();
	if (body == "ok") {
		client->setFileList(jSobject);
		User u(ui->UsernameEdit->text(), pixmapFrom(jSobject["propic"]), jSobject["name"].toString(), jSobject["surname"].toString());
		qDebug() << u.getName() << " " << u.getSurname();
		client->setLoggedUser(u);
		QApplication::restoreOverrideCursor();
		client->openFileChoiceWindow(true);
		this->accept();
	} else if (body == "alreadyregistered") {
		reactivateWindow(this);
        createMessageBox(this, QMessageBox::Information, "Username already used.\nTry another one.");
		statusBar->showMessage(tr("Username already used."), MSGTIME);
	} else if (body == "fail") {
		reactivateWindow(this);
        createMessageBox(this, QMessageBox::Warning, "Server error.\nTry again later.");
		statusBar->showMessage(tr("Server error."), MSGTIME);
	}
}

// Metodi privati
void RegistrationWindow::adjustGraphics(QString &username) {
	statusBar = QSharedPointer<QStatusBar>::create(this);
    statusBar->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    statusBar->setSizeGripEnabled(false);
	ui->verticalLayout->addWidget(statusBar.get());
	ui->UsernameEdit->setText(username);
	
	ui->UsernameEdit->setToolTip(usernameInfo);
	ui->PasswordEdit->setToolTip(passwordInfo);
	
	hidePassword = ui->PasswordEdit->addAction(QIcon(iconsPath + "myicons-eye-on.png"), QLineEdit::TrailingPosition);
	passwordButton = qobject_cast<QToolButton *>(hidePassword->associatedWidgets().last());
	passwordButton->setCursor(QCursor(Qt::PointingHandCursor));
	
	hideRepeatPassword = ui->RepeatPasswordEdit->addAction(QIcon(iconsPath + "myicons-eye-on.png"), QLineEdit::TrailingPosition);
	repeatPasswordButton = qobject_cast<QToolButton *>(hideRepeatPassword->associatedWidgets().last());
	repeatPasswordButton->setCursor(QCursor(Qt::PointingHandCursor));

    ui->NameEdit->setAttribute(Qt::WA_MacShowFocusRect, 0);
    ui->SurnameEdit->setAttribute(Qt::WA_MacShowFocusRect, 0);
    ui->UsernameEdit->setAttribute(Qt::WA_MacShowFocusRect, 0);
    ui->PasswordEdit->setAttribute(Qt::WA_MacShowFocusRect, 0);
    ui->RepeatPasswordEdit->setAttribute(Qt::WA_MacShowFocusRect, 0);

}

void RegistrationWindow::createConnections() {
	connect(passwordButton, &QToolButton::pressed, this, [this](){ pressPasswordButton(ui->PasswordEdit, passwordButton); });
	connect(passwordButton, &QToolButton::released, this, [this](){ releasePasswordButton(ui->PasswordEdit, passwordButton); });
	connect(repeatPasswordButton, &QToolButton::pressed, this, [this](){ pressPasswordButton(ui->RepeatPasswordEdit, repeatPasswordButton); });
	connect(repeatPasswordButton, &QToolButton::released, this, [this](){ releasePasswordButton(ui->RepeatPasswordEdit, repeatPasswordButton); });
	
	connect(ui->NameEdit, &QLineEdit::textChanged, this, &RegistrationWindow::enableRegisterButton);
	connect(ui->SurnameEdit, &QLineEdit::textChanged, this, &RegistrationWindow::enableRegisterButton);
	connect(ui->UsernameEdit, &QLineEdit::textChanged, this, &RegistrationWindow::enableRegisterButton);
	connect(ui->UsernameEdit, &QLineEdit::textChanged, this, [this](){ correctUsername(ui->UsernameEdit->text(), ui->CorrectUsername); });
	connect(ui->PasswordEdit, &QLineEdit::textChanged, this, &RegistrationWindow::enableRegisterButton);
	connect(ui->PasswordEdit, &QLineEdit::textChanged, this, [this](){ correctPassword(ui->PasswordEdit->text(), ui->CorrectPassword); });
	connect(ui->RepeatPasswordEdit, &QLineEdit::textChanged, this, &RegistrationWindow::enableRegisterButton);
	connect(ui->RepeatPasswordEdit, &QLineEdit::textChanged, this, [this](){
		if (ui->RepeatPasswordEdit->text() == ui->PasswordEdit->text() | ui->RepeatPasswordEdit->text().isEmpty()) {
			correctPassword(ui->RepeatPasswordEdit->text(), ui->CorrectRepeatPassword);
		} else {
			ui->CorrectRepeatPassword->setIcon(QIcon(iconsPath + "myicons-cancel.png"));
		}
	});
	connect(ui->RegisterButton, &QPushButton::released, this, &RegistrationWindow::requestRegistration);
	connect(ui->ProfilePictureButton, &QPushButton::released, this, &RegistrationWindow::uploadProfilePicture);
	connect(ui->DeletePictureButton, &QPushButton::released, this, &RegistrationWindow::deleteProfilePicture);
	connect(ui->InfoUsername, &QPushButton::released, this, [this](){ createMessageBox(this, QMessageBox::Information, usernameInfo); });
	connect(ui->InfoPassword, &QPushButton::released, this, [this](){ createMessageBox(this, QMessageBox::Information, passwordInfo); });
	connect(ui->BackButton, &QPushButton::released, this, [this](){ this->reject(); });
}

// Slots
void RegistrationWindow::enableRegisterButton() {
	if (ui->UsernameEdit->text() == QString("myicons-default-user-image")) {
		statusBar->showMessage(tr("This username is not valid."));
		ui->RegisterButton->setEnabled(false);
		return;
	}
	
	if (!ui->NameEdit->text().isEmpty() & !ui->SurnameEdit->text().isEmpty() & !ui->UsernameEdit->text().isEmpty() & !ui->PasswordEdit->text().isEmpty() & !ui->RepeatPasswordEdit->text().isEmpty()) {
		if (ui->PasswordEdit->text() != ui->RepeatPasswordEdit->text() | !checkPasswordFormat(ui->PasswordEdit->text()) | !checkUsernameFormat(ui->UsernameEdit->text())) {
			ui->RegisterButton->setEnabled(false);
		} else {
			ui->RegisterButton->setEnabled(true);
		}
	} else {
		ui->RegisterButton->setEnabled(false);
	}
	
	if (!checkUsernameFormat(ui->UsernameEdit->text()) & !ui->UsernameEdit->text().isEmpty()) {
		if (statusBar->currentMessage() != QString(tr("The username format is not valid."))) {
			statusBar->showMessage(tr("The username format is not valid."));
		}
		return;
	} else {
		statusBar->clearMessage();
	}
	
	if (!checkPasswordFormat(ui->PasswordEdit->text()) & !ui->PasswordEdit->text().isEmpty()) {
		if (statusBar->currentMessage() != QString(tr("The password format is not valid."))) {
			statusBar->showMessage(tr("The password format is not valid."));
		}
		return;
	} else {
		statusBar->clearMessage();
	}
	
	if (ui->PasswordEdit->text() != ui->RepeatPasswordEdit->text()) {
		if (statusBar->currentMessage() != QString(tr("The passwords do not coincide!"))) {
			statusBar->showMessage(tr("The passwords do not coincide!"));
		}
	} else {
		statusBar->clearMessage();
	}
}

void RegistrationWindow::uploadProfilePicture() {
	qDebug() << "Uploading profile picture";
	QString filename = QFileDialog::getOpenFileName(this, tr("Choose profile picture"), QStandardPaths::standardLocations(QStandardPaths::PicturesLocation).last(), tr("Images (*.jpg *.png *.jpeg *.bmp *.JPG *.PNG *.JPEG *.BMP)"));
	if (QString::compare(filename, QString()) != 0) {
		QImage image;
		bool valid = image.load(filename);
		if (valid) {
			ui->ProfilePicture->setPixmap(QPixmap::fromImage(image).scaled(96, 96, Qt::KeepAspectRatio));
			ui->DeletePictureButton->setEnabled(true);
		}
	}
}

void RegistrationWindow::deleteProfilePicture() {
	qDebug() << "Deleting profile picture";
	ui->ProfilePicture->setPixmap(QPixmap(defaultPicture).scaled(96, 96, Qt::KeepAspectRatio));
	ui->DeletePictureButton->setEnabled(false);
	ui->DeletePictureButton->parentWidget()->setFocus();
}

void RegistrationWindow::requestRegistration() {
	if (!ui->DeletePictureButton->isEnabled()) {
        auto ans = createMessageBox(this, QMessageBox::Question, "You did not select a profile picture.\nDo you want to continue anyway?", QMessageBox::Yes | QMessageBox::No);
		if (ans == QMessageBox::No) {
			uploadProfilePicture();
			return;
		}
	}
	
	deactivateWindow(this);
	
	if (!client->checkSocket()) {
        createMessageBox(this, QMessageBox::Warning, "Connection error.");
		statusBar->showMessage(tr("Connection error."), MSGTIME);
		reactivateWindow(this);
		return;
	}
	
	if (!sendJSonMessage(client, "registration", ui->UsernameEdit->text(), ui->PasswordEdit->text(), ui->NameEdit->text(), ui->SurnameEdit->text(), jsonValFromPixmap(ui->ProfilePicture->pixmap(Qt::ReturnByValue)))) {
        createMessageBox(this, QMessageBox::Warning, "Could not send message.\nTry again later.");
		statusBar->showMessage(tr("Could not send message."), MSGTIME);
		reactivateWindow(this);
		return;
	}
	
	statusBar->showMessage(tr("Checking the database..."), MSGTIME);
	qDebug() << "Checking the database...";
}
