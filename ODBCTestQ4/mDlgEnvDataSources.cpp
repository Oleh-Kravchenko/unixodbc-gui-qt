/****************************************************************************
** Meta object code from reading C++ file 'DlgEnvDataSources.h'
**
** Created
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "DlgEnvDataSources.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DlgEnvDataSources.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DlgEnvDataSources[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x09,
      24,   18,   18,   18, 0x09,
      38,   18,   18,   18, 0x09,
      57,   18,   18,   18, 0x09,
      69,   18,   18,   18, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_DlgEnvDataSources[] = {
    "DlgEnvDataSources\0\0Ok()\0server_clkd()\0"
    "description_clkd()\0nlp1_clkd()\0"
    "nlp2_clkd()\0"
};

const QMetaObject DlgEnvDataSources::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DlgEnvDataSources,
      qt_meta_data_DlgEnvDataSources, 0 }
};

const QMetaObject *DlgEnvDataSources::metaObject() const
{
    return &staticMetaObject;
}

void *DlgEnvDataSources::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DlgEnvDataSources))
        return static_cast<void*>(const_cast< DlgEnvDataSources*>(this));
    return QDialog::qt_metacast(_clname);
}

int DlgEnvDataSources::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: Ok(); break;
        case 1: server_clkd(); break;
        case 2: description_clkd(); break;
        case 3: nlp1_clkd(); break;
        case 4: nlp2_clkd(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
