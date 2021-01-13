
#ifndef CLIENT_USER_H
#define CLIENT_USER_H

#include <QtCore>
#include <QtGui>

class User {
private:
	QString username;
	QPixmap propic;
	QString name;
	QString surname;
	
public:
	User(QString username, QPixmap propic, QString name, QString surname);
	
	// Getters e setters
	const QString &getUsername() const;
	const QPixmap &getPropic() const;
	const QString &getName() const;
	const QString &getSurname() const;
	void setUsername(const QString &username);
	void setPropic(const QPixmap &propic);
	void setName(const QString &name);
	void setSurname(const QString &surname);
};


#endif //CLIENT_USER_H
