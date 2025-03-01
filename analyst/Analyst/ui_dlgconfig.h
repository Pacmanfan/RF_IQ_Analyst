/********************************************************************************
** Form generated from reading UI file 'dlgconfig.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGCONFIG_H
#define UI_DLGCONFIG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_dlgConfig
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tbAudio;
    QWidget *wgtPlaybackDevice;
    QHBoxLayout *horizontalLayout;
    QLabel *lblPlaybackDevice;
    QComboBox *cmbPlaybackDevice;
    QWidget *wgtPlaybackrate;
    QHBoxLayout *horizontalLayout_2;
    QLabel *lblPlaybackrate;
    QComboBox *cmbPlaybackrate;
    QWidget *tbplug;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QTableWidget *tblPlugins;
    QTextBrowser *textBrowser;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *dlgConfig)
    {
        if (dlgConfig->objectName().isEmpty())
            dlgConfig->setObjectName(QString::fromUtf8("dlgConfig"));
        dlgConfig->resize(543, 442);
        verticalLayout = new QVBoxLayout(dlgConfig);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new QTabWidget(dlgConfig);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tbAudio = new QWidget();
        tbAudio->setObjectName(QString::fromUtf8("tbAudio"));
        wgtPlaybackDevice = new QWidget(tbAudio);
        wgtPlaybackDevice->setObjectName(QString::fromUtf8("wgtPlaybackDevice"));
        wgtPlaybackDevice->setGeometry(QRect(10, 10, 331, 45));
        horizontalLayout = new QHBoxLayout(wgtPlaybackDevice);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lblPlaybackDevice = new QLabel(wgtPlaybackDevice);
        lblPlaybackDevice->setObjectName(QString::fromUtf8("lblPlaybackDevice"));

        horizontalLayout->addWidget(lblPlaybackDevice);

        cmbPlaybackDevice = new QComboBox(wgtPlaybackDevice);
        cmbPlaybackDevice->setObjectName(QString::fromUtf8("cmbPlaybackDevice"));

        horizontalLayout->addWidget(cmbPlaybackDevice);

        wgtPlaybackrate = new QWidget(tbAudio);
        wgtPlaybackrate->setObjectName(QString::fromUtf8("wgtPlaybackrate"));
        wgtPlaybackrate->setGeometry(QRect(10, 60, 331, 45));
        horizontalLayout_2 = new QHBoxLayout(wgtPlaybackrate);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        lblPlaybackrate = new QLabel(wgtPlaybackrate);
        lblPlaybackrate->setObjectName(QString::fromUtf8("lblPlaybackrate"));

        horizontalLayout_2->addWidget(lblPlaybackrate);

        cmbPlaybackrate = new QComboBox(wgtPlaybackrate);
        cmbPlaybackrate->setObjectName(QString::fromUtf8("cmbPlaybackrate"));

        horizontalLayout_2->addWidget(cmbPlaybackrate);

        tabWidget->addTab(tbAudio, QString());
        tbplug = new QWidget();
        tbplug->setObjectName(QString::fromUtf8("tbplug"));
        verticalLayout_2 = new QVBoxLayout(tbplug);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label = new QLabel(tbplug);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_2->addWidget(label);

        tblPlugins = new QTableWidget(tbplug);
        tblPlugins->setObjectName(QString::fromUtf8("tblPlugins"));

        verticalLayout_2->addWidget(tblPlugins);

        textBrowser = new QTextBrowser(tbplug);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));

        verticalLayout_2->addWidget(textBrowser);

        tabWidget->addTab(tbplug, QString());

        verticalLayout->addWidget(tabWidget);

        buttonBox = new QDialogButtonBox(dlgConfig);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(dlgConfig);
        QObject::connect(buttonBox, SIGNAL(accepted()), dlgConfig, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), dlgConfig, SLOT(reject()));

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(dlgConfig);
    } // setupUi

    void retranslateUi(QDialog *dlgConfig)
    {
        dlgConfig->setWindowTitle(QCoreApplication::translate("dlgConfig", "Dialog", nullptr));
        lblPlaybackDevice->setText(QCoreApplication::translate("dlgConfig", "Audio Playback Device", nullptr));
        lblPlaybackrate->setText(QCoreApplication::translate("dlgConfig", "Audio Playback Rate", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tbAudio), QCoreApplication::translate("dlgConfig", "Audio", nullptr));
        label->setText(QCoreApplication::translate("dlgConfig", "Plugin Information", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tbplug), QCoreApplication::translate("dlgConfig", "Plugins", nullptr));
    } // retranslateUi

};

namespace Ui {
    class dlgConfig: public Ui_dlgConfig {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGCONFIG_H
