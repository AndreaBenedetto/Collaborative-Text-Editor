
#include <QtWidgets>
#include "Client.h"
#include "FileChoiceWindow.h"
#include "ui_filechoicewindow.h"
#include "OtherFunctions.h"
#include "ChooseFileNameWindow.h"

// Metodi pubblici
FileChoiceWindow::FileChoiceWindow(QWidget *parent, Client *client, bool fromRegistration): QDialog(parent), client(client) {
	ui = QSharedPointer<Ui::FileChoiceWindow>::create();
	ui->setupUi(this);
	
	adjustGraphics(fromRegistration);
	createConnections();
	
	this->show();
}

void FileChoiceWindow::readResponse(QJsonObject jSobject) {
    auto header = jSobject["header"].toString();
    auto body = jSobject["body"].toString();
	if (header == "refreshfiles") {
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
	} else if (header == "logout") {
		if (body == "ok") {
			client->getLoggedUser().reset();
			client->getAvailFile().clear();
			client->isCloseEvent = false;
			this->close();
			client->setLogWin();
			QApplication::restoreOverrideCursor();
		}
	} else if (header == "openfile") {
		if (body == "ok") {
			client->pushNewEditor(QSharedPointer<Editor>::create(nullptr, client, ui->OpenMenu->currentText(), jSobject));
			client->pushNewFile(ui->OpenMenu->currentText());
            reactivateWindow(this);
            client->isCloseEvent = false;
            this->close();
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
	} else if (header == "deletefile") {
	    if (body == "ok") {
	        reactivateWindow(this);
            createMessageBox(this, QMessageBox::Information, "File deleted correctly");
	        refreshFileList();
	    } else if (body == "fileopen") {
            reactivateWindow(this);
            createMessageBox(this, QMessageBox::Information, "Somebody is working on the file.\nImpossible to delete it now.");
	    } else if (body == "notexisting") {
            reactivateWindow(this);
            createMessageBox(this, QMessageBox::Information, "The file does not exist on the server.\nCheck again the file name or try to refresh the list.");
	    } else if (body == "notowner") {
            reactivateWindow(this);
            createMessageBox(this, QMessageBox::Information, "You are not the owner of this file.\nOnly the owner can delete a file.");
	    } else if (body == "error") {
            createMessageBox(this, QMessageBox::Critical, "Generic server error.\nTry again later.");
            QApplication::quit();
        }
	} else if (header == "requesturi") {
        if (body == "ok") {
            reactivateWindow(this);
            uriWindow = QSharedPointer<URIWindow>::create(this, client, jSobject["uri"].toString());
        } else if (body == "filenotfound") {
            reactivateWindow(this);
            createMessageBox(this, QMessageBox::Information, "The file does not exist on the server.\nCheck again the file name or try to refresh the list.");
        } else if (body == "unauthorized") {
            reactivateWindow(this);
            createMessageBox(this, QMessageBox::Information, "You are not authorized to share this file.");
        }
	} else if (header == "openfileuri") {
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
void FileChoiceWindow::adjustGraphics(bool fromRegistration) {
	ui->OpenMenu->completer()->setCompletionMode(QCompleter::PopupCompletion);
	ui->OpenMenu->completer()->setFilterMode(Qt::MatchContains);
	ui->OpenMenu->installEventFilter(this);
	auto cbModel = new QStringListModel;
	ui->OpenMenu->setModel(cbModel);
	ui->OpenMenu->lineEdit()->setPlaceholderText(tr("Select file..."));
	
	ui->ProfilePicture->setPixmap(client->getLoggedUser()->getPropic().scaled(96, 96, Qt::KeepAspectRatio));
	
	if (fromRegistration) {
		ui->WelcomeLabel->setText(tr("Welcome,\n%1!").arg(client->getLoggedUser()->getName()));
	} else {
		ui->WelcomeLabel->setText(tr("Welcome back,\n%1!").arg(client->getLoggedUser()->getName()));
	}
	
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

void FileChoiceWindow::createConnections() {
	connect(ui->NewButton, &QPushButton::released, this, &FileChoiceWindow::openNewFile);
	connect(ui->OpenButton, &QPushButton::released, this, &FileChoiceWindow::openExistingFile);
	connect(ui->DeleteButton, &QPushButton::released, this, &FileChoiceWindow::deleteExistingFile);
	connect(ui->OpenMenu->lineEdit(), &QLineEdit::returnPressed, this, &FileChoiceWindow::openExistingFile);
	connect(ui->OpenMenu, &QComboBox::textActivated, this, [this](){ ui->OpenButton->setDefault(true); });
	connect(ui->RefreshButton, &QPushButton::released, this, &FileChoiceWindow::refreshFileList);
	connect(ui->ShareButton, &QPushButton::released, this, &FileChoiceWindow::requestURI);
	connect(ui->URIButton, &QPushButton::released, this, &FileChoiceWindow::insertURI);
	connect(ui->SettingsButton, &QPushButton::released, this, &FileChoiceWindow::openSettingsWindow);
	connect(ui->LogoutButton, &QPushButton::released, this, &FileChoiceWindow::requestLogout);
}

// Slots
void FileChoiceWindow::openNewFile() {
	nameChoiceWin = QSharedPointer<ChooseFileNameWindow>::create(this, client);
}

void FileChoiceWindow::openExistingFile() {
	deactivateWindow(this);
	
	if (!client->checkSocket()) {
        createMessageBox(this, QMessageBox::Warning, "Connection error.");
		reactivateWindow(this);
		return;
	}
	
	if (!sendJSonMessage(client, "openfile", client->getLoggedUser()->getUsername(), "", "", "", QJsonValue::Null, "", -1, "", "", "", ui->OpenMenu->currentText())) {
        createMessageBox(this, QMessageBox::Warning, "Could not send message.\nTry again later.");
		reactivateWindow(this);
		return;
	}
}

void FileChoiceWindow::deleteExistingFile() {
    auto res = createMessageBox(this, QMessageBox::Question, "Do you really want to delete the file?", QMessageBox::Yes | QMessageBox::No);
    if (res == QMessageBox::Yes) {
        deactivateWindow(this);

        if (!client->checkSocket()) {
            createMessageBox(this, QMessageBox::Warning, "Connection error.");
            reactivateWindow(this);
            return;
        }

        if (!sendJSonMessage(client, "deletefile", client->getLoggedUser()->getUsername(), "", "", "", QJsonValue::Null, "", -1, "", ui->OpenMenu->currentText())) {
            createMessageBox(this, QMessageBox::Warning, "Could not send message.\nTry again later.");
            reactivateWindow(this);
            return;
        }
    }
}

void FileChoiceWindow::refreshFileList() {
	deactivateWindow(this);
	
	if (!client->checkSocket()) {
        createMessageBox(this, QMessageBox::Warning, "Connection error.");
		reactivateWindow(this);
		return;
	}
	
	if (!sendJSonMessage(client, "refreshfiles", client->getLoggedUser()->getUsername(), "", "", "", QJsonValue::Null, "")) {
        createMessageBox(this, QMessageBox::Warning, "Could not send message.\nTry again later.");
		reactivateWindow(this);
		return;
	}
	
	qDebug() << "Refreshing file list...";
}

void FileChoiceWindow::requestURI() {
    deactivateWindow(this);

    if (!client->checkSocket()) {
        createMessageBox(this, QMessageBox::Warning, "Connection error.");
        reactivateWindow(this);
        return;
    }

    if (!sendJSonMessage(client, "requesturi", client->getLoggedUser()->getUsername(), "", "", "", QJsonValue::Null, "", -1, "", ui->OpenMenu->currentText())) {
        createMessageBox(this, QMessageBox::Warning, "Could not send message.\nTry again later.");
        reactivateWindow(this);
        return;
    }
}

void FileChoiceWindow::insertURI() {
    QInputDialog inputDialog;
    inputDialog.setInputMode(QInputDialog::TextInput);
    inputDialog.setLabelText("Insert the URI:");
    inputDialog.setTextEchoMode(QLineEdit::Normal);
    QLinearGradient linearGrad(QPointF(inputDialog.geometry().x() + inputDialog.geometry().width(), inputDialog.geometry().y() + inputDialog.geometry().height()), QPointF(inputDialog.geometry().x(), inputDialog.geometry().y()));
    linearGrad.setColorAt(0, QColor(0, 133, 255, 255));
    linearGrad.setColorAt(1, QColor(241, 255, 253, 255));
    QBrush brush(linearGrad);
    QPalette palette;
    palette.setBrush(QPalette::Window, brush);
    inputDialog.setPalette(palette);
    inputDialog.exec();
    auto uri = inputDialog.textValue();
    auto ok = inputDialog.result();

    if (ok != QDialog::Accepted) {
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

    if (!sendJSonMessage(client, "openfileuri", client->getLoggedUser()->getUsername(), "", "", "", QJsonValue::Null, "", -1, "", "", uri)) {
        createMessageBox(this, QMessageBox::Warning, "Could not send message.\nTry again later.");
        reactivateWindow(this);
        return;
    }
}

void FileChoiceWindow::openSettingsWindow() {
	this->setVisible(false);
	settWin = QSharedPointer<SettingsWindow>::create(nullptr, client);
	connect(settWin.get(), &QDialog::rejected, this, [this](){
		QApplication::restoreOverrideCursor();
		ui->ProfilePicture->setPixmap(client->getLoggedUser()->getPropic());
		this->setVisible(true);
		settWin.reset();
	});
}

void FileChoiceWindow::requestLogout() {
	deactivateWindow(this);
	if (!client->checkSocket()) {
        createMessageBox(this, QMessageBox::Warning, "Connection error.");
		reactivateWindow(this);
		return;
	}
	
	if (!sendJSonMessage(client, "logout", client->getLoggedUser()->getUsername(), "", "", "", QJsonValue::Null, "")) {
        createMessageBox(this, QMessageBox::Warning, "Could not send message.\nTry again later.");
		reactivateWindow(this);
		return;
	}
	
	qDebug() << "Logging out...";
}

void FileChoiceWindow::closeEvent(QCloseEvent *event) {
	if (client->isCloseEvent) {
		event->ignore();
        auto res = createMessageBox(this, QMessageBox::Question, "Do you really want to exit the application?", QMessageBox::Yes | QMessageBox::No);
		if (res == QMessageBox::Yes) {
			event->accept();
		}
	}
	client->isCloseEvent = true;
}

void FileChoiceWindow::reject() {
	this->close();
}

// Getters e setters
QSharedPointer<SettingsWindow> FileChoiceWindow::getSettWin() {
	return settWin;
}

QSharedPointer<ChooseFileNameWindow> FileChoiceWindow::getNameChoiceWin() {
	return nameChoiceWin;
}