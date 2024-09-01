/****************************************************************************
** Meta object code from reading C++ file 'musicmenu.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../musicmenu.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'musicmenu.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MusicMenu_t {
    QByteArrayData data[18];
    char stringdata0[268];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MusicMenu_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MusicMenu_t qt_meta_stringdata_MusicMenu = {
    {
QT_MOC_LITERAL(0, 0, 9), // "MusicMenu"
QT_MOC_LITERAL(1, 10, 14), // "handlePrevSlot"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 14), // "handlePlaySlot"
QT_MOC_LITERAL(4, 41, 14), // "handleNextSlot"
QT_MOC_LITERAL(5, 56, 20), // "handleSwitchModeSlot"
QT_MOC_LITERAL(6, 77, 16), // "handleVolumeSlot"
QT_MOC_LITERAL(7, 94, 15), // "handleLyricSlot"
QT_MOC_LITERAL(8, 110, 17), // "handleCollectSlot"
QT_MOC_LITERAL(9, 128, 18), // "handleDurationSlot"
QT_MOC_LITERAL(10, 147, 8), // "duration"
QT_MOC_LITERAL(11, 156, 18), // "handlePositionSlot"
QT_MOC_LITERAL(12, 175, 8), // "position"
QT_MOC_LITERAL(13, 184, 17), // "handleTimeoutSlot"
QT_MOC_LITERAL(14, 202, 21), // "handleStateChangeSlot"
QT_MOC_LITERAL(15, 224, 21), // "handleDoubleClickSlot"
QT_MOC_LITERAL(16, 246, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(17, 263, 4) // "item"

    },
    "MusicMenu\0handlePrevSlot\0\0handlePlaySlot\0"
    "handleNextSlot\0handleSwitchModeSlot\0"
    "handleVolumeSlot\0handleLyricSlot\0"
    "handleCollectSlot\0handleDurationSlot\0"
    "duration\0handlePositionSlot\0position\0"
    "handleTimeoutSlot\0handleStateChangeSlot\0"
    "handleDoubleClickSlot\0QListWidgetItem*\0"
    "item"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MusicMenu[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x08 /* Private */,
       3,    0,   75,    2, 0x08 /* Private */,
       4,    0,   76,    2, 0x08 /* Private */,
       5,    0,   77,    2, 0x08 /* Private */,
       6,    0,   78,    2, 0x08 /* Private */,
       7,    0,   79,    2, 0x08 /* Private */,
       8,    0,   80,    2, 0x08 /* Private */,
       9,    1,   81,    2, 0x08 /* Private */,
      11,    1,   84,    2, 0x08 /* Private */,
      13,    0,   87,    2, 0x08 /* Private */,
      14,    0,   88,    2, 0x08 /* Private */,
      15,    1,   89,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong,   10,
    QMetaType::Void, QMetaType::LongLong,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 16,   17,

       0        // eod
};

void MusicMenu::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MusicMenu *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->handlePrevSlot(); break;
        case 1: _t->handlePlaySlot(); break;
        case 2: _t->handleNextSlot(); break;
        case 3: _t->handleSwitchModeSlot(); break;
        case 4: _t->handleVolumeSlot(); break;
        case 5: _t->handleLyricSlot(); break;
        case 6: _t->handleCollectSlot(); break;
        case 7: _t->handleDurationSlot((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 8: _t->handlePositionSlot((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 9: _t->handleTimeoutSlot(); break;
        case 10: _t->handleStateChangeSlot(); break;
        case 11: _t->handleDoubleClickSlot((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MusicMenu::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MusicMenu.data,
    qt_meta_data_MusicMenu,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MusicMenu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MusicMenu::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MusicMenu.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MusicMenu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
