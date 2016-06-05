/****************************************************************************
** Meta object code from reading C++ file 'projecter.h'
**
** Created: Tue Sep 22 09:57:49 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../projecter.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'projecter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_projecter[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x08,
      24,   10,   10,   10, 0x08,
      50,   10,   10,   10, 0x08,
      78,   10,   10,   10, 0x08,
     106,   10,   10,   10, 0x08,
     134,   10,   10,   10, 0x08,
     162,   10,   10,   10, 0x08,
     190,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_projecter[] = {
    "projecter\0\0projectRun()\0"
    "lineEdit_changed(QString)\0"
    "lineEdit_2_changed(QString)\0"
    "lineEdit_3_changed(QString)\0"
    "lineEdit_4_changed(QString)\0"
    "lineEdit_5_changed(QString)\0"
    "lineEdit_6_changed(QString)\0"
    "lineEdit_7_changed(QString)\0"
};

void projecter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        projecter *_t = static_cast<projecter *>(_o);
        switch (_id) {
        case 0: _t->projectRun(); break;
        case 1: _t->lineEdit_changed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->lineEdit_2_changed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->lineEdit_3_changed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->lineEdit_4_changed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->lineEdit_5_changed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->lineEdit_6_changed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->lineEdit_7_changed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData projecter::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject projecter::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_projecter,
      qt_meta_data_projecter, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &projecter::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *projecter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *projecter::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_projecter))
        return static_cast<void*>(const_cast< projecter*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int projecter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
