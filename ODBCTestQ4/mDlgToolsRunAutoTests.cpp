/****************************************************************************
** Meta object code from reading C++ file 'DlgToolsRunAutoTests.h'
**
** Created
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "DlgToolsRunAutoTests.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DlgToolsRunAutoTests.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DlgToolsRunAutoTests[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      22,   21,   21,   21, 0x09,
      27,   21,   21,   21, 0x09,
      33,   21,   21,   21, 0x09,
      49,   21,   21,   21, 0x09,
      68,   21,   21,   21, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_DlgToolsRunAutoTests[] = {
    "DlgToolsRunAutoTests\0\0Ok()\0Log()\0"
    "LogChanged(int)\0CursorChanged(int)\0"
    "TestsChanged()\0"
};

const QMetaObject DlgToolsRunAutoTests::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DlgToolsRunAutoTests,
      qt_meta_data_DlgToolsRunAutoTests, 0 }
};

const QMetaObject *DlgToolsRunAutoTests::metaObject() const
{
    return &staticMetaObject;
}

void *DlgToolsRunAutoTests::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DlgToolsRunAutoTests))
        return static_cast<void*>(const_cast< DlgToolsRunAutoTests*>(this));
    return QDialog::qt_metacast(_clname);
}

int DlgToolsRunAutoTests::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: Ok(); break;
        case 1: Log(); break;
        case 2: LogChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: CursorChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: TestsChanged(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
