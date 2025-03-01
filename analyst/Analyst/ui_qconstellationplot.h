/********************************************************************************
** Form generated from reading UI file 'qconstellationplot.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QCONSTELLATIONPLOT_H
#define UI_QCONSTELLATIONPLOT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_QConstellationPlot
{
public:
    QHBoxLayout *horizontalLayout;
    QCustomPlot *wgtPlot;
    QWidget *wgtControls;

    void setupUi(QWidget *QConstellationPlot)
    {
        if (QConstellationPlot->objectName().isEmpty())
            QConstellationPlot->setObjectName(QString::fromUtf8("QConstellationPlot"));
        QConstellationPlot->resize(804, 487);
        horizontalLayout = new QHBoxLayout(QConstellationPlot);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        wgtPlot = new QCustomPlot(QConstellationPlot);
        wgtPlot->setObjectName(QString::fromUtf8("wgtPlot"));

        horizontalLayout->addWidget(wgtPlot);

        wgtControls = new QWidget(QConstellationPlot);
        wgtControls->setObjectName(QString::fromUtf8("wgtControls"));
        wgtControls->setMaximumSize(QSize(200, 16777215));

        horizontalLayout->addWidget(wgtControls);


        retranslateUi(QConstellationPlot);

        QMetaObject::connectSlotsByName(QConstellationPlot);
    } // setupUi

    void retranslateUi(QWidget *QConstellationPlot)
    {
        QConstellationPlot->setWindowTitle(QCoreApplication::translate("QConstellationPlot", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QConstellationPlot: public Ui_QConstellationPlot {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QCONSTELLATIONPLOT_H
