
#include "Client.h"
#include "OtherFunctions.h"
#include <QMessageBox>

// Metodi pubblici
Client::Client(QWidget *parent): QObject(parent) {
	// Setting del socket TCP e dello stream dei dati
	tcpSocket = QSharedPointer<QTcpSocket>::create(this);
	in.setDevice(tcpSocket.get());

	in.setVersion(QDataStream::Qt_4_0);

	connectSocket();
	requestConnection();
	setConfigurationManager();
	
	// Apre la finestra di login
	logWin = QSharedPointer<LoginWindow>::create(nullptr, this);

}

bool Client::checkSocket() {
	if (tcpSocket == nullptr) {
		qDebug() << "Socket TCP nullo.";
		return false;
	}
	if (!tcpSocket->isValid()) {
		qDebug() << "Socket TCP non valido.";
		return false;
	}
	if (!tcpSocket->isOpen()) {
		qDebug() << "Socket TCP non aperto.";
		return false;
	}
	return true;
}

void Client::pushNewEditor(QSharedPointer<Editor> newEditor) {
	openedEditors.push_back(newEditor);
}

void Client::pushNewFile(QString filename) {
	openedFiles.push_back(filename);
	printOpenFiles();
}

void Client::removeClosedEditor(Editor *closedEditor) {
	for (auto it = openedEditors.begin(); it != openedEditors.end(); it++) {
		if (it->get() == closedEditor) {
            (static_cast<QMainWindow> (closedEditor)).QMainWindow::close();
			openedEditors.erase(it);
			return;
		}
	}
}

void Client::removeClosedFile(QString filename) {
	for (auto it = openedFiles.begin(); it != openedFiles.end(); it++) {
		if (*it == filename) {
			openedFiles.erase(it);
			return;
		}
	}
	printOpenFiles();
}

void Client::openFileChoiceWindow(bool fromRegistration) {
	choiceWin = QSharedPointer<FileChoiceWindow>::create(nullptr, this, fromRegistration);
}

// Metodi privati
void Client::connectSocket() {
	connect(tcpSocket.get(), &QIODevice::readyRead, this, &Client::readResponse);
	connect(tcpSocket.get(), &QAbstractSocket::errorOccurred, this, &Client::connectionError);
}

void Client::requestConnection() {
	qDebug()<< "Requesting connection...";
	
#ifndef LOCALHOST
//	auto host = "127.0.0.1";
    auto host = "192.168.2.17";
#else
	auto host = QHostAddress(QHostAddress::LocalHost).toString();
#endif
	
	int port = 4848;
	tcpSocket->abort();
	tcpSocket->connectToHost(host, port);
}

void Client::setConfigurationManager() {
    /*
	QNetworkConfigurationManager manager;
	if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired) {
		// Ottenere la configurazione del network salvata
		QSettings settings(QSettings::UserScope, QLatin1String("PdsProject"));
		settings.beginGroup(QLatin1String("QtNetwork"));
		const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
		settings.endGroup();
		
		// Se la configurazione salvata non è scoperta usare il default di sistema
		QNetworkConfiguration config = manager.configurationFromIdentifier(id);
		if ((config.state() & QNetworkConfiguration::Discovered) != QNetworkConfiguration::Discovered) {
			config = manager.defaultConfiguration();
		}
		
		networkSession = QSharedPointer<QNetworkSession>::create(config, this);
		connect(networkSession.get(), &QNetworkSession::opened, this, &Client::sessionOpened);
		
		networkSession->open();
	}
     */
}

void Client::sessionOpened() {
    /*
	QNetworkConfiguration config = networkSession->configuration();
	QString id;
	if (config.type() == QNetworkConfiguration::UserChoice)
		id = networkSession->sessionProperty(QLatin1String("UserChoiceConfiguration")).toString();
	else
		id = config.identifier();
	
	QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
	settings.beginGroup(QLatin1String("QtNetwork"));
	settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
	settings.endGroup();
	qDebug() << "Connession established.";
     */
}

// Slots
void Client::connectionError(QAbstractSocket::SocketError socketError) {
	QApplication::restoreOverrideCursor();
	switch (socketError) {
		case QAbstractSocket::RemoteHostClosedError:
		    createMessageBox(logWin.get(), QMessageBox::Critical, "Server closed connection.\nRelaunch the program in a few minutes.");
			qDebug() << "The server has disconnected. Client will close, try to launch again in few seconds.";
			break;
		case QAbstractSocket::HostNotFoundError:
			createMessageBox(logWin.get(), QMessageBox::Critical, "The host was not found.\nPlease check the host name and port settings.");
			qDebug() << "The host was not found. Please check the host name and port settings.";
			break;
		case QAbstractSocket::ConnectionRefusedError:
            createMessageBox(logWin.get(), QMessageBox::Critical, "The connection was refused by the server.\nMake sure the PDS server is running and check that the host name and port settings are correct.");
			qDebug() << "The connection was refused by the server. Make sure the PDS server is running and check that the host name and port settings are correct.";
			break;
		default:
			createMessageBox(logWin.get(), QMessageBox::Critical, QString("The following error occurred:\n%1.").arg(tcpSocket->errorString()));
			qDebug() << QString("The following error occurred: %1.").arg(tcpSocket->errorString());
	}
	QApplication::quit();
}

void Client::readResponse() {
	QByteArray jSmessage;
	QString header;
	QString result;
	QJsonObject jSobject;
	QPixmap propic;

    in.startTransaction();
    in >> jSmessage;

    if (!in.commitTransaction()) {
        return;
    }

	QJsonParseError parseError;
	const QJsonDocument jsonDoc = QJsonDocument::fromJson(jSmessage, &parseError);
	if (parseError.error == QJsonParseError::NoError) {
	    // Se i dati sono JSON valido
		if (jsonDoc.isObject()) {
			jSobject = jsonDoc.object();
			header = jSobject["header"].toString();
			result = jSobject["body"].toString();
		} else {
			createMessageBox(QApplication::activeWindow(), QMessageBox::Critical, "Generic server error.\nTry again later.");
			QApplication::quit();
		}
	} else {
        createMessageBox(QApplication::activeWindow(), QMessageBox::Critical, "Generic server error.\nTry again later.");
        QApplication::quit();
	}
	
	qDebug().noquote() << header + ": " + result;
	
	if (header == "error") {
        createMessageBox(QApplication::activeWindow(), QMessageBox::Critical, "Generic server error.\nTry again later.");
        QApplication::quit();
	} else if (header == "login") {
		logWin->readResponse(jSobject);
	} else if (header == "registration") {
		logWin->getRegWin()->readResponse(jSobject);
	} else if (header == "cancellation") {
		logWin->getCancWin()->readResponse(jSobject);
	} else if (header == "refreshfiles" | header == "logout" | header == "openfile" | header == "deletefile" | header == "requesturi" | header == "openfileuri") {
		choiceWin->readResponse(jSobject);
	} else if (header == "updatepropic" | header == "updatepassword") {
		choiceWin->getSettWin()->readResponse(jSobject);
	} else if (header == "getactiveusers" | header == "getprofilepicture" | header == "closefile" | header == "closelastfile" | header == "logouteditor" | header == "requesturieditor") {
        QString fn = jSobject["filename"].toString();
        for (auto &ed: openedEditors) {
            if (ed->getFileName() == fn) {
                ed->readResponse(jSobject);
                return;
            }
        }
	} else if (header == "updatepropiceditor" | header == "updatepasswordeditor") {
        QString fn = jSobject["filename"].toString();
        for (auto &ed: openedEditors) {
            if (ed->getFileName() == fn) {
                ed->getSettWin()->readResponse(jSobject);
                return;
            }
        }
	} else if (header == "checkfilename") {
		choiceWin->getNameChoiceWin()->readResponse(jSobject);
	} else if (header == "checkfilenameeditor") {
        QString fn = jSobject["filename"].toString();
        for (auto &ed: openedEditors) {
            if (ed->getFileName() == fn) {
                ed->getNameChoiceWin()->readResponse(jSobject);
                return;
            }
        }
	} else if (header == "inserttext" | header == "deletetext" | header == "modifycharformat" | header == "modifyblockformat") {
		QString fn = jSobject["filename"].toString();
		for (auto &ed: openedEditors) {
			if (ed->getFileName() == fn) {
				ed->getTextEdit()->readResponse(jSobject);
				return;
			}
		}
	} else if (header == "refreshfileseditor" | header == "openfileeditor" | header == "openfileurieditor") {
        QString fn = jSobject["filename"].toString();
        for (auto &ed: openedEditors) {
            if (ed->getFileName() == fn) {
                ed->getOpenFileWin()->readResponse(jSobject);
                return;
            }
        }
	} else {
		qDebug() << "Message not recognized";
	}
}

// Getters e setters
QSharedPointer<QTcpSocket> Client::getTcpSocket() {
	return tcpSocket;
}

QSharedPointer<User> Client::getLoggedUser() {
	return loggedUser;
}

void Client::setLoggedUser(const User &user) {
	loggedUser = QSharedPointer<User>::create(user);
}

QList<QString> Client::getAvailFile() {
	return availFile;
}

void Client::setFileList(QJsonObject& data) {
	availFile.clear();
	for (auto s: data["filelist"].toArray()){
		availFile.push_back(s.toString());
	}
}

QSharedPointer<LoginWindow> Client::getLogWin() {
	return logWin;
}

void Client::setLogWin() {
	logWin.reset();
	logWin = QSharedPointer<LoginWindow>::create(nullptr, this);
}

void Client::setChoiceWin() {
    choiceWin.reset();
    choiceWin = QSharedPointer<FileChoiceWindow>::create(nullptr, this);
}

unsigned long Client::numberOpenEditors() {
	return openedEditors.size();
}

// Da cancellare
void Client::printOpenFiles() {
	if (openedFiles.empty()) {
		qDebug() << "No opened files";
		return;
	}
	
	QString names = "Opened files: ";
	for (auto &name: openedFiles) {
		names += name + "  ";
	}
	qDebug().noquote() << names << "\n";
}
