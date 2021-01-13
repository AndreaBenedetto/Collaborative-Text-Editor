
#ifndef SERVER_SYMBOL_H
#define SERVER_SYMBOL_H

#include <QtGui>

class Symbol {
private:
	QChar character;
	QString usernameCreator;
	QVector<int> fractionalPosition;
	QTextCharFormat charFormat;
	QTextBlockFormat blockFormat;

public:
	Symbol();
	Symbol(QChar character, QString usernameCreator, QVector<int> fractionalPosition, QTextCharFormat charFormat, QTextBlockFormat blockFormat);
	Symbol& operator=(const Symbol& source);
    QDataStream& serialize(QDataStream &out);
    QDataStream& deserialize(QDataStream &in);

// Getters e setters
    QVector<int> getFractionalPosition() const;
	QChar getCharacter() const;
	QTextCharFormat getCharFormat() const;
	void setCharFormat(QTextCharFormat format);
	QTextBlockFormat getBlockFormat() const;
	void setBlockFormat(QTextBlockFormat format);
	QString getUsernameCreator() const;
};

#endif //SERVER_SYMBOL_H
