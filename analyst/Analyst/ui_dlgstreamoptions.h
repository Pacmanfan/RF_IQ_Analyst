/********************************************************************************
** Form generated from reading UI file 'dlgstreamoptions.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGSTREAMOPTIONS_H
#define UI_DLGSTREAMOPTIONS_H

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

class Ui_dlgStreamOptions
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_4;
    QLabel *lblDataType;
    QComboBox *cmbDataType;
    QWidget *wgtCF;
    QHBoxLayout *horizontalLayout_3;
    QLabel *lblCF;
    QLineEdit *leCF;
    QSpacerItem *horizontalSpacer;
    QWidget *wgtSampleRate;
    QHBoxLayout *horizontalLayout_2;
    QLabel *lblSampleRate;
    QLineEdit *leSampleRate;
    QSpacerItem *horizontalSpacer_2;
    QWidget *wgtBandwidth;
    QHBoxLayout *horizontalLayout;
    QLabel *lblBandwidth;
    QLineEdit *leBandwidth;
    QSpacerItem *horizontalSpacer_3;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *cmdOK;
    QPushButton *cmdCancel;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *dlgStreamOptions)
    {
        if (dlgStreamOptions->objectName().isEmpty())
            dlgStreamOptions->setObjectName(QString::fromUtf8("dlgStreamOptions"));
        dlgStreamOptions->resize(471, 273);
        verticalLayout = new QVBoxLayout(dlgStreamOptions);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget = new QWidget(dlgStreamOptions);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout_4 = new QHBoxLayout(widget);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        lblDataType = new QLabel(widget);
        lblDataType->setObjectName(QString::fromUtf8("lblDataType"));

        horizontalLayout_4->addWidget(lblDataType);

        cmbDataType = new QComboBox(widget);
        cmbDataType->addItem(QString());
        cmbDataType->addItem(QString());
        cmbDataType->addItem(QString());
        cmbDataType->addItem(QString());
        cmbDataType->addItem(QString());
        cmbDataType->setObjectName(QString::fromUtf8("cmbDataType"));

        horizontalLayout_4->addWidget(cmbDataType);


        verticalLayout->addWidget(widget);

        wgtCF = new QWidget(dlgStreamOptions);
        wgtCF->setObjectName(QString::fromUtf8("wgtCF"));
        horizontalLayout_3 = new QHBoxLayout(wgtCF);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        lblCF = new QLabel(wgtCF);
        lblCF->setObjectName(QString::fromUtf8("lblCF"));

        horizontalLayout_3->addWidget(lblCF);

        leCF = new QLineEdit(wgtCF);
        leCF->setObjectName(QString::fromUtf8("leCF"));

        horizontalLayout_3->addWidget(leCF);

        horizontalSpacer = new QSpacerItem(126, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        verticalLayout->addWidget(wgtCF);

        wgtSampleRate = new QWidget(dlgStreamOptions);
        wgtSampleRate->setObjectName(QString::fromUtf8("wgtSampleRate"));
        horizontalLayout_2 = new QHBoxLayout(wgtSampleRate);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        lblSampleRate = new QLabel(wgtSampleRate);
        lblSampleRate->setObjectName(QString::fromUtf8("lblSampleRate"));

        horizontalLayout_2->addWidget(lblSampleRate);

        leSampleRate = new QLineEdit(wgtSampleRate);
        leSampleRate->setObjectName(QString::fromUtf8("leSampleRate"));

        horizontalLayout_2->addWidget(leSampleRate);

        horizontalSpacer_2 = new QSpacerItem(147, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addWidget(wgtSampleRate);

        wgtBandwidth = new QWidget(dlgStreamOptions);
        wgtBandwidth->setObjectName(QString::fromUtf8("wgtBandwidth"));
        horizontalLayout = new QHBoxLayout(wgtBandwidth);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lblBandwidth = new QLabel(wgtBandwidth);
        lblBandwidth->setObjectName(QString::fromUtf8("lblBandwidth"));

        horizontalLayout->addWidget(lblBandwidth);

        leBandwidth = new QLineEdit(wgtBandwidth);
        leBandwidth->setObjectName(QString::fromUtf8("leBandwidth"));

        horizontalLayout->addWidget(leBandwidth);

        horizontalSpacer_3 = new QSpacerItem(156, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        verticalLayout->addWidget(wgtBandwidth);

        widget_5 = new QWidget(dlgStreamOptions);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        horizontalLayout_5 = new QHBoxLayout(widget_5);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);

        cmdOK = new QPushButton(widget_5);
        cmdOK->setObjectName(QString::fromUtf8("cmdOK"));

        horizontalLayout_5->addWidget(cmdOK);

        cmdCancel = new QPushButton(widget_5);
        cmdCancel->setObjectName(QString::fromUtf8("cmdCancel"));

        horizontalLayout_5->addWidget(cmdCancel);

        horizontalSpacer_4 = new QSpacerItem(125, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);


        verticalLayout->addWidget(widget_5);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(dlgStreamOptions);

        cmbDataType->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(dlgStreamOptions);
    } // setupUi

    void retranslateUi(QDialog *dlgStreamOptions)
    {
        dlgStreamOptions->setWindowTitle(QCoreApplication::translate("dlgStreamOptions", "Dialog", nullptr));
        lblDataType->setText(QCoreApplication::translate("dlgStreamOptions", "Data Type", nullptr));
        cmbDataType->setItemText(0, QCoreApplication::translate("dlgStreamOptions", "2 channel unsigned 8 bit", nullptr));
        cmbDataType->setItemText(1, QCoreApplication::translate("dlgStreamOptions", "2 channel signed 8 bit", nullptr));
        cmbDataType->setItemText(2, QCoreApplication::translate("dlgStreamOptions", "2 channel unsigned 16 bit", nullptr));
        cmbDataType->setItemText(3, QCoreApplication::translate("dlgStreamOptions", "2 channel signed 16 bit", nullptr));
        cmbDataType->setItemText(4, QCoreApplication::translate("dlgStreamOptions", "2 channel float 32bit", nullptr));

        lblCF->setText(QCoreApplication::translate("dlgStreamOptions", "Center Frequency (Hz)", nullptr));
        leCF->setText(QCoreApplication::translate("dlgStreamOptions", "100000000", nullptr));
        lblSampleRate->setText(QCoreApplication::translate("dlgStreamOptions", "Sample Rate (SPS)", nullptr));
        leSampleRate->setText(QCoreApplication::translate("dlgStreamOptions", "5000000", nullptr));
        lblBandwidth->setText(QCoreApplication::translate("dlgStreamOptions", "Bandwidth (Hz)", nullptr));
        leBandwidth->setText(QCoreApplication::translate("dlgStreamOptions", "5000000", nullptr));
        cmdOK->setText(QCoreApplication::translate("dlgStreamOptions", "OK", nullptr));
        cmdCancel->setText(QCoreApplication::translate("dlgStreamOptions", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class dlgStreamOptions: public Ui_dlgStreamOptions {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGSTREAMOPTIONS_H
