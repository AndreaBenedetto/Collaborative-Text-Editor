
#include "URIWindow.h"
#include "ui_uriwindow.h"

URIWindow::URIWindow(QWidget *parent, Client *client, QString uri): QDialog(parent), client(client) {
    ui = QSharedPointer<Ui::URIWindow>::create();
    ui->setupUi(this);

    adjustGraphics(uri);
    createConnections();

    this->exec();
}

void URIWindow::adjustGraphics(QString uri) {
    ui->URIEdit->setText(uri);
}

void URIWindow::createConnections() {
    connect(ui->URIEdit, &QLineEdit::returnPressed, ui->OkButton, &QPushButton::released);
    connect(ui->OkButton, &QPushButton::released, this, &QDialog::close);
}