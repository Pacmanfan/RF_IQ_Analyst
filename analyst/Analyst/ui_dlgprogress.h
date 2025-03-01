/********************************************************************************
** Form generated from reading UI file 'dlgprogress.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGPROGRESS_H
#define UI_DLGPROGRESS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_dlgProgress
{
public:
    QHBoxLayout *horizontalLayout;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QProgressBar *progressBar;

    void setupUi(QDialog *dlgProgress)
    {
        if (dlgProgress->objectName().isEmpty())
            dlgProgress->setObjectName(QString::fromUtf8("dlgProgress"));
        dlgProgress->resize(407, 110);
        horizontalLayout = new QHBoxLayout(dlgProgress);
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(2, 2, 2, 2);
        frame = new QFrame(dlgProgress);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setPointSize(16);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        progressBar = new QProgressBar(frame);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setMaximum(0);
        progressBar->setValue(-1);

        verticalLayout->addWidget(progressBar);


        horizontalLayout->addWidget(frame);


        retranslateUi(dlgProgress);

        QMetaObject::connectSlotsByName(dlgProgress);
    } // setupUi

    void retranslateUi(QDialog *dlgProgress)
    {
        dlgProgress->setWindowTitle(QCoreApplication::translate("dlgProgress", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("dlgProgress", "Building File Index", nullptr));
    } // retranslateUi

};

namespace Ui {
    class dlgProgress: public Ui_dlgProgress {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGPROGRESS_H
