
#include "User.h"

User::User(QString username): username(username) {}

const QString &User::getUsername() const {
	return username;
}

void User::setUsername(const QString &username) {
	this->username = username;
}

bool User::operator==(const User &rhs) const {
	return username == rhs.username;
}

bool User::operator<(const User &rhs) const {
	return username < rhs.username;
}
