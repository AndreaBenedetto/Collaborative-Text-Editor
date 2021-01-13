
#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

#include <QtCore>
#include <QDialog>
#include <QtNetwork>
#include <memory>
#include <array>
#include "User.h"
#include "Symbol.h"

#define LOCALHOST 1
#define TIMERTIME 300000
#define URILENGTH 16

static QString picturePath("../Pictures/");
static QVector<QString> colors{"salmon", "palegreen", "lightblue", "paleturquoise", "lightpink", "khaki", "darkseagreen"};
static QVector<bool> usedColors{false, false, false, false, false, false, false};
static int userCount = 0;

QT_BEGIN_NAMESPACE
namespace Ui { class Server; }
QT_END_NAMESPACE

class Server: public QDialog {
	Q_OBJECT
	
private:
	QSharedPointer<Ui::Server> ui;
	QSharedPointer<QTcpServer> tcpServer;
	QDataStream in;
//	QSharedPointer<QNetworkSession> networkSession;
    QMap<User, QTcpSocket*> activeUsers;                                        // Mappa user - socket
	QMap<User, QString> userColorMap;                                           // Mappa user - colore
	QMap<User, QVector<QString>> userOpenedFilesMap;                            // Mappa user - file aperti
	QMap<QString, QVector<Symbol>> fileSymbolsMap;                              // Mappa file - contenuto
	QMap<QString, QVector<User>> fileUsersMap;                                  // Mappa file - user
	QMap<User, QVector<QString>> userFilePermissionsMap;                        // Mappa user - file a cui ha accesso
	QMap<QString, QPair<QTimer*, QString>> URIMap;                              // Mappa URI - timer - file

public:
	explicit Server(QWidget *parent = nullptr);
	
private:
	void setConfigurationManager();
	void createConnections();
	void initializePermissions();
	void printConsole(QString msg, bool err = false);
	QJsonObject prepareJsonReply(QString header, QString result, QString username, bool propic = false, bool filelist = false, bool personal_info = false);
	QJsonValue jsonValFromPixmap(const QPixmap &p);
	QPixmap pixmapFrom(const QJsonValue &val);
	QDataStream& serializeVector(QVector<Symbol> vec, QDataStream& out);
    QDataStream& deserializeVector(QVector<Symbol>& vec, QDataStream& in);
	void sendMessage(QJsonObject message, QTcpSocket *activeSocket);
	void loginUser(QJsonObject &data, QTcpSocket *activeSocket);
	void registerUser(QJsonObject &data, QTcpSocket *activeSocket);
	void cancelUser(QJsonObject &data, QTcpSocket *activeSocket);
	void refreshFileList(QJsonObject &data, QTcpSocket *activeSocket);
	void updateUserPropic(QJsonObject &data, QTcpSocket *activeSocket);
	void updateUserPassword(QJsonObject &data, QTcpSocket *activeSocket);
	void logoutUser(QJsonObject &data, QTcpSocket *activeSocket);
	void getActiveUsers(QJsonObject &data, QTcpSocket *activeSocket);
	void getProfilePicture(QJsonObject &data, QTcpSocket *activeSocket);
	void createFile(QJsonObject &data, QTcpSocket *activeSocket);
	void addOpenedFile(QJsonObject &data, QTcpSocket *activeSocket);
    void addOpenedFileURI(QJsonObject &data, QTcpSocket *activeSocket);
	void removeOpenedFile(QJsonObject &data, QTcpSocket *activeSocket);
	void deleteExistingFile(QJsonObject &data, QTcpSocket *activeSocket);
	void generateURI(QJsonObject &data, QTcpSocket *activeSocket);
	void insertText(QJsonObject &data, QTcpSocket *activeSocket);
    void deleteText(QJsonObject &data, QTcpSocket *activeSocket);
	void modifyCharFormat(QJsonObject &data, QTcpSocket *activeSocket);
	void modifyBlockFormat(QJsonObject &data, QTcpSocket *activeSocket);
	void printActiveUsers();
	void saveFile(QString filename, QString header, QTcpSocket *activeSocket);
	
private slots:
	void sessionOpened();
	void getConnectedSocket();
	void processUserRequest();
	void handleDisconnection();
	
// Da cancellare
private:
	void printOpenFiles();
	void debugSymbols();
	void debugSymbol(Symbol &sym);
};

#endif //SERVER_SERVER_H