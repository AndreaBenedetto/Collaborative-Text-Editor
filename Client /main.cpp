#include <QApplication>
#include "Client.h"

int main(int argc, char **argv) {
	QApplication app(argc, argv);
	QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
	QApplication::setApplicationDisplayName("PDS Client");
	QApplication::setFont(QFont("Manjari", 14));
	Client client;
	
	return app.exec();
}
