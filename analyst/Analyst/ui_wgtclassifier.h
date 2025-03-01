/********************************************************************************
** Form generated from reading UI file 'wgtclassifier.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WGTCLASSIFIER_H
#define UI_WGTCLASSIFIER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_wgtClassifier
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QVBoxLayout *verticalLayout_8;
    QTableWidget *tblClassifiers;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_10;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *cmdAddClassifier;
    QPushButton *cmdRemoveClassifier;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *cmdClearTraininData;
    QSpacerItem *horizontalSpacer;
    QFrame *frame_3;
    QVBoxLayout *verticalLayout_9;
    QLabel *lblExportMarkerdata;
    QPushButton *cmdExportMarkerTrainingData;
    QCheckBox *chkAllTaggedMarkers;
    QWidget *wgtTraingStatus;
    QVBoxLayout *verticalLayout_2;
    QLabel *lbltrainingstatus;
    QPushButton *cmdStartStraining;

    void setupUi(QWidget *wgtClassifier)
    {
        if (wgtClassifier->objectName().isEmpty())
            wgtClassifier->setObjectName(QString::fromUtf8("wgtClassifier"));
        wgtClassifier->resize(271, 463);
        verticalLayout = new QVBoxLayout(wgtClassifier);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame = new QFrame(wgtClassifier);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_8 = new QVBoxLayout(frame);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        tblClassifiers = new QTableWidget(frame);
        if (tblClassifiers->columnCount() < 1)
            tblClassifiers->setColumnCount(1);
        tblClassifiers->setObjectName(QString::fromUtf8("tblClassifiers"));
        tblClassifiers->setMaximumSize(QSize(16777215, 300));
        tblClassifiers->setSelectionMode(QAbstractItemView::SingleSelection);
        tblClassifiers->setSelectionBehavior(QAbstractItemView::SelectRows);
        tblClassifiers->setColumnCount(1);

        verticalLayout_8->addWidget(tblClassifiers);


        verticalLayout->addWidget(frame);

        frame_2 = new QFrame(wgtClassifier);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setMinimumSize(QSize(0, 100));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        verticalLayout_10 = new QVBoxLayout(frame_2);
        verticalLayout_10->setSpacing(2);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        verticalLayout_10->setContentsMargins(2, 2, 2, 2);
        widget_2 = new QWidget(frame_2);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        horizontalLayout_7 = new QHBoxLayout(widget_2);
        horizontalLayout_7->setSpacing(3);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(3, 3, 3, 3);
        cmdAddClassifier = new QPushButton(widget_2);
        cmdAddClassifier->setObjectName(QString::fromUtf8("cmdAddClassifier"));

        horizontalLayout_7->addWidget(cmdAddClassifier);

        cmdRemoveClassifier = new QPushButton(widget_2);
        cmdRemoveClassifier->setObjectName(QString::fromUtf8("cmdRemoveClassifier"));

        horizontalLayout_7->addWidget(cmdRemoveClassifier);


        verticalLayout_10->addWidget(widget_2);

        widget_3 = new QWidget(frame_2);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        horizontalLayout_6 = new QHBoxLayout(widget_3);
        horizontalLayout_6->setSpacing(2);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(2, 2, 2, 2);
        cmdClearTraininData = new QPushButton(widget_3);
        cmdClearTraininData->setObjectName(QString::fromUtf8("cmdClearTraininData"));

        horizontalLayout_6->addWidget(cmdClearTraininData);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer);


        verticalLayout_10->addWidget(widget_3);


        verticalLayout->addWidget(frame_2);

        frame_3 = new QFrame(wgtClassifier);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setMinimumSize(QSize(0, 100));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        verticalLayout_9 = new QVBoxLayout(frame_3);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        lblExportMarkerdata = new QLabel(frame_3);
        lblExportMarkerdata->setObjectName(QString::fromUtf8("lblExportMarkerdata"));
        lblExportMarkerdata->setWordWrap(true);

        verticalLayout_9->addWidget(lblExportMarkerdata);

        cmdExportMarkerTrainingData = new QPushButton(frame_3);
        cmdExportMarkerTrainingData->setObjectName(QString::fromUtf8("cmdExportMarkerTrainingData"));

        verticalLayout_9->addWidget(cmdExportMarkerTrainingData);

        chkAllTaggedMarkers = new QCheckBox(frame_3);
        chkAllTaggedMarkers->setObjectName(QString::fromUtf8("chkAllTaggedMarkers"));

        verticalLayout_9->addWidget(chkAllTaggedMarkers);


        verticalLayout->addWidget(frame_3);

        wgtTraingStatus = new QWidget(wgtClassifier);
        wgtTraingStatus->setObjectName(QString::fromUtf8("wgtTraingStatus"));
        wgtTraingStatus->setMinimumSize(QSize(0, 100));
        verticalLayout_2 = new QVBoxLayout(wgtTraingStatus);
        verticalLayout_2->setSpacing(2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(2, 2, 2, 2);
        lbltrainingstatus = new QLabel(wgtTraingStatus);
        lbltrainingstatus->setObjectName(QString::fromUtf8("lbltrainingstatus"));
        lbltrainingstatus->setWordWrap(true);

        verticalLayout_2->addWidget(lbltrainingstatus);

        cmdStartStraining = new QPushButton(wgtTraingStatus);
        cmdStartStraining->setObjectName(QString::fromUtf8("cmdStartStraining"));

        verticalLayout_2->addWidget(cmdStartStraining);


        verticalLayout->addWidget(wgtTraingStatus);


        retranslateUi(wgtClassifier);

        QMetaObject::connectSlotsByName(wgtClassifier);
    } // setupUi

    void retranslateUi(QWidget *wgtClassifier)
    {
        wgtClassifier->setWindowTitle(QCoreApplication::translate("wgtClassifier", "Form", nullptr));
        cmdAddClassifier->setText(QCoreApplication::translate("wgtClassifier", "Add", nullptr));
        cmdRemoveClassifier->setText(QCoreApplication::translate("wgtClassifier", "Remove", nullptr));
        cmdClearTraininData->setText(QCoreApplication::translate("wgtClassifier", "Clear Data", nullptr));
        lblExportMarkerdata->setText(QCoreApplication::translate("wgtClassifier", "Exported Selected Tagged Marker to Training data.", nullptr));
        cmdExportMarkerTrainingData->setText(QCoreApplication::translate("wgtClassifier", "Export Training Data", nullptr));
        chkAllTaggedMarkers->setText(QCoreApplication::translate("wgtClassifier", "All Tagged Markers", nullptr));
        lbltrainingstatus->setText(QString());
        cmdStartStraining->setText(QCoreApplication::translate("wgtClassifier", "Start Training", nullptr));
    } // retranslateUi

};

namespace Ui {
    class wgtClassifier: public Ui_wgtClassifier {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WGTCLASSIFIER_H
