
#ifndef CLIENT_USERINFO_H
#define CLIENT_USERINFO_H

#include <QtWidgets>

QT_BEGIN_NAMESPACE
namespace Ui { class UserInfo; }
class Client;
QT_END_NAMESPACE

class UserInfo: public QDialog {
	Q_OBJECT

private:
    QSharedPointer<Ui::UserInfo> ui;
	
public:
	explicit UserInfo(QWidget *parent = nullptr, QString username = "", QString name = "", QString surname = "", QPixmap pixmap = QPixmap(), QString color = "transparent");
	
private:
	void adjustGraphics(QString username, QString name, QString surname, QPixmap pixmap, QString color);
};


#endif //CLIENT_USERINFO_H
