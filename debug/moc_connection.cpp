/****************************************************************************
** Meta object code from reading C++ file 'connection.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../connection.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'connection.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Connection_t {
    QByteArrayData data[15];
    char stringdata0[229];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Connection_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Connection_t qt_meta_stringdata_Connection = {
    {
QT_MOC_LITERAL(0, 0, 10), // "Connection"
QT_MOC_LITERAL(1, 11, 25), // "readyCreateNewConnections"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 20), // "connecionsCountTypes"
QT_MOC_LITERAL(4, 59, 16), // "connectionOpened"
QT_MOC_LITERAL(5, 76, 13), // "nameInterface"
QT_MOC_LITERAL(6, 90, 7), // "subName"
QT_MOC_LITERAL(7, 98, 16), // "connectionClosed"
QT_MOC_LITERAL(8, 115, 4), // "name"
QT_MOC_LITERAL(9, 120, 25), // "connectionClosedWithError"
QT_MOC_LITERAL(10, 146, 20), // "addConnectionRequest"
QT_MOC_LITERAL(11, 167, 13), // "addConnection"
QT_MOC_LITERAL(12, 181, 5), // "param"
QT_MOC_LITERAL(13, 187, 31), // "getAvailableListInterfaceOfType"
QT_MOC_LITERAL(14, 219, 9) // "indexType"

    },
    "Connection\0readyCreateNewConnections\0"
    "\0connecionsCountTypes\0connectionOpened\0"
    "nameInterface\0subName\0connectionClosed\0"
    "name\0connectionClosedWithError\0"
    "addConnectionRequest\0addConnection\0"
    "param\0getAvailableListInterfaceOfType\0"
    "indexType"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Connection[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       4,    2,   52,    2, 0x06 /* Public */,
       7,    1,   57,    2, 0x06 /* Public */,
       9,    1,   60,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
      10,    0,   63,    2, 0x02 /* Public */,
      11,    3,   64,    2, 0x02 /* Public */,
      13,    1,   71,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    5,    6,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::QString,    8,

 // methods: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,    5,    6,   12,
    QMetaType::QStringList, QMetaType::Int,   14,

       0        // eod
};

void Connection::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Connection *_t = static_cast<Connection *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->readyCreateNewConnections((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->connectionOpened((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: _t->connectionClosed((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->connectionClosedWithError((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->addConnectionRequest(); break;
        case 5: _t->addConnection((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 6: { QStringList _r = _t->getAvailableListInterfaceOfType((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Connection::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Connection::readyCreateNewConnections)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Connection::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Connection::connectionOpened)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Connection::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Connection::connectionClosed)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Connection::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Connection::connectionClosedWithError)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Connection::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Connection.data,
      qt_meta_data_Connection,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Connection::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Connection::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Connection.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Connection::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void Connection::readyCreateNewConnections(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Connection::connectionOpened(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Connection::connectionClosed(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Connection::connectionClosedWithError(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
