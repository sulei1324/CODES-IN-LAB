/****************************************************************************
** Meta object code from reading C++ file 'qttest.h'
**
** Created: Sun May 8 13:13:34 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qttest.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qttest.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_qttest[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x05,

 // slots: signature, parameters, type, tag, flags
      26,    7,    7,    7, 0x0a,
      50,    7,    7,    7, 0x0a,
      61,    7,    7,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_qttest[] = {
    "qttest\0\0textListChanged()\0"
    "on_pushButton_clicked()\0showTime()\0"
    "showText1()\0"
};

void qttest::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        qttest *_t = static_cast<qttest *>(_o);
        switch (_id) {
        case 0: _t->textListChanged(); break;
        case 1: _t->on_pushButton_clicked(); break;
        case 2: _t->showTime(); break;
        case 3: _t->showText1(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData qttest::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject qttest::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_qttest,
      qt_meta_data_qttest, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &qttest::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *qttest::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *qttest::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_qttest))
        return static_cast<void*>(const_cast< qttest*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int qttest::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void qttest::textListChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
