
#include <QtWidgets>
#include "MyTextEdit.h"
#include "OtherFunctions.h"

int counter = 0;

// Metodi pubblici
MyTextEdit::MyTextEdit(QWidget *parent): QTextEdit(parent) {
    setMouseTracking(true);
}

void MyTextEdit::readResponse(QJsonObject jSobject) {
    auto header = jSobject["header"].toString();
    auto body = jSobject["body"].toString();
    if (header == "inserttext") {
        if (body == "notexisting" | body == "error") {
            createMessageBox(this, QMessageBox::Critical, "Generic server error.\nTry again later.");
            QApplication::quit();
        } else if (body == "forward") {
            auto content = QByteArray::fromBase64(jSobject["content"].toString().toLatin1());

            QDataStream inStream(content);
            inStream.setVersion(QDataStream::Qt_4_0);

            QVector<Symbol> vec;
            deserializeVector(vec, inStream);

            bool present = false;
            for (auto j = 0; j < vec.size(); j++) {
                int position = -1;
                for (auto i = 0; i < symbols.size(); i++) {
                    if (vec.at(j).getFractionalPosition() < symbols.at(i).getFractionalPosition()) {
                        symbols.insert(symbols.begin() + i, vec.at(j));
                        position = i;
                        break;
                    } else if (vec.at(j).getFractionalPosition() == symbols.at(i).getFractionalPosition()) {
                        if (vec.at(j).getUsernameCreator() < symbols.at(i).getUsernameCreator()) {
                            symbols.insert(symbols.begin() + i, vec.at(j));
                            position = i;
                            break;
                        }
                    }
                }
                if (position == -1) {
                    symbols.push_back(vec.at(j));
                    position = symbols.size() - 1;
                }

                auto cursor = textCursor();
                setTextCursor(cursor);
                auto originalPosition = cursor.position();

                cursor.setPosition(position);
                cursor.mergeBlockFormat(vec.at(j).getBlockFormat());
                auto cfmt = vec.at(j).getCharFormat();
                cursor.insertText(vec.at(j).getCharacter(), cfmt);
                auto f = [this, vec, j]() mutable { MyTextEdit::removeHighlight(vec.at(j)); };

                auto iter = lastSymbolsModified.find(vec.at(j).getUsernameCreator());
                if (iter != lastSymbolsModified.end() && j == 0) {
                    present = true;
                    for (auto pair = iter.value().begin(); pair < iter.value().end(); pair++) {
                        auto ch = pair->first;
                        if (pair->second->remainingTime() > 0) {
                            removeHighlight(ch);
                            if (symbols.indexOf(ch) != -1) {
                                pair->second->stop();
                            }
                        }
                    }
                    iter.value().clear();
                }

                cfmt.setBackground(QBrush(QColor(jSobject["color"].toString())));
                cursor.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor);
                cursor.mergeCharFormat(cfmt);

                auto timer = new QTimer(this);
                timer->setSingleShot(true);
                connect(timer, &QTimer::timeout, this, f);
                timer->start(1000);

                if (!present) {
                    lastSymbolsModified.insert(vec.at(j).getUsernameCreator(), {qMakePair<Symbol, QTimer*> (vec.at(j), timer)});
                    present = true;
                } else {
                    iter.value().push_back(qMakePair<Symbol, QTimer*> (vec.at(j), timer));
                }

                if (position <= originalPosition) {
                    cursor.setPosition(originalPosition + 1);
                } else {
                    cursor.setPosition(originalPosition);
                }
            }
        }
    } else if (header == "deletetext") {
        if (body == "notexisting" | body == "error") {
            createMessageBox(this, QMessageBox::Critical, "Generic server error.\nTry again later.");
            QApplication::quit();
        } else if (body == "forward") {
            auto content = QByteArray::fromBase64(jSobject["content"].toString().toLatin1());
            QDataStream in(content);
            in.setVersion(QDataStream::Qt_4_0);
            QVector<Symbol> vec;
            deserializeVector(vec, in);

            for (auto &symToDelete: vec) {
                for (auto i = 0; i < symbols.size(); i++) {
                    if (symbols.at(i).getFractionalPosition() == symToDelete.getFractionalPosition() & symbols.at(i).getUsernameCreator() == symToDelete.getUsernameCreator()) {
                        symbols.erase(symbols.begin() + i);

                        auto cursor = textCursor();
                        setTextCursor(cursor);
                        auto originalPosition = cursor.position();

                        cursor.setPosition(i);
                        cursor.deleteChar();

                        if (i <= originalPosition) {
                            cursor.setPosition(originalPosition - 1);
                        } else {
                            cursor.setPosition(originalPosition);
                        }
                        break;
                    }
                }
            }
        }
    } else if (header == "modifycharformat") {
        if (body == "notexisting" | body == "error") {
            createMessageBox(this, QMessageBox::Critical, "Generic server error.\nTry again later.");
            QApplication::quit();
        } else if (body == "forward") {
            auto content = QByteArray::fromBase64(jSobject["content"].toString().toLatin1());
            QDataStream in(content);
            in.setVersion(QDataStream::Qt_4_0);
            QVector<Symbol> vec;
            deserializeVector(vec, in);

            bool present = false;
            for (auto j = 0; j < vec.size(); j++) {
                for (auto i = 0; i < symbols.size(); i++) {
                    if (symbols.at(i).getFractionalPosition() == vec.at(j).getFractionalPosition() & symbols.at(i).getUsernameCreator() == vec.at(j).getUsernameCreator()) {
                        QTextCharFormat temp = symbols.at(i).getCharFormat();
                        temp.merge(vec.at(j).getCharFormat());
                        vec.value(j).setCharFormat(temp);
                        symbols[i] = vec.at(j);

                        auto cursor = textCursor();
                        setTextCursor(cursor);
                        auto originalPosition = cursor.position();

                        auto f = [this, vec, j]() mutable { MyTextEdit::removeHighlight(vec.at(j)); };

                        cursor.setPosition(i);
                        cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor);
                        cursor.mergeCharFormat(temp);

                        auto iter = lastSymbolsModified.find(jSobject["username"].toString());
                        if (iter != lastSymbolsModified.end() && j == 0) {
                            present = true;
                            for (auto pair = iter.value().begin(); pair < iter.value().end(); pair++) {
                                auto ch = pair->first;
                                if (pair->second->remainingTime() > 0) {
                                    removeHighlight(ch);
                                    if (symbols.indexOf(ch) != -1) {
                                        pair->second->stop();
                                    }
                                }
                            }
                            iter.value().clear();
                        }

                        auto timer = new QTimer(this);
                        timer->setSingleShot(true);
                        connect(timer, &QTimer::timeout, this, f);
                        timer->start(1000);

                        if (!present) {
                            lastSymbolsModified.insert(vec.at(j).getUsernameCreator(), {qMakePair<Symbol, QTimer*> (vec.at(j), timer)});
                            present = true;
                        } else {
                            iter.value().push_back(qMakePair<Symbol, QTimer*> (vec.at(j), timer));
                        }

                        temp.setBackground(QBrush(QColor(jSobject["color"].toString())));
                        cursor.setPosition(i);
                        cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor);
                        cursor.mergeCharFormat(temp);

                        cursor.setPosition(originalPosition);
                        break;
                    }
                }
            }
            emit formatChangeFinished();
        }
    } else if (header == "modifyblockformat") {
        if (body == "notexisting" | body == "error") {
            createMessageBox(this, QMessageBox::Critical, "Generic server error.\nTry again later.");
            QApplication::quit();
        } else if (body == "forward") {
            auto content = QByteArray::fromBase64(jSobject["content"].toString().toLatin1());
            QDataStream in(content);
            in.setVersion(QDataStream::Qt_4_0);
            QVector<Symbol> vec;
            deserializeVector(vec, in);

            bool present = false;
            for (auto j = 0; j < vec.size(); j++) {
                for (auto i = 0; i < symbols.size(); i++) {
                    if (symbols.at(i).getFractionalPosition() == vec.at(j).getFractionalPosition() & symbols.at(i).getUsernameCreator() == vec.at(j).getUsernameCreator()) {
                        QTextCharFormat tempChar = symbols.at(i).getCharFormat();
                        QTextBlockFormat tempBlock = symbols.at(i).getBlockFormat();
                        tempBlock.merge(vec.at(j).getBlockFormat());
                        vec.value(j).setBlockFormat(tempBlock);
                        symbols[i] = vec.at(j);

                        auto cursor = textCursor();
                        setTextCursor(cursor);
                        auto originalPosition = cursor.position();

                        tempChar.setBackground(QBrush(QColor(jSobject["color"].toString())));
                        auto f = [this, vec, j]() mutable { MyTextEdit::removeHighlight(vec.at(j)); };

                        cursor.setPosition(i);
                        cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor);
                        cursor.mergeBlockFormat(tempBlock);

                        auto iter = lastSymbolsModified.find(jSobject["username"].toString());
                        if (iter != lastSymbolsModified.end() && j == 0) {
                            present = true;
                            for (auto pair = iter.value().begin(); pair < iter.value().end(); pair++) {
                                auto ch = pair->first;
                                if (pair->second->remainingTime() > 0) {
                                    removeHighlight(ch);
                                    if (symbols.indexOf(ch) != -1) {
                                        pair->second->stop();
                                    }
                                }
                            }
                            iter.value().clear();
                        }

                        cursor.mergeCharFormat(tempChar);

                        auto timer = new QTimer(this);
                        timer->setSingleShot(true);
                        connect(timer, &QTimer::timeout, this, f);
                        timer->start(1000);

                        if (!present) {
                            lastSymbolsModified.insert(vec.at(j).getUsernameCreator(), {qMakePair<Symbol, QTimer*> (vec.at(j), timer)});
                            present = true;
                        } else {
                            iter.value().push_back(qMakePair<Symbol, QTimer*> (vec.at(j), timer));
                        }

                        cursor.setPosition(originalPosition);
                        break;
                    }
                }
            }

            emit formatChangeFinished();
        }
    }
}

// Metodi privati
void MyTextEdit::removeHighlight(Symbol symb) {
    if (symbols.indexOf(symb) != -1) {
        QTextCursor cursor = this->textCursor();
        cursor.setPosition(symbols.indexOf(symb));
        cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor);
        QTextCharFormat fmt = cursor.charFormat();
        fmt.clearBackground();
        cursor.setCharFormat(fmt);
    }
}

// Slots pubblici
Symbol MyTextEdit::insertSymbol(QChar character, bool singleSymbol) {
    counter++;
	qDebug() << "Symbol insertion..." << counter;
	
	auto cursor = textCursor();
	auto index = cursor.position();
	auto anchor = cursor.anchor();
	auto username = client->getLoggedUser()->getUsername();
	auto charFormat = cursor.charFormat();
	auto blockFormat = cursor.blockFormat();

	charFormat.clearBackground();
	setCurrentCharFormat(charFormat);

	if (anchor < index) {
	    index = anchor;
	}
	
	Symbol insertedSymbol;
	
	if (symbols.empty()) {
		Symbol newSymbol(character, username, QVector<int>{MIDDLE}, charFormat, blockFormat);
		symbols.insert(symbols.begin(), newSymbol);
		insertedSymbol = newSymbol;
	} else if (index == symbols.size()) {
        QVector<int> vSym = symbols.at(index - 1).getFractionalPosition();
		(*(vSym.end() - 1))++;
		Symbol newSymbol(character, username, vSym, charFormat, blockFormat);
		symbols.insert(symbols.begin() + index, newSymbol);
		insertedSymbol = newSymbol;
	} else {
        QVector<int> vSym;
		bool flag = false;
		if (index != 0) {
			Symbol sym1 = symbols.at(index - 1);
			auto vec1 = sym1.getFractionalPosition();
			auto it1 = vec1.begin();
			Symbol sym2 = symbols.at(index);
			auto vec2 = sym2.getFractionalPosition();
			auto it2 = vec2.begin();
			while (!flag) {
				if (it1 == vec1.end() && it2 == vec2.end()) {
					vSym.push_back(MIDDLE);
					Symbol newSymbol(character, username, vSym, charFormat, blockFormat);
					symbols.insert(symbols.begin() + index, newSymbol);
					insertedSymbol = newSymbol;
					flag = true;
				} else if (it1 == vec1.end()) {
					if (*it2 >= 2) {
						vSym.push_back(*it2 - 1);
						if (*it2 - 1 <= 1) {
							vSym.push_back(MIDDLE);
						}
						Symbol newSymbol(character, username, vSym, charFormat, blockFormat);
						symbols.insert(symbols.begin() + index, newSymbol);
						insertedSymbol = newSymbol;
						flag = true;
					} else if (*it2 == 1) {
						vSym.push_back(0);
						vSym.push_back(MIDDLE);
						Symbol newSymbol(character, username, vSym, charFormat, blockFormat);
						symbols.insert(symbols.begin() + index, newSymbol);
						insertedSymbol = newSymbol;
						flag = true;
					} else {
						vSym.push_back(0);
						it2++;
					}
				} else if (it2 == vec2.end()) {
					vSym.push_back(*it1 + MIDDLE);
					Symbol newSymbol(character, username, vSym, charFormat, blockFormat);
					symbols.insert(symbols.begin() + index, newSymbol);
					insertedSymbol = newSymbol;
					flag = true;
				} else if (*it2 - *it1 <= 1) {
					vSym.push_back(*it1);
					it1++;
					it2++;
				} else {
					vSym.push_back(*it2 - 1);
					if (*it2 - 1 <= 1) {
						vSym.push_back(MIDDLE);
					}
					Symbol newSymbol(character, username, vSym, charFormat, blockFormat);
					symbols.insert(symbols.begin() + index, newSymbol);
					insertedSymbol = newSymbol;
					flag = true;
				}
			}
		} else {
			Symbol sym2 = symbols.at(index);
			auto vec2 = sym2.getFractionalPosition();
			auto it2 = vec2.rbegin();
            QVector<int> vInv;
			while (!flag) {
				if (*it2 != 0) {
					if (*it2 == 2) {
						vInv.push_back(MIDDLE);
					}
					vInv.push_back(*it2 - 1);
					it2++;
					while (it2 != vec2.rend()) {
						vInv.push_back(*it2);
						it2++;
					}
					for (auto itmp = vInv.rbegin(); itmp != vInv.rend(); itmp++) {
						vSym.push_back(*itmp);
					}
					Symbol newSymbol(character, username, vSym, charFormat, blockFormat);
					symbols.insert(symbols.begin() + index, newSymbol);
					insertedSymbol = newSymbol;
					flag = true;
				} else {
					it2++;
				}
			}
		}
	}

	if (singleSymbol) {
	    QVector<Symbol> vec{insertedSymbol};

        if (!client->checkSocket()) {
            createMessageBox(this, QMessageBox::Critical, "Connection error.");
            QApplication::quit();
        }

        if (!sendMultipleActionsToServer(client, "inserttext", fileName, vec)) {
            createMessageBox(this, QMessageBox::Critical, "Could not send message.\nTry again later.");
            QApplication::quit();
        }
	}

	return insertedSymbol;
}

void MyTextEdit::deleteSymbol(QString action) {
	auto cursor = textCursor();
	auto anchor = cursor.anchor();
	auto index = cursor.position();
	
	if (!cursor.hasSelection() & ((index == 0 && action == "backspace") | (index == symbols.size() && action == "delete"))) {
		return;
	}
	
	int start;
	int end;
	
	if (action == "ctrl+backspace") {
		cursor.movePosition(QTextCursor::PreviousWord);
		start = cursor.position();
		end = index;
	} else if (action == "ctrl+delete") {
		start = index;
		cursor.movePosition(QTextCursor::EndOfWord);
		cursor.movePosition(QTextCursor::NextWord);
		end = cursor.position();
	} else {
		if (anchor < index) {
			start = anchor;
			end = index;
		} else {
			start = index;
			end = anchor;
		}
	}
	
	qDebug() << "Symbol deletion...";
	
	// Bisogna mandare al server il messaggio perché se no
	// i simboli sono già stati cancellati dal vettore
	if (!client->checkSocket()) {
        createMessageBox(this, QMessageBox::Critical, "Connection error.");
		QApplication::quit();
	}

    QVector<Symbol> vec;
	if (start == end) {
		if (action == "backspace") {
		    vec.push_back(symbols.at(end - 1));
			symbols.erase(symbols.begin() + end - 1);
		} else if (action == "delete") {
		    vec.push_back(symbols.at(end));
			symbols.erase(symbols.begin() + end);
		}
	} else {
	    for (auto i = end - 1; i >= start; i--) {
	        vec.push_back(symbols.at(i));
            symbols.erase(symbols.begin() + i);
	    }
	}

    if (!sendMultipleActionsToServer(client, "deletetext", fileName, vec)) {
        createMessageBox(this, QMessageBox::Critical, "Could not send message.\nTry again later.");
        QApplication::quit();
    }
}

void MyTextEdit::modifySymbolFormat(QTextCharFormat format) {
	auto start = textCursor().selectionStart();
	auto end = textCursor().selectionEnd();
	
	if (!client->checkSocket()) {
        createMessageBox(this, QMessageBox::Critical, "Connection error.");
		QApplication::quit();
	}

    QVector<Symbol> vec;
    for (auto i = start; i < end; i++) {
        QTextCharFormat temp = symbols.at(i).getCharFormat();
        temp.merge(format);
        symbols[i].setCharFormat(temp);
        vec.push_back(symbols.at(i));
    }

    if (!sendMultipleActionsToServer(client, "modifycharformat", fileName, vec)) {
        createMessageBox(this, QMessageBox::Critical, "Could not send message.\nTry again later.");
        QApplication::quit();
    }
}

void MyTextEdit::modifyBlockFormat(QTextBlockFormat format) {
    auto cursor = textCursor();
    int start;
    int end;
    if (!cursor.hasSelection()) {
        cursor.select(QTextCursor::BlockUnderCursor);
        start = cursor.selectionStart();
        end = cursor.selectionEnd();
    } else {
        auto tempCursorStart = cursor;
        auto tempCursorEnd = cursor;
        tempCursorStart.setPosition(cursor.selectionStart());
        tempCursorEnd.setPosition(cursor.selectionEnd());
        tempCursorStart.movePosition(QTextCursor::StartOfBlock);
        tempCursorEnd.movePosition(QTextCursor::EndOfBlock);
        start = tempCursorStart.position();
        end = tempCursorEnd.position();
    }
	
	if (!client->checkSocket()) {
        createMessageBox(this, QMessageBox::Critical, "Connection error.");
		QApplication::quit();
	}

    QVector<Symbol> vec;
	for (auto i = start; i < end; i++) {
        symbols[i].setBlockFormat(format);
        vec.push_back(symbols.at(i));
	}

    if (!sendMultipleActionsToServer(client, "modifyblockformat", fileName, vec)) {
        createMessageBox(this, QMessageBox::Critical, "Could not send message.\nTry again later.");
        QApplication::quit();
    }
}

// Override degli eventi
void MyTextEdit::keyPressEvent(QKeyEvent *event) {
	auto k = event->key();
	
#ifndef QT_NO_CLIPBOARD
	if (event == QKeySequence::Cut) {
		deleteSymbol("cut");
	} else if (event == QKeySequence::Copy) {
		;
	} else if (event == QKeySequence::Paste) {
        if (textCursor().hasSelection()) {
            deleteSymbol("backspace");
        }

		auto pasteLength = QApplication::clipboard()->mimeData()->text().length();
		auto cursor = textCursor();

		QTextEdit::paste();

		cursor.setPosition(cursor.position() - pasteLength, QTextCursor::KeepAnchor);
		QString word = cursor.selectedText();
		cursor.clearSelection();
		setTextCursor(cursor);
		QVector<Symbol> vec;
		for (auto i = 0; i < pasteLength; i++) {
		    Symbol sym = insertSymbol(word.at(i), false);
			vec.push_back(sym);
			cursor.movePosition(QTextCursor::NextCharacter);
			setTextCursor(cursor);
		}

        if (!client->checkSocket()) {
            createMessageBox(this, QMessageBox::Critical, "Connection error.");
            QApplication::quit();
        }

        if (!sendMultipleActionsToServer(client, "inserttext", fileName, vec)) {
            createMessageBox(this, QMessageBox::Critical, "Could not send message.\nTry again later.");
            QApplication::quit();
        }
		return;
	}
#endif
	else if (event == QKeySequence::DeleteStartOfWord) {
		deleteSymbol("ctrl+backspace");
	} else if (event == QKeySequence::DeleteEndOfWord) {
		deleteSymbol("ctrl+delete");
	} else if (k == Qt::Key_Backspace) {
		deleteSymbol("backspace");
	} else if (k == Qt::Key_Delete) {
		deleteSymbol("delete");
	} else if ((event->modifiers() & Qt::ControlModifier) && (k != Qt::Key_Return)) {
	    ;
	} else if ((k == Qt::Key_Tab) | (k == Qt::Key_Return) | (k >= Qt::Key_Space & k <= Qt::Key_ydiaeresis)) {
		if (textCursor().hasSelection()) {
			deleteSymbol("backspace");
		}
		QChar ch;
        ch = event->text().front();
		insertSymbol(ch);
	}

    QTextEdit::keyPressEvent(event);
}

void MyTextEdit::mouseMoveEvent(QMouseEvent *event) {
    auto point = this->mapFromGlobal(QPoint(cursor().pos().x(), cursor().pos().y()));
    auto x = point.x();
    auto y = point.y();
    int index = document()->documentLayout()->hitTest(QPointF(x, y), Qt::ExactHit);
    if (index != -1) {
        QToolTip::showText(QPoint(cursor().pos().x(), cursor().pos().y()), symbols.at(index).getUsernameCreator(), this);
    } else {
        QToolTip::hideText();
    }
    QTextEdit::mouseMoveEvent(event);
}

void MyTextEdit::contextMenuEvent(QContextMenuEvent *event) {}

// Getters e setters
void MyTextEdit::setClient(Client *cl) {
	client = cl;
}

void MyTextEdit::setEditorId(int id) {
	editorId = id;
}

void MyTextEdit::setFileName(QString filename) {
	fileName = filename;
}

void MyTextEdit::setSymbols(QVector<Symbol> vec) {
    symbols = vec;
    auto cursor = textCursor();

    for (auto& sym: symbols) {
        cursor.insertText(sym.getCharacter(), sym.getCharFormat());
        cursor.mergeBlockFormat(sym.getBlockFormat());
        cursor.movePosition(QTextCursor::End);
    }
}

// Funzioni da cancellare
void MyTextEdit::printSymbols() {
	QChar character;
	QTextCharFormat charFormat;
	QTextBlockFormat blockFormat;
	auto cursor = textCursor();
	setTextCursor(cursor);
	insertPlainText("\n\n");
	for (auto &sym: symbols) {
		character = sym.getCharacter();
		charFormat = sym.getCharFormat();
		blockFormat = sym.getBlockFormat();
		setCurrentCharFormat(charFormat);
		cursor.setBlockFormat(blockFormat);
		insertPlainText(character);
	}
}

void MyTextEdit::debugSymbols() {
	for (auto &sym: symbols) {
		qDebug() << sym.getCharacter().toLatin1() << sym.getFractionalPosition() << sym.getCharFormat().fontWeight() << sym.getCharFormat().fontUnderline() << sym.getBlockFormat().alignment() << sym.getCharFormat().foreground().color();
	}
	qDebug() << "";
}

void MyTextEdit::debugSymbol(Symbol &sym) {
    qDebug() << sym.getCharacter().toLatin1() << sym.getFractionalPosition() << sym.getCharFormat().fontWeight() << sym.getCharFormat().fontUnderline() << sym.getBlockFormat().alignment() << sym.getCharFormat().foreground().color();
}