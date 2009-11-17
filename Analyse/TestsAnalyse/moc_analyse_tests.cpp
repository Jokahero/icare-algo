/****************************************************************************
** Meta object code from reading C++ file 'analyse_tests.h'
**
** Created: Tue Nov 17 21:16:36 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "analyse_tests.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'analyse_tests.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Analyse_tests[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x08,
      30,   14,   14,   14, 0x08,
      46,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Analyse_tests[] = {
    "Analyse_tests\0\0initTestCase()\0"
    "testGlossaire()\0cleanupTestCase()\0"
};

const QMetaObject Analyse_tests::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Analyse_tests,
      qt_meta_data_Analyse_tests, 0 }
};

const QMetaObject *Analyse_tests::metaObject() const
{
    return &staticMetaObject;
}

void *Analyse_tests::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Analyse_tests))
        return static_cast<void*>(const_cast< Analyse_tests*>(this));
    return QObject::qt_metacast(_clname);
}

int Analyse_tests::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: initTestCase(); break;
        case 1: testGlossaire(); break;
        case 2: cleanupTestCase(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
