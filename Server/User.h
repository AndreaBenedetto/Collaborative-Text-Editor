
#ifndef SERVER_USER_H
#define SERVER_USER_H

#include <QtCore>
#include <QtGui>

class User {
private:
	QString username;

public:
	explicit User(QString username);
	const QString &getUsername() const;
	void setUsername(const QString &username);
	bool operator==(const User &rhs) const;
	bool operator<(const User &rhs) const;
};


#endif //SERVER_USER_H
