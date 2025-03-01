/********************************************************************************
** Form generated from reading UI file 'dlgnewclassifier.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGNEWCLASSIFIER_H
#define UI_DLGNEWCLASSIFIER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_dlgNewClassifier
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QLineEdit *leName;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QComboBox *cmbType;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QComboBox *cmdBW;
    QSpacerItem *verticalSpacer;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QPushButton *cmdOK;

    void setupUi(QDialog *dlgNewClassifier)
    {
        if (dlgNewClassifier->objectName().isEmpty())
            dlgNewClassifier->setObjectName(QString::fromUtf8("dlgNewClassifier"));
        dlgNewClassifier->resize(329, 247);
        verticalLayout = new QVBoxLayout(dlgNewClassifier);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget_3 = new QWidget(dlgNewClassifier);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        horizontalLayout_3 = new QHBoxLayout(widget_3);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label = new QLabel(widget_3);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_3->addWidget(label);

        leName = new QLineEdit(widget_3);
        leName->setObjectName(QString::fromUtf8("leName"));

        horizontalLayout_3->addWidget(leName);


        verticalLayout->addWidget(widget_3);

        widget_2 = new QWidget(dlgNewClassifier);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        horizontalLayout = new QHBoxLayout(widget_2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_2 = new QLabel(widget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        cmbType = new QComboBox(widget_2);
        cmbType->addItem(QString());
        cmbType->addItem(QString());
        cmbType->setObjectName(QString::fromUtf8("cmbType"));

        horizontalLayout->addWidget(cmbType);


        verticalLayout->addWidget(widget_2);

        widget = new QWidget(dlgNewClassifier);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_2->addWidget(label_3);

        cmdBW = new QComboBox(widget);
        cmdBW->addItem(QString());
        cmdBW->addItem(QString());
        cmdBW->addItem(QString());
        cmdBW->addItem(QString());
        cmdBW->addItem(QString());
        cmdBW->setObjectName(QString::fromUtf8("cmdBW"));

        horizontalLayout_2->addWidget(cmdBW);


        verticalLayout->addWidget(widget);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        widget_4 = new QWidget(dlgNewClassifier);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        horizontalLayout_4 = new QHBoxLayout(widget_4);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        cmdOK = new QPushButton(widget_4);
        cmdOK->setObjectName(QString::fromUtf8("cmdOK"));

        horizontalLayout_4->addWidget(cmdOK);


        verticalLayout->addWidget(widget_4);


        retranslateUi(dlgNewClassifier);

        QMetaObject::connectSlotsByName(dlgNewClassifier);
    } // setupUi

    void retranslateUi(QDialog *dlgNewClassifier)
    {
        dlgNewClassifier->setWindowTitle(QCoreApplication::translate("dlgNewClassifier", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("dlgNewClassifier", "Name", nullptr));
        label_2->setText(QCoreApplication::translate("dlgNewClassifier", "Type", nullptr));
        cmbType->setItemText(0, QCoreApplication::translate("dlgNewClassifier", "Time Series", nullptr));
        cmbType->setItemText(1, QCoreApplication::translate("dlgNewClassifier", "FFT", nullptr));

        label_3->setText(QCoreApplication::translate("dlgNewClassifier", "Max Bandwidth", nullptr));
        cmdBW->setItemText(0, QCoreApplication::translate("dlgNewClassifier", "32 KHz", nullptr));
        cmdBW->setItemText(1, QCoreApplication::translate("dlgNewClassifier", "64 KHz", nullptr));
        cmdBW->setItemText(2, QCoreApplication::translate("dlgNewClassifier", "128 KHz", nullptr));
        cmdBW->setItemText(3, QCoreApplication::translate("dlgNewClassifier", "256 KHz", nullptr));
        cmdBW->setItemText(4, QCoreApplication::translate("dlgNewClassifier", "512 KHz", nullptr));

        cmdOK->setText(QCoreApplication::translate("dlgNewClassifier", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class dlgNewClassifier: public Ui_dlgNewClassifier {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGNEWCLASSIFIER_H
