
#ifndef CLIENT_CLIENT_H
#define CLIENT_CLIENT_H

#include <QtWidgets>
#include <QtNetwork>
#include <memory>
#include "User.h"
#include "LoginWindow.h"
#include "FileChoiceWindow.h"

#define LOCALHOST 1
#define MSGTIME 3000
#define WAITTIME 5000

static QString iconsPath("../IconsClient/");
static QString defaultPicture(iconsPath + "myicons-default-user-image.png");
static QString usernameInfo("The username should be at least 4 and at most 16 characters long.\nIt should not contain space characters.");
static QString passwordInfo("The password should be at least 4 and at most 16 characters long.\nIt should not contain space characters.\nIt should contain at least a lowercase and an uppercase letter.");
static QString titleClient("PDS Client");
static QString applicationFontFamily = "Manjari";
static int applicationFontSize = 14;

QT_BEGIN_NAMESPACE
class Editor;
QT_END_NAMESPACE

class Client: public QObject {
	Q_OBJECT

private:
	QSharedPointer<QTcpSocket> tcpSocket;
	QDataStream in;
//	QSharedPointer<QNetworkSession> networkSession;
    QSharedPointer<User> loggedUser;
	QList<QString> availFile;
	
	QSharedPointer<LoginWindow> logWin;
    QSharedPointer<FileChoiceWindow> choiceWin;
	
	QVector<QSharedPointer<Editor>> openedEditors;
	QVector<QString> openedFiles;
	
public:
	int editorIdentifier = 0;
	bool isCloseEvent = true;

public:
	explicit Client(QWidget *parent = nullptr);
	bool checkSocket();
	void pushNewEditor(QSharedPointer<Editor> newEditor);
	void pushNewFile(QString filename);
	void removeClosedEditor(Editor *closedEditor);
	void removeClosedFile(QString filename);
	void openFileChoiceWindow(bool fromRegistration);
	
private:
	void connectSocket();
	void requestConnection();
	void setConfigurationManager();
	void sessionOpened();
	
private slots:
	void connectionError(QAbstractSocket::SocketError socketError);
	void readResponse();
	
// Getters e setters
public:
    QSharedPointer<QTcpSocket> getTcpSocket();
    QSharedPointer<User> getLoggedUser();
	void setLoggedUser(const User &user);
	QList<QString> getAvailFile();
	void setFileList(QJsonObject& data);
    QSharedPointer<LoginWindow> getLogWin();
	void setLogWin();
	void setChoiceWin();
	unsigned long numberOpenEditors();
	
// Da cancellare
private:
	void printOpenFiles();
};


#endif //CLIENT_CLIENT_H
