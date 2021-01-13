
#ifndef CLIENT_SETTINGSWINDOW_H
#define CLIENT_SETTINGSWINDOW_H

#include <QtCore>
#include <QtWidgets>
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui { class SettingsWindow; }
class Client;
QT_END_NAMESPACE

class SettingsWindow: public QDialog {
	Q_OBJECT

private:
    QSharedPointer<Ui::SettingsWindow> ui;
    QSharedPointer<QStatusBar> statusBar;
	QToolButton *currentPasswordButton = nullptr;
	QAction *hideCurrentPassword = nullptr;
	QToolButton *newPasswordButton = nullptr;
	QAction *hideNewPassword = nullptr;
	QToolButton *repeatNewPasswordButton = nullptr;
	QAction *hideRepeatNewPassword = nullptr;
	
	Client *client;
	
	bool imageUpdatable = false;
	QString filename;
	
public:
	explicit SettingsWindow(QWidget *parent = nullptr, Client *client = nullptr, QString filename = "");
	void readResponse(QJsonObject jSobject);

private:
	void adjustGraphics();
	void createConnections();
	
private slots:
	void uploadProfilePicture();
	void deleteProfilePicture();
	void resetProfilePicture();
	void enableButtons();
	void requestPictureUpdate();
	void requestPasswordUpdate();
};


#endif //CLIENT_SETTINGSWINDOW_H
