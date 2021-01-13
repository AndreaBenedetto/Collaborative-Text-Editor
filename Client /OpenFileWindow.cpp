
#include "OpenFileWindow.h"
#include "ui_openfilewindow.h"
#include "OtherFunctions.h"

// Metodi pubblici
OpenFileWindow::OpenFileWindow(QWidget *parent, Client *client, QString filename): QDialog(parent), client(client), filename(filename) {
	ui = QSharedPointer<Ui::OpenFileWindow>::create();
	ui->setupUi(this);
	
	adjustGraphics();
	createConnections();
	
	this->show();
}

void OpenFileWindow::readResponse(QJsonObject jSobject) {
    auto header = jSobject["header"].toString();
    auto body = jSobject["body"].toString();
	if (header == "refreshfileseditor") {
		if (body == "ok") {
			client->setFileList(jSobject);
			QStringList fileList;
			for (auto &s: client->getAvailFile()){
				fileList += s;
			}
			fileList.sort(Qt::CaseInsensitive);
			ui->OpenMenu->clear();
			for (auto &file: fileList) {
				ui->OpenMenu->addItem(file);
			}
			ui->OpenMenu->setCurrentText("");
			reactivateWindow(this);
		}
	} else if (header == "openfileeditor") {
		if (body == "ok") {
			client->isCloseEvent = false;
			this->close();
			reactivateWindow(this);
			client->pushNewEditor(QSharedPointer<Editor>::create(nullptr, client, ui->OpenMenu->currentText(), jSobject));
			client->pushNewFile(ui->OpenMenu->currentText());
		} else if (body == "filenotfound") {
			reactivateWindow(this);
			createMessageBox(this, QMessageBox::Information, "The file does not exist on the server.\nCheck again the file name or try to refresh the list.");
		} else if (body == "alreadyopen") {
			reactivateWindow(this);
			createMessageBox(this, QMessageBox::Information, "This file is already open.");
		} else if (body == "unauthorized") {
            reactivateWindow(this);
            createMessageBox(this, QMessageBox::Information, "You are not authorized to open this file.");
        } else if (body == "error") {
            createMessageBox(this, QMessageBox::Critical, "Generic server error.\nTry again later.");
            QApplication::quit();
        }
	} else if (header == "openfileurieditor") {
        if (body == "ok") {
            client->isCloseEvent = false;
            this->close();
            reactivateWindow(this);
            client->pushNewEditor(QSharedPointer<Editor>::create(nullptr, client, jSobject["filename"].toString(), jSobject));
            client->pushNewFile(ui->OpenMenu->currentText());
        } else if (body == "filenotfound") {
            reactivateWindow(this);
            createMessageBox(this, QMessageBox::Information, "The file does not exist on the server.\nCheck again the file name or try to refresh the list.");
        } else if (body == "alreadyopen") {
            reactivateWindow(this);
            createMessageBox(this, QMessageBox::Information, "This file is already open.");
        } else if (body == "invalid") {
            reactivateWindow(this);
            createMessageBox(this, QMessageBox::Information, "The URI you used is either invalid or expired.");
        } else if (body == "error") {
            createMessageBox(this, QMessageBox::Critical, "Generic server error.\nTry again later.");
            QApplication::quit();
        }
    }
}

// Metodi privati
void OpenFileWindow::adjustGraphics() {
	ui->OpenMenu->completer()->setCompletionMode(QCompleter::PopupCompletion);
	ui->OpenMenu->completer()->setFilterMode(Qt::MatchContains);
	ui->OpenMenu->installEventFilter(this);
	auto cbModel = new QStringListModel;
	ui->OpenMenu->setModel(cbModel);
	ui->OpenMenu->lineEdit()->setPlaceholderText(tr("Select file..."));
	
	QStringList fileList;
	for(auto &s: client->getAvailFile()){
		fileList += s;
	}
    fileList.sort(Qt::CaseInsensitive);
	
	for (auto &file: fileList) {
		ui->OpenMenu->addItem(file);
	}
	ui->OpenMenu->setCurrentText("");

    ui->OpenMenu->setAttribute(Qt::WA_MacShowFocusRect, 0);
    ui->OpenMenu->setPalette(QColor(255,255,255,0));
}

void OpenFileWindow::createConnections() {
	connect(ui->OpenButton, &QPushButton::released, this, &OpenFileWindow::openExistingFile);
	connect(ui->OpenMenu->lineEdit(), &QLineEdit::returnPressed, this, &OpenFileWindow::openExistingFile);
	connect(ui->RefreshButton, &QPushButton::released, this, &OpenFileWindow::refreshFileList);
    connect(ui->URIButton, &QPushButton::released, this, &OpenFileWindow::insertURI);
}

// Slot privati
void OpenFileWindow::openExistingFile() {
	deactivateWindow(this);
	
	if (!client->checkSocket()) {
        createMessageBox(this, QMessageBox::Warning, "Connection error.");
		reactivateWindow(this);
		return;
	}
	
	if (!sendJSonMessage(client, "openfileeditor", client->getLoggedUser()->getUsername(), "", "", "", QJsonValue::Null, "", -1, "", filename, "", ui->OpenMenu->currentText())) {
        createMessageBox(this, QMessageBox::Warning, "Could not send message.\nTry again later.");
		reactivateWindow(this);
		return;
	}
}

void OpenFileWindow::refreshFileList() {
	deactivateWindow(this);
	
	if (!client->checkSocket()) {
        createMessageBox(this, QMessageBox::Warning, "Connection error.");
		reactivateWindow(this);
		return;
	}
	
	if (!sendJSonMessage(client, "refreshfileseditor", client->getLoggedUser()->getUsername(), "", "", "", QJsonValue::Null, "", -1, "", filename)) {
        createMessageBox(this, QMessageBox::Warning, "Could not send message.\nTry again later.");
		reactivateWindow(this);
		return;
	}
	
	qDebug() << "Refreshing file list...";
}

void OpenFileWindow::insertURI() {
    bool ok;
    QInputDialog inputDialog(nullptr);
    inputDialog.setLabelText("Insert the URI:");
    inputDialog.setTextEchoMode(QLineEdit::Normal);
    QLinearGradient linearGrad(QPointF(inputDialog.geometry().x() + inputDialog.geometry().width(), inputDialog.geometry().y() + inputDialog.geometry().height()), QPointF(inputDialog.geometry().x(), inputDialog.geometry().y()));
    linearGrad.setColorAt(0, QColor(0, 133, 255, 255));
    linearGrad.setColorAt(1, QColor(241, 255, 253, 255));
    linearGrad.setSpread(QGradient::ReflectSpread);
    QBrush brush(linearGrad);
    QPalette palette;
    palette.setBrush(QPalette::Window, brush);
    inputDialog.setPalette(palette);
    inputDialog.exec();
    auto uri = inputDialog.textValue();

    if (!ok) {
        return;
    }

    if (uri.isEmpty()) {
        createMessageBox(this, QMessageBox::Information, "You did not insert a valid URI.");
        return;
    }

    deactivateWindow(this);
    if (!client->checkSocket()) {
        createMessageBox(this, QMessageBox::Warning, "Connection error.");

        reactivateWindow(this);
        return;
    }

    if (!sendJSonMessage(client, "openfileurieditor", client->getLoggedUser()->getUsername(), "", "", "", QJsonValue::Null, "", -1, "", filename, uri)) {
        createMessageBox(this, QMessageBox::Warning, "Could not send message.\nTry again later.");
        reactivateWindow(this);
        return;
    }
}