/********************************************************************************
** Form generated from reading UI file 'dlgsignaldetector.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGSIGNALDETECTOR_H
#define UI_DLGSIGNALDETECTOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_dlgSignalDetector
{
public:
    QVBoxLayout *verticalLayout;
    QRadioButton *rbEntire;
    QRadioButton *rbWindow;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QDoubleSpinBox *spnThreshold;
    QSpacerItem *horizontalSpacer_2;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QSlider *sldFFT;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *lbl_NumBins;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_4;
    QLabel *lblRBW;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer_3;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *cmdStart;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;
    QProgressBar *progressBar;

    void setupUi(QDialog *dlgSignalDetector)
    {
        if (dlgSignalDetector->objectName().isEmpty())
            dlgSignalDetector->setObjectName(QString::fromUtf8("dlgSignalDetector"));
        dlgSignalDetector->resize(632, 326);
        verticalLayout = new QVBoxLayout(dlgSignalDetector);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        rbEntire = new QRadioButton(dlgSignalDetector);
        rbEntire->setObjectName(QString::fromUtf8("rbEntire"));
        rbEntire->setChecked(true);

        verticalLayout->addWidget(rbEntire);

        rbWindow = new QRadioButton(dlgSignalDetector);
        rbWindow->setObjectName(QString::fromUtf8("rbWindow"));

        verticalLayout->addWidget(rbWindow);

        widget = new QWidget(dlgSignalDetector);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        spnThreshold = new QDoubleSpinBox(widget);
        spnThreshold->setObjectName(QString::fromUtf8("spnThreshold"));
        spnThreshold->setMinimum(1.000000000000000);
        spnThreshold->setMaximum(5.000000000000000);
        spnThreshold->setSingleStep(0.250000000000000);
        spnThreshold->setValue(2.500000000000000);

        horizontalLayout_2->addWidget(spnThreshold);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addWidget(widget);

        widget_3 = new QWidget(dlgSignalDetector);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        horizontalLayout_3 = new QHBoxLayout(widget_3);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(widget_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_3->addWidget(label_2);

        sldFFT = new QSlider(widget_3);
        sldFFT->setObjectName(QString::fromUtf8("sldFFT"));
        sldFFT->setMinimum(0);
        sldFFT->setMaximum(6);
        sldFFT->setPageStep(4);
        sldFFT->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(sldFFT);


        verticalLayout->addWidget(widget_3);

        widget_4 = new QWidget(dlgSignalDetector);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        horizontalLayout_4 = new QHBoxLayout(widget_4);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        lbl_NumBins = new QLabel(widget_4);
        lbl_NumBins->setObjectName(QString::fromUtf8("lbl_NumBins"));

        horizontalLayout_4->addWidget(lbl_NumBins);

        label_3 = new QLabel(widget_4);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_4->addWidget(label_3);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        lblRBW = new QLabel(widget_4);
        lblRBW->setObjectName(QString::fromUtf8("lblRBW"));

        horizontalLayout_4->addWidget(lblRBW);

        label_5 = new QLabel(widget_4);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_4->addWidget(label_5);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);


        verticalLayout->addWidget(widget_4);

        widget_2 = new QWidget(dlgSignalDetector);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        horizontalLayout = new QHBoxLayout(widget_2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        cmdStart = new QPushButton(widget_2);
        cmdStart->setObjectName(QString::fromUtf8("cmdStart"));

        horizontalLayout->addWidget(cmdStart);

        horizontalSpacer = new QSpacerItem(507, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addWidget(widget_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        progressBar = new QProgressBar(dlgSignalDetector);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(24);

        verticalLayout->addWidget(progressBar);


        retranslateUi(dlgSignalDetector);

        QMetaObject::connectSlotsByName(dlgSignalDetector);
    } // setupUi

    void retranslateUi(QDialog *dlgSignalDetector)
    {
        dlgSignalDetector->setWindowTitle(QCoreApplication::translate("dlgSignalDetector", "Dialog", nullptr));
        rbEntire->setText(QCoreApplication::translate("dlgSignalDetector", "Entire Stream", nullptr));
        rbWindow->setText(QCoreApplication::translate("dlgSignalDetector", "Visible Window", nullptr));
        label->setText(QCoreApplication::translate("dlgSignalDetector", "Sensitivity", nullptr));
        label_2->setText(QCoreApplication::translate("dlgSignalDetector", "FFT Resolution", nullptr));
        lbl_NumBins->setText(QCoreApplication::translate("dlgSignalDetector", "256", nullptr));
        label_3->setText(QCoreApplication::translate("dlgSignalDetector", "Bins", nullptr));
        lblRBW->setText(QCoreApplication::translate("dlgSignalDetector", "1000", nullptr));
        label_5->setText(QCoreApplication::translate("dlgSignalDetector", "Hz Resolution Bandwidth", nullptr));
        cmdStart->setText(QCoreApplication::translate("dlgSignalDetector", "Start", nullptr));
    } // retranslateUi

};

namespace Ui {
    class dlgSignalDetector: public Ui_dlgSignalDetector {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGSIGNALDETECTOR_H
