
#include "Symbol.h"

// Metodi pubblici
Symbol::Symbol(): character(), usernameCreator(), fractionalPosition(), charFormat(), blockFormat() {}

Symbol::Symbol(QChar character, QString usernameCreator, QVector<int> fractionalPosition, QTextCharFormat charFormat, QTextBlockFormat blockFormat): character(character), usernameCreator(usernameCreator), fractionalPosition(fractionalPosition), charFormat(charFormat), blockFormat(blockFormat) {}

Symbol &Symbol::operator=(const Symbol &source) {
	character = source.character;
	usernameCreator = source.usernameCreator;
	fractionalPosition = source.fractionalPosition;
	charFormat = source.charFormat;
	blockFormat = source.blockFormat;
    return *this;
}

QDataStream& Symbol::serialize(QDataStream &out) {
    out << character;
    out << usernameCreator;
    out << fractionalPosition;
    out << charFormat;
    out << blockFormat;
    return out;
}

QDataStream& Symbol::deserialize(QDataStream &in) {
    in >> character;
    in >> usernameCreator;
    in >> fractionalPosition;
    in >> charFormat;
    in >> blockFormat;
    return in;
}

// Getters e setters
QVector<int> Symbol::getFractionalPosition() const {
	return fractionalPosition;
}

QChar Symbol::getCharacter() const {
	return character;
}

QTextCharFormat Symbol::getCharFormat() const {
	return charFormat;
}

void Symbol::setCharFormat(QTextCharFormat format) {
	charFormat = format;
}

QTextBlockFormat Symbol::getBlockFormat() const {
	return blockFormat;
}

void Symbol::setBlockFormat(QTextBlockFormat format) {
	blockFormat = format;
}

QString Symbol::getUsernameCreator() const {
	return usernameCreator;
}