
#ifndef CLIENT_MYTEXTEDIT_H
#define CLIENT_MYTEXTEDIT_H

#include <QTextEdit>
#include "Client.h"
#include "Symbol.h"

#define MIDDLE 3

class MyTextEdit: public QTextEdit {
	Q_OBJECT

private:
	QVector<Symbol> symbols;
	Client *client;
	int editorId;
	QString fileName;
	QMap<QString, QVector<QPair<Symbol, QTimer*>>> lastSymbolsModified;

public:
	explicit MyTextEdit(QWidget *parent = nullptr);
	void readResponse(QJsonObject jSobject);
	
private:
    void removeHighlight(Symbol symb);

public slots:
	Symbol insertSymbol(QChar character, bool singleSymbol = true);
	void deleteSymbol(QString action);
	void modifySymbolFormat(QTextCharFormat format);
	void modifyBlockFormat(QTextBlockFormat format);

signals:
    void formatChangeFinished();

private:
// Override degli eventi
	void keyPressEvent(QKeyEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void contextMenuEvent(QContextMenuEvent *event) override;
	
// Getters e setters
public:
	void setClient(Client *cl);
	void setEditorId(int id);
	void setFileName(QString filename);
	void setSymbols(QVector<Symbol> vec);
	
// Funzioni da cancellare
public slots:
	void printSymbols();

private:
	void debugSymbols();
	void debugSymbol(Symbol &sym);
};


#endif //CLIENT_MYTEXTEDIT_H
