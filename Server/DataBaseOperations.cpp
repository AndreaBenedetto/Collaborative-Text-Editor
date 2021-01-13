
#include <iostream>
#include "DataBaseOperations.h"


QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
QSet<QString> filesDB;
QSet<QPair<QString, QString>> permissionsTemporary;
QList<QString> filesToChangeOwner;

bool openDB(QSqlDatabase db) {
    db.setDatabaseName(dbPath);

    if (!db.open()) {
        qDebug() << "ERROR: " << db.lastError();
        return false;
    } else {
//        qDebug() << "Db opened with success";
        return true;
    }
}

bool closeDB(QSqlDatabase db) {
    db.close();
}

QPair<QString, QString> getPersonalInfo(QString username) {

//    qDebug() << "Getting personal info...";

    QPair<QString, QString> result;
	
	if (!openDB(db)) {
	    return qMakePair<QString, QString> ("db_error", "Can't open the database");
	}

	QSqlQuery query;
    query.prepare( "SELECT * FROM USERS WHERE USERNAME = '" + username + "'");
	dbCounter = 0;
	
	if (!execQuery(query, personalInfo)) {
		return qMakePair<QString, QString> ("db_error", errMsg);
	}
	
	closeDB(db);
	
	if (dbCounter == 1) {
		// L'utente esiste
		result = qMakePair<QString, QString> (infoName, infoSurname);
		return result;
	} else {
		// L'utente non esiste o le credenziali sono sbagliate
		result = qMakePair<QString, QString> ("db_error", "User does not exist");
		return result;
	}
}

static bool personalInfo(QSqlQuery query) {
    QSqlRecord record;
    query.first();
    if (query.isValid()) {
        record = query.record();
        // argc è 4 perché i campi del DB sono USERNAME, PASSWORD, NAME, SURNAME
        if (record.count() != 4) {
            std::cerr << "Error in the number of columns." << std::endl;
            return false;
        }
    }

    query.previous();

    while(query.next()) {
        dbCounter++;
        infoName = query.value(2).toString();
        infoSurname = query.value(3).toString();
    }
    return true;
}

int readFiles() {
//    QSqlDatabase db = QSqlDatabase::addDatabase(DRIVER);

//    qDebug() << "Reading files...";

    if (!openDB(db)) {
        return -1;
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM FILES");
    dbCounter = 0;

    if(!execQuery(query, files)) {
        return -1;
    }

    closeDB(db);

    if (dbCounter >= 1)
        return 1;
    return 0;

}

bool execQuery(QSqlQuery query,bool (*function)(QSqlQuery qry)) {

//    qDebug() << "Executing query...";

    if(!query.exec()) {
        qWarning() << "ERROR: " << query.lastError().text();
        errMsg = query.lastError().text();
        return false;
    }

    if (function == nullptr) {
        return true;
    }

    bool rt = function(query);
    if (!rt) {
        closeDB(db);
        return false;
    }
    return true;
}

static bool files(QSqlQuery query) {
    QSqlRecord record;
    query.first();
    if (query.isValid()) {
        record = query.record();
        // argc è 3 perché i campi del DB sono ID, NAME, OWNER
        if (record.count() != 3) {
            std::cerr << "Error in the number of columns." << std::endl;
            return false;
        }
    }

    query.previous();

    while(query.next()) {
        dbCounter++;
        QString file = query.value(1).toString();
//        qDebug() << "file" << file;
        filesDB.insert(file);
    }
    return true;
}

int checkCredentials(QString usr, QString password) {

//    qDebug() << "Checking credentials...";

	if (!openDB(db)) {
		return -1;
	}

	QSqlQuery query;
    cipher.addData(password.toUtf8());
	query.prepare("SELECT * FROM USERS WHERE USERNAME = '" + usr + "' AND PASSWORD = '" + QString(cipher.result().toHex()) + "'");
//	query.prepare("SELECT * FROM USERS WHERE USERNAME = '" + usr + "' AND PASSWORD = '" + password + "'");
	cipher.reset();
	dbCounter = 0;
	
	if (!execQuery(query,check)) {
		return -1;
	}
	
	closeDB(db);
	
	if (dbCounter == 1) {
		return 1;
	}
	return 0;
}

static bool check(QSqlQuery query) {
    while(query.next()) {
        dbCounter++;
//        qDebug() << "counter: " << dbCounter;
    }
	return true;
}

int addUser(QString username, QString password, QString name, QString surname) {

//    qDebug() << "Adding user...";

	if (!openDB(db)) {
		return -1;
	}

    QSqlQuery query;
	query.prepare("SELECT * FROM USERS WHERE USERNAME = '" + username + "'");
	dbCounter = 0;
	
	if (!execQuery(query,check)) {
		return -1;
	}
	
	if (dbCounter == 1) {
		closeDB(db);
		return 0;
	}

    cipher.addData(password.toUtf8());
	query.prepare("INSERT INTO USERS ('USERNAME', 'PASSWORD', 'NAME', 'SURNAME') VALUES ('" + username + "', '" + QString(cipher.result().toHex()) + "', '" + name + "', '" + surname + "')");
//	query.prepare("INSERT INTO USERS ('USERNAME', 'PASSWORD', 'NAME', 'SURNAME') VALUES ('" + username + "', '" + password + "', '" + name + "', '" + surname + "')");
	cipher.reset();

	if (!execQuery(query,nullptr)) {
		return -1;
	}
	
	closeDB(db);
	return 1;
}

int deleteUser(QString username, QString password) {

//    qDebug() << "Deleting user...";

	if (!openDB(db)) {
		return -1;
	}

    QSqlQuery query;
    cipher.addData(password.toUtf8());
	query.prepare("SELECT * FROM USERS WHERE USERNAME = '" + username + "' AND PASSWORD = '" + QString(cipher.result().toHex()) + "';");
//	query.prepare("SELECT * FROM USERS WHERE USERNAME = '" + username + "' AND PASSWORD = '" + password + "';");
	cipher.reset();
	dbCounter = 0;
	
	if (!execQuery(query, check)) {
		return -1;
	}
	
	if (dbCounter == 1) {
        cipher.addData(password.toUtf8());
		query.prepare("DELETE FROM USERS WHERE USERNAME = '" + username + "' AND PASSWORD = '" + QString(cipher.result().toHex()) + "';");
//		query.prepare("DELETE FROM USERS WHERE USERNAME = '" + username + "' AND PASSWORD = '" + password + "';");
		cipher.reset();
		if (!execQuery(query, nullptr)) {
			return -1;
		}

		// TODO: cambiare l'ownership dei file di cui era owner l'utente cancellato
		filesToChangeOwner.clear();
		query.prepare("SELECT * FROM FILES WHERE OWNER = '" + username + "'");
		if (!execQuery(query, fileOwner)) {
            return -1;
		}

		query.prepare("DELETE FROM PERMISSIONS WHERE USERNAME = '" + username + "'");
        if (!execQuery(query, nullptr)) {
            return -1;
        }

		closeDB(db);
		return 1;
	}
	
	closeDB(db);
	return 0;
}

int addFile(QString name, QString username) {

//    qDebug() << "Adding file...";

	if (!openDB(db)) {
		return -1;
	}

    QSqlQuery query;
	query.prepare("SELECT * FROM FILES WHERE LOWER(NAME) = LOWER('" + name + "')");
	dbCounter = 0;

	if (!execQuery(query, check)) {
		return -1;
	}

	if (dbCounter == 1) {
		closeDB(db);
		return 0;
	}

    QFile file(fsRoot + name);
    file.open(QIODevice::WriteOnly);
    if (!file.isOpen()) {
        return 0;
    }

    QByteArray byteArrayBuffer;
    QDataStream stream(&byteArrayBuffer, QIODevice::ReadWrite);
    stream.setVersion(QDataStream::Qt_4_0);

    file.write(byteArrayBuffer);
    file.close();
	
	query.prepare("INSERT INTO FILES ('NAME', 'OWNER') VALUES ('" + name + "', '" + username + "')");
//    () << "Inserting file...";

	if (!execQuery(query, nullptr)) {
		return -1;
	}

	query.prepare("INSERT INTO PERMISSIONS ('USERNAME', 'FILE') VALUES ('" + username + "', '" + name + "')");
//    qDebug() << "inserting permission...";

	if (!execQuery(query, nullptr)) {
	    return -1;
	}

	closeDB(db);
	return 1;
}

int deleteFile(QString name, QString username) {

//    qDebug() << "Deleting file...";

	if (!openDB(db)) {
		return -1;
	}

    QSqlQuery query;
	query.prepare("SELECT * FROM FILES WHERE NAME = '" + name + "'");
    dbCounter = 0;

    if (!execQuery(query, check)) {
        return -1;
    }

    if (dbCounter == 0) {
        closeDB(db);
        return 0;
    }

    query.prepare("SELECT * FROM FILES WHERE NAME = '" + name + "' AND OWNER = '" + username + "'");
	dbCounter = 0;

	if (!execQuery(query, check)) {
		return -1;
	}
	
	if (dbCounter == 0) {
		closeDB(db);
		return -2;
	}

	query.prepare("DELETE FROM FILES WHERE NAME = '" + name + "'");
	
	if (!execQuery(query, nullptr)) {
		return -1;
	}

	query.prepare("DELETE FROM PERMISSIONS WHERE FILE = '" + name + "'");

    if (!execQuery(query, nullptr)) {
        return -1;
    }
	
	closeDB(db);
	return 1;
}

int checkFile(QString name) {

//    qDebug() << "Checking file...";

    if (!openDB(db)) {
        return -1;
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM FILES WHERE NAME = '" + name + "'");
    dbCounter = 0;

    if (!execQuery(query, check)) {
        return -1;
    }
    closeDB(db);

    if (dbCounter == 1) {
        return 1;
    }
    return 0;
}

int changePassword(QString username, QString oldPassword, QString newPassword) {

//    qDebug() << "Changing password...";

	if (!openDB(db)) {
		return -1;
	}

    QSqlQuery query;
    cipher.addData(oldPassword.toUtf8());
    query.prepare( "SELECT * FROM USERS WHERE USERNAME = '" + username + "' AND PASSWORD = '" + QString(cipher.result().toHex()) + "'");
//    query.prepare( "SELECT * FROM USERS WHERE USERNAME = '" + username + "' AND PASSWORD = '" + oldPassword + "'");
    cipher.reset();
	dbCounter = 0;
	
	if (!execQuery(query, check)) {
		return -1;
	}
	
	if (dbCounter == 0) {
		closeDB(db);
		return 0;
	}

    cipher.addData(newPassword.toUtf8());
    query.prepare( "UPDATE USERS SET PASSWORD = '" + QString(cipher.result().toHex()) + "' WHERE USERNAME = '" + username + "'");
//    query.prepare( "UPDATE USERS SET PASSWORD = '" + newPassword + "' WHERE USERNAME = '" + username + "'");
    cipher.reset();

	if (!execQuery(query, nullptr)) {
		return -1;
	}
	
	closeDB(db);
	return 1;
}

int readPermissions() {

//    qDebug() << "Reading premissions...";

    if (!openDB(db)) {
        return -1;
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM PERMISSIONS");

    permissionsTemporary.clear();
    if (!execQuery(query,permissions)) {
        return -1;
    }

    closeDB(db);
    return 1;
}

static bool permissions(QSqlQuery query) {

    QSqlRecord record;
    query.first();
    if (query.isValid()) {
        record = query.record();
        // argc è 2 perché i campi del DB sono USERNAME, FILE
        if (record.count() != 2) {
            std::cerr << "Error in the number of columns." << std::endl;
            return false;
        }
    }

    query.previous();

    while(query.next()) {
        permissionsTemporary.insert(qMakePair<QString, QString> (query.value(0).toString(), query.value(1).toString()));
    }
    return true;
}

static bool fileOwner(QSqlQuery query) {
    QSqlRecord record;
    query.first();
    if (query.isValid()) {
        record = query.record();
        // argc è 3 perché i campi del DB sono ID, NAME, OWNER
        if (record.count() != 3) {
            std::cerr << "Error in the number of columns." << std::endl;
            return false;
        }
    }

    query.previous();
    while(query.next()) {
        filesToChangeOwner.push_back(query.value(1).toString());
    }
    return true;
}

int changeFileOwnership(QString file, QString newOwner) {

//    qDebug() << "Changing file ownership...";

    if (!openDB(db)) {
        return -1;
    }

    QSqlQuery query;
    query.prepare( "UPDATE FILES SET OWNER = '" + newOwner + "' WHERE NAME = '" + file + "'");
    if (!execQuery(query, nullptr)) {
        return -1;
    }

    closeDB(db);
    return 1;
}

int giveAuthorization(QString username, QString filename) {

//    qDebug() << "Giving authorization...";

    if (!openDB(db)) {
        return -1;
    }

    QSqlQuery query;
    query.prepare( "INSERT INTO PERMISSIONS ('USERNAME', 'FILE') VALUES ('" + username + "', '" + filename + "')");
    if (!execQuery(query, nullptr)) {
        return -1;
    }

    closeDB(db);
    return 1;
}