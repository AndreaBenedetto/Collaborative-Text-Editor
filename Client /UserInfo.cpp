
#include "UserInfo.h"
#include "ui_userinfo.h"

// Metodi pubblici
UserInfo::UserInfo(QWidget *parent, QString username, QString name, QString surname, QPixmap pixmap, QString color): QDialog(parent) {
	ui = QSharedPointer<Ui::UserInfo>::create();
	ui->setupUi(this);
	
	adjustGraphics(username, name, surname, pixmap, color);

    this->show();
}

// Metodi privati
void UserInfo::adjustGraphics(QString username, QString name, QString surname, QPixmap pixmap, QString color) {
	ui->ProfilePicture->setPixmap(pixmap.scaled(96, 96, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->UsernameLabel->setStyleSheet("QLabel{background-color: " + color + "; color: black; border-radius: 10px}");
	ui->UsernameLabel->setText(username);
    ui->NameLabel->setText(name + " " + surname);
}