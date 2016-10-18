#pragma once

#include <QtCore>
#include <QtGui>
#include "ui_viewer.h"
#include "gl_viewer.h"

class Viewer : public QMainWindow
{

	Q_OBJECT

public:
	Viewer(QWidget *parent = 0);

public slots:
	void setCoords(double x, double y);
	void addToList(QString str);
	void addToList();
	void updateTranslation();
	void updateRotation();
	void updateScale();
	void receiveInfo(std::vector<double> info);
	void newProject();
	void saveProject();
	void loadProject();
	void removeObjectClicked();
	void colorWheel();
	void aboutInfo();
	void helpInfo();

signals:
	void sendTranslation(int index, double x, double y, double z);
	void sendRotation(int index, double x, double y, double z);
	void sendScale(int index, double x, double y, double z);
	void sendColor(int index, double r, double g, double b);
	void requestInfo(int index);
	void removeObject(int index);
	void callSave(QString fileName);
	void callLoad(QString fileName);
	void manualListUpdate(int index);

private:
	Ui::Viewer ui;
	GLViewer *glViewer;
	QColor color;

};