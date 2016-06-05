/****************************************************************************
** Meta object code from reading C++ file 'pre_lzw_mp.h'
**
** Created: Tue Oct 27 22:33:07 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../pre_lzw_mp.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pre_lzw_mp.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_pre_lzw_mp[] = {

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
      12,   11,   11,   11, 0x0a,
      22,   11,   11,   11, 0x0a,
      38,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_pre_lzw_mp[] = {
    "pre_lzw_mp\0\0do_work()\0enable_button()\0"
    "do_lzw(QString)\0"
};

void pre_lzw_mp::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        pre_lzw_mp *_t = static_cast<pre_lzw_mp *>(_o);
        switch (_id) {
        case 0: _t->do_work(); break;
        case 1: _t->enable_button(); break;
        case 2: _t->do_lzw((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData pre_lzw_mp::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject pre_lzw_mp::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_pre_lzw_mp,
      qt_meta_data_pre_lzw_mp, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &pre_lzw_mp::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *pre_lzw_mp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *pre_lzw_mp::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_pre_lzw_mp))
        return static_cast<void*>(const_cast< pre_lzw_mp*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int pre_lzw_mp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
