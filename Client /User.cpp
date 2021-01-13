
#include "User.h"

// Metodi pubblici
User::User(QString username, QPixmap propic, QString name, QString surname): username(username), propic(propic), name(name), surname(surname) {}

// Getters e setters
const QString &User::getUsername() const {
	return username;
}

const QPixmap &User::getPropic() const {
	return propic;
}

const QString &User::getName() const {
	return name;
}

const QString &User::getSurname() const {
	return surname;
}

void User::setUsername(const QString &username) {
	this->username = username;
}

void User::setPropic(const QPixmap &propic) {
	this->propic = propic;
}

void User::setName(const QString &name) {
	this->name = name;
}

void User::setSurname(const QString &surname) {
	this->surname = surname;
}
