

#ifndef CLIENT_CANCELLATIONWINDOW_H
#define CLIENT_CANCELLATIONWINDOW_H

#include <QtWidgets>
#include <memory>
#include "CancellationWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class CancellationWindow; }
class Client;
QT_END_NAMESPACE

class CancellationWindow: public QDialog {
Q_OBJECT

private:
    QSharedPointer<Ui::CancellationWindow> ui;
    QSharedPointer<QStatusBar> statusBar;
	QToolButton *passwordButton = nullptr;
	QAction *hidePassword = nullptr;
	
	Client *client;

public:
	explicit CancellationWindow(QWidget *parent = nullptr, Client *client = nullptr, QString username = QString(""));
	void readResponse(QJsonObject jSobject);

private:
	void adjustGraphics(QString &username);
	void createConnections();

private slots:
	void enableCancelButton();
	void requestCancellation();
};

#endif //CLIENT_CANCELLATIONWINDOW_H
