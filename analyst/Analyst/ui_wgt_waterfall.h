/********************************************************************************
** Form generated from reading UI file 'wgt_waterfall.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WGT_WATERFALL_H
#define UI_WGT_WATERFALL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_wgt_waterfall
{
public:
    QHBoxLayout *horizontalLayout;
    QCustomPlot *wgtWaterfall;
    QWidget *wgtControls;

    void setupUi(QWidget *wgt_waterfall)
    {
        if (wgt_waterfall->objectName().isEmpty())
            wgt_waterfall->setObjectName(QString::fromUtf8("wgt_waterfall"));
        wgt_waterfall->resize(854, 474);
        horizontalLayout = new QHBoxLayout(wgt_waterfall);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        wgtWaterfall = new QCustomPlot(wgt_waterfall);
        wgtWaterfall->setObjectName(QString::fromUtf8("wgtWaterfall"));

        horizontalLayout->addWidget(wgtWaterfall);

        wgtControls = new QWidget(wgt_waterfall);
        wgtControls->setObjectName(QString::fromUtf8("wgtControls"));
        wgtControls->setMaximumSize(QSize(150, 16777215));

        horizontalLayout->addWidget(wgtControls);


        retranslateUi(wgt_waterfall);

        QMetaObject::connectSlotsByName(wgt_waterfall);
    } // setupUi

    void retranslateUi(QWidget *wgt_waterfall)
    {
        wgt_waterfall->setWindowTitle(QCoreApplication::translate("wgt_waterfall", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class wgt_waterfall: public Ui_wgt_waterfall {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WGT_WATERFALL_H
