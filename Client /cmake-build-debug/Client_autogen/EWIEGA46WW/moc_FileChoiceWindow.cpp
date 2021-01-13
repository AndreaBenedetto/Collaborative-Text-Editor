/****************************************************************************
** Meta object code from reading C++ file 'FileChoiceWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../FileChoiceWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FileChoiceWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FileChoiceWindow_t {
    QByteArrayData data[14];
    char stringdata0[173];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FileChoiceWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FileChoiceWindow_t qt_meta_stringdata_FileChoiceWindow = {
    {
QT_MOC_LITERAL(0, 0, 16), // "FileChoiceWindow"
QT_MOC_LITERAL(1, 17, 11), // "openNewFile"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 16), // "openExistingFile"
QT_MOC_LITERAL(4, 47, 18), // "deleteExistingFile"
QT_MOC_LITERAL(5, 66, 15), // "refreshFileList"
QT_MOC_LITERAL(6, 82, 10), // "requestURI"
QT_MOC_LITERAL(7, 93, 9), // "insertURI"
QT_MOC_LITERAL(8, 103, 18), // "openSettingsWindow"
QT_MOC_LITERAL(9, 122, 13), // "requestLogout"
QT_MOC_LITERAL(10, 136, 10), // "closeEvent"
QT_MOC_LITERAL(11, 147, 12), // "QCloseEvent*"
QT_MOC_LITERAL(12, 160, 5), // "event"
QT_MOC_LITERAL(13, 166, 6) // "reject"

    },
    "FileChoiceWindow\0openNewFile\0\0"
    "openExistingFile\0deleteExistingFile\0"
    "refreshFileList\0requestURI\0insertURI\0"
    "openSettingsWindow\0requestLogout\0"
    "closeEvent\0QCloseEvent*\0event\0reject"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FileChoiceWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x08 /* Private */,
       3,    0,   65,    2, 0x08 /* Private */,
       4,    0,   66,    2, 0x08 /* Private */,
       5,    0,   67,    2, 0x08 /* Private */,
       6,    0,   68,    2, 0x08 /* Private */,
       7,    0,   69,    2, 0x08 /* Private */,
       8,    0,   70,    2, 0x08 /* Private */,
       9,    0,   71,    2, 0x08 /* Private */,
      10,    1,   72,    2, 0x08 /* Private */,
      13,    0,   75,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void,

       0        // eod
};

void FileChoiceWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FileChoiceWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->openNewFile(); break;
        case 1: _t->openExistingFile(); break;
        case 2: _t->deleteExistingFile(); break;
        case 3: _t->refreshFileList(); break;
        case 4: _t->requestURI(); break;
        case 5: _t->insertURI(); break;
        case 6: _t->openSettingsWindow(); break;
        case 7: _t->requestLogout(); break;
        case 8: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 9: _t->reject(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject FileChoiceWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_FileChoiceWindow.data,
    qt_meta_data_FileChoiceWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *FileChoiceWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FileChoiceWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FileChoiceWindow.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int FileChoiceWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
