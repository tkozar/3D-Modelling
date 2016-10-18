#include "gl_viewer.h"
#include <cmath>
#include <sstream>
#include <fstream>
#include <iostream>
#include <QTextStream>
#include <QFile>

/****************/
/* GL FUNCTIONS */
/****************/

GLViewer::GLViewer(QWidget *parent) : QGLWidget(parent)
{
  // Mouse/Keyboard event tracking
  setMouseTracking(true);
  setFocusPolicy(Qt::StrongFocus);

  // Mouse setup
  this->setCursor(Qt::CrossCursor);

  // Setup camera
  camPosition.push_back(8.0); camPosition.push_back(5.0); camPosition.push_back(8.0);
  camRotation.push_back(M_PI + M_PI / 4.0); camRotation.push_back(- M_PI / 6.0); // 45 degree, 30 degree
  forwardVec.push_back(0.0); forwardVec.push_back(0.0); forwardVec.push_back(0.0);
  rightVec.push_back(0.0); rightVec.push_back(0.0); rightVec.push_back(0.0);
  upVec.push_back(0.0); upVec.push_back(0.0); upVec.push_back(0.0);
  rotateSpeed = 50.0;
  moveSpeed = 50.0;
}

GLViewer::~GLViewer()
{
  // Empty
}

void GLViewer::initializeGL()
{
  glClearColor(0.8, 0.8, 0.8, 0.0);
  glShadeModel(GL_FLAT);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glClearDepth(1.0);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  //glEnable(GL_LIGHT1);
  glEnable(GL_NORMALIZE);

  // Ambient light
  float ambientColor[] = {0.2, 0.2, 0.2, 1.0};
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

  // Add positioned light
  float posLightColor[] = {0.8, 0.8, 0.8, 1.0}; // Diffuse color
  float posLightSpecular[] = {1.0, 1.0, 1.0, 1.0}; // Specular color
  float posLightPosition[] = {25, 50.0, 25, 1.0}; // Fourth float dictates that this is a positioned light
  glLightfv(GL_LIGHT0, GL_DIFFUSE, posLightColor);
  //glLightfv(GL_LIGHT0, GL_SPECULAR, posLightSpecular);
  glLightfv(GL_LIGHT0, GL_POSITION,  posLightPosition);

  /*
  // Add directed light
  float dirLightColor[] = {0.5, 0.2, 0.2, 1.0};
  float dirLightPosition[] = {25.0, 50.0, -25.0, 0.0}; // Fourth float dictates that this light is a directed light
  glLightfv(GL_LIGHT1, GL_DIFFUSE, dirLightColor);
  glLightfv(GL_LIGHT1, GL_POSITION, dirLightPosition);
  */

  glEnable(GL_COLOR_MATERIAL);
  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
  glMaterialfv(GL_FRONT, GL_SPECULAR, posLightSpecular);
  glMateriali(GL_FRONT, GL_SHININESS, 128);
}

void GLViewer::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Get depth buffer higher??
  glLoadIdentity();


  gluLookAt(camPosition[0], camPosition[1], camPosition[2], camPosition[0] + forwardVec[0], camPosition[1] + forwardVec[1], camPosition[2] + forwardVec[2], upVec[0], upVec[1], upVec[2]);

  // Render floor grid
  glColor3f(0.4, 0.4, 0.4);
  for (double i = -5.0; i <= 5.0; i++)
  {
    glNormal3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(i, 0.0, 5.0);
    glVertex3f(i, 0.0, -5.0);
    glEnd();
    glBegin(GL_LINES);
    glVertex3f(5.0, 0.0, i);
    glVertex3f(-5.0, 0.0, i);
    glEnd();
  }

  // Render objects
  for (unsigned int i = 0; i < objects.size(); i++)
  {
    glPushMatrix(); // Save matrix before transformations

    // Translate, rotate, scale
    glTranslated(translates[i][0], translates[i][1], translates[i][2]);
    glRotated(rotations[i][0], 1.0, 0.0, 0.0);
    glRotated(rotations[i][1], 0.0, 1.0, 0.0);
    glRotated(rotations[i][2], 0.0, 0.0, 1.0);
    glScaled(scales[i][0], scales[i][1], scales[i][2]);

    switch (objects[i])
    {
    // Plane
    case 0:
      glColor3f(colors[i][0], colors[i][1], colors[i][2]);
      glBegin(GL_POLYGON);
      glNormal3f(0.0, 1.0, 0.0); // Normals used for lighting
      glVertex3f(0.5, 0.0, -0.5);
      glVertex3f(0.5, 0.0, 0.5);
      glVertex3f(-0.5, 0.0, 0.5);
      glVertex3f(-0.5, 0.0, -0.5);
      glEnd();
      break;

    // Cube
    case 1:
      glColor3f(colors[i][0], colors[i][1], colors[i][2]);
      // Front
      glNormal3f(0.0, 0.0, -1.0);
      glBegin(GL_POLYGON);
      glVertex3f(0.5, -0.5, -0.5);
      glVertex3f(0.5, 0.5, -0.5);
      glVertex3f(-0.5, 0.5, -0.5);
      glVertex3f(-0.5, -0.5, -0.5);
      glEnd();
      // Back
      glNormal3f(0.0, 0.0, 1.0);
      glBegin(GL_POLYGON);
      glVertex3f(0.5, -0.5, 0.5);
      glVertex3f(0.5, 0.5, 0.5);
      glVertex3f(-0.5, 0.5, 0.5);
      glVertex3f(-0.5, -0.5, 0.5);
      glEnd();
      // Right
      glNormal3f(1.0, 0.0, 0.0);
      glBegin(GL_POLYGON);
      glVertex3f(0.5, -0.5, -0.5);
      glVertex3f(0.5, 0.5, -0.5);
      glVertex3f(0.5, 0.5, 0.5);
      glVertex3f(0.5, -0.5, 0.5);
      glEnd();
      // Left
      glNormal3f(-1.0, 0.0, 0.0);
      glBegin(GL_POLYGON);
      glVertex3f(-0.5, -0.5, 0.5);
      glVertex3f(-0.5, 0.5, 0.5);
      glVertex3f(-0.5, 0.5, -0.5);
      glVertex3f(-0.5, -0.5, -0.5);
      glEnd();
      //Top
      glBegin(GL_POLYGON);
      glNormal3f(0.0, 1.0, 0.0);
      glVertex3f(0.5, 0.5, 0.5);
      glVertex3f(0.5, 0.5, -0.5);
      glVertex3f(-0.5, 0.5, -0.5);
      glVertex3f(-0.5, 0.5, 0.5);
      glEnd();
      // Bottom
      glNormal3f(0.0, -1.0, 0.0);
      glBegin(GL_POLYGON);
      glVertex3f(0.5, -0.5, -0.5);
      glVertex3f(0.5, -0.5, 0.5);
      glVertex3f(-0.5, -0.5, 0.5);
      glVertex3f(-0.5, -0.5, -0.5);
      glEnd();
      break;

    // Sphere
    case 2:
      glColor3f(colors[i][0], colors[i][1], colors[i][2]);
      gluSphere(gluNewQuadric(), 0.5, 16, 16);
      break;

    // Cone
    case 3:
      glColor3f(colors[i][0], colors[i][1], colors[i][2]);
      glTranslated(0.0, 0.0, -0.5);
      gluCylinder(gluNewQuadric(), 0.5, 0.0, 1.0, 16, 16);
      glTranslated(0.0, 0.0, 0.5);

      // Bottom
      glNormal3f(0.0, 0.0, -1.0);
      glTranslated(0.0, 0.0, -0.5);
      glBegin(GL_TRIANGLE_FAN);
      for (int j = 0; j < 16; j++)
      {
        glVertex2f(0 + (0.5 * cos(j * 2.0 * M_PI / 16)), 0 + (0.5 * sin(j * 2.0 * M_PI / 16)));
      }
      glEnd();
      glTranslated(0.0, 0.0, 0.5);
      break;

    // Cylinder
    case 4:
      glColor3f(colors[i][0], colors[i][1], colors[i][2]);
      // Sides
      glTranslated(0.0, 0.0, -0.5);
      gluCylinder(gluNewQuadric(), 0.5, 0.5, 1.0, 16, 16);
      glTranslated(0.0, 0.0, 0.5);

      // Top
      glNormal3f(0.0, 0.0, 1.0);
      glTranslated(0.0, 0.0, 0.5);
      glBegin(GL_TRIANGLE_FAN);
      for (int j = 0; j < 16; j++)
      {
        glVertex2f(0 + (0.5 * cos(j * 2.0 * M_PI / 16)), 0 + (0.5 * sin(j * 2.0 * M_PI / 16)));
      }
      glEnd();
      glTranslated(0.0, 0.0, -0.5);

      // Bottom
      glNormal3f(0.0, 0.0, -1.0);
      glTranslated(0.0, 0.0, -0.5);
      glBegin(GL_TRIANGLE_FAN);
      for (int j = 0; j < 16; j++)
      {
        glVertex2f(0 + (0.5 * cos(j * 2.0 * M_PI / 16)), 0 + (0.5 * sin(j * 2.0 * M_PI / 16)));
      }
      glEnd();
      glTranslated(0.0, 0.0, 0.5);
      break;

    case 5:
      glColor3f(colors[i][0], colors[i][1], colors[i][2]);
      // Bottom
      glNormal3f(0.0, -1.0, 0.0);
      glBegin(GL_POLYGON);
      glVertex3f(0.5, -0.5, -0.5);
      glVertex3f(0.5, -0.5, 0.5);
      glVertex3f(-0.5, -0.5, 0.5);
      glVertex3f(-0.5, -0.5, -0.5);
      glEnd();
      // First Triangle
      glNormal3f(0.5, 1.0, 0.0);
      glBegin(GL_POLYGON);
      glVertex3f(0.5, -0.5, -0.5);
      glVertex3f(0.5, -0.5, 0.5);
      glVertex3f(0.0, 0.5, 0.0);
      glEnd();
      // Second Triangle
      glNormal3f(0.0, 1.0, 0.5);
      glBegin(GL_POLYGON);
      glVertex3f(0.5, -0.5, 0.5);
      glVertex3f(-0.5, -0.5, 0.5);
      glVertex3f(0.0, 0.5, 0.0);
      glEnd();
      // Third Triangle
      glNormal3f(-0.5, 1.0, 0.0);
      glBegin(GL_POLYGON);
      glVertex3f(-0.5, -0.5, 0.5);
      glVertex3f(-0.5, -0.5, -0.5);
      glVertex3f(0.0, 0.5, 0.0);
      glEnd();
      // Fourth Triangle
      glNormal3f(0.0, 1.0, -0.5);
      glBegin(GL_POLYGON);
      glVertex3f(0.5, -0.5, -0.5);
      glVertex3f(-0.5, -0.5, -0.5);
      glVertex3f(0.0, 0.5, 0.0);
      glEnd();
      break;


    case 6:
      glColor3f(colors[i][0], colors[i][1], colors[i][2]);
      // Bottom
      glBegin(GL_POLYGON);
      glNormal3f(0.0, -1.0, 0.0);
      glVertex3f(0.5, -0.5, -0.5);
      glVertex3f(0.5, -0.5, 0.5);
      glVertex3f(-0.5, -0.5, 0.5);
      glVertex3f(-0.5, -0.5, -0.5);
      glEnd();

      // Right
      glBegin(GL_POLYGON);
      glNormal3f(1.0, 0.0, 0.0);
      glVertex3f(0.5, -0.5, -0.5);
      glVertex3f(0.5, 0.5, -0.5);
      glVertex3f(0.5, 0.5, 0.5);
      glVertex3f(0.5, -0.5, 0.5);
      glEnd();

      // Slant
      glNormal3f(-1.0, 1.0, 0.0);
      glBegin(GL_POLYGON);
      glVertex3f(0.5, 0.5, -0.5);
      glVertex3f(0.5, 0.5, 0.5);
      glVertex3f(-0.5, -0.5, 0.5);
      glVertex3f(-0.5, -0.5, -0.5);
      glEnd();

      // Left Triangle
      glNormal3f(0.0, 0.0, 1.0);
      glBegin(GL_POLYGON);
      glVertex3f(0.5, -0.5, 0.5);
      glVertex3f(0.5, 0.5, 0.5);
      glVertex3f(-0.5, -0.5, 0.5);
      glEnd();

      // Right Triangle
      glNormal3f(0.0, 0.0, -1.0);
      glBegin(GL_TRIANGLES);
      glVertex3f(0.5, -0.5, -0.5);
      glVertex3f(0.5, 0.5, -0.5);
      glVertex3f(-0.5, -0.5, -0.5);
      glEnd();
      break;

    default:
      break;
    }

    glPopMatrix(); // Get old matrix bac (before transformations)
  }
}

void GLViewer::resizeGL(int width, int height)
{
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45, (GLdouble)width / (GLdouble)height, 0.01, 100.0); // GLU is old and doesn't work on some systems
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  updateCameraRotation();
}

/******************/
/* INPUT HANDLING */
/******************/

void GLViewer::mousePressEvent(QMouseEvent *event)
{
  // Mouse press event
  this->setCursor(Qt::BlankCursor);

  QPoint localCenter = QPoint(width() / 2.0, height() / 2.0);
  QPoint globalCenter = mapToGlobal(localCenter);
  QCursor::setPos(globalCenter);
  lastPos = localCenter;

}

void GLViewer::mouseMoveEvent(QMouseEvent *event)
{
  emit changeCoords(event->x(), event->y());

  double dx = GLdouble(event->x() - lastPos.x()) / width();
  double dy = GLdouble(event->y() - lastPos.y()) / height();

  if ((event->buttons() & Qt::RightButton) && (event->buttons() & Qt::LeftButton))
  {
    // Forward/Backwards
    camPosition[0] -= forwardVec[0] * moveSpeed * dy;
    camPosition[1] -= forwardVec[1] * moveSpeed * dy;
    camPosition[2] -= forwardVec[2] * moveSpeed * dy;

    QPoint localCenter = QPoint(width() / 2.0, height() / 2.0);
    QPoint globalCenter = mapToGlobal(localCenter);
    QCursor::setPos(globalCenter);
    lastPos = localCenter;
  }

  else if (event->buttons() & Qt::RightButton)
  {

    // Make sure rotation is always between 0 and 360.0 degrees
    camRotation[0] -= rotateSpeed * (dx * M_PI / 180.0);
    if (camRotation[0] < 0.0)
      camRotation[0] += (2 * M_PI);
    else if (camRotation[0] > (2 * M_PI))
      camRotation[0] -= (2 * M_PI);

    camRotation[1] -= rotateSpeed * (dy * M_PI / 180.0);
    if (camRotation[1] < 0.0)
      camRotation[1] += (2 * M_PI);
    else if (camRotation[1] > (2 * M_PI))
      camRotation[1] -= (2 * M_PI);

    updateCameraRotation();

    QPoint localCenter = QPoint(width() / 2.0, height() / 2.0);
    QPoint globalCenter = mapToGlobal(localCenter);
    QCursor::setPos(globalCenter);
    lastPos = localCenter;
  }

  else if (event->buttons() & Qt::LeftButton)
  {
    // Right/Left
    camPosition[0] += rightVec[0] * moveSpeed * dx;
    camPosition[1] += rightVec[1] * moveSpeed * dx;
    camPosition[2] += rightVec[2] * moveSpeed * dx;

    // Up/Down
    camPosition[0] -= upVec[0] * moveSpeed * dy;
    camPosition[1] -= upVec[1] * moveSpeed * dy;
    camPosition[2] -= upVec[2] * moveSpeed * dy;

    QPoint localCenter = QPoint(width() / 2.0, height() / 2.0);
    QPoint globalCenter = mapToGlobal(localCenter);
    QCursor::setPos(globalCenter);
    lastPos = localCenter;
  }

  updateGL();
}

void GLViewer::mouseReleaseEvent(QMouseEvent *event)
{
  // Mouse released event
  this->setCursor(Qt::CrossCursor);
}

/*******************/
/* OBJECT CREATION */
/*******************/

void GLViewer::createPlane()
{
  // Push object properties to respective vectors
  objects.push_back(0);
  std::vector<double> zeroVector(3, 0.0);
  translates.push_back(zeroVector);
  rotations.push_back(zeroVector);
  std::vector<double> oneVector(3, 1.0);
  scales.push_back(oneVector);
  std::vector<double> colorVector(3, 0.8);
  colors.push_back(colorVector);

  // Add to object list
  emit addToList("Plane");

  updateGL();
}

void GLViewer::createCube()
{
  // Push object properties to respective vectors
  objects.push_back(1);
  std::vector<double> zeroVector(3, 0.0);
  translates.push_back(zeroVector);
  rotations.push_back(zeroVector);
  std::vector<double> oneVector(3, 1.0);
  scales.push_back(oneVector);
  std::vector<double> colorVector(3, 0.8);
  colors.push_back(colorVector);

  // Add to object list
  emit addToList("Cube");

  updateGL();
}

void GLViewer::createSphere()
{
  // Push object properties to respective vectors
  objects.push_back(2);
  std::vector<double> zeroVector(3, 0.0);
  translates.push_back(zeroVector);
  rotations.push_back(zeroVector);
  std::vector<double> oneVector(3, 1.0);
  scales.push_back(oneVector);
  std::vector<double> colorVector(3, 0.8);
  colors.push_back(colorVector);

  // Add to object list
  emit addToList("Sphere");

  updateGL();
}

void GLViewer::createCone()
{
  // Push object properties to respective vectors
  objects.push_back(3);
  std::vector<double> zeroVector(3, 0.0);
  translates.push_back(zeroVector);
  rotations.push_back(zeroVector);
  std::vector<double> oneVector(3, 1.0);
  scales.push_back(oneVector);
  std::vector<double> colorVector(3, 0.8);
  colors.push_back(colorVector);

  // Add to object list
  emit addToList("Cone");

  updateGL();
}

void GLViewer::createCylinder()
{
  // Push object properties to respective vectors
  objects.push_back(4);
  std::vector<double> zeroVector(3, 0.0);
  translates.push_back(zeroVector);
  rotations.push_back(zeroVector);
  std::vector<double> oneVector(3, 1.0);
  scales.push_back(oneVector);
  std::vector<double> colorVector(3, 0.8);
  colors.push_back(colorVector);

  // Add to object list
  emit addToList("Cylinder");

  updateGL();
}

void GLViewer::createPyramid()
{
  // Push object properties to respective vectors
  objects.push_back(5);
  std::vector<double> zeroVector(3, 0.0);
  translates.push_back(zeroVector);
  rotations.push_back(zeroVector);
  std::vector<double> oneVector(3, 1.0);
  scales.push_back(oneVector);
  std::vector<double> colorVector(3, 0.8);
  colors.push_back(colorVector);

  // Add to object list
  emit addToList("Pyramid");

  updateGL();
}

void GLViewer::createWedge()
{
  // Push object properties to respective vectors
  objects.push_back(6);
  std::vector<double> zeroVector(3, 0.0);
  translates.push_back(zeroVector);
  rotations.push_back(zeroVector);
  std::vector<double> oneVector(3, 1.0);
  scales.push_back(oneVector);
  std::vector<double> colorVector(3, 0.8);
  colors.push_back(colorVector);

  // Add to object list
  emit addToList("Wedge");

  updateGL();
}

/*****************/
/* SIGNALS/SLOTS */
/*****************/

void GLViewer::removeObject(int index)
{
  //qDebug() << "\nIndex: " << index;
  if (index > -1)
  {
    objects.erase(objects.begin() + index);
    translates.erase(translates.begin() + index);
    rotations.erase(rotations.begin() + index);
    scales.erase(scales.begin() + index);
    colors.erase(colors.begin() + index);

    updateGL();
  }
}

//Translate Function
void GLViewer::receiveTranslation(int index, double x, double y, double z)
{
  if (index > -1)
  {
    translates[index][0] = x;
    translates[index][1] = y;
    translates[index][2] = z;
    //qDebug() << "Update Translation: " << index << x << y << z;

    updateGL();
  }
}

//Rotation Function
void GLViewer::receiveRotation(int index, double x, double y, double z)
{
  if (index > -1)
  {
    rotations[index][0] = x;
    rotations[index][1] = y;
    rotations[index][2] = z;
    //qDebug() << "Update Rotation: " << index << x << y << z;

    updateGL();
  }
}

//Scale Function
void GLViewer::receiveScale(int index, double x, double y, double z)
{
  if (index > -1)
  {
    scales[index][0] = x;
    scales[index][1] = y;
    scales[index][2] = z;
    //qDebug() << "Update Scale: " << index << x << y << z;

    updateGL();
  }
}

void GLViewer::receiveColor(int index, double r, double g, double b)
{
  if (index > -1)
  {
    colors[index][0] = r;
    colors[index][1] = g;
    colors[index][2] = b;
    //qDebug() << "Update Color: " << index << r << g << b;

    updateGL();
  }
}

void GLViewer::answerInfo(int index)
{
  if (index > -1)
  {
    std::vector<double> info;
    info.push_back(translates[index][0]);
    info.push_back(translates[index][1]);
    info.push_back(translates[index][2]);
    info.push_back(rotations[index][0]);
    info.push_back(rotations[index][1]);
    info.push_back(rotations[index][2]);
    info.push_back(scales[index][0]);
    info.push_back(scales[index][1]);
    info.push_back(scales[index][2]);
    info.push_back(colors[index][0]);
    info.push_back(colors[index][1]);
    info.push_back(colors[index][2]);
    emit sendInfo(info);
    //qDebug() << "Info: " << info[0] << info[1] << info[2] << info[3] << info[4] << info[5] << info[6] << info[7] << info[8];
  }
  //qDebug() << "\nIndex: " << index;
  //qDebug() << "Translations: " << translates.size();
  //qDebug() << "Rotations: " << rotations.size();
  //qDebug() << "Scales: " << scales.size();
  //qDebug() << "Color: " << colors.size();
}

void GLViewer::updateCameraRotation()
{
  double horizontalAngle = camRotation[0];
  double verticalAngle = camRotation[1];

  // Compute forward vector
  forwardVec[0] = (cos(verticalAngle) * sin(horizontalAngle));
  forwardVec[1] = sin(verticalAngle);
  forwardVec[2] = cos(verticalAngle) * cos(horizontalAngle);

  // Compute right vector
  rightVec[0] = sin(horizontalAngle - M_PI / 2.0);
  rightVec[2] = cos(horizontalAngle - M_PI / 2.0);

  // Compute up vector using cross product
  upVec[0] = rightVec[1] * forwardVec[2] - rightVec[2] * forwardVec[1];
  upVec[1] = rightVec[2] * forwardVec[0] - rightVec[0] * forwardVec[2];
  upVec[2] = rightVec[0] * forwardVec[1] - rightVec[1] * forwardVec[0];

  //qDebug() << "ForwardVec: " << forwardVec[0] << forwardVec[1] << forwardVec[2];
  //qDebug() << "RightVec: " << rightVec[0] << rightVec[1] << rightVec[2];
  //qDebug() << "UpVec: " << upVec[0] << upVec[1] << upVec[2];
}

// Save scene to .vox file
void GLViewer::saveFile(QString fileName)
{
  QFile outFile(fileName);
  if (outFile.open(QIODevice::ReadWrite))
  {
    QTextStream outStream(&outFile);

    for (int i = 0; i < objects.size(); i++)
      outStream << objects[i] << ',';
    outStream << endl;

    for (int j = 0; j < translates.size(); j++)
    {
      for (int i = 0; i < translates[j].size(); i++)
        outStream << translates[j][i] << ',';
      outStream << ';';
    }
    outStream << endl;

    for (int j = 0; j < rotations.size(); j++)
    {
      for (int i = 0; i < rotations[j].size(); i++)
        outStream << rotations[j][i] << ',';
      outStream << ';';
    }
    outStream << endl;

    for (int j = 0; j < scales.size(); j++)
    {
      for (int i = 0; i < scales[j].size(); i++)
        outStream << scales[j][i] << ',';
      outStream << ';';
    }
    outStream << endl;

    for (int j = 0; j < colors.size(); j++)
    {
      for (int i = 0; i < colors[j].size(); i++)
        outStream << colors[j][i] << ',';
      outStream << ';';
    }
    outStream.flush();
  }
  outFile.close();
}

// Read scene from vox file
void GLViewer::loadFile(QString fileName)
{
  QFile inFile(fileName);
  if (inFile.open(QIODevice::ReadWrite))
  {
    //qDebug() << "Input file opened";
    QTextStream inStream(&inFile);
    int lineCount = 0;
    while (!inStream.atEnd() && lineCount < 5)
    {
      QString line = inStream.readLine();
      QStringList elements = line.split(";");

      // Check for line type
      // 0 = objects, 1 = translates, 2 = rotates, 3 = scales, 4 = colors
      switch (lineCount)
      {
      // OBJECTS
      case 0: {
        //qDebug() << "Objects: case";
        QStringList numbers = line.split(",");
        for (int i = 0; i < numbers.size() - 1; i++)
        {
          //qDebug() << "Objects: i loop";
          objects.push_back(numbers.at(i).toInt());
          emit addToList();
        }
        lineCount++;
        break;
      }

      // TRANSLATES
      case 1:
        //qDebug() << "Translation: case";
        for (int i = 0; i < elements.size() - 1; i++)
        {
          //qDebug() << "Translation: i loop";
          std::vector<double> tempVector;
          tempVector.push_back(0.0); tempVector.push_back(0.0); tempVector.push_back(0.0);
          translates.push_back(tempVector);
          QStringList numbers = elements.at(i).split(",");
          for (int j = 0; j < numbers.size() - 1; j++)
          {
            //qDebug() << "Translation: j loop";
            translates[i][j] = numbers.at(j).toDouble();
          }
        }
        lineCount++;
        break;
        
        // ROTATIONS
        case 2:
        //qDebug() << "Rotation: case";
        for (int i = 0; i < elements.size() - 1; i++)
        {
          //qDebug() << "Rotation: i loop";
          std::vector<double> tempVector;
          tempVector.push_back(0.0); tempVector.push_back(0.0); tempVector.push_back(0.0);
          rotations.push_back(tempVector);
          QStringList numbers = elements.at(i).split(",");
          for (int j = 0; j < numbers.size() - 1; j++)
          {
            //qDebug() << "Rotation: j loop";
            rotations[i][j] = numbers.at(j).toDouble();
          }
        }
        lineCount++;
        break;

        // SCALES
        case 3:
        //qDebug() << "Scale: case";
        for (int i = 0; i < elements.size() - 1; i++)
        {
          //qDebug() << "Scale: i loop";
          std::vector<double> tempVector;
          tempVector.push_back(0.0); tempVector.push_back(0.0); tempVector.push_back(0.0);
          scales.push_back(tempVector);
          QStringList numbers = elements.at(i).split(",");
          for (int j = 0; j < numbers.size() - 1; j++)
          {
            //qDebug() << "Scale: j loop";
            scales[i][j] = numbers.at(j).toDouble();
          }
        }
        lineCount++;
        break;

        // COLORS
        case 4:
        //qDebug() << "Color: case";
        for (int i = 0; i < elements.size() - 1; i++)
        {
          //qDebug() << "Color: i loop";
          std::vector<double> tempVector;
          tempVector.push_back(0.0); tempVector.push_back(0.0); tempVector.push_back(0.0);
          colors.push_back(tempVector);
          QStringList numbers = elements.at(i).split(",");
          for (int j = 0; j < numbers.size() - 1; j++)
          {
            //qDebug() << "Color: j loop";
            colors[i][j] = numbers.at(j).toDouble();
          }
        }
        lineCount++;
        break;

        // DEFAULT
        default:
          break;
      }
    }
  }
  inFile.close();
  updateGL();
  //printInfo();
}

void GLViewer::printInfo()
{
  qDebug() << "\nObjects: ";
  for (int i = 0; i < objects.size(); i++)
    qDebug() << objects[i] << ",";

  qDebug() << "\nTranslation: ";
  for (int i = 0; i < translates.size(); i++)
  {
    for (int j = 0; j < translates[i].size(); j++)
      qDebug() << translates[i][j] << ",";
    qDebug() << ";";
  }

  qDebug() << "\nRotation: ";
  for (int i = 0; i < rotations.size(); i++)
  {
    for (int j = 0; j < rotations[i].size(); j++)
      qDebug() << rotations[i][j] << ",";
    qDebug() << ";";
  }

  qDebug() << "\nScale: ";
  for (int i = 0; i < scales.size(); i++)
  {
    for (int j = 0; j < scales[i].size(); j++)
      qDebug() << scales[i][j] << ",";
    qDebug() << ";";
  }

  qDebug() << "\nColor: ";
  for (int i = 0; i < colors.size(); i++)
  {
    for (int j = 0; j < colors[i].size(); j++)
      qDebug() << colors[i][j] << ",";
    qDebug() << ";";
  }
}