
#ifndef CLIENT_FILECHOICEWINDOW_H
#define CLIENT_FILECHOICEWINDOW_H

#include "SettingsWindow.h"
#include "Editor.h"
#include "ChooseFileNameWindow.h"
#include "URIWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class FileChoiceWindow; }
class Client;
class URIWindow;
QT_END_NAMESPACE

class FileChoiceWindow: public QDialog {
	Q_OBJECT

private:
    QSharedPointer<Ui::FileChoiceWindow> ui;
	
	Client *client;
    QSharedPointer<SettingsWindow> settWin;
    QSharedPointer<ChooseFileNameWindow> nameChoiceWin;
    QSharedPointer<URIWindow> uriWindow;

public:
	explicit FileChoiceWindow(QWidget *parent = nullptr, Client *client = nullptr, bool fromRegistration = false);
	void readResponse(QJsonObject jSobject);
	
private:
	void adjustGraphics(bool fromRegistration);
	void createConnections();

private slots:
	void openNewFile();
	void openExistingFile();
	void deleteExistingFile();
	void refreshFileList();
	void requestURI();
	void insertURI();
	void openSettingsWindow();
	void requestLogout();
	void closeEvent(QCloseEvent *event) override;
	void reject() override;

// Getters e setters
public:
    QSharedPointer<SettingsWindow> getSettWin();
    QSharedPointer<ChooseFileNameWindow> getNameChoiceWin();
};


#endif //CLIENT_FILECHOICEWINDOW_H
