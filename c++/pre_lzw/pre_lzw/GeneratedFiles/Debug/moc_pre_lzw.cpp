/****************************************************************************
** Meta object code from reading C++ file 'pre_lzw.h'
**
** Created: Sat Oct 24 16:23:32 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../pre_lzw.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pre_lzw.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_pre_lzw[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x0a,
      19,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_pre_lzw[] = {
    "pre_lzw\0\0do_work()\0enable_button()\0"
};

void pre_lzw::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        pre_lzw *_t = static_cast<pre_lzw *>(_o);
        switch (_id) {
        case 0: _t->do_work(); break;
        case 1: _t->enable_button(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData pre_lzw::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject pre_lzw::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_pre_lzw,
      qt_meta_data_pre_lzw, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &pre_lzw::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *pre_lzw::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *pre_lzw::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_pre_lzw))
        return static_cast<void*>(const_cast< pre_lzw*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int pre_lzw::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
