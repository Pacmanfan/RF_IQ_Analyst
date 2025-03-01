/********************************************************************************
** Form generated from reading UI file 'frmdfworkshop.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMDFWORKSHOP_H
#define UI_FRMDFWORKSHOP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "wgt_scope.h"

QT_BEGIN_NAMESPACE

class Ui_frmDFWorkshop
{
public:
    QVBoxLayout *verticalLayout;
    wgt_Scope *wgtDFScope;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *cmdTest;
    QSpacerItem *horizontalSpacer;

    void setupUi(QDialog *frmDFWorkshop)
    {
        if (frmDFWorkshop->objectName().isEmpty())
            frmDFWorkshop->setObjectName(QString::fromUtf8("frmDFWorkshop"));
        frmDFWorkshop->resize(927, 588);
        verticalLayout = new QVBoxLayout(frmDFWorkshop);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        wgtDFScope = new wgt_Scope(frmDFWorkshop);
        wgtDFScope->setObjectName(QString::fromUtf8("wgtDFScope"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(wgtDFScope->sizePolicy().hasHeightForWidth());
        wgtDFScope->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(wgtDFScope);

        widget = new QWidget(frmDFWorkshop);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        cmdTest = new QPushButton(widget);
        cmdTest->setObjectName(QString::fromUtf8("cmdTest"));

        horizontalLayout->addWidget(cmdTest);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addWidget(widget);


        retranslateUi(frmDFWorkshop);

        QMetaObject::connectSlotsByName(frmDFWorkshop);
    } // setupUi

    void retranslateUi(QDialog *frmDFWorkshop)
    {
        frmDFWorkshop->setWindowTitle(QCoreApplication::translate("frmDFWorkshop", "Dialog", nullptr));
        cmdTest->setText(QCoreApplication::translate("frmDFWorkshop", "Test", nullptr));
    } // retranslateUi

};

namespace Ui {
    class frmDFWorkshop: public Ui_frmDFWorkshop {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMDFWORKSHOP_H
