/********************************************************************************
** Form generated from reading UI file 'wgt_fft.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WGT_FFT_H
#define UI_WGT_FFT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_wgt_FFT
{
public:
    QHBoxLayout *horizontalLayout;
    QCustomPlot *plotFFT;
    QWidget *wgt_Controls;

    void setupUi(QWidget *wgt_FFT)
    {
        if (wgt_FFT->objectName().isEmpty())
            wgt_FFT->setObjectName(QString::fromUtf8("wgt_FFT"));
        wgt_FFT->resize(731, 300);
        horizontalLayout = new QHBoxLayout(wgt_FFT);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        plotFFT = new QCustomPlot(wgt_FFT);
        plotFFT->setObjectName(QString::fromUtf8("plotFFT"));

        horizontalLayout->addWidget(plotFFT);

        wgt_Controls = new QWidget(wgt_FFT);
        wgt_Controls->setObjectName(QString::fromUtf8("wgt_Controls"));
        wgt_Controls->setMaximumSize(QSize(200, 16777215));

        horizontalLayout->addWidget(wgt_Controls);


        retranslateUi(wgt_FFT);

        QMetaObject::connectSlotsByName(wgt_FFT);
    } // setupUi

    void retranslateUi(QWidget *wgt_FFT)
    {
        wgt_FFT->setWindowTitle(QCoreApplication::translate("wgt_FFT", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class wgt_FFT: public Ui_wgt_FFT {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WGT_FFT_H
