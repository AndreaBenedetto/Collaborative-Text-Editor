
#include <random>
#include "Server.h"
#include "DataBaseOperations.h"
#include "ui_server.h"

int counter = 0;

Server::Server(QWidget *parent): QDialog(parent) {
	ui = QSharedPointer<Ui::Server>::create();
	ui->setupUi(this);
	
	setConfigurationManager();
	createConnections();
	initializePermissions();
}

void Server::setConfigurationManager() {
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

		connect(networkSession.get(), &QNetworkSession::opened, this, &Server::sessionOpened);
		
		networkSession->open();

	} else {
		sessionOpened();
	}
    */
    sessionOpened();
}

void Server::createConnections() {
	connect(tcpServer.get(), &QTcpServer::newConnection, this, &Server::getConnectedSocket);
	connect(ui->Console, &QTextEdit::textChanged, this, [this](){ ui->Console->ensureCursorVisible(); });
}

void Server::initializePermissions() {
    readPermissions();

    for (auto it = permissionsTemporary.begin(); it != permissionsTemporary.end(); it++) {
        auto it2 = userFilePermissionsMap.find(User(it->first));
        if (it2 != userFilePermissionsMap.end()) {
            it2.value().push_back(it->second);
        } else {
            userFilePermissionsMap.insert(User(it->first), QVector<QString> {it->second});
        }
    }
}

void Server::printConsole(QString msg, bool err) {
	time_t t = time(nullptr);
	QString timeString;
	char mbstr[100];
	strftime(mbstr, sizeof(mbstr), "%T", localtime(&t));
	
	auto cursor = ui->Console->textCursor();
	ui->Console->setTextCursor(cursor);
	if (!cursor.atEnd()) {
		cursor.movePosition(QTextCursor::End);
		ui->Console->setTextCursor(cursor);
	}
	
	// Stampa sulla console del server
	if (err)
		this->ui->Console->insertHtml(QString("<p style=\"color:red;\"><b>" + QString(mbstr) + "</b> " + msg + "<br></p>"));
	else
		this->ui->Console->insertHtml(QString("<p><b>" + QString(mbstr) + "</b> " + msg + "<br></p>"));
}

QJsonObject Server::prepareJsonReply(QString header, QString result, QString username, bool propic, bool filelist, bool personalInfo) {
	
	QJsonObject message;
	if (header == "error") {
		message["header"] = "error";
		return message;
	}
	
	message["header"] = header;
	message["body"] = result;
	
	if (propic) {
		QString url(picturePath + username + ".png");
		QPixmap img(url);
		message["propic"] = jsonValFromPixmap(img);
	}
	
	if (filelist) {

		int ret = readFiles();
		if (ret == -1) {
			message["header"] = "error";
			return message;
		}

        QJsonArray filelist;
        auto it = userFilePermissionsMap.find(User(username));
        if (it != userFilePermissionsMap.end()) {
            for (auto &file: it.value()) {
                filelist.push_back(file);
            }
        }
        message["filelist"] = filelist;
	}
	
	if (personalInfo) {
		auto personalInfoData = getPersonalInfo(username);
		if (personalInfoData.first == "db_error" ) {
			message["header"]="error";
			return message;
		}
		message["name"] = personalInfoData.first;
		message["surname"] = personalInfoData.second;
	}
	
	return message;
}

QJsonValue Server::jsonValFromPixmap(const QPixmap &p) {
	QBuffer buffer;
	buffer.open(QIODevice::WriteOnly);
	p.save(&buffer, "PNG");
	auto const encoded = buffer.data().toBase64();
	return {QLatin1String(encoded)};
}

QPixmap Server::pixmapFrom(const QJsonValue &val) {
	auto const encoded = val.toString().toLatin1();
	QPixmap p;
	p.loadFromData(QByteArray::fromBase64(encoded), "PNG");
	return p;
}

QDataStream& Server::serializeVector(QVector<Symbol> vec, QDataStream& out) {
    for (auto &sym: vec) {
        sym.serialize(out);
    }
    return out;
}

QDataStream& Server::deserializeVector(QVector<Symbol>& vec, QDataStream& in) {
    Symbol sym;
    while (!in.atEnd()) {
        sym.deserialize(in);
        vec.push_back(sym);
    }
    return in;
}

void Server::sendMessage(QJsonObject message, QTcpSocket *activeSocket) {
	if (activeSocket != nullptr) {
		if (!activeSocket->isValid()) {
			printConsole("Socket TCP not valid.", true);
			return;
		}
		if (!activeSocket->isOpen()) {
			printConsole("Socket TCP not open.", true);
			return;
		}
		
		QByteArray block;
		QDataStream out(&block, QIODevice::WriteOnly);
		out.setVersion(QDataStream::Qt_4_0);
		printConsole("Sending back " + message["header"].toString() + " " + message["body"].toString());
		
		out << QJsonDocument(message).toJson();

		if (!activeSocket->write(block)) {
			printConsole("Impossible to answer.", true);
		}
		activeSocket->flush();
	} else {
		printConsole("Trying to write to a non existing socket!", true);
	}
}

void Server::loginUser(QJsonObject &data, QTcpSocket *activeSocket) {
	QString username = data["username"].toString();
	QString password = data["password"].toString();
	printConsole("Trying to login " + username);
	
	bool propic = false;
	bool filelist = false;
	bool personalinfo = false;
	
	QString loginResult;
	int queryResult = checkCredentials(username, password);
	if (queryResult == 1) {
		loginResult = "ok";
		User u(username);
		bool found = false;
		if (activeUsers.find(u) != activeUsers.end()) {
		    found = true;
            loginResult = "alreadyloggedin";
		}

		if (!found) {
			// Inserisci l'utente nella lista di quelli attualmente connessi
			activeUsers.insert(u, activeSocket);
			
			// Assegna colore random allo user
			QString userColor = colors[QRandomGenerator::global()->generate() % colors.size()];
            userCount++;
			while (usedColors[colors.indexOf(userColor)] == true && userCount <= colors.size()) {
                userColor = colors[QRandomGenerator::global()->generate() % colors.size()];
			}
			usedColors[colors.indexOf(userColor)] = true;
			userColorMap.insert(u, userColor);
			
			// Inserisci l'utente nella lista con i file aperti
			userOpenedFilesMap.insert(u, QVector<QString> {});
		}

		printActiveUsers();
		
		propic = true;
		filelist = true;
		personalinfo = true;
		
	} else if (queryResult == 0) {
		loginResult = "notregistered";
	} else {
		loginResult = "fail";
	}
	
	QJsonObject message;
	message = prepareJsonReply("login", loginResult, username, propic, filelist, personalinfo);
	sendMessage(message, activeSocket);
	
//	printOpenFiles();
}

void Server::registerUser(QJsonObject &data, QTcpSocket *activeSocket) {
	auto username = data["username"].toString();
	auto password = data["password"].toString();
	auto name = data["name"].toString();
	auto surname = data["surname"].toString();
	QPixmap picture = pixmapFrom(data["propic"]);
	
	bool propic = false;
	bool filelist = false;
	bool personalinfo = false;
	
	QString registrationResult;
	int queryResult = addUser(username, password, name, surname);
	if (queryResult == 1) {
		registrationResult = "ok";
		User u(username);

		activeUsers.insert(u, activeSocket);

		QFile file(picturePath + username + ".png");
		file.open(QIODevice::WriteOnly);
		picture.save(&file, "png", 100);

        QString userColor = colors[QRandomGenerator::global()->generate() % colors.size()];
        userCount++;
        while (usedColors[colors.indexOf(userColor)] == true && userCount <= colors.size()) {
            userColor = colors[QRandomGenerator::global()->generate() % colors.size()];
        }
        usedColors[colors.indexOf(userColor)] = true;
        userColorMap.insert(u, userColor);

        userOpenedFilesMap.insert(u, QVector<QString> {});
		
		printActiveUsers();
		
		propic = true;
		filelist = true;
		personalinfo = true;
		
	} else if (queryResult == 0) {
		registrationResult = "alreadyregistered";
	} else {
		registrationResult = "fail";
	}
	
	QJsonObject message;
	message = prepareJsonReply("registration", registrationResult, username, propic, filelist, personalinfo);
	sendMessage(message, activeSocket);
	
//	printOpenFiles();
}

void Server::cancelUser(QJsonObject &data, QTcpSocket *activeSocket) {
	auto username = data["username"].toString();
	auto password = data["password"].toString();
	printConsole("Trying to delete " + username);
	
	QString cancResult;
	User u(username);
	bool online = false;
	QString activeUser;

	auto it = activeUsers.find(u);
	while (it != activeUsers.end() && it.key() == u) {
	    online = true;
	    activeUser += u.getUsername() + " ";
	    it++;
	}
	
	if (online) {
		printConsole("While you are trying to delete the following users are online..." + activeUser);
		cancResult = "fail";
	} else {
		int queryResult = deleteUser(username, password);
		if (queryResult == 1) {
			cancResult = "ok";
			QFile file(picturePath + username + ".png");
			file.remove();
			userFilePermissionsMap.erase(userFilePermissionsMap.find(User(username)));

			for (auto it1 = filesToChangeOwner.begin(); it1 != filesToChangeOwner.end(); it1++) {
                bool found = false;
                for (auto it2 = userFilePermissionsMap.begin(); it2 != userFilePermissionsMap.end(); it2++) {
                    for (auto &f: it2.value()) {
                        if (f == *it1) {
                            found = true;
                            changeFileOwnership(f, it2.key().getUsername());
                        }
                    }
                    if (found) {
                        break;
                    }
                }
                if (!found) {
                    deleteFile(*it1, username);
                    QFile file(fsRoot + *it1);
                    file.remove();
                }
			}

		} else if (queryResult == 0) {
			cancResult = "notexistent";
		} else {
			cancResult = "fail";
		}
	}
	
	QJsonObject message;
	message = prepareJsonReply("cancellation", cancResult, username);
	sendMessage(message, activeSocket);
}

void Server::refreshFileList(QJsonObject &data, QTcpSocket *activeSocket) {
    auto header = data["header"].toString();
	auto username = data["username"].toString();
	QJsonObject message;
//	message = prepareJsonReply(header, refreshResult, username, false, true, false);
    message["header"] = header;
    message["username"] = username;
    QJsonArray filelist;
    auto it = userFilePermissionsMap.find(User(username));
    if (it != userFilePermissionsMap.end()) {
        for (auto &file: it.value()) {
            filelist.push_back(file);
        }
    }
    message["filelist"] = filelist;
    message["body"] = "ok";
	
	if (header == "refreshfileseditor") {
//		int edid = data["editorid"].toInt();
//		message["editorid"] = edid;
        message["filename"] = data["filename"].toString();
	}
	
	sendMessage(message, activeSocket);
}

void Server::updateUserPropic(QJsonObject &data, QTcpSocket *activeSocket) {
    auto header = data["header"].toString();
	auto username = data["username"].toString();
	auto password = data["password"].toString();
	QPixmap picture = pixmapFrom(data["propic"]);
	
	QString updateResult;
	int queryResult = checkCredentials(username, password);
	if (queryResult == 1) {
		updateResult = "ok";
		QFile file(picturePath + username + ".png");
		file.open(QIODevice::WriteOnly);
		picture.save(&file, "png", 100);
	} else if (queryResult == 0) {
		updateResult = "wrongpassword";
	} else {
		updateResult = "fail";
	}
	
	QJsonObject message;
	message = prepareJsonReply(header, updateResult, username, false, false, false);
	if (header == "updatepropiceditor") {
//		int editorId = data["editorid"].toInt();
//		message["editorid"] = editorId;
        message["filename"] = data["filename"].toString();
	}
	sendMessage(message, activeSocket);
}

void Server::updateUserPassword(QJsonObject &data, QTcpSocket *activeSocket) {
    auto header = data["header"].toString();
	auto username = data["username"].toString();
	auto password = data["password"].toString();
	auto newpassword = data["newpassword"].toString();
	
	QString updateResult;
	int queryResult = changePassword(username, password, newpassword);
	if (queryResult == 1) {
		updateResult = "ok";
	} else if (queryResult == 0) {
		updateResult = "wrongpassword";
	} else {
		updateResult = "fail";
	}
	
	QJsonObject message;
	message = prepareJsonReply(header, updateResult, username, false, false, false);
	if (header == "updatepasswordeditor") {
//		int editorId = data["editorid"].toInt();
//		message["editorid"] = editorId;
        message["filename"] = data["filename"].toString();
	}
	sendMessage(message, activeSocket);
}

void Server::logoutUser(QJsonObject &data, QTcpSocket *activeSocket) {
    auto header = data["header"].toString();
	auto username = data["username"].toString();
    auto filename = data["filename"].toString();

	User u(username);
	usedColors[colors.indexOf(userColorMap.value(u))] = false;
	userCount--;
    userColorMap.erase(userColorMap.find(u));
    activeUsers.erase(activeUsers.find(u));
    userOpenedFilesMap.erase(userOpenedFilesMap.find(u));

	printConsole("Disconnected user: " + username);
	printActiveUsers();

	auto it = fileUsersMap.find(filename);
	if (it != fileUsersMap.end()) {
	    if (it.value().size() > 1) {
	        it.value().erase(std::remove_if(it.value().begin(), it.value().end(), [u](auto &us){
                return (us == u);
	        }), it.value().end());
	    } else {
	        fileUsersMap.erase(fileUsersMap.find(it.key()));

            // Flusha tutto il contenuto del vettore di simboli sul file
            saveFile(filename, header, activeSocket);

            // Cancella il file dalla mappa perché nessuno ha più il file aperto
            fileSymbolsMap.erase(fileSymbolsMap.find(filename));
	    }
	}
	
	QString logoutResult = "ok";
	QJsonObject message;
	message = prepareJsonReply(header, logoutResult, username, false, false, false);
	if (header == "logouteditor") {
//		message["editorid"] = data["editorid"].toInt();
        message["filename"] = data["filename"].toString();
	}
	sendMessage(message, activeSocket);
	
//	printOpenFiles();
}

void Server::getActiveUsers(QJsonObject &data, QTcpSocket *activeSocket) {
	auto username = data["username"].toString();
	int editorId = data["editorid"].toInt();
	auto filename = data["filename"].toString();

	QJsonArray usernamesArray;
	QJsonArray colorsArray;

	auto iterator = fileUsersMap.find(filename);
	if (iterator != fileUsersMap.end()) {
        for (auto &it : iterator.value()) {
            if (it.getUsername() != username) {
                usernamesArray.push_back(it.getUsername());
                colorsArray.push_back(userColorMap.value(it));
            }
        }
	}
	
	QJsonObject message;
	message["header"] = data["header"].toString();
	message["body"] = "ok";
//	message["editorid"] = editorId;
    message["filename"] = filename;
	message["usernames"] = usernamesArray;
	message["colors"] = colorsArray;
	
	sendMessage(message, activeSocket);
}

void Server::getProfilePicture(QJsonObject &data, QTcpSocket *activeSocket) {
	QString username = data["username"].toString();
	int editorId = data["editorid"].toInt();
	QString color = data["color"].toString();
	QString filename = data["filename"].toString();
	
	QJsonObject message;
	message["header"] = data["header"].toString();
	message["body"] = "ok";
	message["username"] = username;
//	message["editorid"] = editorId;
    message["filename"] = filename;
	message["color"] = color;
	message["propic"] = jsonValFromPixmap(QPixmap(picturePath + username + ".png"));

    auto infoPair = getPersonalInfo(username);
    message["name"] = infoPair.first;
    message["surname"] = infoPair.second;
	
	sendMessage(message, activeSocket);
}

void Server::createFile(QJsonObject &data, QTcpSocket *activeSocket) {
    auto header = data["header"].toString();
	auto username = data["username"].toString();
	QString newFilename = data["filenametocheck"].toString();
	QJsonObject message;
    message["header"] = header;
	
	int ret = addFile(newFilename, username);
	if (ret == 0) {
		message["body"] = "alreadyexisting";
	} else if (ret == 1) {
		message["body"] = "ok";
	} else {
		message["body"] = "error";
	}
	
	if (header == "checkfilenameeditor") {
//		int edid = data["editorid"].toInt();
//		message["editorid"] = edid;
        message["filename"] = data["filename"].toString();
	}
	
	if (message["body"] == "ok") {
	    userOpenedFilesMap.find(User(username)).value().push_back(newFilename);
        fileSymbolsMap.insert(newFilename, QVector<Symbol> {});
        fileUsersMap.insert(newFilename, QVector<User> {User(username)});
        auto it = userFilePermissionsMap.find(User(username));
        if (it != userFilePermissionsMap.end()) {
            it.value().push_back(newFilename);
        } else {
            userFilePermissionsMap.insert(User(username), QVector<QString> {newFilename});
        }
	}
	
	sendMessage(message, activeSocket);
	
//	printOpenFiles();
}

void Server::addOpenedFile(QJsonObject &data, QTcpSocket *activeSocket) {
    auto header = data["header"].toString();
	auto newFilename = data["filenametocheck"].toString();
	auto username = data["username"].toString();
	
	QJsonObject message;
	message["header"] = header;
	
	if (header == "openfileeditor") {
//        int edid = data["editorid"].toInt();
//        message["editorid"] = edid;
        message["filename"] = data["filename"].toString();
    }
    readFiles();
	for (auto &file: filesDB) {
		if (file == newFilename) {
            bool authorized = false;
            auto iterator = userFilePermissionsMap.find(User(username));
            if (iterator != userFilePermissionsMap.end()) {
                for (auto &file: iterator.value()) {
                    if (newFilename == file) {
                        authorized = true;
                        break;
                    }
                }
            }

            if (!authorized) {
                message["body"] = "unauthorized";
                sendMessage(message, activeSocket);
                return;
            }

		    bool found = false;

		    auto it = fileUsersMap.find(newFilename);
		    if (it != fileUsersMap.end()) {
		        found = true;
		        for (auto &us: it.value()) {
		            if (us.getUsername() == username) {
                        message["body"] = "alreadyopen";
                        sendMessage(message, activeSocket);
                        return;
		            }
		        }
		        it.value().push_back(User(username));
		    }

		    userOpenedFilesMap.find(User(username)).value().push_back(newFilename);

            QByteArray content;
		    if (!found) {
		        fileUsersMap.insert(newFilename, QVector<User> {User(username)});
		        QFile file(fsRoot + newFilename);
		        file.open(QIODevice::ReadOnly);
		        if (!file.isOpen()) {
                    message["body"] = "error";
                    sendMessage(message, activeSocket);
                    printConsole("Error reading file <i>" + newFilename + "</i>", true);
                    return;
		        }
		        content = file.readAll();
		        file.close();
                QDataStream inStream(content);
                inStream.setVersion(QDataStream::Qt_4_0);

		        QVector<Symbol> vec;
		        deserializeVector(vec, inStream);
		        fileSymbolsMap.insert(newFilename, vec);
		    } else {
                auto it = fileSymbolsMap.find(newFilename);
                QDataStream outStream(&content, QIODevice::ReadWrite);
                outStream.setVersion(QDataStream::Qt_4_0);
                outStream << serializeVector(it.value(), outStream);
		    }

            message["content"] = QLatin1String(content.toBase64());

		    message["body"] = "ok";
		    sendMessage(message, activeSocket);
		    return;
		}
	}

	message["body"] = "filenotfound";
    sendMessage(message, activeSocket);
}

void Server::addOpenedFileURI(QJsonObject &data, QTcpSocket *activeSocket) {
    auto header = data["header"].toString();
    auto uri = data["uri"].toString();
    auto username = data["username"].toString();

    QJsonObject message;
    message["header"] = header;

    if (header == "openfileurieditor") {
//        int edid = data["editorid"].toInt();
//        message["editorid"] = edid;
        message["filename"] = data["filename"].toString();
    }

    auto iter = URIMap.find(uri);
    if (iter == URIMap.end()) {
        message["body"] = "invalid";
        sendMessage(message, activeSocket);
        return;
    }
    auto filename = iter.value().second;
    message["filename"] = filename;

    readFiles();
    for (auto &file: filesDB) {
        if (file == filename) {
            bool authorized = false;
            auto iterator = userFilePermissionsMap.find(User(username));
            if (iterator != userFilePermissionsMap.end()) {
                for (auto &file: iterator.value()) {
                    if (filename == file) {
                        authorized = true;
                        break;
                    }
                }
            }

            if (!authorized) {
                giveAuthorization(username, filename);
                auto it1 = userFilePermissionsMap.find(User(username));
                if (it1 == userFilePermissionsMap.end()) {
                    userFilePermissionsMap.insert(User(username), QVector<QString>{filename});
                } else {
                    it1.value().push_back(filename);
                }
            }

            bool found = false;

            auto it = fileUsersMap.find(filename);
            if (it != fileUsersMap.end()) {
                found = true;
                for (auto &us: it.value()) {
                    if (us.getUsername() == username) {
                        message["body"] = "alreadyopen";
                        sendMessage(message, activeSocket);
                        return;
                    }
                }
                it.value().push_back(User(username));
            }

            userOpenedFilesMap.find(User(username)).value().push_back(filename);

            QByteArray content;
            if (!found) {
                fileUsersMap.insert(filename, QVector<User> {User(username)});
                QFile file(fsRoot + filename);
                file.open(QIODevice::ReadOnly);
                if (!file.isOpen()) {
                    message["body"] = "error";
                    sendMessage(message, activeSocket);
                    printConsole("Error reading file <i>" + filename + "</i>", true);
                    return;
                }
                content = file.readAll();
                file.close();
                QDataStream inStream(content);
                inStream.setVersion(QDataStream::Qt_4_0);

                QVector<Symbol> vec;
                deserializeVector(vec, inStream);
                fileSymbolsMap.insert(filename, vec);
            } else {
                auto it = fileSymbolsMap.find(filename);
                QDataStream outStream(&content, QIODevice::ReadWrite);
                outStream.setVersion(QDataStream::Qt_4_0);
                outStream << serializeVector(it.value(), outStream);
            }

            message["body"] = "ok";
            message["content"] = QLatin1String(content.toBase64());
            sendMessage(message, activeSocket);
            return;
        }
    }

    message["body"] = "filenotfound";
    sendMessage(message, activeSocket);
}

void Server::removeOpenedFile(QJsonObject &data, QTcpSocket *activeSocket) {
    auto header = data["header"].toString();
	auto fileName = data["filename"].toString();
	auto username = data["username"].toString();
	
	QJsonObject message;

	auto it = userOpenedFilesMap.find(User(username));
	it.value().erase(std::remove_if(it.value().begin(), it.value().end(), [fileName](auto &fn){
	    return (fn == fileName);
	}), it.value().end());

	auto it2 = fileUsersMap.find(fileName);
	if (it2 != fileUsersMap.end()) {
	    User u(username);
	    it2.value().erase(std::remove_if(it2.value().begin(), it2.value().end(), [u](auto &us){
	        return (u == us);
	    }), it2.value().end());

	    if (it2.value().empty()) {
	        fileUsersMap.erase(fileUsersMap.find(it2.key()));

            // Flusha tutto il contenuto del vettore di simboli sul file
            saveFile(fileName, header, activeSocket);

            // Cancella il file dalla mappa perché nessuno ha più il file aperto
            fileSymbolsMap.erase(fileSymbolsMap.find(fileName));
	    }
	}

	bool filelist;
	if (header == "closefile") {
	    filelist = false;
	} else if (header == "closelastfile") {
	    filelist = true;
	}

	message = prepareJsonReply(header, "ok", username, false, filelist, false);
	message["filename"] = fileName;
	sendMessage(message, activeSocket);
	
//	printOpenFiles();
}

void Server::deleteExistingFile(QJsonObject &data, QTcpSocket *activeSocket) {
    auto username = data["username"].toString();
    auto filename = data["filename"].toString();
    auto content = QByteArray::fromBase64(data["content"].toString().toLatin1());

    QJsonObject message;
    message["header"] = data["header"];
    message["filename"] = filename;

    auto it = fileSymbolsMap.find(filename);
    if (it != fileSymbolsMap.end()) {
        message["body"] = "fileopen";
        sendMessage(message, activeSocket);
        printConsole("Some user is currently modifying file <i>" + filename + "</i>", true);
        return;
    }

    int ret = deleteFile(filename, username);
    if (ret == -1) {
        message["body"] = "error";
        sendMessage(message, activeSocket);
        printConsole("Error deleting file <i>" + filename + "</i>", true);
        return;
    } else if (ret == 0) {
        message["body"] = "notexisting";
        sendMessage(message, activeSocket);
        printConsole("File <i>" + filename + "</i> does not exist", true);
        return;
    } else if (ret == -2) {
        message["body"] = "notowner";
        sendMessage(message, activeSocket);
        printConsole("Error deleting file <i>" + filename + "</i>", true);
        return;
    }

    QFile file(fsRoot + filename);
    auto res = file.remove();
    if (!res) {
        message["body"] = "error";
        sendMessage(message, activeSocket);
        printConsole("Error deleting file <i>" + filename + "</i>", true);
        return;
    }

    for (auto it2 = userFilePermissionsMap.begin(); it2 != userFilePermissionsMap.end(); it2++) {
        it2.value().erase(std::remove_if(it2.value().begin(), it2.value().end(), [filename](auto &f){
            return (f == filename);
        }), it2.value().end());

        if (it2.value().isEmpty()) {
            auto checkIt = userFilePermissionsMap.erase(it2);
            if (checkIt == userFilePermissionsMap.end()) {
                break;
            }
        }
    }

    message["body"] = "ok";
    sendMessage(message, activeSocket);
    printConsole("File deleted successfully");
}

void Server::generateURI(QJsonObject &data, QTcpSocket *activeSocket) {
    auto header = data["header"].toString();
    auto filename = data["filename"].toString();
    auto username = data["username"].toString();

    QJsonObject message;
    message["header"] = header;
    if (header == "requesturieditor") {
        message["filename"] = filename;
    }

    readFiles();

    for (auto &file: filesDB) {
        if (file == filename) {
            bool authorized = false;
            auto iterator = userFilePermissionsMap.find(User(username));
            if (iterator != userFilePermissionsMap.end()) {
                for (auto &file: iterator.value()) {
                    if (filename == file) {
                        authorized = true;
                        break;
                    }
                }
            }

            if (!authorized) {
                message["body"] = "unauthorized";
                sendMessage(message, activeSocket);
                return;
            }

            const QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");

            QString uri;
            bool ok = false;
            while (!ok) {
                for (int i = 0; i < URILENGTH; i++) {
                    int index = QRandomGenerator::global()->generate() % possibleCharacters.length();
                    QChar nextChar = possibleCharacters.at(index);
                    uri.append(nextChar);
                }
                if (URIMap.find(uri) != URIMap.end()) {
                    uri.clear();
                } else {
                    ok = true;
                }
            }

            auto it = URIMap.insert(uri, qMakePair<QTimer*, QString> (new QTimer(this), filename));
            connect(it.value().first, &QTimer::timeout, this, [this, uri](){ URIMap.erase(URIMap.find(uri)); });
            it.value().first->start(TIMERTIME);

            message["uri"] = uri;
            message["body"] = "ok";

            sendMessage(message, activeSocket);
            return;
        }
    }

    message["body"] = "filenotfound";
    sendMessage(message, activeSocket);
}

void Server::insertText(QJsonObject &data, QTcpSocket *activeSocket) {
    auto filename = data["filename"].toString();
    auto content = QByteArray::fromBase64(data["content"].toString().toLatin1());

    QJsonObject message;
    message["header"] = data["header"];
    message["filename"] = filename;

    int ret = checkFile(filename);
    if (ret == -1) {
        message["body"] = "error";
        sendMessage(message, activeSocket);
        printConsole("Error inserting character in file <i>" + filename + "</i>", true);
        return;
    } else if (ret == 0) {
        message["body"] = "notexisting";
        sendMessage(message, activeSocket);
        printConsole("File <i>" + filename + "</i> does not exist", true);
        return;
    }

    auto it = fileSymbolsMap.find(filename);
    if (it != fileSymbolsMap.end()) {
        QDataStream inStream(content);
        inStream.setVersion(QDataStream::Qt_4_0);

        QVector<Symbol> vec;
        deserializeVector(vec, inStream);

        for (auto j = 0; j < vec.size(); j++) {
            int position = -1;
            for (auto i = 0; i < it.value().size(); i++) {
                if (vec.at(j).getFractionalPosition() < it.value().at(i).getFractionalPosition()) {
                    it.value().insert(it.value().begin() + i, vec.at(j));
                    position = i;
                    break;
                } else if (vec.at(j).getFractionalPosition() == it.value().at(i).getFractionalPosition()) {
                    if (vec.at(j).getUsernameCreator() < it.value().at(i).getUsernameCreator()) {
                        it.value().insert(it.value().begin() + i, vec.at(j));
                        position = i;
                        break;
                    }
                }
            }
            if (position == -1) {
                it.value().push_back(vec.at(j));
                position = it.value().size() - 1;
            }
        }
    }

    message["body"] = "ok";
    sendMessage(message, activeSocket);
    printConsole("Text inserted successfully");

    data["body"] = "forward";
    auto it2 = fileUsersMap.find(filename);
    for (auto &user: it2.value()) {
        if (activeUsers.find(user).value() == activeSocket) {
            data["color"] = userColorMap.find(user).value();
        }
    }

    for (auto &user: it2.value()) {
        auto sock = activeUsers.find(user).value();
        if (sock != activeSocket) {
            sendMessage(data, sock);
        }
    }
//    debugSymbols();
}

void Server::deleteText(QJsonObject &data, QTcpSocket *activeSocket) {
    auto filename = data["filename"].toString();
    auto content = QByteArray::fromBase64(data["content"].toString().toLatin1());

    QJsonObject message;
    message["header"] = data["header"];
    message["filename"] = filename;

    int ret = checkFile(filename);
    if (ret == -1) {
        message["body"] = "error";
        sendMessage(message, activeSocket);
        printConsole("Error inserting character in file <i>" + filename + "</i>", true);
        return;
    } else if (ret == 0) {
        message["body"] = "notexisting";
        sendMessage(message, activeSocket);
        printConsole("File <i>" + filename + "</i> does not exist", true);
        return;
    }

    auto it = fileSymbolsMap.find(filename);
    if (it != fileSymbolsMap.end()) {
        QDataStream in(content);
        in.setVersion(QDataStream::Qt_4_0);
        QVector<Symbol> vec;
        deserializeVector(vec, in);
        for (auto &symbolToDelete: vec) {
            for (auto i = 0; i < it.value().size(); i++) {
                auto sym = it.value().at(i);
                if (sym.getFractionalPosition() == symbolToDelete.getFractionalPosition() && sym.getUsernameCreator() == symbolToDelete.getUsernameCreator()) {
                    it.value().erase(it.value().begin() + i);
                    break;
                }
            }
        }
    }

    message["body"] = "ok";
    sendMessage(message, activeSocket);
    printConsole("Text deleted successfully");

    data["body"] = "forward";
    auto it2 = fileUsersMap.find(filename);
    for (auto &user: it2.value()) {
        auto sock = activeUsers.find(user).value();
        if (sock != activeSocket) {
            sendMessage(data, sock);
        }
    }
//    debugSymbols();
}

void Server::modifyCharFormat(QJsonObject &data, QTcpSocket *activeSocket) {
    auto filename = data["filename"].toString();
    auto content = QByteArray::fromBase64(data["content"].toString().toLatin1());

    QJsonObject message;
    message["header"] = data["header"];
    message["filename"] = filename;

    int ret = checkFile(filename);
    if (ret == -1) {
        message["body"] = "error";
        sendMessage(message, activeSocket);
        printConsole("Error inserting character in file <i>" + filename + "</i>", true);
        return;
    } else if (ret == 0) {
        message["body"] = "notexisting";
        sendMessage(message, activeSocket);
        printConsole("File <i>" + filename + "</i> does not exist", true);
        return;
    }

    auto it = fileSymbolsMap.find(filename);
    if (it != fileSymbolsMap.end()) {
        QDataStream in(content);
        in.setVersion(QDataStream::Qt_4_0);
        QVector<Symbol> vec;
        deserializeVector(vec, in);
        for (auto &symbolToModify: vec) {
            for (auto i = 0; i < it.value().size(); i++) {
                auto sym = it.value().at(i);
                if (sym.getFractionalPosition() == symbolToModify.getFractionalPosition() && sym.getUsernameCreator() == symbolToModify.getUsernameCreator()) {
                    QTextCharFormat temp = it.value().at(i).getCharFormat();
                    temp.merge(symbolToModify.getCharFormat());
                    symbolToModify.setCharFormat(temp);
                    it.value().replace(i, symbolToModify);
                    break;
                }
            }
        }
    }

    message["body"] = "ok";
    sendMessage(message, activeSocket);
    printConsole("Text format modified successfully");

    data["body"] = "forward";
    auto it2 = fileUsersMap.find(filename);
    for (auto &user: it2.value()) {
        if (activeUsers.find(user).value() == activeSocket) {
            data["color"] = userColorMap.find(user).value();
            data["username"] = user.getUsername();
        }
    }

    for (auto &user: it2.value()) {
        auto sock = activeUsers.find(user).value();
        if (sock != activeSocket) {
            sendMessage(data, sock);
        }
    }

//    debugSymbols();
}

void Server::modifyBlockFormat(QJsonObject &data, QTcpSocket *activeSocket) {
    auto filename = data["filename"].toString();
    auto content = QByteArray::fromBase64(data["content"].toString().toLatin1());

    QJsonObject message;
    message["header"] = data["header"];
    message["filename"] = filename;

    int ret = checkFile(filename);
    if (ret == -1) {
        message["body"] = "error";
        sendMessage(message, activeSocket);
        printConsole("Error inserting character in file <i>" + filename + "</i>", true);
        return;
    } else if (ret == 0) {
        message["body"] = "notexisting";
        sendMessage(message, activeSocket);
        printConsole("File <i>" + filename + "</i> does not exist", true);
        return;
    }

    auto it = fileSymbolsMap.find(filename);
    if (it != fileSymbolsMap.end()) {
        QDataStream in(content);
        in.setVersion(QDataStream::Qt_4_0);
        QVector<Symbol> vec;
        deserializeVector(vec, in);
        for (auto &symbolToModify: vec) {
            for (auto i = 0; i < it.value().size(); i++) {
                auto sym = it.value().at(i);
                if (sym.getFractionalPosition() == symbolToModify.getFractionalPosition() && sym.getUsernameCreator() == symbolToModify.getUsernameCreator()) {
                    QTextBlockFormat temp = it.value().at(i).getBlockFormat();
                    temp.merge(symbolToModify.getBlockFormat());
                    symbolToModify.setBlockFormat(temp);
                    it.value().replace(i, symbolToModify);
                    break;
                }
            }
        }
    }

    message["body"] = "ok";
    sendMessage(message, activeSocket);
    printConsole("Block format modified successfully");

    data["body"] = "forward";
    auto it2 = fileUsersMap.find(filename);
    for (auto &user: it2.value()) {
        if (activeUsers.find(user).value() == activeSocket) {
            data["color"] = userColorMap.find(user).value();
            data["username"] = user.getUsername();
        }
    }

    for (auto &user: it2.value()) {
        auto sock = activeUsers.find(user).value();
        if (sock != activeSocket) {
            sendMessage(data, sock);
        }
    }

//    debugSymbols();
}

void Server::printActiveUsers() {
	QString userList;
	for (auto it = activeUsers.begin(); it != activeUsers.end(); it++) {
	    userList += it.key().getUsername() + " -> " + QString::number(it.value()->socketDescriptor()) + "\t";
	}
	if (!userList.isEmpty()) {
        printConsole("List of active users and their sockets: " + userList);
	} else {
	    printConsole("Nobody is connected");
	}
}

void Server::saveFile(QString filename, QString header, QTcpSocket* activeSocket) {
    QByteArray content;
    QDataStream out(&content, QIODevice::ReadWrite);
    out.setVersion(QDataStream::Qt_4_0);

    QFile file(fsRoot + filename);
    file.open(QIODevice::WriteOnly);
    if (!file.isOpen()) {
        QJsonObject message;
        message["header"] = header;
        message["body"] = "error";
        sendMessage(message, activeSocket);
        printConsole("Error saving file <i>" + filename + "</i>", true);
        return;
    }
    auto it = fileSymbolsMap.find(filename);
    out << serializeVector(it.value(), out);
    file.resize(0);
    file.write(content);
    file.close();
    qDebug() << "File " << filename << " saved";

//    debugSymbols();
}

// Slot privati
void Server::sessionOpened() {
	QString ipAddress;
#ifndef LOCALHOST
	QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
	// Utilizza il primo indirizzo IPv4 non locale
	for (const auto &i : ipAddressesList) {
	    qDebug() << i.toString();
		if (i != QHostAddress::LocalHost & i.toIPv4Address()) {
			ipAddress = i.toString();
			break;
		}
	}
	// Se non lo trova, usa l'indirizzo IPv4 locale
	if (ipAddress.isEmpty()) {
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    }
#else
	ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
#endif
	
	int port = 4848;

	/*
	if (networkSession) {
		QNetworkConfiguration config = networkSession->configuration();
		QString id;
		if (config.type() == QNetworkConfiguration::UserChoice) {
            id = networkSession->sessionProperty(QLatin1String("UserChoiceConfiguration")).toString();
        } else {
            id = config.identifier();
        }

		QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
		settings.beginGroup(QLatin1String("QtNetwork"));
		settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
		settings.endGroup();
	}
	 */
	
	tcpServer = QSharedPointer<QTcpServer>::create(this);
	if (!tcpServer->listen(QHostAddress::Any, port)) {
		printConsole("Impossible to start the server: " + tcpServer->errorString(), true);
		this->close();
		return;
	}
	
	printConsole("Working server at:  <u>" + ipAddress + ":" + QString::number(tcpServer->serverPort()) + "</u>");
}

void Server::getConnectedSocket() {
	auto activeSocket = tcpServer->nextPendingConnection();
	printConsole("Accepting a new connection from socket " + QString::number(activeSocket->socketDescriptor()));
	connect(activeSocket, &QIODevice::readyRead, this, &Server::processUserRequest);
	connect(activeSocket, &QAbstractSocket::disconnected, this, &Server::handleDisconnection);
}

void Server::processUserRequest() {
	QTcpSocket *activeSocket = (QTcpSocket *) sender();
	in.setDevice(activeSocket);
	
	while (activeSocket->bytesAvailable() > 0) {
        // Legge i messaggi in arrivo dal client
        QByteArray jSmessage;
        QString header;
        QJsonObject jSobject;

        in.startTransaction();
        in >> jSmessage;
        if (!in.commitTransaction()) {
            return;
        }

		QJsonParseError parseError;
		
		// Prova a creare un documento JSon con i dati letti
		const QJsonDocument jsonDoc = QJsonDocument::fromJson(jSmessage, &parseError);
		if (parseError.error == QJsonParseError::NoError) {
			// Se i dati sono validi
			if (jsonDoc.isObject()) {
				jSobject = jsonDoc.object();
				header = jSobject["header"].toString();
			} else {
				QJsonObject message = prepareJsonReply("error", "error", "");
				sendMessage(message, activeSocket);
				return;
			}
		} else {
			QJsonObject message = prepareJsonReply("error", "error", "");
			sendMessage(message, activeSocket);
			return;
		}

		printConsole("[" + activeSocket->peerAddress().toString() + ":" + QString::number(activeSocket->peerPort()) + "] " + header);
		
		if (header == "login") {
			loginUser(jSobject, activeSocket);
		} else if (header == "registration") {
			registerUser(jSobject, activeSocket);
		} else if (header == "cancellation") {
			cancelUser(jSobject, activeSocket);
		} else if (header == "refreshfiles" || header == "refreshfileseditor") {
			refreshFileList(jSobject, activeSocket);
		} else if (header == "updatepropic" | header == "updatepropiceditor") {
			updateUserPropic(jSobject, activeSocket);
		} else if (header == "updatepassword" | header == "updatepasswordeditor") {
			updateUserPassword(jSobject, activeSocket);
		} else if (header == "logout" | header == "logouteditor") {
			logoutUser(jSobject, activeSocket);
		} else if (header == "inserttext") {
		    insertText(jSobject, activeSocket);
		} else if (header == "deletetext") {
            deleteText(jSobject, activeSocket);
        } else if (header == "modifycharformat") {
            modifyCharFormat(jSobject, activeSocket);
		} else if (header == "modifyblockformat") {
			modifyBlockFormat(jSobject, activeSocket);
		} else if (header == "getactiveusers") {
			getActiveUsers(jSobject, activeSocket);
		} else if (header == "getprofilepicture") {
			getProfilePicture(jSobject, activeSocket);
		} else if (header == "checkfilename" | header == "checkfilenameeditor") {
			createFile(jSobject, activeSocket);
		} else if (header == "openfile" | header == "openfileeditor") {
			addOpenedFile(jSobject, activeSocket);
		} else if (header == "closefile" | header == "closelastfile") {
			removeOpenedFile(jSobject, activeSocket);
		} else if (header == "deletefile") {
		    deleteExistingFile(jSobject, activeSocket);
		} else if (header == "requesturi" | header == "requesturieditor") {
		    generateURI(jSobject, activeSocket);
		} else if (header == "openfileuri" | header == "openfileurieditor") {
		    addOpenedFileURI(jSobject, activeSocket);
		} else {
			qDebug() << "Message not recognized";
		}
	}
}

void Server::handleDisconnection() {
	auto disconnectedSocket = (QTcpSocket *) sender();
	QString disconnectedUsername;

	for (auto it = activeUsers.begin(); it != activeUsers.end(); it++) {
	    if (it.value() == disconnectedSocket) {
	        disconnectedUsername = it.key().getUsername();
	        break;
	    }
	}

    User u(disconnectedUsername);
	if (userColorMap.find(u) != userColorMap.end()) {
        usedColors[colors.indexOf(userColorMap.value(u))] = false;
        userCount--;
        userColorMap.erase(userColorMap.find(u));
        activeUsers.erase(activeUsers.find(u));
        userOpenedFilesMap.erase(userOpenedFilesMap.find(u));

        QList<QString> filesToClose;
        for (auto it = fileUsersMap.begin(); it != fileUsersMap.end(); it++) {
            it.value().erase(std::remove_if(it.value().begin(), it.value().end(), [u](auto &us){
                return (u == us);
            }), it.value().end());
            if (it.value().empty()) {
                // Flusha tutto il contenuto del vettore di simboli sul file
                saveFile(it.key(), "logouteditor", disconnectedSocket);

                // Cancella il file dalla mappa perché nessuno ha più il file aperto
                fileSymbolsMap.erase(fileSymbolsMap.find(it.key()));
                filesToClose.push_back(it.key());
            }
        }
        for (auto &name: filesToClose) {
            fileUsersMap.erase(fileUsersMap.find(name));
        }

        printConsole("Disconnected user: " + disconnectedUsername);
        printActiveUsers();
	}
	
	disconnectedSocket->deleteLater();
	
//	printOpenFiles();
}

// Da cancellare
void Server::printOpenFiles() {
	if (userOpenedFilesMap.empty()) {
		qDebug() << "Nobody connected";
		return;
	}

	for (auto it = userOpenedFilesMap.begin(); it != userOpenedFilesMap.end(); it++) {
	    qDebug() << "User: " << it.key().getUsername();
	    QString names;
        for (auto &name: it.value()) {
            names += name + "  ";
        }
        qDebug().noquote() << names;
	}
}

void Server::debugSymbols() {
    for (auto it = fileSymbolsMap.begin(); it != fileSymbolsMap.end(); it++) {
        qDebug() << "\tFile:" << it.key();
        for (auto &sym: it.value()) {
            qDebug() << sym.getCharacter().toLatin1() << sym.getFractionalPosition() << sym.getCharFormat().fontWeight() << sym.getCharFormat().fontUnderline() << sym.getBlockFormat().alignment() << sym.getCharFormat().foreground().color();
        }
        qDebug() << "";
    }
}

void Server::debugSymbol(Symbol &sym) {
    qDebug() << sym.getCharacter().toLatin1() << sym.getFractionalPosition() << sym.getCharFormat().fontWeight() << sym.getCharFormat().fontUnderline() << sym.getBlockFormat().alignment() << sym.getCharFormat().foreground().color();
}
