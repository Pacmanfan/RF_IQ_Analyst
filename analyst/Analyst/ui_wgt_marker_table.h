/********************************************************************************
** Form generated from reading UI file 'wgt_marker_table.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WGT_MARKER_TABLE_H
#define UI_WGT_MARKER_TABLE_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>
#include "wgt_marker_editor.h"

QT_BEGIN_NAMESPACE

class Ui_wgt_marker_table
{
public:
    QHBoxLayout *horizontalLayout;
    wgt_marker_editor *wgt_marker_edit;
    QWidget *wgtButtons;
    QPushButton *cmdAdd;
    QPushButton *cmdRemove;
    QPushButton *cmdGoto;
    QPushButton *cmdExport;
    QPushButton *cmdRemoveAll;
    QPushButton *cmdMerge;
    QPushButton *cmdDirectionFind;
    QTableWidget *tblMarkers;

    void setupUi(QWidget *wgt_marker_table)
    {
        if (wgt_marker_table->objectName().isEmpty())
            wgt_marker_table->setObjectName(QString::fromUtf8("wgt_marker_table"));
        wgt_marker_table->resize(1319, 280);
        wgt_marker_table->setMaximumSize(QSize(16777215, 280));
        horizontalLayout = new QHBoxLayout(wgt_marker_table);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(2, 0, 2, 0);
        wgt_marker_edit = new wgt_marker_editor(wgt_marker_table);
        wgt_marker_edit->setObjectName(QString::fromUtf8("wgt_marker_edit"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(wgt_marker_edit->sizePolicy().hasHeightForWidth());
        wgt_marker_edit->setSizePolicy(sizePolicy);
        wgt_marker_edit->setMaximumSize(QSize(280, 16777215));

        horizontalLayout->addWidget(wgt_marker_edit);

        wgtButtons = new QWidget(wgt_marker_table);
        wgtButtons->setObjectName(QString::fromUtf8("wgtButtons"));
        sizePolicy.setHeightForWidth(wgtButtons->sizePolicy().hasHeightForWidth());
        wgtButtons->setSizePolicy(sizePolicy);
        wgtButtons->setMaximumSize(QSize(230, 16000000));
        cmdAdd = new QPushButton(wgtButtons);
        cmdAdd->setObjectName(QString::fromUtf8("cmdAdd"));
        cmdAdd->setGeometry(QRect(20, 20, 85, 27));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/add"), QSize(), QIcon::Normal, QIcon::Off);
        cmdAdd->setIcon(icon);
        cmdRemove = new QPushButton(wgtButtons);
        cmdRemove->setObjectName(QString::fromUtf8("cmdRemove"));
        cmdRemove->setGeometry(QRect(20, 60, 85, 27));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/minus"), QSize(), QIcon::Normal, QIcon::Off);
        cmdRemove->setIcon(icon1);
        cmdGoto = new QPushButton(wgtButtons);
        cmdGoto->setObjectName(QString::fromUtf8("cmdGoto"));
        cmdGoto->setGeometry(QRect(20, 100, 85, 27));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("icons/forward_arrow.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmdGoto->setIcon(icon2);
        cmdExport = new QPushButton(wgtButtons);
        cmdExport->setObjectName(QString::fromUtf8("cmdExport"));
        cmdExport->setGeometry(QRect(120, 100, 85, 27));
        cmdRemoveAll = new QPushButton(wgtButtons);
        cmdRemoveAll->setObjectName(QString::fromUtf8("cmdRemoveAll"));
        cmdRemoveAll->setGeometry(QRect(120, 60, 85, 27));
        cmdMerge = new QPushButton(wgtButtons);
        cmdMerge->setObjectName(QString::fromUtf8("cmdMerge"));
        cmdMerge->setGeometry(QRect(120, 20, 85, 27));
        cmdDirectionFind = new QPushButton(wgtButtons);
        cmdDirectionFind->setObjectName(QString::fromUtf8("cmdDirectionFind"));
        cmdDirectionFind->setGeometry(QRect(20, 140, 184, 27));

        horizontalLayout->addWidget(wgtButtons);

        tblMarkers = new QTableWidget(wgt_marker_table);
        tblMarkers->setObjectName(QString::fromUtf8("tblMarkers"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(2);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tblMarkers->sizePolicy().hasHeightForWidth());
        tblMarkers->setSizePolicy(sizePolicy1);
        tblMarkers->setAlternatingRowColors(true);
        tblMarkers->setSelectionMode(QAbstractItemView::SingleSelection);
        tblMarkers->setSelectionBehavior(QAbstractItemView::SelectRows);

        horizontalLayout->addWidget(tblMarkers);


        retranslateUi(wgt_marker_table);

        QMetaObject::connectSlotsByName(wgt_marker_table);
    } // setupUi

    void retranslateUi(QWidget *wgt_marker_table)
    {
        wgt_marker_table->setWindowTitle(QCoreApplication::translate("wgt_marker_table", "Form", nullptr));
        cmdAdd->setText(QCoreApplication::translate("wgt_marker_table", "Add", nullptr));
        cmdRemove->setText(QCoreApplication::translate("wgt_marker_table", "Remove", nullptr));
        cmdGoto->setText(QCoreApplication::translate("wgt_marker_table", "Go To", nullptr));
        cmdExport->setText(QCoreApplication::translate("wgt_marker_table", "Export", nullptr));
        cmdRemoveAll->setText(QCoreApplication::translate("wgt_marker_table", "Remove All", nullptr));
        cmdMerge->setText(QCoreApplication::translate("wgt_marker_table", "Merge", nullptr));
        cmdDirectionFind->setText(QCoreApplication::translate("wgt_marker_table", "Direction Find", nullptr));
    } // retranslateUi

};

namespace Ui {
    class wgt_marker_table: public Ui_wgt_marker_table {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WGT_MARKER_TABLE_H
