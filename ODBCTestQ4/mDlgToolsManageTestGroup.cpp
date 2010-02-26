/****************************************************************************
** Meta object code from reading C++ file 'DlgToolsManageTestGroup.h'
**
** Created
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "DlgToolsManageTestGroup.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DlgToolsManageTestGroup.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DlgToolsManageTestGroup[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      31,   25,   24,   24, 0x09,
      50,   46,   24,   24, 0x09,
      69,   24,   24,   24, 0x09,
      74,   24,   24,   24, 0x09,
      80,   24,   24,   24, 0x09,
      89,   24,   24,   24, 0x09,
      95,   24,   24,   24, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_DlgToolsManageTestGroup[] = {
    "DlgToolsManageTestGroup\0\0index\0"
    "Activated(int)\0str\0Activated(QString)\0"
    "Ok()\0Add()\0Remove()\0New()\0Delete()\0"
};

const QMetaObject DlgToolsManageTestGroup::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DlgToolsManageTestGroup,
      qt_meta_data_DlgToolsManageTestGroup, 0 }
};

const QMetaObject *DlgToolsManageTestGroup::metaObject() const
{
    return &staticMetaObject;
}

void *DlgToolsManageTestGroup::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DlgToolsManageTestGroup))
        return static_cast<void*>(const_cast< DlgToolsManageTestGroup*>(this));
    return QDialog::qt_metacast(_clname);
}

int DlgToolsManageTestGroup::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: Activated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: Activated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: Ok(); break;
        case 3: Add(); break;
        case 4: Remove(); break;
        case 5: New(); break;
        case 6: Delete(); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
