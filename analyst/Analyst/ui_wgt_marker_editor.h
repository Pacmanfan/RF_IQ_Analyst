/********************************************************************************
** Form generated from reading UI file 'wgt_marker_editor.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WGT_MARKER_EDITOR_H
#define UI_WGT_MARKER_EDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_wgt_marker_editor
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *lblName;
    QLineEdit *leName;
    QWidget *wgtBWCF;
    QHBoxLayout *horizontalLayout;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout_3;
    QLabel *lblCF;
    QLineEdit *leCF;
    QWidget *wgtBW;
    QVBoxLayout *verticalLayout_2;
    QLabel *lblBW;
    QLineEdit *leBW;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_2;
    QWidget *widget_5;
    QVBoxLayout *verticalLayout_4;
    QLabel *lblLowF;
    QLineEdit *leLowF;
    QWidget *widget_6;
    QVBoxLayout *verticalLayout_5;
    QLabel *lblHighF;
    QLineEdit *leHighF;
    QWidget *wgt_st_end_t;
    QHBoxLayout *horizontalLayout_4;
    QWidget *wgtstatime;
    QVBoxLayout *verticalLayout_8;
    QLabel *lblStartTime;
    QLineEdit *leStartTime;
    QWidget *widget_12;
    QVBoxLayout *verticalLayout_9;
    QLabel *lblEndTime;
    QLineEdit *leEndTime;
    QWidget *widget_11;
    QHBoxLayout *horizontalLayout_6;
    QLabel *lblDuration;
    QWidget *wgtTimeChks;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *chkNoStartT;
    QCheckBox *chkNoEndT;
    QWidget *wgtTags;
    QVBoxLayout *verticalLayout_6;
    QLabel *lblTags;
    QLineEdit *leTags;

    void setupUi(QFrame *wgt_marker_editor)
    {
        if (wgt_marker_editor->objectName().isEmpty())
            wgt_marker_editor->setObjectName(QString::fromUtf8("wgt_marker_editor"));
        wgt_marker_editor->resize(279, 277);
        wgt_marker_editor->setFrameShape(QFrame::StyledPanel);
        wgt_marker_editor->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(wgt_marker_editor);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(2, 0, 2, 0);
        lblName = new QLabel(wgt_marker_editor);
        lblName->setObjectName(QString::fromUtf8("lblName"));

        verticalLayout->addWidget(lblName);

        leName = new QLineEdit(wgt_marker_editor);
        leName->setObjectName(QString::fromUtf8("leName"));

        verticalLayout->addWidget(leName);

        wgtBWCF = new QWidget(wgt_marker_editor);
        wgtBWCF->setObjectName(QString::fromUtf8("wgtBWCF"));
        horizontalLayout = new QHBoxLayout(wgtBWCF);
        horizontalLayout->setSpacing(1);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(1, 1, 1, 1);
        widget_3 = new QWidget(wgtBWCF);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        verticalLayout_3 = new QVBoxLayout(widget_3);
        verticalLayout_3->setSpacing(1);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(1, 1, 1, 1);
        lblCF = new QLabel(widget_3);
        lblCF->setObjectName(QString::fromUtf8("lblCF"));

        verticalLayout_3->addWidget(lblCF);

        leCF = new QLineEdit(widget_3);
        leCF->setObjectName(QString::fromUtf8("leCF"));

        verticalLayout_3->addWidget(leCF);


        horizontalLayout->addWidget(widget_3);

        wgtBW = new QWidget(wgtBWCF);
        wgtBW->setObjectName(QString::fromUtf8("wgtBW"));
        verticalLayout_2 = new QVBoxLayout(wgtBW);
        verticalLayout_2->setSpacing(1);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(1, 1, 1, 1);
        lblBW = new QLabel(wgtBW);
        lblBW->setObjectName(QString::fromUtf8("lblBW"));

        verticalLayout_2->addWidget(lblBW);

        leBW = new QLineEdit(wgtBW);
        leBW->setObjectName(QString::fromUtf8("leBW"));

        verticalLayout_2->addWidget(leBW);


        horizontalLayout->addWidget(wgtBW);


        verticalLayout->addWidget(wgtBWCF);

        widget_4 = new QWidget(wgt_marker_editor);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        horizontalLayout_2 = new QHBoxLayout(widget_4);
        horizontalLayout_2->setSpacing(1);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(1, 0, 1, 0);
        widget_5 = new QWidget(widget_4);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        verticalLayout_4 = new QVBoxLayout(widget_5);
        verticalLayout_4->setSpacing(1);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(1, 1, 1, 1);
        lblLowF = new QLabel(widget_5);
        lblLowF->setObjectName(QString::fromUtf8("lblLowF"));

        verticalLayout_4->addWidget(lblLowF);

        leLowF = new QLineEdit(widget_5);
        leLowF->setObjectName(QString::fromUtf8("leLowF"));

        verticalLayout_4->addWidget(leLowF);


        horizontalLayout_2->addWidget(widget_5);

        widget_6 = new QWidget(widget_4);
        widget_6->setObjectName(QString::fromUtf8("widget_6"));
        verticalLayout_5 = new QVBoxLayout(widget_6);
        verticalLayout_5->setSpacing(1);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(1, 1, 1, 1);
        lblHighF = new QLabel(widget_6);
        lblHighF->setObjectName(QString::fromUtf8("lblHighF"));

        verticalLayout_5->addWidget(lblHighF);

        leHighF = new QLineEdit(widget_6);
        leHighF->setObjectName(QString::fromUtf8("leHighF"));

        verticalLayout_5->addWidget(leHighF);


        horizontalLayout_2->addWidget(widget_6);


        verticalLayout->addWidget(widget_4);

        wgt_st_end_t = new QWidget(wgt_marker_editor);
        wgt_st_end_t->setObjectName(QString::fromUtf8("wgt_st_end_t"));
        horizontalLayout_4 = new QHBoxLayout(wgt_st_end_t);
        horizontalLayout_4->setSpacing(1);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(1, 1, 1, 1);
        wgtstatime = new QWidget(wgt_st_end_t);
        wgtstatime->setObjectName(QString::fromUtf8("wgtstatime"));
        verticalLayout_8 = new QVBoxLayout(wgtstatime);
        verticalLayout_8->setSpacing(1);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(1, 0, 1, 0);
        lblStartTime = new QLabel(wgtstatime);
        lblStartTime->setObjectName(QString::fromUtf8("lblStartTime"));

        verticalLayout_8->addWidget(lblStartTime);

        leStartTime = new QLineEdit(wgtstatime);
        leStartTime->setObjectName(QString::fromUtf8("leStartTime"));

        verticalLayout_8->addWidget(leStartTime);


        horizontalLayout_4->addWidget(wgtstatime);

        widget_12 = new QWidget(wgt_st_end_t);
        widget_12->setObjectName(QString::fromUtf8("widget_12"));
        verticalLayout_9 = new QVBoxLayout(widget_12);
        verticalLayout_9->setSpacing(1);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        verticalLayout_9->setContentsMargins(1, 0, 1, 0);
        lblEndTime = new QLabel(widget_12);
        lblEndTime->setObjectName(QString::fromUtf8("lblEndTime"));

        verticalLayout_9->addWidget(lblEndTime);

        leEndTime = new QLineEdit(widget_12);
        leEndTime->setObjectName(QString::fromUtf8("leEndTime"));

        verticalLayout_9->addWidget(leEndTime);


        horizontalLayout_4->addWidget(widget_12);


        verticalLayout->addWidget(wgt_st_end_t);

        widget_11 = new QWidget(wgt_marker_editor);
        widget_11->setObjectName(QString::fromUtf8("widget_11"));
        horizontalLayout_6 = new QHBoxLayout(widget_11);
        horizontalLayout_6->setSpacing(1);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(1, 1, 1, 0);
        lblDuration = new QLabel(widget_11);
        lblDuration->setObjectName(QString::fromUtf8("lblDuration"));

        horizontalLayout_6->addWidget(lblDuration);


        verticalLayout->addWidget(widget_11);

        wgtTimeChks = new QWidget(wgt_marker_editor);
        wgtTimeChks->setObjectName(QString::fromUtf8("wgtTimeChks"));
        horizontalLayout_3 = new QHBoxLayout(wgtTimeChks);
        horizontalLayout_3->setSpacing(1);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(1, 0, 1, 0);
        chkNoStartT = new QCheckBox(wgtTimeChks);
        chkNoStartT->setObjectName(QString::fromUtf8("chkNoStartT"));

        horizontalLayout_3->addWidget(chkNoStartT);

        chkNoEndT = new QCheckBox(wgtTimeChks);
        chkNoEndT->setObjectName(QString::fromUtf8("chkNoEndT"));

        horizontalLayout_3->addWidget(chkNoEndT);


        verticalLayout->addWidget(wgtTimeChks);

        wgtTags = new QWidget(wgt_marker_editor);
        wgtTags->setObjectName(QString::fromUtf8("wgtTags"));
        verticalLayout_6 = new QVBoxLayout(wgtTags);
        verticalLayout_6->setSpacing(1);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(1, 1, 1, 1);
        lblTags = new QLabel(wgtTags);
        lblTags->setObjectName(QString::fromUtf8("lblTags"));

        verticalLayout_6->addWidget(lblTags);

        leTags = new QLineEdit(wgtTags);
        leTags->setObjectName(QString::fromUtf8("leTags"));

        verticalLayout_6->addWidget(leTags);


        verticalLayout->addWidget(wgtTags);


        retranslateUi(wgt_marker_editor);

        QMetaObject::connectSlotsByName(wgt_marker_editor);
    } // setupUi

    void retranslateUi(QFrame *wgt_marker_editor)
    {
        wgt_marker_editor->setWindowTitle(QCoreApplication::translate("wgt_marker_editor", "Frame", nullptr));
        lblName->setText(QCoreApplication::translate("wgt_marker_editor", "Name", nullptr));
        lblCF->setText(QCoreApplication::translate("wgt_marker_editor", "Center Freq (Mhz)", nullptr));
        lblBW->setText(QCoreApplication::translate("wgt_marker_editor", "Bandwidth (Mhz)", nullptr));
        lblLowF->setText(QCoreApplication::translate("wgt_marker_editor", "Low Freq (Mhz)", nullptr));
        lblHighF->setText(QCoreApplication::translate("wgt_marker_editor", "High Freq (Mhz)", nullptr));
        lblStartTime->setText(QCoreApplication::translate("wgt_marker_editor", "Start Time (S)", nullptr));
        lblEndTime->setText(QCoreApplication::translate("wgt_marker_editor", "End Time (S)", nullptr));
        lblDuration->setText(QCoreApplication::translate("wgt_marker_editor", "Duration (S)", nullptr));
        chkNoStartT->setText(QCoreApplication::translate("wgt_marker_editor", "No Start Time", nullptr));
        chkNoEndT->setText(QCoreApplication::translate("wgt_marker_editor", "No End Time", nullptr));
        lblTags->setText(QCoreApplication::translate("wgt_marker_editor", "Tags", nullptr));
    } // retranslateUi

};

namespace Ui {
    class wgt_marker_editor: public Ui_wgt_marker_editor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WGT_MARKER_EDITOR_H
