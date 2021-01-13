
#ifndef CLIENT_URIWINDOW_H
#define CLIENT_URIWINDOW_H

#include <QtWidgets>
#include "Client.h"

QT_BEGIN_NAMESPACE
namespace Ui { class URIWindow; }
QT_END_NAMESPACE

class URIWindow: public QDialog {
    Q_OBJECT

private:
    QSharedPointer<Ui::URIWindow> ui;
    Client *client;

public:
    explicit URIWindow(QWidget *parent = nullptr, Client *client = nullptr, QString uri = "");

private:
    void adjustGraphics(QString uri);
    void createConnections();
};


#endif //CLIENT_URIWINDOW_H
