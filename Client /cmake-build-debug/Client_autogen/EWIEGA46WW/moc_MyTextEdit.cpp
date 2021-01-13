/****************************************************************************
** Meta object code from reading C++ file 'MyTextEdit.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../MyTextEdit.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MyTextEdit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MyTextEdit_t {
    QByteArrayData data[15];
    char stringdata0[186];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyTextEdit_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyTextEdit_t qt_meta_stringdata_MyTextEdit = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MyTextEdit"
QT_MOC_LITERAL(1, 11, 20), // "formatChangeFinished"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 12), // "insertSymbol"
QT_MOC_LITERAL(4, 46, 6), // "Symbol"
QT_MOC_LITERAL(5, 53, 9), // "character"
QT_MOC_LITERAL(6, 63, 12), // "singleSymbol"
QT_MOC_LITERAL(7, 76, 12), // "deleteSymbol"
QT_MOC_LITERAL(8, 89, 6), // "action"
QT_MOC_LITERAL(9, 96, 18), // "modifySymbolFormat"
QT_MOC_LITERAL(10, 115, 15), // "QTextCharFormat"
QT_MOC_LITERAL(11, 131, 6), // "format"
QT_MOC_LITERAL(12, 138, 17), // "modifyBlockFormat"
QT_MOC_LITERAL(13, 156, 16), // "QTextBlockFormat"
QT_MOC_LITERAL(14, 173, 12) // "printSymbols"

    },
    "MyTextEdit\0formatChangeFinished\0\0"
    "insertSymbol\0Symbol\0character\0"
    "singleSymbol\0deleteSymbol\0action\0"
    "modifySymbolFormat\0QTextCharFormat\0"
    "format\0modifyBlockFormat\0QTextBlockFormat\0"
    "printSymbols"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyTextEdit[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    2,   50,    2, 0x0a /* Public */,
       3,    1,   55,    2, 0x2a /* Public | MethodCloned */,
       7,    1,   58,    2, 0x0a /* Public */,
       9,    1,   61,    2, 0x0a /* Public */,
      12,    1,   64,    2, 0x0a /* Public */,
      14,    0,   67,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    0x80000000 | 4, QMetaType::QChar, QMetaType::Bool,    5,    6,
    0x80000000 | 4, QMetaType::QChar,    5,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, 0x80000000 | 13,   11,
    QMetaType::Void,

       0        // eod
};

void MyTextEdit::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MyTextEdit *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->formatChangeFinished(); break;
        case 1: { Symbol _r = _t->insertSymbol((*reinterpret_cast< QChar(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< Symbol*>(_a[0]) = std::move(_r); }  break;
        case 2: { Symbol _r = _t->insertSymbol((*reinterpret_cast< QChar(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< Symbol*>(_a[0]) = std::move(_r); }  break;
        case 3: _t->deleteSymbol((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->modifySymbolFormat((*reinterpret_cast< QTextCharFormat(*)>(_a[1]))); break;
        case 5: _t->modifyBlockFormat((*reinterpret_cast< QTextBlockFormat(*)>(_a[1]))); break;
        case 6: _t->printSymbols(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MyTextEdit::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyTextEdit::formatChangeFinished)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MyTextEdit::staticMetaObject = { {
    QMetaObject::SuperData::link<QTextEdit::staticMetaObject>(),
    qt_meta_stringdata_MyTextEdit.data,
    qt_meta_data_MyTextEdit,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MyTextEdit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyTextEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MyTextEdit.stringdata0))
        return static_cast<void*>(this);
    return QTextEdit::qt_metacast(_clname);
}

int MyTextEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTextEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void MyTextEdit::formatChangeFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
