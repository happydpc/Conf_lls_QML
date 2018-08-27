/****************************************************************************
** Meta object code from reading C++ file 'interfaceSerial.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../interfaceSerial.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'interfaceSerial.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_InterfaceSerial_t {
    QByteArrayData data[6];
    char stringdata0[102];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_InterfaceSerial_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_InterfaceSerial_t qt_meta_stringdata_InterfaceSerial = {
    {
QT_MOC_LITERAL(0, 0, 15), // "InterfaceSerial"
QT_MOC_LITERAL(1, 16, 28), // "updateAvailableInterfaceList"
QT_MOC_LITERAL(2, 45, 0), // ""
QT_MOC_LITERAL(3, 46, 11), // "portMessage"
QT_MOC_LITERAL(4, 58, 38), // "InterfaceSerial::eInterfaceMe..."
QT_MOC_LITERAL(5, 97, 4) // "name"

    },
    "InterfaceSerial\0updateAvailableInterfaceList\0"
    "\0portMessage\0InterfaceSerial::eInterfaceMessageType\0"
    "name"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_InterfaceSerial[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x06 /* Public */,
       3,    2,   25,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::QStringList,
    QMetaType::Void, 0x80000000 | 4, QMetaType::QString,    2,    5,

       0        // eod
};

void InterfaceSerial::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        InterfaceSerial *_t = static_cast<InterfaceSerial *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { QStringList _r = _t->updateAvailableInterfaceList();
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = std::move(_r); }  break;
        case 1: _t->portMessage((*reinterpret_cast< InterfaceSerial::eInterfaceMessageType(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = QStringList (InterfaceSerial::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&InterfaceSerial::updateAvailableInterfaceList)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (InterfaceSerial::*)(InterfaceSerial::eInterfaceMessageType , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&InterfaceSerial::portMessage)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject InterfaceSerial::staticMetaObject = {
    { &interfacesAbstract::staticMetaObject, qt_meta_stringdata_InterfaceSerial.data,
      qt_meta_data_InterfaceSerial,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *InterfaceSerial::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *InterfaceSerial::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_InterfaceSerial.stringdata0))
        return static_cast<void*>(this);
    return interfacesAbstract::qt_metacast(_clname);
}

int InterfaceSerial::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = interfacesAbstract::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
QStringList InterfaceSerial::updateAvailableInterfaceList()
{
    QStringList _t0{};
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
    return _t0;
}

// SIGNAL 1
void InterfaceSerial::portMessage(InterfaceSerial::eInterfaceMessageType _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
