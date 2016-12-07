/****************************************************************************
** Meta object code from reading C++ file 'viewer.h'
**
** Created: Wed Dec 7 11:41:59 2016
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "viewer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'viewer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Viewer[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,    8,    7,    7, 0x05,
      62,    8,    7,    7, 0x05,
     101,    8,    7,    7, 0x05,
     149,  137,    7,    7, 0x05,
     191,  185,    7,    7, 0x05,
     208,  185,    7,    7, 0x05,
     235,  226,    7,    7, 0x05,
     253,  226,    7,    7, 0x05,
     271,  185,    7,    7, 0x05,

 // slots: signature, parameters, type, tag, flags
     297,  293,    7,    7, 0x0a,
     326,  322,    7,    7, 0x0a,
     345,    7,    7,    7, 0x0a,
     357,    7,    7,    7, 0x0a,
     377,    7,    7,    7, 0x0a,
     394,    7,    7,    7, 0x0a,
     413,  408,    7,    7, 0x0a,
     446,    7,    7,    7, 0x0a,
     459,    7,    7,    7, 0x0a,
     473,    7,    7,    7, 0x0a,
     487,    7,    7,    7, 0x0a,
     509,    7,    7,    7, 0x0a,
     522,    7,    7,    7, 0x0a,
     534,    7,    7,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Viewer[] = {
    "Viewer\0\0index,x,y,z\0"
    "sendTranslation(int,double,double,double)\0"
    "sendRotation(int,double,double,double)\0"
    "sendScale(int,double,double,double)\0"
    "index,r,g,b\0sendColor(int,double,double,double)\0"
    "index\0requestInfo(int)\0removeObject(int)\0"
    "fileName\0callSave(QString)\0callLoad(QString)\0"
    "manualListUpdate(int)\0x,y\0"
    "setCoords(double,double)\0str\0"
    "addToList(QString)\0addToList()\0"
    "updateTranslation()\0updateRotation()\0"
    "updateScale()\0info\0receiveInfo(std::vector<double>)\0"
    "newProject()\0saveProject()\0loadProject()\0"
    "removeObjectClicked()\0colorWheel()\0"
    "aboutInfo()\0helpInfo()\0"
};

const QMetaObject Viewer::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Viewer,
      qt_meta_data_Viewer, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Viewer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Viewer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Viewer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Viewer))
        return static_cast<void*>(const_cast< Viewer*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Viewer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: sendTranslation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4]))); break;
        case 1: sendRotation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4]))); break;
        case 2: sendScale((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4]))); break;
        case 3: sendColor((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4]))); break;
        case 4: requestInfo((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: removeObject((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: callSave((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: callLoad((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: manualListUpdate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: setCoords((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 10: addToList((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: addToList(); break;
        case 12: updateTranslation(); break;
        case 13: updateRotation(); break;
        case 14: updateScale(); break;
        case 15: receiveInfo((*reinterpret_cast< std::vector<double>(*)>(_a[1]))); break;
        case 16: newProject(); break;
        case 17: saveProject(); break;
        case 18: loadProject(); break;
        case 19: removeObjectClicked(); break;
        case 20: colorWheel(); break;
        case 21: aboutInfo(); break;
        case 22: helpInfo(); break;
        default: ;
        }
        _id -= 23;
    }
    return _id;
}

// SIGNAL 0
void Viewer::sendTranslation(int _t1, double _t2, double _t3, double _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Viewer::sendRotation(int _t1, double _t2, double _t3, double _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Viewer::sendScale(int _t1, double _t2, double _t3, double _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Viewer::sendColor(int _t1, double _t2, double _t3, double _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Viewer::requestInfo(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Viewer::removeObject(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Viewer::callSave(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void Viewer::callLoad(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void Viewer::manualListUpdate(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}
QT_END_MOC_NAMESPACE
