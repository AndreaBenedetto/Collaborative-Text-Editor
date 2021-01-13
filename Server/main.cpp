#include <QApplication>
#include "Server.h"

int main(int argc, char **argv) {
	QApplication app(argc, argv);
	QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
	QApplication::setApplicationDisplayName("PDS Server");
    QApplication::setFont(QFont("Manjari", 14));
	Server server;
	server.show();
	return app.exec();
}