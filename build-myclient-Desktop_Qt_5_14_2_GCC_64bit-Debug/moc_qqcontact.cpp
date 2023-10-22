/****************************************************************************
** Meta object code from reading C++ file 'qqcontact.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../myclient/qqcontact.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qqcontact.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_qqContact_t {
    QByteArrayData data[11];
    char stringdata0[187];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_qqContact_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_qqContact_t qt_meta_stringdata_qqContact = {
    {
QT_MOC_LITERAL(0, 0, 9), // "qqContact"
QT_MOC_LITERAL(1, 10, 21), // "on_add_friend_clicked"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 31), // "on_listWidget_currentRowChanged"
QT_MOC_LITERAL(4, 65, 10), // "currentRow"
QT_MOC_LITERAL(5, 76, 22), // "on_friends_itemClicked"
QT_MOC_LITERAL(6, 99, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(7, 116, 4), // "item"
QT_MOC_LITERAL(8, 121, 23), // "on_group_create_clicked"
QT_MOC_LITERAL(9, 145, 20), // "readPendingDatagrams"
QT_MOC_LITERAL(10, 166, 20) // "on_add_group_clicked"

    },
    "qqContact\0on_add_friend_clicked\0\0"
    "on_listWidget_currentRowChanged\0"
    "currentRow\0on_friends_itemClicked\0"
    "QListWidgetItem*\0item\0on_group_create_clicked\0"
    "readPendingDatagrams\0on_add_group_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_qqContact[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x08 /* Private */,
       3,    1,   45,    2, 0x08 /* Private */,
       5,    1,   48,    2, 0x08 /* Private */,
       8,    0,   51,    2, 0x08 /* Private */,
       9,    0,   52,    2, 0x08 /* Private */,
      10,    0,   53,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void qqContact::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<qqContact *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_add_friend_clicked(); break;
        case 1: _t->on_listWidget_currentRowChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_friends_itemClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 3: _t->on_group_create_clicked(); break;
        case 4: _t->readPendingDatagrams(); break;
        case 5: _t->on_add_group_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject qqContact::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_qqContact.data,
    qt_meta_data_qqContact,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *qqContact::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *qqContact::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_qqContact.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int qqContact::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
