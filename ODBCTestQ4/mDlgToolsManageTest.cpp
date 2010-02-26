/****************************************************************************
** Meta object code from reading C++ file 'DlgToolsManageTest.h'
**
** Created
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "DlgToolsManageTest.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DlgToolsManageTest.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DlgToolsManageTest[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x09,
      25,   19,   19,   19, 0x09,
      37,   19,   19,   19, 0x09,
      55,   49,   19,   19, 0x09,
      74,   70,   19,   19, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_DlgToolsManageTest[] = {
    "DlgToolsManageTest\0\0Ok()\0NewSource()\0"
    "DelSource()\0index\0Activated(int)\0str\0"
    "Activated(QString)\0"
};

const QMetaObject DlgToolsManageTest::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DlgToolsManageTest,
      qt_meta_data_DlgToolsManageTest, 0 }
};

const QMetaObject *DlgToolsManageTest::metaObject() const
{
    return &staticMetaObject;
}

void *DlgToolsManageTest::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DlgToolsManageTest))
        return static_cast<void*>(const_cast< DlgToolsManageTest*>(this));
    return QDialog::qt_metacast(_clname);
}

int DlgToolsManageTest::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: Ok(); break;
        case 1: NewSource(); break;
        case 2: DelSource(); break;
        case 3: Activated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: Activated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
