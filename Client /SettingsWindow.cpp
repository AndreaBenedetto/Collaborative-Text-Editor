
#include "SettingsWindow.h"
#include "ui_settingswindow.h"
#include "Client.h"
#include "OtherFunctions.h"

// Metodi pubblici
SettingsWindow::SettingsWindow(QWidget *parent, Client *client, QString filename): QDialog(parent), client(client), filename(filename) {
	ui = QSharedPointer<Ui::SettingsWindow>::create();
	ui->setupUi(this);
	
	adjustGraphics();
	createConnections();

	if (filename.isEmpty()) {
        this->show();
	} else {
	    this->exec();
	}
}

void SettingsWindow::readResponse(QJsonObject jSobject) {
    auto header = jSobject["header"].toString();
    auto body = jSobject["body"].toString();
	if (header == "updatepropic") {
		if (body == "ok") {
			User u(ui->UsernameEdit->text(), ui->ProfilePicture->pixmap(Qt::ReturnByValue), ui->NameEdit->text(), ui->SurnameEdit->text());
			client->setLoggedUser(u);
			ui->UndoButton->setEnabled(false);
			imageUpdatable = false;
			enableButtons();
			reactivateWindow(this);
			statusBar->showMessage(tr("Profile picture updated correctly."), MSGTIME);
		} else if (body == "wrongpassword") {
			reactivateWindow(this);
			createMessageBox(this, QMessageBox::Information, "The password is wrong.\nTry again.");
			statusBar->showMessage(tr("Wrong password."), MSGTIME);
		} else if (body == "fail") {
			reactivateWindow(this);
			createMessageBox(this, QMessageBox::Warning, "Server error.\nTry again later.");
			statusBar->showMessage(tr("Server error."), MSGTIME);
		}
	} else if (header == "updatepassword") {
		if (body == "ok") {
			ui->CurrentPasswordEdit->clear();
            ui->NewPasswordEdit->clear();
            ui->RepeatNewPasswordEdit->clear();
			reactivateWindow(this);
			statusBar->showMessage(tr("Password updated correctly."), MSGTIME);
		} else if (body == "wrongpassword") {
			reactivateWindow(this);
			createMessageBox(this, QMessageBox::Information, "The password is wrong.\nTry again.");
			statusBar->showMessage(tr("Wrong password."), MSGTIME);
		} else if (body == "fail") {
			reactivateWindow(this);
            createMessageBox(this, QMessageBox::Warning, "Server error.\nTry again later.");
			statusBar->showMessage(tr("Server error."), MSGTIME);
		}
	} else if (header == "updatepropiceditor") {
		if (body == "ok") {
			User u(ui->UsernameEdit->text(), ui->ProfilePicture->pixmap(Qt::ReturnByValue), ui->NameEdit->text(), ui->SurnameEdit->text());
			client->setLoggedUser(u);
			ui->UndoButton->setEnabled(false);
			imageUpdatable = false;
			enableButtons();
			reactivateWindow(this);
			statusBar->showMessage(tr("Profile picture updated correctly."), MSGTIME);
		} else if (body == "wrongpassword") {
			reactivateWindow(this);
            createMessageBox(this, QMessageBox::Information, "The password is wrong.\nTry again.");
			statusBar->showMessage(tr("Wrong password."), MSGTIME);
		} else if (body == "fail") {
			reactivateWindow(this);
            createMessageBox(this, QMessageBox::Critical, "Server error.\nTry again later.");
			QApplication::quit();
		}
	} else if (header == "updatepasswordeditor") {
		if (body == "ok") {
			ui->CurrentPasswordEdit->clear();
			ui->NewPasswordEdit->clear();
            ui->RepeatNewPasswordEdit->clear();
			reactivateWindow(this);
			statusBar->showMessage(tr("Password updated correctly."), MSGTIME);
		} else if (body == "wrongpassword") {
			reactivateWindow(this);
            createMessageBox(this, QMessageBox::Information, "The password is wrong.\nTry again.");
			statusBar->showMessage(tr("Wrong password."), MSGTIME);
		} else if (body == "fail") {
			reactivateWindow(this);
            createMessageBox(this, QMessageBox::Critical, "Server error.\nTry again later.");
			QApplication::quit();
		}
	}
}

// Metodi privati
void SettingsWindow::adjustGraphics() {
	statusBar = QSharedPointer<QStatusBar>::create(this);
    statusBar->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    statusBar->setSizeGripEnabled(false);
	ui->verticalLayout->addWidget(statusBar.get());
	ui->ProfilePicture->setPixmap(client->getLoggedUser()->getPropic().scaled(96, 96, Qt::KeepAspectRatio));
	ui->NameEdit->setText(client->getLoggedUser()->getName());
	ui->SurnameEdit->setText(client->getLoggedUser()->getSurname());
	ui->UsernameEdit->setText(client->getLoggedUser()->getUsername());
	
	ui->NewPasswordEdit->setToolTip(passwordInfo);
	
	hideCurrentPassword = ui->CurrentPasswordEdit->addAction(QIcon(iconsPath + "myicons-eye-on.png"), QLineEdit::TrailingPosition);
	currentPasswordButton = qobject_cast<QToolButton *>(hideCurrentPassword->associatedWidgets().last());
	currentPasswordButton->setCursor(QCursor(Qt::PointingHandCursor));
	
	hideNewPassword = ui->NewPasswordEdit->addAction(QIcon(iconsPath + "myicons-eye-on.png"), QLineEdit::TrailingPosition);
	newPasswordButton = qobject_cast<QToolButton *>(hideNewPassword->associatedWidgets().last());
	newPasswordButton->setCursor(QCursor(Qt::PointingHandCursor));

    hideRepeatNewPassword = ui->RepeatNewPasswordEdit->addAction(QIcon(iconsPath + "myicons-eye-on.png"), QLineEdit::TrailingPosition);
    repeatNewPasswordButton = qobject_cast<QToolButton *>(hideRepeatNewPassword->associatedWidgets().last());
    repeatNewPasswordButton->setCursor(QCursor(Qt::PointingHandCursor));

    ui->NameEdit->setAttribute(Qt::WA_MacShowFocusRect, 0);
    ui->SurnameEdit->setAttribute(Qt::WA_MacShowFocusRect, 0);
    ui->UsernameEdit->setAttribute(Qt::WA_MacShowFocusRect, 0);
    ui->CurrentPasswordEdit->setAttribute(Qt::WA_MacShowFocusRect, 0);
    ui->NewPasswordEdit->setAttribute(Qt::WA_MacShowFocusRect, 0);
    ui->RepeatNewPasswordEdit->setAttribute(Qt::WA_MacShowFocusRect, 0);
	
	if (!filename.isEmpty()) {
		ui->BackButton->setVisible(false);
	}
}

void SettingsWindow::createConnections() {
	connect(currentPasswordButton, &QToolButton::pressed, this, [this](){ pressPasswordButton(ui->CurrentPasswordEdit, currentPasswordButton); });
	connect(currentPasswordButton, &QToolButton::released, this, [this](){ releasePasswordButton(ui->CurrentPasswordEdit, currentPasswordButton); });
	connect(newPasswordButton, &QToolButton::pressed, this, [this](){ pressPasswordButton(ui->NewPasswordEdit, newPasswordButton); });
	connect(newPasswordButton, &QToolButton::released, this, [this](){ releasePasswordButton(ui->NewPasswordEdit, newPasswordButton); });
    connect(repeatNewPasswordButton, &QToolButton::pressed, this, [this](){ pressPasswordButton(ui->RepeatNewPasswordEdit, repeatNewPasswordButton); });
    connect(repeatNewPasswordButton, &QToolButton::released, this, [this](){ releasePasswordButton(ui->RepeatNewPasswordEdit, repeatNewPasswordButton); });
	
	connect(ui->ProfilePictureButton, &QPushButton::released, this, &SettingsWindow::uploadProfilePicture);
	connect(ui->DeletePictureButton, &QPushButton::released, this, &SettingsWindow::deleteProfilePicture);
	connect(ui->UndoButton, &QPushButton::released, this, &SettingsWindow::resetProfilePicture);
	connect(ui->CurrentPasswordEdit, &QLineEdit::textChanged, this, &SettingsWindow::enableButtons);
	connect(ui->NewPasswordEdit, &QLineEdit::textChanged, this, &SettingsWindow::enableButtons);
    connect(ui->RepeatNewPasswordEdit, &QLineEdit::textChanged, this, &SettingsWindow::enableButtons);
	connect(ui->NewPasswordEdit, &QLineEdit::textChanged, this, [this](){ correctPassword(ui->NewPasswordEdit->text(), ui->CorrectNewPassword); });
    connect(ui->RepeatNewPasswordEdit, &QLineEdit::textChanged, this, [this](){ correctPassword(ui->RepeatNewPasswordEdit->text(), ui->CorrectRepeatNewPassword); });
	connect(ui->InfoPassword, &QPushButton::released, this, [this](){ createMessageBox(this, QMessageBox::Information, passwordInfo); });
	connect(ui->UpdatePictureButton, &QPushButton::released, this, &SettingsWindow::requestPictureUpdate);
	connect(ui->UpdatePasswordButton, &QPushButton::released, this, &SettingsWindow::requestPasswordUpdate);
	connect(ui->BackButton, &QPushButton::released, this, [this](){ this->reject(); });
}

// Slots
void SettingsWindow::uploadProfilePicture() {
	qDebug() << "Uploading profile picture";
	QString filename = QFileDialog::getOpenFileName(this, tr("Choose profile picture"), QStandardPaths::standardLocations(QStandardPaths::PicturesLocation).last(), tr("Images (*.jpg *.png *.jpeg *.bmp *.JPG *.PNG *.JPEG *.BMP)"));
	if (QString::compare(filename, QString()) != 0) {
		QImage image;
		bool valid = image.load(filename);
		if (valid) {
			ui->ProfilePicture->setPixmap(QPixmap::fromImage(image).scaled(96, 96, Qt::KeepAspectRatio));
			ui->DeletePictureButton->setEnabled(true);
			ui->UndoButton->setEnabled(true);
			imageUpdatable = true;
			enableButtons();
		}
	}
}

void SettingsWindow::deleteProfilePicture() {
	qDebug() << "Deleting profile picture";
	ui->ProfilePicture->setPixmap(QPixmap(defaultPicture).scaled(96, 96, Qt::KeepAspectRatio));
	ui->DeletePictureButton->setEnabled(false);
	ui->UndoButton->setEnabled(true);
	ui->DeletePictureButton->parentWidget()->setFocus();
	imageUpdatable = true;
	enableButtons();
}

void SettingsWindow::resetProfilePicture() {
	qDebug() << "Resetting profile picture";
	ui->ProfilePicture->setPixmap(client->getLoggedUser()->getPropic().scaled(96, 96, Qt::KeepAspectRatio));
	ui->DeletePictureButton->setEnabled(true);
	ui->UndoButton->setEnabled(false);
	imageUpdatable = false;
	enableButtons();
}

void SettingsWindow::enableButtons() {
	if (imageUpdatable & !ui->CurrentPasswordEdit->text().isEmpty()) {
		ui->UpdatePictureButton->setEnabled(true);
	} else {
		ui->UpdatePictureButton->setEnabled(false);
	}

    if (!ui->CurrentPasswordEdit->text().isEmpty() & (ui->CurrentPasswordEdit->text() == ui->NewPasswordEdit->text() | ui->CurrentPasswordEdit->text() == ui->RepeatNewPasswordEdit->text())) {
        if (statusBar->currentMessage() != QString(tr("Old and new passwords can not be equal."))) {
            statusBar->showMessage(tr("Old and new passwords can not be equal."));
        }
        ui->UpdatePasswordButton->setEnabled(false);
        return;
    }

    if (!ui->CurrentPasswordEdit->text().isEmpty() & !ui->NewPasswordEdit->text().isEmpty() & !ui->RepeatNewPasswordEdit->text().isEmpty()) {
        if (ui->NewPasswordEdit->text() != ui->RepeatNewPasswordEdit->text() | !checkPasswordFormat(ui->NewPasswordEdit->text()) | !checkPasswordFormat(ui->RepeatNewPasswordEdit->text())) {
            ui->UpdatePasswordButton->setEnabled(false);
        } else {
            ui->UpdatePasswordButton->setEnabled(true);
        }
    } else {
        ui->UpdatePasswordButton->setEnabled(false);
    }

    if ((!checkPasswordFormat(ui->NewPasswordEdit->text()) & !ui->NewPasswordEdit->text().isEmpty()) | (!checkPasswordFormat(ui->RepeatNewPasswordEdit->text()) & !ui->RepeatNewPasswordEdit->text().isEmpty())) {
        if (statusBar->currentMessage() != QString(tr("The password format is not valid."))) {
            statusBar->showMessage(tr("The password format is not valid."));
        }
        return;
    } else {
        statusBar->clearMessage();
    }

    if (ui->NewPasswordEdit->text() != ui->RepeatNewPasswordEdit->text()) {
        if (statusBar->currentMessage() != QString(tr("The passwords do not coincide!"))) {
            statusBar->showMessage(tr("The passwords do not coincide!"));
        }
    } else {
        statusBar->clearMessage();
    }
}

void SettingsWindow::requestPictureUpdate() {
	deactivateWindow(this);
	
	if (!client->checkSocket()) {
		createMessageBox(this, QMessageBox::Warning, "Connection error.");
		statusBar->showMessage(tr("Connection error."), MSGTIME);
		reactivateWindow(this);
		return;
	}
	
	QString header;
	if (!filename.isEmpty()) {
		header = "updatepropiceditor";
	} else {
		header = "updatepropic";
	}
	
	if (!sendJSonMessage(client, header, ui->UsernameEdit->text(), ui->CurrentPasswordEdit->text(), "", "", jsonValFromPixmap(ui->ProfilePicture->pixmap(Qt::ReturnByValue)), "", -1, "", filename)) {
		createMessageBox(this, QMessageBox::Warning, "Could not send message.\nTry again later.");
		statusBar->showMessage(tr("Could not send message."), MSGTIME);
		reactivateWindow(this);
		return;
	}
	
	statusBar->showMessage(tr("Checking the database..."), MSGTIME);
	qDebug() << "Checking the database...";
}

void SettingsWindow::requestPasswordUpdate() {
	deactivateWindow(this);
	
	if (!client->checkSocket()) {
		statusBar->showMessage(tr("Connection error."), MSGTIME);
		reactivateWindow(this);
		return;
	}
	
	QString header;
	if (!filename.isEmpty()) {
		header = "updatepasswordeditor";
	} else {
		header = "updatepassword";
	}
	
	if (!sendJSonMessage(client, header, ui->UsernameEdit->text(), ui->CurrentPasswordEdit->text(), "", "", QJsonValue::Null, ui->NewPasswordEdit->text(), -1, "", filename)) {
        createMessageBox(this, QMessageBox::Warning, "Could not send message.\nTry again later.");
		statusBar->showMessage(tr("Could not send message."), MSGTIME);
		reactivateWindow(this);
		return;
	}
	
	statusBar->showMessage(tr("Checking the database..."), MSGTIME);
	qDebug() << "Checking the database...";
}
