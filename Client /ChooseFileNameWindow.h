
#ifndef CLIENT_CHOOSEFILENAMEWINDOW_H
#define CLIENT_CHOOSEFILENAMEWINDOW_H

#include <QtWidgets>
#include <memory>
#include "Client.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ChooseFileNameWindow; }
QT_END_NAMESPACE

class ChooseFileNameWindow: public QDialog {
	Q_OBJECT
	
private:
    QSharedPointer<Ui::ChooseFileNameWindow> ui;
    QSharedPointer<QStatusBar> statusBar;
	
	Client *client;
	
	QString filename;
	
public:
	explicit ChooseFileNameWindow(QWidget *parent = nullptr, Client *client = nullptr, QString filename = "");
	void readResponse(QJsonObject jSobject);

private:
	void adjustGraphics();
	void createConnections();
	
private slots:
	void enableButton();
	void checkFileName();
};


#endif //CLIENT_CHOOSEFILENAMEWINDOW_H
