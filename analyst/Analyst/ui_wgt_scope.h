/********************************************************************************
** Form generated from reading UI file 'wgt_scope.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WGT_SCOPE_H
#define UI_WGT_SCOPE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_wgt_Scope
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *wgtControls;
    QHBoxLayout *horizontalLayout_4;
    QTabWidget *tabWidget;
    QWidget *tbChannels;
    QVBoxLayout *verticalLayout;
    QTableWidget *tblTraces;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *chkAverage;
    QSpinBox *spnAverage;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QComboBox *cmbnumSamples;
    QCustomPlot *plotScope;

    void setupUi(QWidget *wgt_Scope)
    {
        if (wgt_Scope->objectName().isEmpty())
            wgt_Scope->setObjectName(QString::fromUtf8("wgt_Scope"));
        wgt_Scope->resize(846, 300);
        horizontalLayout = new QHBoxLayout(wgt_Scope);
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(2, 0, 2, 0);
        wgtControls = new QWidget(wgt_Scope);
        wgtControls->setObjectName(QString::fromUtf8("wgtControls"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(wgtControls->sizePolicy().hasHeightForWidth());
        wgtControls->setSizePolicy(sizePolicy);
        wgtControls->setMaximumSize(QSize(200, 16777215));
        horizontalLayout_4 = new QHBoxLayout(wgtControls);
        horizontalLayout_4->setSpacing(2);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(2, 2, 2, 2);
        tabWidget = new QTabWidget(wgtControls);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tbChannels = new QWidget();
        tbChannels->setObjectName(QString::fromUtf8("tbChannels"));
        verticalLayout = new QVBoxLayout(tbChannels);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(1, 1, 0, 0);
        tblTraces = new QTableWidget(tbChannels);
        tblTraces->setObjectName(QString::fromUtf8("tblTraces"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(tblTraces->sizePolicy().hasHeightForWidth());
        tblTraces->setSizePolicy(sizePolicy1);
        tblTraces->setMaximumSize(QSize(16777215, 16777215));
        tblTraces->verticalHeader()->setVisible(false);

        verticalLayout->addWidget(tblTraces);

        widget = new QWidget(tbChannels);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(0, 0));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setSpacing(1);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(1, 1, 1, 1);
        widget_2 = new QWidget(widget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 2, -1, 2);
        chkAverage = new QCheckBox(widget_2);
        chkAverage->setObjectName(QString::fromUtf8("chkAverage"));

        horizontalLayout_2->addWidget(chkAverage);

        spnAverage = new QSpinBox(widget_2);
        spnAverage->setObjectName(QString::fromUtf8("spnAverage"));
        spnAverage->setMinimum(1);
        spnAverage->setMaximum(50);
        spnAverage->setValue(2);

        horizontalLayout_2->addWidget(spnAverage);


        verticalLayout_2->addWidget(widget_2);

        widget_3 = new QWidget(widget);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        horizontalLayout_3 = new QHBoxLayout(widget_3);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(-1, 2, -1, 2);
        label = new QLabel(widget_3);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_3->addWidget(label);

        cmbnumSamples = new QComboBox(widget_3);
        cmbnumSamples->addItem(QString());
        cmbnumSamples->addItem(QString());
        cmbnumSamples->addItem(QString());
        cmbnumSamples->addItem(QString());
        cmbnumSamples->addItem(QString());
        cmbnumSamples->addItem(QString());
        cmbnumSamples->addItem(QString());
        cmbnumSamples->setObjectName(QString::fromUtf8("cmbnumSamples"));

        horizontalLayout_3->addWidget(cmbnumSamples);


        verticalLayout_2->addWidget(widget_3);


        verticalLayout->addWidget(widget);

        tabWidget->addTab(tbChannels, QString());

        horizontalLayout_4->addWidget(tabWidget);


        horizontalLayout->addWidget(wgtControls);

        plotScope = new QCustomPlot(wgt_Scope);
        plotScope->setObjectName(QString::fromUtf8("plotScope"));

        horizontalLayout->addWidget(plotScope);


        retranslateUi(wgt_Scope);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(wgt_Scope);
    } // setupUi

    void retranslateUi(QWidget *wgt_Scope)
    {
        wgt_Scope->setWindowTitle(QCoreApplication::translate("wgt_Scope", "Form", nullptr));
        chkAverage->setText(QCoreApplication::translate("wgt_Scope", "Average FM", nullptr));
        label->setText(QCoreApplication::translate("wgt_Scope", "# Samples", nullptr));
        cmbnumSamples->setItemText(0, QCoreApplication::translate("wgt_Scope", "250", nullptr));
        cmbnumSamples->setItemText(1, QCoreApplication::translate("wgt_Scope", "500", nullptr));
        cmbnumSamples->setItemText(2, QCoreApplication::translate("wgt_Scope", "1000", nullptr));
        cmbnumSamples->setItemText(3, QCoreApplication::translate("wgt_Scope", "2000", nullptr));
        cmbnumSamples->setItemText(4, QCoreApplication::translate("wgt_Scope", "5000", nullptr));
        cmbnumSamples->setItemText(5, QCoreApplication::translate("wgt_Scope", "10000", nullptr));
        cmbnumSamples->setItemText(6, QCoreApplication::translate("wgt_Scope", "25000", nullptr));

        tabWidget->setTabText(tabWidget->indexOf(tbChannels), QCoreApplication::translate("wgt_Scope", "Channels", nullptr));
    } // retranslateUi

};

namespace Ui {
    class wgt_Scope: public Ui_wgt_Scope {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WGT_SCOPE_H
