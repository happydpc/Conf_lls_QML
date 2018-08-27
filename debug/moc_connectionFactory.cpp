/****************************************************************************
** Meta object code from reading C++ file 'connectionFactory.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../connectionFactory.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'connectionFactory.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ConnectionFactory_t {
    QByteArrayData data[20];
    char stringdata0[392];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ConnectionFactory_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ConnectionFactory_t qt_meta_stringdata_ConnectionFactory = {
    {
QT_MOC_LITERAL(0, 0, 17), // "ConnectionFactory"
QT_MOC_LITERAL(1, 18, 13), // "addConnection"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 35), // "interfacesAbstract::eInterfac..."
QT_MOC_LITERAL(4, 69, 4), // "name"
QT_MOC_LITERAL(5, 74, 4), // "int*"
QT_MOC_LITERAL(6, 79, 3), // "arg"
QT_MOC_LITERAL(7, 83, 16), // "removeConnection"
QT_MOC_LITERAL(8, 100, 30), // "getAvailableInterfacesFromType"
QT_MOC_LITERAL(9, 131, 25), // "addConnectionToSerialPort"
QT_MOC_LITERAL(10, 157, 8), // "portName"
QT_MOC_LITERAL(11, 166, 8), // "baudrate"
QT_MOC_LITERAL(12, 175, 18), // "addConnectionToBLE"
QT_MOC_LITERAL(13, 194, 23), // "addConnectionToEthernet"
QT_MOC_LITERAL(14, 218, 28), // "removeConnectionToSerialPort"
QT_MOC_LITERAL(15, 247, 21), // "removeConnectionToBLE"
QT_MOC_LITERAL(16, 269, 26), // "removeConnectionToEthernet"
QT_MOC_LITERAL(17, 296, 34), // "getAvailableInterfacesToSeria..."
QT_MOC_LITERAL(18, 331, 27), // "getAvailableInterfacesToBLE"
QT_MOC_LITERAL(19, 359, 32) // "getAvailableInterfacesToEthernet"

    },
    "ConnectionFactory\0addConnection\0\0"
    "interfacesAbstract::eInterfaceTypes\0"
    "name\0int*\0arg\0removeConnection\0"
    "getAvailableInterfacesFromType\0"
    "addConnectionToSerialPort\0portName\0"
    "baudrate\0addConnectionToBLE\0"
    "addConnectionToEthernet\0"
    "removeConnectionToSerialPort\0"
    "removeConnectionToBLE\0removeConnectionToEthernet\0"
    "getAvailableInterfacesToSerialPort\0"
    "getAvailableInterfacesToBLE\0"
    "getAvailableInterfacesToEthernet"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ConnectionFactory[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    3,   74,    2, 0x08 /* Private */,
       7,    2,   81,    2, 0x08 /* Private */,
       8,    1,   86,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
       9,    2,   89,    2, 0x02 /* Public */,
      12,    1,   94,    2, 0x02 /* Public */,
      13,    1,   97,    2, 0x02 /* Public */,
      14,    1,  100,    2, 0x02 /* Public */,
      15,    1,  103,    2, 0x02 /* Public */,
      16,    1,  106,    2, 0x02 /* Public */,
      17,    0,  109,    2, 0x02 /* Public */,
      18,    0,  110,    2, 0x02 /* Public */,
      19,    0,  111,    2, 0x02 /* Public */,

 // slots: parameters
    QMetaType::Bool, 0x80000000 | 3, QMetaType::QString, 0x80000000 | 5,    2,    4,    6,
    QMetaType::Bool, 0x80000000 | 3, QMetaType::QString,    2,    4,
    QMetaType::QStringList, 0x80000000 | 3,    2,

 // methods: parameters
    QMetaType::Bool, QMetaType::QString, QMetaType::Int,   10,   11,
    QMetaType::Bool, QMetaType::QString,   10,
    QMetaType::Bool, QMetaType::QString,   10,
    QMetaType::Bool, QMetaType::QString,   10,
    QMetaType::Bool, QMetaType::QString,   10,
    QMetaType::Bool, QMetaType::QString,   10,
    QMetaType::QStringList,
    QMetaType::QStringList,
    QMetaType::QStringList,

       0        // eod
};

void ConnectionFactory::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ConnectionFactory *_t = static_cast<ConnectionFactory *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { bool _r = _t->addConnection((*reinterpret_cast< interfacesAbstract::eInterfaceTypes(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int*(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 1: { bool _r = _t->removeConnection((*reinterpret_cast< interfacesAbstract::eInterfaceTypes(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 2: { QStringList _r = _t->getAvailableInterfacesFromType((*reinterpret_cast< interfacesAbstract::eInterfaceTypes(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = std::move(_r); }  break;
        case 3: { bool _r = _t->addConnectionToSerialPort((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 4: { bool _r = _t->addConnectionToBLE((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 5: { bool _r = _t->addConnectionToEthernet((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 6: { bool _r = _t->removeConnectionToSerialPort((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 7: { bool _r = _t->removeConnectionToBLE((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 8: { bool _r = _t->removeConnectionToEthernet((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 9: { QStringList _r = _t->getAvailableInterfacesToSerialPort();
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = std::move(_r); }  break;
        case 10: { QStringList _r = _t->getAvailableInterfacesToBLE();
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = std::move(_r); }  break;
        case 11: { QStringList _r = _t->getAvailableInterfacesToEthernet();
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ConnectionFactory::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ConnectionFactory.data,
      qt_meta_data_ConnectionFactory,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ConnectionFactory::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ConnectionFactory::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ConnectionFactory.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ConnectionFactory::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
