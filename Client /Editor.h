
#ifndef EDITORUI_EDITOR_H
#define EDITORUI_EDITOR_H

#include<QMainWindow>
#include <QtWidgets>
#include <QtPrintSupport>
#include <memory>
#include "UserInfo.h"
#include "SettingsWindow.h"
#include "MyTextEdit.h"
#include "OpenFileWindow.h"
#include "URIWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Editor; }
class Client;
class ChooseFileNameWindow;
class MyTextEdit;
class OpenFileWindow;
class URIWindow;
QT_END_NAMESPACE

class Editor: public QMainWindow {
	Q_OBJECT

private:
    QSharedPointer<Ui::Editor> ui;
	QString fileName;
    QSharedPointer<QMenu> onlineUsersMenu;
	QMap<QString, QString> usernameColorList;
	int id;
	
	Client *client;

    QSharedPointer<UserInfo> userInfoWin;
    QSharedPointer<SettingsWindow> settWin;
    QSharedPointer<ChooseFileNameWindow> nameChoiceWin;
    QSharedPointer<OpenFileWindow> openFileWin;
    QSharedPointer<URIWindow> uriWindow;
	
public:
	explicit Editor(QWidget *parent = nullptr, Client *client = nullptr, QString filename = "", QJsonObject content = QJsonObject());
	void readResponse(QJsonObject jSobject);

protected:
	void closeEvent(QCloseEvent* e) override;

private:
	void adjustGraphics();
	void initialSettings();
	void setShortcuts();
	void createConnections();
	void setWindowSize();
	void setEditorContent(QJsonValue content);
	void setCurrentFileName(const QString& fileName);
	void mergeFormatOnWordOrSelection(const QTextCharFormat& format);
	void fontChanged(const QFont& f);
	void colorChanged(const QColor& c);
	void alignmentChanged(Qt::Alignment a);

private slots:
	void fileOpen();
	void filePrint();
	void filePrintPreview();
	void printPreview(QPrinter* printer);
	void filePrintPdf();
	void textCut();
	void textCopy();
	void textPaste();
	void textBold();
	void textUnderline();
	void textItalic();
	void textFamily(const QString& f);
	void textSize(const QString& p);
	void textColor();
	void textAlign(QAction* a);
	void currentCharFormatChanged(const QTextCharFormat& format);
	void cursorPositionChanged();
	void adjustFormatIndicators();
	void clipboardDataChanged();
	void requestOnlineUsers();
	void openUserInfo(QAction *action);
	void openUserSettings();
	void requestCloseFile();
	void requestCloseLastFile();
	void requestLogout();
	void requestURI();

public slots:
	void fileNew();

// Getters e setters
public:
	int getId();
	QString getFileName();
    QSharedPointer<SettingsWindow> getSettWin();
    QSharedPointer<ChooseFileNameWindow> getNameChoiceWin();
    QSharedPointer<OpenFileWindow> getOpenFileWin();
	MyTextEdit* getTextEdit();
};


#endif //EDITORUI_EDITOR_H
