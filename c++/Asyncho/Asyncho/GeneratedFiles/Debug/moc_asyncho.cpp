/****************************************************************************
** Meta object code from reading C++ file 'asyncho.h'
**
** Created: Mon Jul 18 14:57:58 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../asyncho.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'asyncho.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Asyncho[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,    9,    8,    8, 0x05,
      38,    9,    8,    8, 0x05,

 // slots: signature, parameters, type, tag, flags
      61,    9,    8,    8, 0x0a,
      81,    9,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Asyncho[] = {
    "Asyncho\0\0workType\0needImages(QString)\0"
    "readCompleted(QString)\0readImages(QString)\0"
    "doWork(QString)\0"
};

void Asyncho::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Asyncho *_t = static_cast<Asyncho *>(_o);
        switch (_id) {
        case 0: _t->needImages((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->readCompleted((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->readImages((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->doWork((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Asyncho::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Asyncho::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Asyncho,
      qt_meta_data_Asyncho, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Asyncho::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Asyncho::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Asyncho::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Asyncho))
        return static_cast<void*>(const_cast< Asyncho*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Asyncho::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void Asyncho::needImages(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Asyncho::readCompleted(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
