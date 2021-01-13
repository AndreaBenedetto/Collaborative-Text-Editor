
#ifndef CLIENT_OTHERFUNCTIONS_H
#define CLIENT_OTHERFUNCTIONS_H

#include <QTranslator>
#include <QString>
#include <QDialog>
#include "Client.h"
#include "Symbol.h"

// Per il login
bool sendJSonMessage(Client* client, QString header, QString username = "", QString password = "", QString name = "", QString surname = "", QJsonValue propic = QJsonValue::Null, QString newpassword = "", int editorId = -1, QString color = "", QString fileName = "", QString uri = "", QString filenameToCheck = "");
bool checkPasswordFormat(QString password);
bool checkUsernameFormat(QString username);
QJsonValue jsonValFromPixmap(const QPixmap &p);
QPixmap pixmapFrom(const QJsonValue &val);
void deactivateWindow(QWidget *window);
void reactivateWindow(QWidget *window);
void pressPasswordButton(QLineEdit *lineEdit, QToolButton *button);
void releasePasswordButton(QLineEdit *lineEdit, QToolButton *button);
void correctUsername(QString username, QPushButton *button);
void correctPassword(QString password, QPushButton *button);
int createMessageBox(QWidget *parent, QMessageBox::Icon icon, QString message, QMessageBox::StandardButtons buttons = QMessageBox::Ok);

// Per l'editor
bool sendMultipleActionsToServer(Client *client, QString header, QString fileName, QVector<Symbol> vec);
QDataStream& serializeVector(QVector<Symbol> vec, QDataStream& out);
QDataStream& deserializeVector(QVector<Symbol>& vec, QDataStream& in);

#endif //CLIENT_OTHERFUNCTIONS_H
