
#ifndef CLIENT_OPENFILEWINDOW_H
#define CLIENT_OPENFILEWINDOW_H

#include <QtWidgets>
#include <memory>
#include "Client.h"

QT_BEGIN_NAMESPACE
namespace Ui { class OpenFileWindow; }
QT_END_NAMESPACE

class OpenFileWindow: public QDialog {
	Q_OBJECT

private:
    QSharedPointer<Ui::OpenFileWindow> ui;
	
	Client *client;
	
	QString filename;

public:
	explicit OpenFileWindow(QWidget *parent = nullptr, Client *client = nullptr, QString filename = "");
	void readResponse(QJsonObject jSobject);
	
private:
	void adjustGraphics();
	void createConnections();
	
private slots:
	void openExistingFile();
	void refreshFileList();
	void insertURI();
};


#endif //CLIENT_OPENFILEWINDOW_H
