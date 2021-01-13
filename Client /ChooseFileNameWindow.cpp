
#include "ChooseFileNameWindow.h"
#include "ui_choosefilenamewindow.h"
#include "OtherFunctions.h"

// Metodi pubblici
ChooseFileNameWindow::ChooseFileNameWindow(QWidget *parent, Client *client, QString filename): QDialog(parent), client(client), filename(filename) {
	ui = QSharedPointer<Ui::ChooseFileNameWindow>::create();
	ui->setupUi(this);
	
	adjustGraphics();
	createConnections();
	
	this->show();
}

void ChooseFileNameWindow::readResponse(QJsonObject jSobject) {
    auto body = jSobject["body"].toString();
	if (body == "ok") {
		this->close();
		if (filename.isEmpty()) {
			client->isCloseEvent = false;
			this->parentWidget()->close();
		}
		QApplication::restoreOverrideCursor();
		client->pushNewEditor(QSharedPointer<Editor>::create(nullptr, client, ui->FileNameEdit->text()));
		client->pushNewFile(ui->FileNameEdit->text());
	} else if (body == "alreadyexisting") {
		reactivateWindow(this);
        createMessageBox(this, QMessageBox::Information, "It already exists a file with this name.\nTry another one");
		ui->FileNameEdit->clear();
		statusBar->showMessage("File already present in the server.", MSGTIME);
	} else if (body == "error") {
        createMessageBox(this, QMessageBox::Critical, "Generic server error.\nTry again later.");
        QApplication::quit();
	}
}

// Metodi privati
void ChooseFileNameWindow::adjustGraphics() {
	statusBar = QSharedPointer<QStatusBar>::create(this);
	statusBar->setFixedSize(this->width(), 15);
    statusBar->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    statusBar->setSizeGripEnabled(false);
	ui->verticalLayout->addWidget(statusBar.get());
}

void ChooseFileNameWindow::createConnections() {
	connect(ui->FileNameEdit, &QLineEdit::textChanged, this, &ChooseFileNameWindow::enableButton);
    connect(ui->FileNameEdit, &QLineEdit::returnPressed, ui->OkButton, &QPushButton::released);
	connect(ui->OkButton, &QPushButton::released, this, &ChooseFileNameWindow::checkFileName);
}

// Slots
void ChooseFileNameWindow::enableButton() {
	if (!ui->FileNameEdit->text().isEmpty()) {
		ui->OkButton->setEnabled(true);
	} else {
		ui->OkButton->setEnabled(false);
	}
}

void ChooseFileNameWindow::checkFileName() {
	deactivateWindow(this);
	
	QString header;
	if (filename.isEmpty()) {
		header = "checkfilename";
	} else {
		header = "checkfilenameeditor";
	}
	
	if (!client->checkSocket()) {
        createMessageBox(this, QMessageBox::Warning, "Connection error.");
		reactivateWindow(this);
		return;
	}
	
	if (!sendJSonMessage(client, header, client->getLoggedUser()->getUsername(), "", "", "", QJsonValue::Null, "", -1, "", filename, "", ui->FileNameEdit->text())) {
        createMessageBox(this, QMessageBox::Warning, "Could not send message.\nTry again later.");
		reactivateWindow(this);
		return;
	}
	
	qDebug() << "Refreshing file list...";
}