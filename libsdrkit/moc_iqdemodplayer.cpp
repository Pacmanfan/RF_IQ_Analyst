/****************************************************************************
** Meta object code from reading C++ file 'iqdemodplayer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "iqdemodplayer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'iqdemodplayer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_IQDemodPlayer_t {
    QByteArrayData data[10];
    char stringdata0[112];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_IQDemodPlayer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_IQDemodPlayer_t qt_meta_stringdata_IQDemodPlayer = {
    {
QT_MOC_LITERAL(0, 0, 13), // "IQDemodPlayer"
QT_MOC_LITERAL(1, 14, 13), // "PlaybackEnded"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 14), // "IQDemodPlayer*"
QT_MOC_LITERAL(4, 44, 6), // "player"
QT_MOC_LITERAL(5, 51, 15), // "PlaybackStarted"
QT_MOC_LITERAL(6, 67, 9), // "DataReady"
QT_MOC_LITERAL(7, 77, 20), // "onTunerMarkerChanged"
QT_MOC_LITERAL(8, 98, 9), // "ftmarker*"
QT_MOC_LITERAL(9, 108, 3) // "mrk"

    },
    "IQDemodPlayer\0PlaybackEnded\0\0"
    "IQDemodPlayer*\0player\0PlaybackStarted\0"
    "DataReady\0onTunerMarkerChanged\0ftmarker*\0"
    "mrk"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_IQDemodPlayer[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       5,    1,   37,    2, 0x06 /* Public */,
       6,    1,   40,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   43,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 8,    9,

       0        // eod
};

void IQDemodPlayer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<IQDemodPlayer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->PlaybackEnded((*reinterpret_cast< IQDemodPlayer*(*)>(_a[1]))); break;
        case 1: _t->PlaybackStarted((*reinterpret_cast< IQDemodPlayer*(*)>(_a[1]))); break;
        case 2: _t->DataReady((*reinterpret_cast< IQDemodPlayer*(*)>(_a[1]))); break;
        case 3: _t->onTunerMarkerChanged((*reinterpret_cast< ftmarker*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< IQDemodPlayer* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< IQDemodPlayer* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< IQDemodPlayer* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< ftmarker* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (IQDemodPlayer::*)(IQDemodPlayer * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IQDemodPlayer::PlaybackEnded)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (IQDemodPlayer::*)(IQDemodPlayer * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IQDemodPlayer::PlaybackStarted)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (IQDemodPlayer::*)(IQDemodPlayer * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IQDemodPlayer::DataReady)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject IQDemodPlayer::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_IQDemodPlayer.data,
    qt_meta_data_IQDemodPlayer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *IQDemodPlayer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *IQDemodPlayer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_IQDemodPlayer.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int IQDemodPlayer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void IQDemodPlayer::PlaybackEnded(IQDemodPlayer * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void IQDemodPlayer::PlaybackStarted(IQDemodPlayer * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void IQDemodPlayer::DataReady(IQDemodPlayer * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
