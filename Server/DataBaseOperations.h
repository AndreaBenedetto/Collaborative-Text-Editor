
#ifndef SERVER_DATABASEOPERATIONS_H
#define SERVER_DATABASEOPERATIONS_H

#include <set>
#include <tuple>
#include <sqlite3.h>
#include <vector>
#include "Symbol.h"
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

extern QSet<QString> filesDB;
static QString dbPath = "../pds_db";
const QString fsRoot = "../Files/";
static int dbCounter;
static QString infoName;
static QString infoSurname;
static QCryptographicHash cipher(QCryptographicHash::Md5);
extern QSet<QPair<QString, QString>> permissionsTemporary;
extern QList<QString> filesToChangeOwner;
static QString errMsg;

bool openDB(QSqlDatabase db);
bool execQuery(QSqlQuery query,bool (*function)(QSqlQuery qry));
bool closeDB(QSqlDatabase db);
QPair<QString, QString> getPersonalInfo(QString username);
static bool personalInfo(QSqlQuery query);
int readFiles();
static bool files(QSqlQuery query);
int checkCredentials(QString usr, QString password);
static bool check(QSqlQuery query);
int addUser(QString username, QString password, QString name, QString surname);
int deleteUser(QString username, QString password);
int addFile(QString name, QString username);
int deleteFile(QString name, QString username);
int checkFile(QString name);
int changePassword(QString username, QString oldPassword, QString newPassword);
int readPermissions();
static bool permissions(QSqlQuery query);
static bool fileOwner(QSqlQuery query);
int changeFileOwnership(QString file, QString newOwner);
int giveAuthorization(QString username, QString filename);

#endif //SERVER_DATABASEOPERATIONS_H
