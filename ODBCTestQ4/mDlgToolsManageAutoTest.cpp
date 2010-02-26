/****************************************************************************
** Meta object code from reading C++ file 'DlgToolsManageAutoTest.h'
**
** Created
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "DlgToolsManageAutoTest.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DlgToolsManageAutoTest.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DlgToolsManageAutoTest[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      24,   23,   23,   23, 0x09,
      29,   23,   23,   23, 0x09,
      36,   23,   23,   23, 0x09,
      47,   42,   23,   23, 0x09,
      67,   23,   23,   23, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_DlgToolsManageAutoTest[] = {
    "DlgToolsManageAutoTest\0\0Ok()\0From()\0"
    "Add()\0name\0ListSelect(QString)\0Remove()\0"
};

const QMetaObject DlgToolsManageAutoTest::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DlgToolsManageAutoTest,
      qt_meta_data_DlgToolsManageAutoTest, 0 }
};

const QMetaObject *DlgToolsManageAutoTest::metaObject() const
{
    return &staticMetaObject;
}

void *DlgToolsManageAutoTest::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DlgToolsManageAutoTest))
        return static_cast<void*>(const_cast< DlgToolsManageAutoTest*>(this));
    return QDialog::qt_metacast(_clname);
}

int DlgToolsManageAutoTest::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: Ok(); break;
        case 1: From(); break;
        case 2: Add(); break;
        case 3: ListSelect((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: Remove(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
