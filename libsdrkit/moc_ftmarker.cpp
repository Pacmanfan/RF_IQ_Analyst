/****************************************************************************
** Meta object code from reading C++ file 'ftmarker.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "ftmarker.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ftmarker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ftmarker_t {
    QByteArrayData data[5];
    char stringdata0[38];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ftmarker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ftmarker_t qt_meta_stringdata_ftmarker = {
    {
QT_MOC_LITERAL(0, 0, 8), // "ftmarker"
QT_MOC_LITERAL(1, 9, 13), // "MarkerChanged"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 9), // "ftmarker*"
QT_MOC_LITERAL(4, 34, 3) // "mrk"

    },
    "ftmarker\0MarkerChanged\0\0ftmarker*\0mrk"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ftmarker[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void ftmarker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ftmarker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->MarkerChanged((*reinterpret_cast< ftmarker*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
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
            using _t = void (ftmarker::*)(ftmarker * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ftmarker::MarkerChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ftmarker::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ftmarker.data,
    qt_meta_data_ftmarker,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ftmarker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ftmarker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ftmarker.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ftmarker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void ftmarker::MarkerChanged(ftmarker * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_freq_markers_t {
    QByteArrayData data[11];
    char stringdata0[124];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_freq_markers_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_freq_markers_t qt_meta_stringdata_freq_markers = {
    {
QT_MOC_LITERAL(0, 0, 12), // "freq_markers"
QT_MOC_LITERAL(1, 13, 13), // "MarkerChanged"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 9), // "ftmarker*"
QT_MOC_LITERAL(4, 38, 3), // "mrk"
QT_MOC_LITERAL(5, 42, 11), // "MarkerAdded"
QT_MOC_LITERAL(6, 54, 12), // "MarkersAdded"
QT_MOC_LITERAL(7, 67, 18), // "QVector<ftmarker*>"
QT_MOC_LITERAL(8, 86, 7), // "markers"
QT_MOC_LITERAL(9, 94, 13), // "MarkerRemoved"
QT_MOC_LITERAL(10, 108, 15) // "OnMarkerChanged"

    },
    "freq_markers\0MarkerChanged\0\0ftmarker*\0"
    "mrk\0MarkerAdded\0MarkersAdded\0"
    "QVector<ftmarker*>\0markers\0MarkerRemoved\0"
    "OnMarkerChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_freq_markers[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       5,    1,   42,    2, 0x06 /* Public */,
       6,    1,   45,    2, 0x06 /* Public */,
       9,    1,   48,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    1,   51,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void freq_markers::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<freq_markers *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->MarkerChanged((*reinterpret_cast< ftmarker*(*)>(_a[1]))); break;
        case 1: _t->MarkerAdded((*reinterpret_cast< ftmarker*(*)>(_a[1]))); break;
        case 2: _t->MarkersAdded((*reinterpret_cast< QVector<ftmarker*>(*)>(_a[1]))); break;
        case 3: _t->MarkerRemoved((*reinterpret_cast< ftmarker*(*)>(_a[1]))); break;
        case 4: _t->OnMarkerChanged((*reinterpret_cast< ftmarker*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< ftmarker* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< ftmarker* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<ftmarker*> >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< ftmarker* >(); break;
            }
            break;
        case 4:
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
            using _t = void (freq_markers::*)(ftmarker * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&freq_markers::MarkerChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (freq_markers::*)(ftmarker * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&freq_markers::MarkerAdded)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (freq_markers::*)(QVector<ftmarker*> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&freq_markers::MarkersAdded)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (freq_markers::*)(ftmarker * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&freq_markers::MarkerRemoved)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject freq_markers::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_freq_markers.data,
    qt_meta_data_freq_markers,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *freq_markers::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *freq_markers::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_freq_markers.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int freq_markers::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void freq_markers::MarkerChanged(ftmarker * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void freq_markers::MarkerAdded(ftmarker * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void freq_markers::MarkersAdded(QVector<ftmarker*> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void freq_markers::MarkerRemoved(ftmarker * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
