/****************************************************************************
** Meta object code from reading C++ file 'pre_map.h'
**
** Created: Fri Jun 3 22:09:18 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../pre_map.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pre_map.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_pre_map[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x08,
      34,    8,    8,    8, 0x08,
      59,    8,    8,    8, 0x08,
      83,    8,    8,    8, 0x08,
      98,    8,    8,    8, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_pre_map[] = {
    "pre_map\0\0on_actionSrc_triggered()\0"
    "on_actionDst_triggered()\0"
    "on_pushButton_clicked()\0display_time()\0"
    "display_msg()\0"
};

void pre_map::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        pre_map *_t = static_cast<pre_map *>(_o);
        switch (_id) {
        case 0: _t->on_actionSrc_triggered(); break;
        case 1: _t->on_actionDst_triggered(); break;
        case 2: _t->on_pushButton_clicked(); break;
        case 3: _t->display_time(); break;
        case 4: _t->display_msg(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData pre_map::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject pre_map::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_pre_map,
      qt_meta_data_pre_map, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &pre_map::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *pre_map::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *pre_map::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_pre_map))
        return static_cast<void*>(const_cast< pre_map*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int pre_map::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
