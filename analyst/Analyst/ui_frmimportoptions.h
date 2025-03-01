/********************************************************************************
** Form generated from reading UI file 'frmimportoptions.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMIMPORTOPTIONS_H
#define UI_FRMIMPORTOPTIONS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frmImportOptions
{
public:
    QVBoxLayout *verticalLayout_2;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QTableWidget *tblRecInfo;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QComboBox *cmbStreamID;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *frmImportOptions)
    {
        if (frmImportOptions->objectName().isEmpty())
            frmImportOptions->setObjectName(QString::fromUtf8("frmImportOptions"));
        frmImportOptions->resize(592, 572);
        verticalLayout_2 = new QVBoxLayout(frmImportOptions);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        frame = new QFrame(frmImportOptions);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setPointSize(14);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        tblRecInfo = new QTableWidget(frame);
        tblRecInfo->setObjectName(QString::fromUtf8("tblRecInfo"));
        tblRecInfo->horizontalHeader()->setVisible(false);
        tblRecInfo->verticalHeader()->setVisible(false);

        verticalLayout->addWidget(tblRecInfo);

        widget = new QWidget(frame);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);

        horizontalLayout->addWidget(label_2);

        cmbStreamID = new QComboBox(widget);
        cmbStreamID->setObjectName(QString::fromUtf8("cmbStreamID"));
        cmbStreamID->setFont(font);

        horizontalLayout->addWidget(cmbStreamID);


        verticalLayout->addWidget(widget);

        buttonBox = new QDialogButtonBox(frame);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        verticalLayout_2->addWidget(frame);


        retranslateUi(frmImportOptions);
        QObject::connect(buttonBox, SIGNAL(accepted()), frmImportOptions, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), frmImportOptions, SLOT(reject()));

        QMetaObject::connectSlotsByName(frmImportOptions);
    } // setupUi

    void retranslateUi(QDialog *frmImportOptions)
    {
        frmImportOptions->setWindowTitle(QCoreApplication::translate("frmImportOptions", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("frmImportOptions", "File Recording Details", nullptr));
        label_2->setText(QCoreApplication::translate("frmImportOptions", "Stream ID", nullptr));
    } // retranslateUi

};

namespace Ui {
    class frmImportOptions: public Ui_frmImportOptions {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMIMPORTOPTIONS_H
