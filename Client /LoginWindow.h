
#ifndef CLIENT_LOGINWINDOW_H
#define CLIENT_LOGINWINDOW_H

#include <QtWidgets>
#include <memory>
#include "RegistrationWindow.h"
#include "CancellationWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class LoginWindow; }
class Client;
QT_END_NAMESPACE

class LoginWindow: public QDialog {
	Q_OBJECT

private:
    QSharedPointer<Ui::LoginWindow> ui;
    QSharedPointer<QStatusBar> statusBar;
	QToolButton *passwordButton = nullptr;
	QAction *hidePassword = nullptr;
	
	Client *client;
    QSharedPointer<RegistrationWindow> regWin;
    QSharedPointer<CancellationWindow> cancWin;
	
public:
	explicit LoginWindow(QWidget *parent = nullptr, Client *client = nullptr);
	
private:
	void adjustGraphics();
	void createConnections();

private slots:
	void enableLoginButton();
	void requestLogin();
	void openRegistrationWindow();
	void openCancellationWindow();
	void closeEvent(QCloseEvent *event) override;
	void reject() override;
	
// Getters e setters
public:
    QSharedPointer<RegistrationWindow> getRegWin();
    QSharedPointer<CancellationWindow> getCancWin();
    QSharedPointer<QStatusBar> getStatusBar();
	void readResponse(QJsonObject jSobject);
};


#endif //CLIENT_LOGINWINDOW_H
