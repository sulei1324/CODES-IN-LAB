/****************************************************************************
** Meta object code from reading C++ file 'qtcheckfiles.h'
**
** Created: Sat Sep 5 16:05:27 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qtcheckfiles.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtcheckfiles.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_qtCheckFiles[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x0a,
      40,   13,   13,   13, 0x0a,
      66,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_qtCheckFiles[] = {
    "qtCheckFiles\0\0get_file_address(QString)\0"
    "get_file_postfix(QString)\0find_lost_serials()\0"
};

void qtCheckFiles::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        qtCheckFiles *_t = static_cast<qtCheckFiles *>(_o);
        switch (_id) {
        case 0: _t->get_file_address((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->get_file_postfix((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->find_lost_serials(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData qtCheckFiles::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject qtCheckFiles::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_qtCheckFiles,
      qt_meta_data_qtCheckFiles, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &qtCheckFiles::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *qtCheckFiles::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *qtCheckFiles::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_qtCheckFiles))
        return static_cast<void*>(const_cast< qtCheckFiles*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int qtCheckFiles::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
