
#include "Editor.h"
#include "ui_editor.h"
#include "OtherFunctions.h"
#include "UserInfo.h"

#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport>
#if QT_CONFIG(printer)
#if QT_CONFIG(printdialog)
#include <QPrintDialog>
#endif
#include <QPrinter>
#if QT_CONFIG(printpreviewdialog)
#include <QPrintPreviewDialog>
#endif
#endif
#endif

// Metodi pubblici
Editor::Editor(QWidget *parent, Client *client, QString filename, QJsonObject content): QMainWindow(parent), client(client), id(client->editorIdentifier++) {
	ui = QSharedPointer<Ui::Editor>::create();
	ui->setupUi(this);
	
	setCurrentFileName(filename);
	adjustGraphics();
    setEditorContent(content);
	initialSettings();
	adjustFormatIndicators();
	setShortcuts();
	createConnections();
	setWindowSize();
	
	this->show();
}

void Editor::readResponse(QJsonObject jSobject) {
    auto header = jSobject["header"].toString();
    auto body = jSobject["body"].toString();
	if (header == "getactiveusers") {
		if (body == "ok") {
			onlineUsersMenu->clear();
			
			QPixmap pix(16, 16);
			pix.fill(Qt::black);
			onlineUsersMenu->addAction(QIcon(pix), client->getLoggedUser()->getUsername());
			
			QJsonArray usernamesArray = jSobject["usernames"].toArray();
			QJsonArray colorsArray = jSobject["colors"].toArray();

			for (auto i = 0; i < usernamesArray.size(); i++) {
				usernameColorList.insert(usernamesArray.at(i).toString(), colorsArray.at(i).toString());
			}

			for (auto it = usernameColorList.begin(); it != usernameColorList.end(); it++) {
			    pix.fill(QColor(it.value()));
			    onlineUsersMenu->addAction(QIcon(pix), it.key());
			}
			ui->OnlineUsersButton->setMenu(onlineUsersMenu.get());
			ui->OnlineUsersButton->showMenu();
			ui->OnlineUsersButton->setMenu(nullptr);
			usernameColorList.clear();
		}
	} else if (header == "getprofilepicture") {
		if (body == "ok") {
			userInfoWin = QSharedPointer<UserInfo>::create(this, jSobject["username"].toString(), jSobject["name"].toString(), jSobject["surname"].toString(), pixmapFrom(jSobject["propic"]), jSobject["color"].toString());
		}
	} else if (header == "logouteditor") {
		if (body == "ok") {
			client->setLogWin();
			client->removeClosedFile(fileName);
			client->removeClosedEditor(this);
		}
	} else if (header == "closefile") {
		if (body == "ok") {
			client->removeClosedFile(fileName);
            reactivateWindow(this);
			client->removeClosedEditor(this);
		}
	} else if (header == "closelastfile") {
	    if (body == "ok") {
            client->setFileList(jSobject);
	        client->setChoiceWin();
            client->removeClosedFile(fileName);
            reactivateWindow(this);
            client->removeClosedEditor(this);
	    }
	} else if (header == "requesturieditor") {
        if (body == "ok") {
            reactivateWindow(this);
            uriWindow = QSharedPointer<URIWindow>::create(this, client, jSobject["uri"].toString());
        } else if (body == "filenotfound") {
            reactivateWindow(this);
            createMessageBox(this, QMessageBox::Information, "The file does not exist on the server.\nCheck again the file name or try to refresh the list.");
        } else if (body == "unauthorized") {
            reactivateWindow(this);
            createMessageBox(this, QMessageBox::Information, "You are not authorized to share this file.");
        }
	}
}

// Metodi protetti
void Editor::closeEvent(QCloseEvent* e) {
	e->ignore();
	
	auto res = createMessageBox(this, QMessageBox::Question, "Do you really want to close the document?", QMessageBox::Yes | QMessageBox::No);
	if (res == QMessageBox::Yes) {
		if (client->numberOpenEditors() == 1) {
            requestCloseLastFile();
		} else {
			requestCloseFile();
		}
	}
}

// Metodi privati
void Editor::adjustGraphics() {
	ui->textEdit->setClient(client);
	ui->textEdit->setEditorId(id);
	ui->textEdit->setFileName(fileName);
	
	QFont font;
	font.setBold(true);
	ui->actionBold->setFont(font);
	font.setBold(false);
	font.setItalic(true);
	ui->actionItalic->setFont(font);
	font.setItalic(false);
	font.setUnderline(true);
	ui->actionUnderline->setFont(font);
	
	QPixmap pix(16, 16);
	pix.fill(Qt::black);
	ui->actionColor->setIcon(pix);
	
	ui->toolBarStyle->addWidget(ui->comboFont);
	ui->toolBarStyle->addWidget(ui->comboSize);
	const QList<int> standardSizes = QFontDatabase::standardSizes();
	for (int size: standardSizes) {
		ui->comboSize->addItem(QString::number(size));
	}
	ui->comboSize->setCurrentIndex(standardSizes.indexOf(QApplication::font().pointSize()));
	
	ui->toolBarOnlineUsers->addWidget(ui->OnlineUsersButton);
	onlineUsersMenu = QSharedPointer<QMenu>::create(tr("Online users"), this);
	QFont menuFont(applicationFontFamily, applicationFontSize);
	onlineUsersMenu->setFont(menuFont);
	
	ui->toolBarOnlineUsers->addAction(ui->actionSettings);
	ui->toolBarOnlineUsers->addAction(ui->actionShare);
}

void Editor::initialSettings() {
	fontChanged(ui->textEdit->font());
	colorChanged(ui->textEdit->textColor());
	alignmentChanged(ui->textEdit->alignment());

	ui->actionCut->setEnabled(false);
	ui->actionCopy->setEnabled(false);
}

void Editor::setShortcuts() {
	ui->actionNew->setShortcut(QKeySequence::New);
	ui->actionOpen->setShortcut(QKeySequence::Open);
	ui->actionPrint->setShortcut(QKeySequence::Print);
	ui->actionExportPDF->setShortcut(Qt::CTRL + Qt::Key_D);
	ui->actionQuit->setShortcut(Qt::CTRL + Qt::Key_Q);
	ui->actionCut->setShortcut(QKeySequence::Cut);
	ui->actionCopy->setShortcut(QKeySequence::Copy);
	ui->actionPaste->setShortcut(QKeySequence::Paste);
	ui->actionBold->setShortcut(Qt::CTRL + Qt::Key_B);
	ui->actionItalic->setShortcut(Qt::CTRL + Qt::Key_I);
	ui->actionUnderline->setShortcut(Qt::CTRL + Qt::Key_U);
	ui->actionLeft->setShortcut(Qt::CTRL + Qt::Key_L);
	ui->actionCenter->setShortcut(Qt::CTRL + Qt::Key_E);
	ui->actionRight->setShortcut(Qt::CTRL + Qt::Key_R);
//	ui->actionJustify->setShortcut(Qt::CTRL + Qt::Key_J);
}

void Editor::createConnections() {
	connect(ui->textEdit, &QTextEdit::currentCharFormatChanged, this, &Editor::currentCharFormatChanged);
	connect(ui->textEdit, &QTextEdit::cursorPositionChanged, this, &Editor::cursorPositionChanged);
	connect(ui->textEdit, &MyTextEdit::formatChangeFinished, this, &Editor::adjustFormatIndicators);
	connect(ui->textEdit, &QTextEdit::copyAvailable, ui->actionCut, &QAction::setEnabled);
	connect(ui->textEdit, &QTextEdit::copyAvailable, ui->actionCopy, &QAction::setEnabled);
	connect(QApplication::clipboard(), &QClipboard::dataChanged, this, &Editor::clipboardDataChanged);
	connect(ui->comboFont, QOverload<const QString&>::of(&QComboBox::textActivated), this, &Editor::textFamily);
	connect(ui->comboSize, QOverload<const QString&>::of(&QComboBox::textActivated), this, &Editor::textSize);
	
	// Connessione QAction
	connect(ui->actionNew, &QAction::triggered, this, &Editor::fileNew);
	connect(ui->actionOpen, &QAction::triggered, this, &Editor::fileOpen);
	connect(ui->actionPrint, &QAction::triggered, this, &Editor::filePrint);
	connect(ui->actionPrintPreview, &QAction::triggered, this, &Editor::filePrintPreview);
	connect(ui->actionExportPDF, &QAction::triggered, this, &Editor::filePrintPdf);
	connect(ui->actionQuit, &QAction::triggered, this, &QWidget::close);
	connect(ui->actionCut, &QAction::triggered, this, &Editor::textCut);
	connect(ui->actionCopy, &QAction::triggered, this, &Editor::textCopy);
	connect(ui->actionPaste, &QAction::triggered, this, &Editor::textPaste);
	connect(ui->actionBold, &QAction::triggered, this, &Editor::textBold);
	connect(ui->actionItalic, &QAction::triggered, this, &Editor::textItalic);
	connect(ui->actionUnderline, &QAction::triggered, this, &Editor::textUnderline);
	connect(ui->actionLeft, &QAction::triggered, this, [this](){ textAlign(ui->actionLeft); });
	connect(ui->actionCenter, &QAction::triggered, this, [this](){ textAlign(ui->actionCenter); });
	connect(ui->actionRight, &QAction::triggered, this, [this](){ textAlign(ui->actionRight); });
//	connect(ui->actionJustify, &QAction::triggered, this, [this](){ textAlign(ui->actionJustify); });
	connect(ui->actionColor, &QAction::triggered, this, &Editor::textColor);
	connect(ui->OnlineUsersButton, &QPushButton::released, this, &Editor::requestOnlineUsers);
	connect(onlineUsersMenu.get(), &QMenu::triggered, this, &Editor::openUserInfo);
	connect(ui->actionSettings, &QAction::triggered, this, &Editor::openUserSettings);
    connect(ui->actionShare, &QAction::triggered, this, &Editor::requestURI);
}

void Editor::setWindowSize() {
	QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
	const QByteArray geometry = settings.value("geometry", QByteArray()).toByteArray();
	const QRect availableGeometry = QApplication::desktop()->availableGeometry(this);
	resize(availableGeometry.width() / 1.2, availableGeometry.height() / 1.2);
//	resize(availableGeometry.width() / 4, availableGeometry.height() / 4);
	move((availableGeometry.width() - width()) / 2,(availableGeometry.height() - height()) / 2);
}

void Editor::setEditorContent(QJsonValue content) {
    auto data = QByteArray::fromBase64(content["content"].toString().toLatin1());
    QDataStream in(data);
    in.setVersion(QDataStream::Qt_4_0);

    QVector<Symbol> vec;
    deserializeVector(vec, in);
    getTextEdit()->setSymbols(QVector<Symbol> (vec.begin(), vec.end()));
}

void Editor::setCurrentFileName(const QString &fileName) {
	this->fileName = fileName;
	
	QString shownName;
	if (fileName.isEmpty()) {
		shownName = "untitled";
	} else {
		shownName = QFileInfo(fileName).fileName();
	}
	
	setWindowTitle(tr("%1 - %2").arg(shownName, QCoreApplication::applicationName()));
}

void Editor::mergeFormatOnWordOrSelection(const QTextCharFormat &format) {
	QTextCursor cursor = ui->textEdit->textCursor();
	cursor.mergeCharFormat(format);
	ui->textEdit->mergeCurrentCharFormat(format);
	
	ui->textEdit->modifySymbolFormat(format);
}

void Editor::fontChanged(const QFont &f) {
	ui->comboFont->setCurrentIndex(ui->comboFont->findText(QFontInfo(f).family()));
	ui->comboSize->setCurrentIndex(ui->comboSize->findText(QString::number(f.pointSize())));
	ui->actionBold->setChecked(f.bold());
	ui->actionItalic->setChecked(f.italic());
	ui->actionUnderline->setChecked(f.underline());
}

void Editor::colorChanged(const QColor &c) {
	QPixmap pix(16, 16);
	pix.fill(c);
	ui->actionColor->setIcon(pix);
}

void Editor::alignmentChanged(Qt::Alignment a) {
	if (a & Qt::AlignLeft) {
		ui->actionLeft->setChecked(true);
		ui->actionCenter->setChecked(false);
		ui->actionRight->setChecked(false);
//		ui->actionJustify->setChecked(false);
	} else if (a & Qt::AlignHCenter) {
		ui->actionLeft->setChecked(false);
		ui->actionCenter->setChecked(true);
		ui->actionRight->setChecked(false);
//		ui->actionJustify->setChecked(false);
	} else if (a & Qt::AlignRight) {
		ui->actionLeft->setChecked(false);
		ui->actionCenter->setChecked(false);
		ui->actionRight->setChecked(true);
//		ui->actionJustify->setChecked(false);
//	} else if (a & Qt::AlignJustify) {
//		ui->actionLeft->setChecked(false);
//		ui->actionCenter->setChecked(false);
//		ui->actionRight->setChecked(false);
//		ui->actionJustify->setChecked(!ui->actionJustify->isChecked());
	}
}

// Slots privati
void Editor::fileOpen() {
	openFileWin = QSharedPointer<OpenFileWindow>::create(this, client, fileName);
}

void Editor::filePrint() {
#if QT_CONFIG(printdialog)
	QPrinter printer(QPrinter::HighResolution);
	auto dlg = new  QPrintDialog(&printer, this);
	if (ui->textEdit->textCursor().hasSelection()) {
		dlg->addEnabledOption(QAbstractPrintDialog::PrintSelection);
	}
	dlg->setWindowTitle(tr("Print Document"));
	if (dlg->exec() == QDialog::Accepted) {
		ui->textEdit->print(&printer);
	}
	delete dlg;
#endif
}

void Editor::filePrintPreview() {
#if QT_CONFIG(printpreviewdialog)
	QPrinter printer(QPrinter::HighResolution);
	QPrintPreviewDialog preview(&printer, this);
	connect(&preview, &QPrintPreviewDialog::paintRequested, this, &Editor::printPreview);
	preview.exec();
#endif
}

void Editor::printPreview(QPrinter *printer) {
#ifdef  QT_NO_PRINTER
	Q_UNUSED(printer);
#else
	ui->textEdit->print(printer);
#endif
}

void Editor::filePrintPdf() {
#ifndef QT_NO_PRINTER
	QFileDialog fileDialog(this, tr("Export PDF"));
	fileDialog.setAcceptMode(QFileDialog::AcceptSave);
	fileDialog.setMimeTypeFilters(QStringList("application/pdf"));
	fileDialog.setDefaultSuffix("pdf");
	if (fileDialog.exec() != QDialog::Accepted) {
		return;
	}
	QString fileName = fileDialog.selectedFiles().first();
	QPrinter printer(QPrinter::HighResolution);
	printer.setOutputFormat(QPrinter::PdfFormat);
	printer.setOutputFileName(fileName);
	ui->textEdit->document()->print(&printer);
#endif
}

void Editor::textCut() {
	ui->textEdit->deleteSymbol("cut");
	ui->textEdit->QTextEdit::cut();
}

void Editor::textCopy() {
	ui->textEdit->QTextEdit::copy();
}

void Editor::textPaste() {
	auto pasteLength = QApplication::clipboard()->mimeData()->text().length();
	auto cursor = ui->textEdit->textCursor();
	
	ui->textEdit->QTextEdit::paste();
	
	cursor.setPosition(cursor.position() - pasteLength, QTextCursor::KeepAnchor);
	QString word = cursor.selectedText();
	cursor.clearSelection();
	ui->textEdit->setTextCursor(cursor);
	for (auto i = 0; i < pasteLength; i++) {
		ui->textEdit->insertSymbol(word.at(i));
		cursor.movePosition(QTextCursor::NextCharacter);
		ui->textEdit->setTextCursor(cursor);
	}
}

void Editor::textBold() {
	QTextCharFormat fmt;
	if (ui->actionBold->isChecked()) {
		fmt.setFontWeight(QFont::Bold);
	} else {
		fmt.setFontWeight(QFont::Normal);
	}
	mergeFormatOnWordOrSelection(fmt);
}

void Editor::textUnderline() {
	QTextCharFormat fmt;
	fmt.setFontUnderline(ui->actionUnderline->isChecked());
	mergeFormatOnWordOrSelection(fmt);
}

void Editor::textItalic() {
	QTextCharFormat fmt;
	fmt.setFontItalic(ui->actionItalic->isChecked());
	mergeFormatOnWordOrSelection(fmt);
}

void Editor::textFamily(const QString &f) {
	QTextCharFormat fmt;
	fmt.setFontFamily(f);
    ui->textEdit->setFocus(Qt::MouseFocusReason);
	mergeFormatOnWordOrSelection(fmt);
}

void Editor::textSize(const QString &p) {
	int currentIndex = ui->comboSize->currentIndex();
	for (auto &ch: p) {
		if (!ch.isDigit()) {
			ui->comboSize->removeItem(ui->comboSize->count() - 1);
			ui->comboSize->setCurrentIndex(currentIndex);
			return;
		}
	}
	qreal pointSize = p.toFloat();
	if (p.toFloat() > 0) {
		QTextCharFormat fmt;
		fmt.setFontPointSize(pointSize);
		ui->textEdit->setFocus(Qt::MouseFocusReason);
		mergeFormatOnWordOrSelection(fmt);
	}
}

void Editor::textColor() {
	QColor col = QColorDialog::getColor(ui->textEdit->textColor(), this);
	if (!col.isValid()) {
		return;
	}
	QTextCharFormat fmt;
	fmt.setForeground(col);
	mergeFormatOnWordOrSelection(fmt);
	colorChanged(col);
}

void Editor::textAlign(QAction *a) {
	if (a == ui->actionLeft) {
		ui->textEdit->setAlignment(Qt::AlignLeft | Qt::AlignAbsolute);
	} else if (a == ui->actionCenter) {
		ui->textEdit->setAlignment(Qt::AlignHCenter);
	} else if (a == ui->actionRight) {
		ui->textEdit->setAlignment(Qt::AlignRight | Qt::AlignAbsolute);
//	} else if (a == ui->actionJustify) {
//		ui->textEdit->setAlignment(Qt::AlignJustify);
	}
	alignmentChanged(ui->textEdit->alignment());
	
	ui->textEdit->modifyBlockFormat(ui->textEdit->textCursor().blockFormat());
}

void Editor::currentCharFormatChanged(const QTextCharFormat &format) {
	fontChanged(format.font());
	colorChanged(format.foreground().color());
}

void Editor::cursorPositionChanged() {
	alignmentChanged(ui->textEdit->alignment());
}

void Editor::adjustFormatIndicators() {
    auto charFormat = ui->textEdit->textCursor().charFormat();
    auto blockFormat = ui->textEdit->textCursor().blockFormat();

    fontChanged(charFormat.font());
    colorChanged(charFormat.foreground().color());
    alignmentChanged(blockFormat.alignment());
}

void Editor::clipboardDataChanged() {
#ifndef QT_NO_CLIPBOARD
	if (const QMimeData* md = QApplication::clipboard()->mimeData()) {
		ui->actionPaste->setEnabled(md->hasText());
	}
#endif
}

void Editor::requestOnlineUsers() {
	if (!client->checkSocket()) {
        createMessageBox(this, QMessageBox::Warning, "Connection error.");
		return;
	}
	
	if (!sendJSonMessage(client, "getactiveusers", client->getLoggedUser()->getUsername(), "", "", "", QJsonValue::Null, "", id, "", fileName)) {
        createMessageBox(this, QMessageBox::Warning, "Could not send message.\nTry again later.");
		return;
	}
	
	qDebug() << "User list requested...";
}

void Editor::openUserInfo(QAction *action) {
	if (action->text() == client->getLoggedUser()->getUsername()) {
		userInfoWin = QSharedPointer<UserInfo>::create(this, client->getLoggedUser()->getUsername(), client->getLoggedUser()->getName(), client->getLoggedUser()->getSurname(), client->getLoggedUser()->getPropic());
		return;
	}

	auto it = usernameColorList.find(action->text());
	if (it != usernameColorList.end()) {
        if (!client->checkSocket()) {
            createMessageBox(this, QMessageBox::Warning, "Connection error.");
            return;
        }

        if (!sendJSonMessage(client, "getprofilepicture", it.key(), "", "", "", QJsonValue::Null, "", id, it.value(), getFileName())) {
            createMessageBox(this, QMessageBox::Warning, "Could not send message.\nTry again later.");
            return;
        }

        qDebug() << "Profile picture requested...";
	}
}

void Editor::openUserSettings() {
	settWin = QSharedPointer<SettingsWindow>::create(this, client, fileName);
}

void Editor::requestCloseFile() {
    deactivateWindow(this);

	if (!client->checkSocket()) {
        createMessageBox(this, QMessageBox::Critical, "Connection error.");
		QApplication::quit();
	}
	
	if (!sendJSonMessage(client, "closefile", client->getLoggedUser()->getUsername(), "", "", "", QJsonValue::Null, "", id, "", fileName)) {
        createMessageBox(this, QMessageBox::Critical, "Could not send message.\nTry again later.");
		QApplication::quit();
	}
	
	qDebug() << "Closing file...";
}

void Editor::requestCloseLastFile() {
    deactivateWindow(this);

    if (!client->checkSocket()) {
        createMessageBox(this, QMessageBox::Critical, "Connection error.");
        QApplication::quit();
    }

    if (!sendJSonMessage(client, "closelastfile", client->getLoggedUser()->getUsername(), "", "", "", QJsonValue::Null, "", id, "", fileName)) {
        createMessageBox(this, QMessageBox::Critical, "Could not send message.\nTry again later.");
        QApplication::quit();
    }

    qDebug() << "Closing file...";
}

void Editor::requestLogout() {
	if (!client->checkSocket()) {
        createMessageBox(this, QMessageBox::Critical, "Connection error.");
		QApplication::quit();
	}
	
	if (!sendJSonMessage(client, "logouteditor", client->getLoggedUser()->getUsername(), "", "", "", QJsonValue::Null, "", id, "", fileName)) {
        createMessageBox(this, QMessageBox::Critical, "Could not send message.\nTry again later.");
		QApplication::quit();
	}
	
	qDebug() << "Logging out...";
}

void Editor::requestURI() {
    deactivateWindow(this);

    if (!client->checkSocket()) {
        createMessageBox(this, QMessageBox::Warning, "Connection error.");
        reactivateWindow(this);
        return;
    }

    if (!sendJSonMessage(client, "requesturieditor", client->getLoggedUser()->getUsername(), "", "", "", QJsonValue::Null, "", -1, "", fileName)) {
        createMessageBox(this, QMessageBox::Warning, "Could not send message.\nTry again later.");
        reactivateWindow(this);
        return;
    }
}

// Slots pubblici
void Editor::fileNew() {
	nameChoiceWin = QSharedPointer<ChooseFileNameWindow>::create(this, client, fileName);
}

// Getters e setters
int Editor::getId() {
	return id;
}

QString Editor::getFileName() {
	return fileName;
}

QSharedPointer<SettingsWindow> Editor::getSettWin() {
	return settWin;
}

QSharedPointer<ChooseFileNameWindow> Editor::getNameChoiceWin() {
	return nameChoiceWin;
}

QSharedPointer<OpenFileWindow> Editor::getOpenFileWin() {
	return openFileWin;
}

MyTextEdit* Editor::getTextEdit() {
	return ui->textEdit;
}