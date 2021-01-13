
#ifndef CLIENT_REGISTRATIONWINDOW_H
#define CLIENT_REGISTRATIONWINDOW_H

#include <QtCore>
#include <QtWidgets>
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui { class RegistrationWindow; }
class Client;
QT_END_NAMESPACE

class RegistrationWindow: public QDialog {
	Q_OBJECT

private:
    QSharedPointer<Ui::RegistrationWindow> ui;
    QSharedPointer<QStatusBar> statusBar;
	QToolButton *passwordButton = nullptr;
	QAction *hidePassword = nullptr;
	QToolButton *repeatPasswordButton = nullptr;
	QAction *hideRepeatPassword = nullptr;
	
	Client *client;

public:
	explicit RegistrationWindow(QWidget *parent = nullptr, Client *client = nullptr, QString username = QString(""));
	void readResponse(QJsonObject jSobject);

private:
	void adjustGraphics(QString &username);
	void createConnections();

private slots:
	void enableRegisterButton();
	void uploadProfilePicture();
	void deleteProfilePicture();
	void requestRegistration();
};


#endif //CLIENT_REGISTRATIONWINDOW_H
