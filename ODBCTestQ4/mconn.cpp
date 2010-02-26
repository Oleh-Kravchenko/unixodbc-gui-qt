/****************************************************************************
** Meta object code from reading C++ file 'conn.h'
**
** Created
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "conn.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'conn.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_dDisconnect[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_dDisconnect[] = {
    "dDisconnect\0\0Ok()\0"
};

const QMetaObject dDisconnect::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_dDisconnect,
      qt_meta_data_dDisconnect, 0 }
};

const QMetaObject *dDisconnect::metaObject() const
{
    return &staticMetaObject;
}

void *dDisconnect::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dDisconnect))
        return static_cast<void*>(const_cast< dDisconnect*>(this));
    return QDialog::qt_metacast(_clname);
}

int dDisconnect::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: Ok(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_dFullConnect[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x09,
      19,   13,   13,   13, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_dFullConnect[] = {
    "dFullConnect\0\0Ok()\0set_dsn(QString)\0"
};

const QMetaObject dFullConnect::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_dFullConnect,
      qt_meta_data_dFullConnect, 0 }
};

const QMetaObject *dFullConnect::metaObject() const
{
    return &staticMetaObject;
}

void *dFullConnect::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dFullConnect))
        return static_cast<void*>(const_cast< dFullConnect*>(this));
    return QDialog::qt_metacast(_clname);
}

int dFullConnect::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: Ok(); break;
        case 1: set_dsn((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
static const uint qt_meta_data_dGetInfo[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x09,
      24,    9,    9,    9, 0x09,
      38,    9,    9,    9, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_dGetInfo[] = {
    "dGetInfo\0\0target_clkd()\0strlen_clkd()\0"
    "Ok()\0"
};

const QMetaObject dGetInfo::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_dGetInfo,
      qt_meta_data_dGetInfo, 0 }
};

const QMetaObject *dGetInfo::metaObject() const
{
    return &staticMetaObject;
}

void *dGetInfo::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dGetInfo))
        return static_cast<void*>(const_cast< dGetInfo*>(this));
    return QDialog::qt_metacast(_clname);
}

int dGetInfo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: target_clkd(); break;
        case 1: strlen_clkd(); break;
        case 2: Ok(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
static const uint qt_meta_data_dGetFunctions[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x09,
      29,   14,   14,   14, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_dGetFunctions[] = {
    "dGetFunctions\0\0target_clkd()\0Ok()\0"
};

const QMetaObject dGetFunctions::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_dGetFunctions,
      qt_meta_data_dGetFunctions, 0 }
};

const QMetaObject *dGetFunctions::metaObject() const
{
    return &staticMetaObject;
}

void *dGetFunctions::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dGetFunctions))
        return static_cast<void*>(const_cast< dGetFunctions*>(this));
    return QDialog::qt_metacast(_clname);
}

int dGetFunctions::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: target_clkd(); break;
        case 1: Ok(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
static const uint qt_meta_data_dBrowseConnect[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x09,
      31,   15,   15,   15, 0x09,
      45,   15,   15,   15, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_dBrowseConnect[] = {
    "dBrowseConnect\0\0out_str_clkd()\0"
    "strlen_clkd()\0Ok()\0"
};

const QMetaObject dBrowseConnect::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_dBrowseConnect,
      qt_meta_data_dBrowseConnect, 0 }
};

const QMetaObject *dBrowseConnect::metaObject() const
{
    return &staticMetaObject;
}

void *dBrowseConnect::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dBrowseConnect))
        return static_cast<void*>(const_cast< dBrowseConnect*>(this));
    return QDialog::qt_metacast(_clname);
}

int dBrowseConnect::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: out_str_clkd(); break;
        case 1: strlen_clkd(); break;
        case 2: Ok(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
static const uint qt_meta_data_dDriverConnect[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x09,
      31,   15,   15,   15, 0x09,
      45,   15,   15,   15, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_dDriverConnect[] = {
    "dDriverConnect\0\0out_str_clkd()\0"
    "strlen_clkd()\0Ok()\0"
};

const QMetaObject dDriverConnect::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_dDriverConnect,
      qt_meta_data_dDriverConnect, 0 }
};

const QMetaObject *dDriverConnect::metaObject() const
{
    return &staticMetaObject;
}

void *dDriverConnect::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dDriverConnect))
        return static_cast<void*>(const_cast< dDriverConnect*>(this));
    return QDialog::qt_metacast(_clname);
}

int dDriverConnect::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: out_str_clkd(); break;
        case 1: strlen_clkd(); break;
        case 2: Ok(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
static const uint qt_meta_data_dNativeSQL[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x09,
      27,   11,   11,   11, 0x09,
      41,   11,   11,   11, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_dNativeSQL[] = {
    "dNativeSQL\0\0out_str_clkd()\0strlen_clkd()\0"
    "Ok()\0"
};

const QMetaObject dNativeSQL::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_dNativeSQL,
      qt_meta_data_dNativeSQL, 0 }
};

const QMetaObject *dNativeSQL::metaObject() const
{
    return &staticMetaObject;
}

void *dNativeSQL::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dNativeSQL))
        return static_cast<void*>(const_cast< dNativeSQL*>(this));
    return QDialog::qt_metacast(_clname);
}

int dNativeSQL::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: out_str_clkd(); break;
        case 1: strlen_clkd(); break;
        case 2: Ok(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
static const uint qt_meta_data_dAllocConnect[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x09,
      20,   14,   14,   14, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_dAllocConnect[] = {
    "dAllocConnect\0\0Ok()\0handle_clkd()\0"
};

const QMetaObject dAllocConnect::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_dAllocConnect,
      qt_meta_data_dAllocConnect, 0 }
};

const QMetaObject *dAllocConnect::metaObject() const
{
    return &staticMetaObject;
}

void *dAllocConnect::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dAllocConnect))
        return static_cast<void*>(const_cast< dAllocConnect*>(this));
    return QDialog::qt_metacast(_clname);
}

int dAllocConnect::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
static const uint qt_meta_data_dFreeConnect[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_dFreeConnect[] = {
    "dFreeConnect\0\0Ok()\0"
};

const QMetaObject dFreeConnect::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_dFreeConnect,
      qt_meta_data_dFreeConnect, 0 }
};

const QMetaObject *dFreeConnect::metaObject() const
{
    return &staticMetaObject;
}

void *dFreeConnect::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dFreeConnect))
        return static_cast<void*>(const_cast< dFreeConnect*>(this));
    return QDialog::qt_metacast(_clname);
}

int dFreeConnect::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: Ok(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
