#pragma once

#include <QtCore>
#include <QtGui>
#include <QGLWidget>
#include <vector>

// Need some more includes for OSX
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#endif

class GLViewer : public QGLWidget
{

    Q_OBJECT

public:
    GLViewer(QWidget *parent = 0);
    ~GLViewer();

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void updateCameraRotation();
    void printInfo();

public slots:
    void createPlane();
    void createCube();
    void createSphere();
    void createCone();
    void createCylinder();
    void createPyramid();
    void createWedge();
    void removeObject(int index);
    void receiveTranslation(int index, double x, double y, double z);
    void receiveRotation(int index, double x, double y, double z);
    void receiveScale(int index, double x, double y, double z);
    void receiveColor(int index, double r, double g, double b);
    void answerInfo(int index);
    //void deleteObject(QListWidget *list);

    void saveFile(QString fileName);
    void loadFile(QString fileName);

signals:
    void changeCoords(double x, double y);
    void addToList(QString str);
    void removeFromList(int index);
    void sendInfo(std::vector<double> info);
    void addToList();

private:
    // Modelling variables
    std::vector<int> objects; // Holds the object types; 0 = Plane, 1 = Cube, 2 = Sphere, 3 = Cone, 4 = Cylinder
    std::vector<std::vector<double> > translates;
    std::vector<std::vector<double> > rotations;
    std::vector<std::vector<double> > scales;
    std::vector<std::vector<double> > colors;

    // Camera variables
    std::vector<double> camPosition;
    std::vector<double> camRotation;
    std::vector<double> forwardVec;
    std::vector<double> rightVec;
    std::vector<double> upVec;
    double rotateSpeed;
    double moveSpeed;
    QPoint lastPos;
};

