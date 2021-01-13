
#include "CancellationWindow.h"
#include "Client.h"
#include "ui_cancellationwindow.h"
#include "OtherFunctions.h"

// Metodi pubblici
CancellationWindow::CancellationWindow(QWidget *parent, Client *client, QString username): QDialog(parent), client(client) {
	ui = QSharedPointer<Ui::CancellationWindow>::create();
	ui->setupUi(this);
	
	adjustGraphics(username);
	createConnections();
	
	if (ui->UsernameEdit->text().isEmpty()) {
		ui->UsernameEdit->setFocus();
	} else {
		ui->PasswordEdit->setFocus();
	}
	this->show();
}

void CancellationWindow::readResponse(QJsonObject jSobject) {
    auto body = jSobject["body"].toString();
	if (body == "ok") {
		client->getLogWin()->getStatusBar()->showMessage(tr("Successful cancellation."), MSGTIME);
		this->accept();
		QApplication::restoreOverrideCursor();
		client->getLogWin()->setVisible(true);
	} else if (body == "notexistent") {
		reactivateWindow(this);
        createMessageBox(this, QMessageBox::Information, "User not found.\nCheck again the username and the password.");
		statusBar->showMessage(tr("User not found or wrong password."), MSGTIME);
	} else if (body == "fail") {
		reactivateWindow(this);
        createMessageBox(this, QMessageBox::Warning, "Server error.\nTry again later.");
		statusBar->showMessage(tr("Server error."), MSGTIME);
	}
}

// Metodi privati
void CancellationWindow::adjustGraphics(QString &username) {
	statusBar = QSharedPointer<QStatusBar>::create(this);
    statusBar->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    statusBar->setSizeGripEnabled(false);
	ui->verticalLayout->addWidget(statusBar.get());
	ui->UsernameEdit->setText(username);
	
	hidePassword = ui->PasswordEdit->addAction(QIcon(iconsPath + "myicons-eye-on.png"), QLineEdit::TrailingPosition);
	passwordButton = qobject_cast<QToolButton *>(hidePassword->associatedWidgets().last());
	passwordButton->setCursor(QCursor(Qt::PointingHandCursor));

    ui->UsernameEdit->setAttribute(Qt::WA_MacShowFocusRect, 0);
    ui->PasswordEdit->setAttribute(Qt::WA_MacShowFocusRect, 0);
}

void CancellationWindow::createConnections() {
	connect(passwordButton, &QToolButton::pressed, this, [this](){ pressPasswordButton(ui->PasswordEdit, passwordButton); });
	connect(passwordButton, &QToolButton::released, this, [this](){ releasePasswordButton(ui->PasswordEdit, passwordButton); });
	
	connect(ui->UsernameEdit, &QLineEdit::textChanged, this, &CancellationWindow::enableCancelButton);
	connect(ui->PasswordEdit, &QLineEdit::textChanged, this, &CancellationWindow::enableCancelButton);
	connect(ui->CancelButton, &QPushButton::released, this, &CancellationWindow::requestCancellation);
	connect(ui->BackButton, &QPushButton::released, this, [this](){ this->reject(); });
}

// Slots
void CancellationWindow::enableCancelButton() {
	if (!ui->UsernameEdit->text().isEmpty() & !ui->PasswordEdit->text().isEmpty()) {
		ui->CancelButton->setEnabled(true);
	} else {
		ui->CancelButton->setEnabled(false);
	}
}

void CancellationWindow::requestCancellation() {
	deactivateWindow(this);
	if (!client->checkSocket()) {
        createMessageBox(this, QMessageBox::Warning, "Connection error.");
		statusBar->showMessage(tr("Connection error."), MSGTIME);
		reactivateWindow(this);
		return;
	}
	
	if (!sendJSonMessage(client, "cancellation", ui->UsernameEdit->text(), ui->PasswordEdit->text())) {
        createMessageBox(this, QMessageBox::Warning, "Could not send message.\nTry again later.");
		statusBar->showMessage(tr("Could not send message."), MSGTIME);
		reactivateWindow(this);
		return;
	}
	
	statusBar->showMessage(tr("Checking the database..."), MSGTIME);
	qDebug() << "Checking the database...";
}
