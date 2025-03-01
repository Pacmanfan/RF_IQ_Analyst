/********************************************************************************
** Form generated from reading UI file 'frmhelp.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMHELP_H
#define UI_FRMHELP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frmHelp
{
public:
    QVBoxLayout *verticalLayout;
    QTextBrowser *txtHelp;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *cmdClose;

    void setupUi(QDialog *frmHelp)
    {
        if (frmHelp->objectName().isEmpty())
            frmHelp->setObjectName(QString::fromUtf8("frmHelp"));
        frmHelp->resize(817, 603);
        verticalLayout = new QVBoxLayout(frmHelp);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        txtHelp = new QTextBrowser(frmHelp);
        txtHelp->setObjectName(QString::fromUtf8("txtHelp"));

        verticalLayout->addWidget(txtHelp);

        widget = new QWidget(frmHelp);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(692, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        cmdClose = new QPushButton(widget);
        cmdClose->setObjectName(QString::fromUtf8("cmdClose"));
        cmdClose->setMinimumSize(QSize(0, 30));

        horizontalLayout->addWidget(cmdClose);


        verticalLayout->addWidget(widget);


        retranslateUi(frmHelp);

        QMetaObject::connectSlotsByName(frmHelp);
    } // setupUi

    void retranslateUi(QDialog *frmHelp)
    {
        frmHelp->setWindowTitle(QCoreApplication::translate("frmHelp", "Dialog", nullptr));
        cmdClose->setText(QCoreApplication::translate("frmHelp", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class frmHelp: public Ui_frmHelp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMHELP_H
