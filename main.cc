#include "viewer.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	Viewer *window = new Viewer;

	window->show();
	return app.exec();
}
