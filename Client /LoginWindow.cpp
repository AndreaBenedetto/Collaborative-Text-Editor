
#include "LoginWindow.h"
#include "Client.h"
#include "OtherFunctions.h"
#include "ui_loginwindow.h"

// Metodi pubblici
LoginWindow::LoginWindow(QWidget *parent, Client *client): QDialog(parent), client(client) {
	ui = QSharedPointer<Ui::LoginWindow>::create();
	ui->setupUi(this);
	
	adjustGraphics();
	createConnections();
	
	this->show();
}

void LoginWindow::readResponse(QJsonObject jSobject) {
    auto body = jSobject["body"].toString();
	if (body == "ok") {
		client->setFileList(jSobject);
		User u(ui->UsernameEdit->text(), pixmapFrom(jSobject["propic"]), jSobject["name"].toString(), jSobject["surname"].toString());
		qDebug() << u.getName() << " " << u.getSurname();
		client->setLoggedUser(u);
		QApplication::restoreOverrideCursor();
		client->openFileChoiceWindow(false);
		client->isCloseEvent = false;
		this->close();
	} else if (body == "notregistered") {
		reactivateWindow(this);
        createMessageBox(this, QMessageBox::Information, "User not found.\nCheck again username and password.");
		statusBar->showMessage(tr("User not found."), MSGTIME);
	} else if (body == "fail") {
		reactivateWindow(this);
        createMessageBox(this, QMessageBox::Warning, "Server error.\nTry again later.");
		statusBar->showMessage(tr("Server error."), MSGTIME);
	} else if (body == "alreadyloggedin") {
		reactivateWindow(this);
		ui->UsernameEdit->clear();
		ui->PasswordEdit->clear();
		ui->UsernameEdit->setFocus();
		statusBar->clearMessage();
        createMessageBox(this, QMessageBox::Information, "User already logged in on another device.");
	}
}

// Metodi privati
void LoginWindow::adjustGraphics() {
	statusBar = QSharedPointer<QStatusBar>::create(this);
    statusBar->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    statusBar->setSizeGripEnabled(false);
	ui->verticalLayout->addWidget(statusBar.get());
	ui->RegistrationLink->setText("<a href=\"whatever\">Register</a>");
	ui->CancellationLink->setText("<a href=\"whatever\">Cancel your account</a>");
	
	hidePassword = ui->PasswordEdit->addAction(QIcon(iconsPath + "myicons-eye-on.png"), QLineEdit::TrailingPosition);
	passwordButton =qobject_cast<QToolButton *>(hidePassword->associatedWidgets().last());
	passwordButton->setCursor(QCursor(Qt::PointingHandCursor));

	ui->UsernameEdit->setAttribute(Qt::WA_MacShowFocusRect, 0);
	ui->PasswordEdit->setAttribute(Qt::WA_MacShowFocusRect, 0);
	
	ui->UsernameEdit->setFocus();
}

void LoginWindow::createConnections() {
	connect(passwordButton, &QToolButton::pressed, this, [this](){ pressPasswordButton(ui->PasswordEdit, passwordButton); });
	connect(passwordButton, &QToolButton::released, this, [this](){ releasePasswordButton(ui->PasswordEdit, passwordButton); });

	connect(ui->UsernameEdit, &QLineEdit::textChanged, this, &LoginWindow::enableLoginButton);
	connect(ui->PasswordEdit, &QLineEdit::textChanged, this, &LoginWindow::enableLoginButton);
	connect(ui->LoginButton, &QPushButton::released, this, &LoginWindow::requestLogin);
	connect(ui->RegistrationLink, &QLabel::linkActivated, this, &LoginWindow::openRegistrationWindow);
	connect(ui->CancellationLink, &QLabel::linkActivated, this, &LoginWindow::openCancellationWindow);
}

// Slots
void LoginWindow::enableLoginButton() {
	if (!ui->UsernameEdit->text().isEmpty() & !ui->PasswordEdit->text().isEmpty()) {
		ui->LoginButton->setEnabled(true);
	} else {
		ui->LoginButton->setEnabled(false);
	}
}

void LoginWindow::requestLogin() {
	deactivateWindow(this);
	if (!client->checkSocket()) {
        createMessageBox(this, QMessageBox::Warning, "Connection error.");
		statusBar->showMessage(tr("Connection error."), MSGTIME);
		reactivateWindow(this);
		return;
	}
	
	if (!sendJSonMessage(client, "login", ui->UsernameEdit->text(), ui->PasswordEdit->text(), "", "", QJsonValue::Null)) {
        createMessageBox(this, QMessageBox::Warning, "Could not send message.\nTry again later.");
		statusBar->showMessage(tr("Could not send message."), MSGTIME);
		reactivateWindow(this);
		return;
	}
	
	statusBar->showMessage(tr("Checking the database..."), MSGTIME);
	qDebug() << "Checking the database...";
}

void LoginWindow::openRegistrationWindow() {
	this->setVisible(false);
	regWin = QSharedPointer<RegistrationWindow>::create(nullptr, client, ui->UsernameEdit->text());
	connect(regWin.get(), &QDialog::rejected, this, [this](){
		QApplication::restoreOverrideCursor();
		this->setVisible(true);
		regWin.reset();
	});
}

void LoginWindow::openCancellationWindow() {
	this->setVisible(false);
	cancWin = QSharedPointer<CancellationWindow>::create(nullptr, client, ui->UsernameEdit->text());
	connect(cancWin.get(), &QDialog::rejected, this, [this](){
		QApplication::restoreOverrideCursor();
		this->setVisible(true);
		cancWin.reset();
	});
}

void LoginWindow::closeEvent(QCloseEvent *event) {
	if (client->isCloseEvent) {
		event->ignore();
        auto res = createMessageBox(this, QMessageBox::Question, "Do you really want to exit the application?", QMessageBox::Yes | QMessageBox::No);

		if (res == QMessageBox::Yes) {
			event->accept();
		}
	}
	client->isCloseEvent = true;
}

void LoginWindow::reject() {
	this->close();
}

// Getters e setters
QSharedPointer<RegistrationWindow> LoginWindow::getRegWin() {
	return regWin;
}

QSharedPointer<CancellationWindow> LoginWindow::getCancWin() {
	return cancWin;
}

QSharedPointer<QStatusBar> LoginWindow::getStatusBar() {
	return statusBar;
}