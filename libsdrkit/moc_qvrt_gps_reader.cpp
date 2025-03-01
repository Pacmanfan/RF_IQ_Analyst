/****************************************************************************
** Meta object code from reading C++ file 'qvrt_gps_reader.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "qvrt_gps_reader.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qvrt_gps_reader.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QVRT_GPS_Reader_t {
    QByteArrayData data[10];
    char stringdata0[103];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QVRT_GPS_Reader_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QVRT_GPS_Reader_t qt_meta_stringdata_QVRT_GPS_Reader = {
    {
QT_MOC_LITERAL(0, 0, 15), // "QVRT_GPS_Reader"
QT_MOC_LITERAL(1, 16, 17), // "QVRT_GPS_Progress"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 16), // "QVRT_GPS_Reader*"
QT_MOC_LITERAL(4, 52, 6), // "reader"
QT_MOC_LITERAL(5, 59, 7), // "percent"
QT_MOC_LITERAL(6, 67, 4), // "done"
QT_MOC_LITERAL(7, 72, 16), // "QVRT_GPS_Message"
QT_MOC_LITERAL(8, 89, 5), // "error"
QT_MOC_LITERAL(9, 95, 7) // "message"

    },
    "QVRT_GPS_Reader\0QVRT_GPS_Progress\0\0"
    "QVRT_GPS_Reader*\0reader\0percent\0done\0"
    "QVRT_GPS_Message\0error\0message"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QVRT_GPS_Reader[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   24,    2, 0x06 /* Public */,
       7,    2,   31,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Float, QMetaType::Bool,    4,    5,    6,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString,    8,    9,

       0        // eod
};

void QVRT_GPS_Reader::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QVRT_GPS_Reader *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->QVRT_GPS_Progress((*reinterpret_cast< QVRT_GPS_Reader*(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 1: _t->QVRT_GPS_Message((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVRT_GPS_Reader* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QVRT_GPS_Reader::*)(QVRT_GPS_Reader * , float , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QVRT_GPS_Reader::QVRT_GPS_Progress)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (QVRT_GPS_Reader::*)(bool , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QVRT_GPS_Reader::QVRT_GPS_Message)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QVRT_GPS_Reader::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_QVRT_GPS_Reader.data,
    qt_meta_data_QVRT_GPS_Reader,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QVRT_GPS_Reader::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QVRT_GPS_Reader::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QVRT_GPS_Reader.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int QVRT_GPS_Reader::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void QVRT_GPS_Reader::QVRT_GPS_Progress(QVRT_GPS_Reader * _t1, float _t2, bool _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QVRT_GPS_Reader::QVRT_GPS_Message(bool _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
