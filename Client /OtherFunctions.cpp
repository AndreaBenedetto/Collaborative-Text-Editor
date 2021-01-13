
#include <QtCore>
#include <regex>
#include "OtherFunctions.h"

// Per il login
bool sendJSonMessage(Client* client, QString header, QString username, QString password, QString name, QString surname, QJsonValue propic, QString newpassword, int editorId, QString color, QString fileName, QString uri, QString filenameToCheck) {
	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_0);
	
	QJsonObject message;
	message["header"] = header;
	if (!username.isEmpty()) {
		message["username"] = username;
	}
	if (!password.isEmpty()) {
		message["password"] = password;
	}
	if (!name.isEmpty()) {
		message["name"] = name;
	}
	if (!surname.isEmpty()) {
		message["surname"] = surname;
	}
	if (!propic.isNull()) {
		message["propic"] = propic;
	}
	if (!newpassword.isEmpty()) {
		message["newpassword"] = newpassword;
	}
	if (editorId != -1) {
		message["editorid"] = editorId;
	}
	if (!color.isEmpty()) {
		message["color"] = color;
	}
	if (!fileName.isEmpty()) {
		message["filename"] = fileName;
	}
    if (!uri.isEmpty()) {
        message["uri"] = uri;
    }
    if (!filenameToCheck.isEmpty()) {
        message["filenametocheck"] = filenameToCheck;
    }
	
	out << QJsonDocument(message).toJson();
	
	if (!client->getTcpSocket()->write(block)) {
		return false;
	}
	client->getTcpSocket()->flush();
	return true;
}

bool checkPasswordFormat(QString password) {
	bool uppercase;
	bool lowercase;
	bool space;
	
	QRegularExpression uppercaseRegex {"[A-Z]+"};
	QRegularExpression lowercaseRegex {"[a-z]+"};
	QRegularExpression spaceRegex {"[ ]+"};
	
	if (password.length() < 4 || password.length() > 16) {
		return false;
	}

	uppercase = uppercaseRegex.match(password).hasMatch();
	lowercase = lowercaseRegex.match(password).hasMatch();
	space = spaceRegex.match(password).hasMatch();
	
	if (space) {
		return false;
	}
	
	if (uppercase & lowercase) {
		return true;
	}
	
	return false;
}

bool checkUsernameFormat(QString username) {
	bool space;
	QRegularExpression spaceRegex {"[ ]+"};
	if (username.length() < 4 || username.length() > 16) {
		return false;
	}
	space = spaceRegex.match(username).hasMatch();
	
	if (space) {
		return false;
	}
	
	return true;
}

QJsonValue jsonValFromPixmap(const QPixmap &p) {
	QBuffer buffer;
	buffer.open(QIODevice::WriteOnly);
	p.save(&buffer, "PNG");
	auto const encoded = buffer.data().toBase64();
	return {QLatin1String(encoded)};
}

QPixmap pixmapFrom(const QJsonValue &val) {
	auto const encoded = val.toString().toLatin1();
	QPixmap p;
	p.loadFromData(QByteArray::fromBase64(encoded), "PNG");
	return p;
}

void deactivateWindow(QWidget *window) {
    window->setEnabled(false);
    QApplication::setOverrideCursor(Qt::WaitCursor);
}

void reactivateWindow(QWidget *window) {
    window->setEnabled(true);
    QApplication::restoreOverrideCursor();
}

void pressPasswordButton(QLineEdit *lineEdit, QToolButton *button) {
	button->setIcon(QIcon(iconsPath + "myicons-eye-off.png"));
	lineEdit->setEchoMode(QLineEdit::Normal);
}

void releasePasswordButton(QLineEdit *lineEdit, QToolButton *button) {
	button->setIcon(QIcon(iconsPath + "myicons-eye-on.png"));
	lineEdit->setEchoMode(QLineEdit::Password);
}

void correctUsername(QString username, QPushButton *button) {
	if (username.isEmpty()) {
		button->setIcon(QIcon());
	} else {
		if (!checkUsernameFormat(username)) {
			button->setIcon(QIcon(iconsPath + "myicons-cancel.png"));
		} else {
			button->setIcon(QIcon(iconsPath + "myicons-tick.png"));
		}
	}
}

void correctPassword(QString password, QPushButton *button) {
	if (password.isEmpty()) {
		button->setIcon(QIcon());
	} else {
		if (!checkPasswordFormat(password)) {
			button->setIcon(QIcon(iconsPath + "myicons-cancel.png"));
		} else {
			button->setIcon(QIcon(iconsPath + "myicons-tick.png"));
		}
	}
}

int createMessageBox(QWidget *parent, QMessageBox::Icon icon, QString message, QMessageBox::StandardButtons buttons) {
    QMessageBox msgBox(parent);
    msgBox.setIcon(icon);
    msgBox.setWindowTitle(titleClient);
    msgBox.setText(message);
    msgBox.setStandardButtons(buttons);
    QFont font(applicationFontFamily);
    font.setPointSize(applicationFontSize);
    msgBox.setFont(font);
    QLinearGradient linearGrad(QPointF(parent->geometry().width(), parent->geometry().height()), QPointF(0, 0));
    linearGrad.setColorAt(0, QColor(0, 133, 255, 255));
    linearGrad.setColorAt(1, QColor(241, 255, 253, 255));
    linearGrad.setSpread(QGradient::ReflectSpread);
    QBrush brush(linearGrad);
    QPalette palette;
    palette.setBrush(QPalette::Window, brush);
    msgBox.setPalette(palette);
    msgBox.exec();
    return msgBox.result();
}

// Per l'editor
bool sendMultipleActionsToServer(Client *client, QString header, QString fileName, QVector<Symbol> vec) {

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);

    QByteArray serializedVector;
    QDataStream vectorStream(&serializedVector, QIODevice::ReadWrite);
    vectorStream.setVersion(QDataStream::Qt_4_0);
    vectorStream << serializeVector(vec, vectorStream);

    QJsonObject message;
    message["header"] = header;
    message["filename"] = fileName;
    message["content"] = QLatin1String(serializedVector.toBase64());

    out << QJsonDocument(message).toJson();

    if (!client->getTcpSocket()->write(block)) {
        return false;
    }
    client->getTcpSocket()->flush();
    return true;
}

QDataStream& serializeVector(QVector<Symbol> vec, QDataStream& out) {
    for (auto &sym: vec) {
        sym.serialize(out);
    }
    return out;
}

QDataStream& deserializeVector(QVector<Symbol>& vec, QDataStream& in) {
    Symbol sym;
    while (!in.atEnd()) {
        sym.deserialize(in);
        vec.push_back(sym);
    }
    return in;
}