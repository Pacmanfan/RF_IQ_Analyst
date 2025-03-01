/********************************************************************************
** Form generated from reading UI file 'wgt_timeeditor.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WGT_TIMEEDITOR_H
#define UI_WGT_TIMEEDITOR_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_wgt_timeeditor
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout_5;
    QSpacerItem *verticalSpacer_2;
    QPushButton *cmdPageup;
    QPushButton *cmdUp;
    QPushButton *cmdUp_Small;
    QPushButton *cmdDown_Small;
    QPushButton *cmdDown;
    QPushButton *cmdPageDown;
    QSpacerItem *verticalSpacer;

    void setupUi(QFrame *wgt_timeeditor)
    {
        if (wgt_timeeditor->objectName().isEmpty())
            wgt_timeeditor->setObjectName(QString::fromUtf8("wgt_timeeditor"));
        wgt_timeeditor->resize(56, 359);
        verticalLayout = new QVBoxLayout(wgt_timeeditor);
        verticalLayout->setSpacing(1);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(3, 3, 3, 3);
        widget = new QWidget(wgt_timeeditor);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(50, 0));
        widget->setMaximumSize(QSize(52, 16777215));
        verticalLayout_5 = new QVBoxLayout(widget);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        verticalSpacer_2 = new QSpacerItem(20, 94, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_2);

        cmdPageup = new QPushButton(widget);
        cmdPageup->setObjectName(QString::fromUtf8("cmdPageup"));
        cmdPageup->setMaximumSize(QSize(50, 60));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/up2"), QSize(), QIcon::Normal, QIcon::Off);
        cmdPageup->setIcon(icon);
        cmdPageup->setIconSize(QSize(48, 48));
        cmdPageup->setAutoRepeat(true);

        verticalLayout_5->addWidget(cmdPageup);

        cmdUp = new QPushButton(widget);
        cmdUp->setObjectName(QString::fromUtf8("cmdUp"));
        cmdUp->setMaximumSize(QSize(50, 60));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/up1"), QSize(), QIcon::Normal, QIcon::Off);
        cmdUp->setIcon(icon1);
        cmdUp->setIconSize(QSize(48, 48));
        cmdUp->setAutoRepeat(true);
        cmdUp->setAutoRepeatDelay(250);

        verticalLayout_5->addWidget(cmdUp);

        cmdUp_Small = new QPushButton(widget);
        cmdUp_Small->setObjectName(QString::fromUtf8("cmdUp_Small"));
        cmdUp_Small->setMaximumSize(QSize(50, 60));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/upsmall"), QSize(), QIcon::Normal, QIcon::Off);
        cmdUp_Small->setIcon(icon2);
        cmdUp_Small->setIconSize(QSize(48, 48));
        cmdUp_Small->setAutoRepeat(true);
        cmdUp_Small->setAutoRepeatDelay(250);

        verticalLayout_5->addWidget(cmdUp_Small);

        cmdDown_Small = new QPushButton(widget);
        cmdDown_Small->setObjectName(QString::fromUtf8("cmdDown_Small"));
        cmdDown_Small->setMaximumSize(QSize(50, 60));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/downsmall"), QSize(), QIcon::Normal, QIcon::Off);
        cmdDown_Small->setIcon(icon3);
        cmdDown_Small->setIconSize(QSize(48, 48));
        cmdDown_Small->setAutoRepeat(true);

        verticalLayout_5->addWidget(cmdDown_Small);

        cmdDown = new QPushButton(widget);
        cmdDown->setObjectName(QString::fromUtf8("cmdDown"));
        cmdDown->setMaximumSize(QSize(50, 60));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/down1"), QSize(), QIcon::Normal, QIcon::Off);
        cmdDown->setIcon(icon4);
        cmdDown->setIconSize(QSize(48, 48));
        cmdDown->setAutoRepeat(true);

        verticalLayout_5->addWidget(cmdDown);

        cmdPageDown = new QPushButton(widget);
        cmdPageDown->setObjectName(QString::fromUtf8("cmdPageDown"));
        cmdPageDown->setMaximumSize(QSize(50, 60));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icons/down2"), QSize(), QIcon::Normal, QIcon::Off);
        cmdPageDown->setIcon(icon5);
        cmdPageDown->setIconSize(QSize(48, 48));
        cmdPageDown->setAutoRepeat(true);

        verticalLayout_5->addWidget(cmdPageDown);

        verticalSpacer = new QSpacerItem(20, 94, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer);


        verticalLayout->addWidget(widget);


        retranslateUi(wgt_timeeditor);

        QMetaObject::connectSlotsByName(wgt_timeeditor);
    } // setupUi

    void retranslateUi(QFrame *wgt_timeeditor)
    {
        wgt_timeeditor->setWindowTitle(QCoreApplication::translate("wgt_timeeditor", "Frame", nullptr));
        cmdPageup->setText(QString());
        cmdUp->setText(QString());
        cmdUp_Small->setText(QString());
        cmdDown_Small->setText(QString());
        cmdDown->setText(QString());
        cmdPageDown->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class wgt_timeeditor: public Ui_wgt_timeeditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WGT_TIMEEDITOR_H
