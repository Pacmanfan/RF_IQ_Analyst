/****************************************************************************
** Meta object code from reading C++ file 'classifier.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "classifier.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'classifier.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Classifier_t {
    QByteArrayData data[13];
    char stringdata0[160];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Classifier_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Classifier_t qt_meta_stringdata_Classifier = {
    {
QT_MOC_LITERAL(0, 0, 10), // "Classifier"
QT_MOC_LITERAL(1, 11, 22), // "ClassificationComplete"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 9), // "ftmarker*"
QT_MOC_LITERAL(4, 45, 3), // "ftm"
QT_MOC_LITERAL(5, 49, 7), // "message"
QT_MOC_LITERAL(6, 57, 19), // "QMap<QString,float>"
QT_MOC_LITERAL(7, 77, 7), // "results"
QT_MOC_LITERAL(8, 85, 16), // "TrainingComplete"
QT_MOC_LITERAL(9, 102, 15), // "TrainingMessage"
QT_MOC_LITERAL(10, 118, 3), // "msg"
QT_MOC_LITERAL(11, 122, 18), // "ReceiveUDPTraining"
QT_MOC_LITERAL(12, 141, 18) // "ReceiveUDPClassify"

    },
    "Classifier\0ClassificationComplete\0\0"
    "ftmarker*\0ftm\0message\0QMap<QString,float>\0"
    "results\0TrainingComplete\0TrainingMessage\0"
    "msg\0ReceiveUDPTraining\0ReceiveUDPClassify"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Classifier[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   39,    2, 0x06 /* Public */,
       8,    0,   46,    2, 0x06 /* Public */,
       9,    1,   47,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    0,   50,    2, 0x0a /* Public */,
      12,    0,   51,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString, 0x80000000 | 6,    4,    5,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   10,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Classifier::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Classifier *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ClassificationComplete((*reinterpret_cast< ftmarker*(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QMap<QString,float>(*)>(_a[3]))); break;
        case 1: _t->TrainingComplete(); break;
        case 2: _t->TrainingMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->ReceiveUDPTraining(); break;
        case 4: _t->ReceiveUDPClassify(); break;
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
            using _t = void (Classifier::*)(ftmarker * , QString , QMap<QString,float> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Classifier::ClassificationComplete)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Classifier::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Classifier::TrainingComplete)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Classifier::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Classifier::TrainingMessage)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Classifier::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Classifier.data,
    qt_meta_data_Classifier,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Classifier::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Classifier::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Classifier.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Classifier::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void Classifier::ClassificationComplete(ftmarker * _t1, QString _t2, QMap<QString,float> _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Classifier::TrainingComplete()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Classifier::TrainingMessage(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
