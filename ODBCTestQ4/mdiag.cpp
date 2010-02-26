/****************************************************************************
** Meta object code from reading C++ file 'diag.h'
**
** Created
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "diag.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'diag.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_dError[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x09,
      13,    7,    7,    7, 0x09,
      27,    7,    7,    7, 0x09,
      40,    7,    7,    7, 0x09,
      54,    7,    7,    7, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_dError[] = {
    "dError\0\0Ok()\0native_clkd()\0error_clkd()\0"
    "perror_clkd()\0sqlstate_clkd()\0"
};

const QMetaObject dError::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_dError,
      qt_meta_data_dError, 0 }
};

const QMetaObject *dError::metaObject() const
{
    return &staticMetaObject;
}

void *dError::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dError))
        return static_cast<void*>(const_cast< dError*>(this));
    return QDialog::qt_metacast(_clname);
}

int dError::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: Ok(); break;
        case 1: native_clkd(); break;
        case 2: error_clkd(); break;
        case 3: perror_clkd(); break;
        case 4: sqlstate_clkd(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
static const uint qt_meta_data_dGetDiagRec[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x09,
      18,   12,   12,   12, 0x09,
      32,   12,   12,   12, 0x09,
      45,   12,   12,   12, 0x09,
      59,   12,   12,   12, 0x09,
      75,   12,   12,   12, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_dGetDiagRec[] = {
    "dGetDiagRec\0\0Ok()\0native_clkd()\0"
    "error_clkd()\0perror_clkd()\0sqlstate_clkd()\0"
    "sel_handle(int)\0"
};

const QMetaObject dGetDiagRec::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_dGetDiagRec,
      qt_meta_data_dGetDiagRec, 0 }
};

const QMetaObject *dGetDiagRec::metaObject() const
{
    return &staticMetaObject;
}

void *dGetDiagRec::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dGetDiagRec))
        return static_cast<void*>(const_cast< dGetDiagRec*>(this));
    return QDialog::qt_metacast(_clname);
}

int dGetDiagRec::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: Ok(); break;
        case 1: native_clkd(); break;
        case 2: error_clkd(); break;
        case 3: perror_clkd(); break;
        case 4: sqlstate_clkd(); break;
        case 5: sel_handle((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}
static const uint qt_meta_data_dGetDiagField[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x09,
      20,   14,   14,   14, 0x09,
      36,   14,   14,   14, 0x09,
      50,   14,   14,   14, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_dGetDiagField[] = {
    "dGetDiagField\0\0Ok()\0diag_ptr_clkd()\0"
    "strlen_clkd()\0sel_handle(int)\0"
};

const QMetaObject dGetDiagField::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_dGetDiagField,
      qt_meta_data_dGetDiagField, 0 }
};

const QMetaObject *dGetDiagField::metaObject() const
{
    return &staticMetaObject;
}

void *dGetDiagField::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dGetDiagField))
        return static_cast<void*>(const_cast< dGetDiagField*>(this));
    return QDialog::qt_metacast(_clname);
}

int dGetDiagField::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: Ok(); break;
        case 1: diag_ptr_clkd(); break;
        case 2: strlen_clkd(); break;
        case 3: sel_handle((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
