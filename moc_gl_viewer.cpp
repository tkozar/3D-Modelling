/****************************************************************************
** Meta object code from reading C++ file 'gl_viewer.h'
**
** Created: Wed Dec 7 11:41:58 2016
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "gl_viewer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gl_viewer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GLViewer[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   10,    9,    9, 0x05,
      46,   42,    9,    9, 0x05,
      71,   65,    9,    9, 0x05,
      96,   91,    9,    9, 0x05,
     126,    9,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
     138,    9,    9,    9, 0x0a,
     152,    9,    9,    9, 0x0a,
     165,    9,    9,    9, 0x0a,
     180,    9,    9,    9, 0x0a,
     193,    9,    9,    9, 0x0a,
     210,    9,    9,    9, 0x0a,
     226,    9,    9,    9, 0x0a,
     240,   65,    9,    9, 0x0a,
     270,  258,    9,    9, 0x0a,
     315,  258,    9,    9, 0x0a,
     357,  258,    9,    9, 0x0a,
     408,  396,    9,    9, 0x0a,
     447,   65,    9,    9, 0x0a,
     472,  463,    9,    9, 0x0a,
     490,  463,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GLViewer[] = {
    "GLViewer\0\0x,y\0changeCoords(double,double)\0"
    "str\0addToList(QString)\0index\0"
    "removeFromList(int)\0info\0"
    "sendInfo(std::vector<double>)\0addToList()\0"
    "createPlane()\0createCube()\0createSphere()\0"
    "createCone()\0createCylinder()\0"
    "createPyramid()\0createWedge()\0"
    "removeObject(int)\0index,x,y,z\0"
    "receiveTranslation(int,double,double,double)\0"
    "receiveRotation(int,double,double,double)\0"
    "receiveScale(int,double,double,double)\0"
    "index,r,g,b\0receiveColor(int,double,double,double)\0"
    "answerInfo(int)\0fileName\0saveFile(QString)\0"
    "loadFile(QString)\0"
};

const QMetaObject GLViewer::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_GLViewer,
      qt_meta_data_GLViewer, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GLViewer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GLViewer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GLViewer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GLViewer))
        return static_cast<void*>(const_cast< GLViewer*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int GLViewer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: changeCoords((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 1: addToList((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: removeFromList((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: sendInfo((*reinterpret_cast< std::vector<double>(*)>(_a[1]))); break;
        case 4: addToList(); break;
        case 5: createPlane(); break;
        case 6: createCube(); break;
        case 7: createSphere(); break;
        case 8: createCone(); break;
        case 9: createCylinder(); break;
        case 10: createPyramid(); break;
        case 11: createWedge(); break;
        case 12: removeObject((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: receiveTranslation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4]))); break;
        case 14: receiveRotation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4]))); break;
        case 15: receiveScale((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4]))); break;
        case 16: receiveColor((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4]))); break;
        case 17: answerInfo((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: saveFile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 19: loadFile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 20;
    }
    return _id;
}

// SIGNAL 0
void GLViewer::changeCoords(double _t1, double _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GLViewer::addToList(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GLViewer::removeFromList(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void GLViewer::sendInfo(std::vector<double> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void GLViewer::addToList()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}
QT_END_MOC_NAMESPACE
