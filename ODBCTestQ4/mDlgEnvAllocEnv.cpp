/****************************************************************************
** Meta object code from reading C++ file 'DlgEnvAllocEnv.h'
**
** Created
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "DlgEnvAllocEnv.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DlgEnvAllocEnv.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DlgEnvAllocEnv[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x09,
      21,   15,   15,   15, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_DlgEnvAllocEnv[] = {
    "DlgEnvAllocEnv\0\0Ok()\0handle_clkd()\0"
};

const QMetaObject DlgEnvAllocEnv::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DlgEnvAllocEnv,
      qt_meta_data_DlgEnvAllocEnv, 0 }
};

const QMetaObject *DlgEnvAllocEnv::metaObject() const
{
    return &staticMetaObject;
}

void *DlgEnvAllocEnv::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DlgEnvAllocEnv))
        return static_cast<void*>(const_cast< DlgEnvAllocEnv*>(this));
    return QDialog::qt_metacast(_clname);
}

int DlgEnvAllocEnv::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: Ok(); break;
        case 1: handle_clkd(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
