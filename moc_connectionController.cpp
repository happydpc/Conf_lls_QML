/****************************************************************************
** Meta object code from reading C++ file 'connectionController.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "connection/connectionController.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'connectionController.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ConnectionController_t {
    QByteArrayData data[13];
    char stringdata0[283];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ConnectionController_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ConnectionController_t qt_meta_stringdata_ConnectionController = {
    {
QT_MOC_LITERAL(0, 0, 20), // "ConnectionController"
QT_MOC_LITERAL(1, 21, 25), // "addConnectionToSerialPort"
QT_MOC_LITERAL(2, 47, 0), // ""
QT_MOC_LITERAL(3, 48, 8), // "portName"
QT_MOC_LITERAL(4, 57, 8), // "baudrate"
QT_MOC_LITERAL(5, 66, 18), // "addConnectionToBLE"
QT_MOC_LITERAL(6, 85, 23), // "addConnectionToEthernet"
QT_MOC_LITERAL(7, 109, 28), // "removeConnectionToSerialPort"
QT_MOC_LITERAL(8, 138, 21), // "removeConnectionToBLE"
QT_MOC_LITERAL(9, 160, 26), // "removeConnectionToEthernet"
QT_MOC_LITERAL(10, 187, 34), // "getAvailableInterfacesToSeria..."
QT_MOC_LITERAL(11, 222, 27), // "getAvailableInterfacesToBLE"
QT_MOC_LITERAL(12, 250, 32) // "getAvailableInterfacesToEthernet"

    },
    "ConnectionController\0addConnectionToSerialPort\0"
    "\0portName\0baudrate\0addConnectionToBLE\0"
    "addConnectionToEthernet\0"
    "removeConnectionToSerialPort\0"
    "removeConnectionToBLE\0removeConnectionToEthernet\0"
    "getAvailableInterfacesToSerialPort\0"
    "getAvailableInterfacesToBLE\0"
    "getAvailableInterfacesToEthernet"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ConnectionController[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: name, argc, parameters, tag, flags
       1,    2,   59,    2, 0x02 /* Public */,
       5,    1,   64,    2, 0x02 /* Public */,
       6,    1,   67,    2, 0x02 /* Public */,
       7,    1,   70,    2, 0x02 /* Public */,
       8,    1,   73,    2, 0x02 /* Public */,
       9,    1,   76,    2, 0x02 /* Public */,
      10,    0,   79,    2, 0x02 /* Public */,
      11,    0,   80,    2, 0x02 /* Public */,
      12,    0,   81,    2, 0x02 /* Public */,

 // methods: parameters
    QMetaType::Bool, QMetaType::QString, QMetaType::Int,    3,    4,
    QMetaType::Bool, QMetaType::QString,    3,
    QMetaType::Bool, QMetaType::QString,    3,
    QMetaType::Bool, QMetaType::QString,    3,
    QMetaType::Bool, QMetaType::QString,    3,
    QMetaType::Bool, QMetaType::QString,    3,
    QMetaType::QStringList,
    QMetaType::QStringList,
    QMetaType::QStringList,

       0        // eod
};

void ConnectionController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ConnectionController *_t = static_cast<ConnectionController *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { bool _r = _t->addConnectionToSerialPort((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 1: { bool _r = _t->addConnectionToBLE((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 2: { bool _r = _t->addConnectionToEthernet((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 3: { bool _r = _t->removeConnectionToSerialPort((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 4: { bool _r = _t->removeConnectionToBLE((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 5: { bool _r = _t->removeConnectionToEthernet((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 6: { QStringList _r = _t->getAvailableInterfacesToSerialPort();
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = std::move(_r); }  break;
        case 7: { QStringList _r = _t->getAvailableInterfacesToBLE();
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = std::move(_r); }  break;
        case 8: { QStringList _r = _t->getAvailableInterfacesToEthernet();
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ConnectionController::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ConnectionController.data,
      qt_meta_data_ConnectionController,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ConnectionController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ConnectionController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ConnectionController.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ConnectionController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
