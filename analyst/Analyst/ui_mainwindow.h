/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <ctkRangeSlider.h>
#include "qconstellationplot.h"
#include "wgt_fft.h"
#include "wgt_marker_table.h"
#include "wgt_scope.h"
#include "wgt_waterfall.h"
#include "wgtclassifier.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QWidget *wgtMainTop;
    QHBoxLayout *horizontalLayout;
    QWidget *wgtLeftTool;
    QVBoxLayout *verticalLayout_2;
    QWidget *wgTopInfo;
    QVBoxLayout *verticalLayout_4;
    QFrame *frametitle;
    QHBoxLayout *horizontalLayout_3;
    QLabel *lblIcon;
    QLabel *lblTitle;
    QTabWidget *tabSelectors;
    QWidget *tbInfo;
    QVBoxLayout *verticalLayout_7;
    QWidget *widgetBox;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *StreamInfoLayout;
    QLabel *lblName;
    QLabel *lblDuration;
    QLabel *lblCenterFreq;
    QLabel *lblFreqRange;
    QLabel *lblBandwidth;
    QLabel *lblGain;
    QVBoxLayout *FFTWaterfallLayout;
    QLabel *lblNumBinsRBW;
    QLabel *lblRBW;
    QSlider *sldFFTRes;
    QLabel *lblFFT_TimeRes;
    QLabel *lblFFT_LineTime;
    QSlider *sldFFTTimRes;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_10;
    QLabel *lblWaterfallColorScheme;
    QComboBox *cmbWaterfallScheme;
    QWidget *wgtWaterfallDirection;
    QHBoxLayout *horizontalLayout_2;
    QLabel *lblWaterDir;
    QComboBox *cmbWaterDir;
    ctkRangeSlider *sldWaterRange;
    QCheckBox *chkAutoRange;
    QPushButton *cmdClearMax;
    QVBoxLayout *TimeFreqStampLayout;
    QLabel *lblPlaybackTimestamp;
    QLabel *lblPlaybackIndex;
    QLabel *lblMOTime;
    QLabel *lblMOFreq;
    QCheckBox *chkWindowFilter;
    QSpacerItem *verticalSpacer_4;
    QWidget *wgtShowControls;
    QHBoxLayout *horizontalLayout_14;
    QCheckBox *chkShowFFT;
    QCheckBox *chkShowScope;
    QCheckBox *chkShowConstellation;
    QWidget *wgtShowControls2;
    QHBoxLayout *horizontalLayout_6;
    QCheckBox *chkMap;
    QCheckBox *chkMarkers;
    QCheckBox *chkShowWaterfall;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_12;
    QPushButton *cmdSettings;
    QPushButton *cmdHelp;
    QPushButton *cmdWorkshop;
    QSpacerItem *horizontalSpacer;
    QPushButton *cmdLoad;
    QWidget *tbClassifier;
    QVBoxLayout *verticalLayout_3;
    wgtClassifier *wgtClassifiers;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_5;
    QGroupBox *groupBox;
    QComboBox *cmbClassifySel;
    QPushButton *cmdClassify;
    QLabel *lblClsRslt;
    QWidget *tbTools;
    QVBoxLayout *verticalLayout_8;
    QVBoxLayout *PluginLayout;
    QComboBox *cmbTool;
    QWidget *wgt_tool_parent;
    QWidget *plgControl;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *cmdDecode;
    QPushButton *cmdProcess;
    QPushButton *cmdDetect;
    QPushButton *cmdEnergyDetect2;
    QSlider *sldDetectSensitivity;
    QSpacerItem *verticalSpacer_3;
    QWidget *wgtRightMain;
    QVBoxLayout *vboxLayout;
    QWidget *wgtScope_Const;
    QHBoxLayout *horizontalLayout_15;
    wgt_Scope *wgtScope2;
    QConstellationPlot *wgtConst;
    wgt_FFT *wgtFFT2;
    wgt_waterfall *wgtWaterfall;
    QWidget *wgtMapDoc;
    wgt_marker_table *wgtMarkerTable;
    QWidget *widget;
    QVBoxLayout *verticalLayout_5;
    QSpacerItem *verticalSpacer_2;
    QWidget *widget_6;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout_9;
    QPushButton *cmdPageup;
    QPushButton *cmdUp;
    QPushButton *cmdUp_Small;
    QPushButton *cmdDown_Small;
    QPushButton *cmdDown;
    QPushButton *cmdPageDown;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1024, 894);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(1);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(1, 1, 1, 1);
        wgtMainTop = new QWidget(centralWidget);
        wgtMainTop->setObjectName(QString::fromUtf8("wgtMainTop"));
        horizontalLayout = new QHBoxLayout(wgtMainTop);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        wgtLeftTool = new QWidget(wgtMainTop);
        wgtLeftTool->setObjectName(QString::fromUtf8("wgtLeftTool"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(wgtLeftTool->sizePolicy().hasHeightForWidth());
        wgtLeftTool->setSizePolicy(sizePolicy);
        wgtLeftTool->setMinimumSize(QSize(0, 0));
        verticalLayout_2 = new QVBoxLayout(wgtLeftTool);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(1, 1, 1, 1);
        wgTopInfo = new QWidget(wgtLeftTool);
        wgTopInfo->setObjectName(QString::fromUtf8("wgTopInfo"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(wgTopInfo->sizePolicy().hasHeightForWidth());
        wgTopInfo->setSizePolicy(sizePolicy1);
        wgTopInfo->setMinimumSize(QSize(0, 40));
        wgTopInfo->setMaximumSize(QSize(16777215, 40));
        verticalLayout_4 = new QVBoxLayout(wgTopInfo);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(5, 5, 5, 5);
        frametitle = new QFrame(wgTopInfo);
        frametitle->setObjectName(QString::fromUtf8("frametitle"));
        frametitle->setMinimumSize(QSize(0, 35));
        frametitle->setMaximumSize(QSize(16777215, 35));
        frametitle->setFrameShape(QFrame::StyledPanel);
        frametitle->setFrameShadow(QFrame::Raised);
        horizontalLayout_3 = new QHBoxLayout(frametitle);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(1, 1, 1, 1);
        lblIcon = new QLabel(frametitle);
        lblIcon->setObjectName(QString::fromUtf8("lblIcon"));
        lblIcon->setMinimumSize(QSize(32, 32));
        lblIcon->setMaximumSize(QSize(32, 32));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        lblIcon->setFont(font);
        lblIcon->setPixmap(QPixmap(QString::fromUtf8(":/icons/analyst")));
        lblIcon->setScaledContents(true);
        lblIcon->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(lblIcon);

        lblTitle = new QLabel(frametitle);
        lblTitle->setObjectName(QString::fromUtf8("lblTitle"));
        lblTitle->setMinimumSize(QSize(196, 0));
        lblTitle->setFont(font);
        lblTitle->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(lblTitle);


        verticalLayout_4->addWidget(frametitle);


        verticalLayout_2->addWidget(wgTopInfo);

        tabSelectors = new QTabWidget(wgtLeftTool);
        tabSelectors->setObjectName(QString::fromUtf8("tabSelectors"));
        tbInfo = new QWidget();
        tbInfo->setObjectName(QString::fromUtf8("tbInfo"));
        verticalLayout_7 = new QVBoxLayout(tbInfo);
        verticalLayout_7->setSpacing(1);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(5, 3, 5, 3);
        widgetBox = new QWidget(tbInfo);
        widgetBox->setObjectName(QString::fromUtf8("widgetBox"));
        widgetBox->setProperty("currentIndex", QVariant(-1));
        widgetBox->setProperty("isPageExpanded", QVariant(true));
        verticalLayout_6 = new QVBoxLayout(widgetBox);
        verticalLayout_6->setSpacing(2);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(2, 2, 2, 2);
        StreamInfoLayout = new QVBoxLayout();
        StreamInfoLayout->setSpacing(0);
        StreamInfoLayout->setObjectName(QString::fromUtf8("StreamInfoLayout"));
        StreamInfoLayout->setContentsMargins(1, 1, 1, 1);
        lblName = new QLabel(widgetBox);
        lblName->setObjectName(QString::fromUtf8("lblName"));
        QFont font1;
        font1.setPointSize(9);
        font1.setBold(true);
        lblName->setFont(font1);

        StreamInfoLayout->addWidget(lblName);

        lblDuration = new QLabel(widgetBox);
        lblDuration->setObjectName(QString::fromUtf8("lblDuration"));
        lblDuration->setFont(font1);

        StreamInfoLayout->addWidget(lblDuration);

        lblCenterFreq = new QLabel(widgetBox);
        lblCenterFreq->setObjectName(QString::fromUtf8("lblCenterFreq"));
        lblCenterFreq->setFont(font1);

        StreamInfoLayout->addWidget(lblCenterFreq);

        lblFreqRange = new QLabel(widgetBox);
        lblFreqRange->setObjectName(QString::fromUtf8("lblFreqRange"));
        lblFreqRange->setFont(font1);

        StreamInfoLayout->addWidget(lblFreqRange);

        lblBandwidth = new QLabel(widgetBox);
        lblBandwidth->setObjectName(QString::fromUtf8("lblBandwidth"));
        lblBandwidth->setFont(font1);

        StreamInfoLayout->addWidget(lblBandwidth);

        lblGain = new QLabel(widgetBox);
        lblGain->setObjectName(QString::fromUtf8("lblGain"));
        lblGain->setFont(font1);

        StreamInfoLayout->addWidget(lblGain);


        verticalLayout_6->addLayout(StreamInfoLayout);

        FFTWaterfallLayout = new QVBoxLayout();
        FFTWaterfallLayout->setSpacing(0);
        FFTWaterfallLayout->setObjectName(QString::fromUtf8("FFTWaterfallLayout"));
        FFTWaterfallLayout->setContentsMargins(0, 0, 0, 0);
        lblNumBinsRBW = new QLabel(widgetBox);
        lblNumBinsRBW->setObjectName(QString::fromUtf8("lblNumBinsRBW"));
        lblNumBinsRBW->setFont(font1);

        FFTWaterfallLayout->addWidget(lblNumBinsRBW);

        lblRBW = new QLabel(widgetBox);
        lblRBW->setObjectName(QString::fromUtf8("lblRBW"));
        lblRBW->setFont(font1);

        FFTWaterfallLayout->addWidget(lblRBW);

        sldFFTRes = new QSlider(widgetBox);
        sldFFTRes->setObjectName(QString::fromUtf8("sldFFTRes"));
        sldFFTRes->setMinimumSize(QSize(0, 20));
        sldFFTRes->setStyleSheet(QString::fromUtf8(".QSlider {\n"
"    min-height: 20x;\n"
"    max-height: 20px;\n"
"}\n"
"\n"
".QSlider::groove:horizontal {\n"
"    border: 1px solid #262626;\n"
"    height: 5px;\n"
"    background: #505050;\n"
"    margin: 0 12px;\n"
"}\n"
"\n"
".QSlider::handle:horizontal {\n"
"    background: rgb(252, 252, 252);\n"
"    border: 2px solid black;\n"
"    width: 20px;\n"
"    height: 20px;\n"
"    margin: -7px -7px;\n"
"}\n"
"QSlider::sub-page\n"
"{\n"
"    background: rgb(41, 128, 218);\n"
"}\n"
"\n"
"QSlider::add-page \n"
"{\n"
"    background: rgb(186, 186, 186);\n"
"}\n"
"\n"
"QSlider {\n"
"    height: 20px;\n"
"}"));
        sldFFTRes->setMinimum(0);
        sldFFTRes->setMaximum(6);
        sldFFTRes->setPageStep(2);
        sldFFTRes->setValue(4);
        sldFFTRes->setOrientation(Qt::Horizontal);

        FFTWaterfallLayout->addWidget(sldFFTRes);

        lblFFT_TimeRes = new QLabel(widgetBox);
        lblFFT_TimeRes->setObjectName(QString::fromUtf8("lblFFT_TimeRes"));
        lblFFT_TimeRes->setFont(font1);

        FFTWaterfallLayout->addWidget(lblFFT_TimeRes);

        lblFFT_LineTime = new QLabel(widgetBox);
        lblFFT_LineTime->setObjectName(QString::fromUtf8("lblFFT_LineTime"));
        lblFFT_LineTime->setFont(font1);

        FFTWaterfallLayout->addWidget(lblFFT_LineTime);

        sldFFTTimRes = new QSlider(widgetBox);
        sldFFTTimRes->setObjectName(QString::fromUtf8("sldFFTTimRes"));
        sldFFTTimRes->setStyleSheet(QString::fromUtf8(".QSlider {\n"
"    min-height: 20x;\n"
"    max-height: 20px;\n"
"}\n"
"\n"
".QSlider::groove:horizontal {\n"
"    border: 1px solid #262626;\n"
"    height: 5px;\n"
"    background: #505050;\n"
"    margin: 0 12px;\n"
"}\n"
"\n"
".QSlider::handle:horizontal {\n"
"    background: rgb(252, 252, 252);\n"
"    border: 2px solid black;\n"
"    width: 20px;\n"
"    height: 20px;\n"
"    margin: -7px -7px;\n"
"}\n"
"QSlider::sub-page\n"
"{\n"
"    background: rgb(41, 128, 218);\n"
"}\n"
"\n"
"QSlider::add-page \n"
"{\n"
"    background: rgb(186, 186, 186);\n"
"}\n"
"\n"
"QSlider {\n"
"    height: 20px;\n"
"}"));
        sldFFTTimRes->setMaximum(16);
        sldFFTTimRes->setPageStep(2);
        sldFFTTimRes->setValue(1);
        sldFFTTimRes->setOrientation(Qt::Horizontal);

        FFTWaterfallLayout->addWidget(sldFFTTimRes);

        widget_4 = new QWidget(widgetBox);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        widget_4->setMinimumSize(QSize(0, 38));
        horizontalLayout_10 = new QHBoxLayout(widget_4);
        horizontalLayout_10->setSpacing(0);
        horizontalLayout_10->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        horizontalLayout_10->setContentsMargins(0, 0, 0, 0);
        lblWaterfallColorScheme = new QLabel(widget_4);
        lblWaterfallColorScheme->setObjectName(QString::fromUtf8("lblWaterfallColorScheme"));
        lblWaterfallColorScheme->setMaximumSize(QSize(139, 16777215));
        QFont font2;
        font2.setBold(true);
        lblWaterfallColorScheme->setFont(font2);

        horizontalLayout_10->addWidget(lblWaterfallColorScheme);

        cmbWaterfallScheme = new QComboBox(widget_4);
        cmbWaterfallScheme->addItem(QString());
        cmbWaterfallScheme->addItem(QString());
        cmbWaterfallScheme->addItem(QString());
        cmbWaterfallScheme->addItem(QString());
        cmbWaterfallScheme->addItem(QString());
        cmbWaterfallScheme->addItem(QString());
        cmbWaterfallScheme->addItem(QString());
        cmbWaterfallScheme->addItem(QString());
        cmbWaterfallScheme->addItem(QString());
        cmbWaterfallScheme->addItem(QString());
        cmbWaterfallScheme->addItem(QString());
        cmbWaterfallScheme->addItem(QString());
        cmbWaterfallScheme->setObjectName(QString::fromUtf8("cmbWaterfallScheme"));
        QFont font3;
        font3.setPointSize(10);
        font3.setBold(false);
        font3.setItalic(false);
        cmbWaterfallScheme->setFont(font3);

        horizontalLayout_10->addWidget(cmbWaterfallScheme);


        FFTWaterfallLayout->addWidget(widget_4);

        wgtWaterfallDirection = new QWidget(widgetBox);
        wgtWaterfallDirection->setObjectName(QString::fromUtf8("wgtWaterfallDirection"));
        wgtWaterfallDirection->setMinimumSize(QSize(0, 38));
        horizontalLayout_2 = new QHBoxLayout(wgtWaterfallDirection);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        lblWaterDir = new QLabel(wgtWaterfallDirection);
        lblWaterDir->setObjectName(QString::fromUtf8("lblWaterDir"));
        lblWaterDir->setFont(font2);

        horizontalLayout_2->addWidget(lblWaterDir);

        cmbWaterDir = new QComboBox(wgtWaterfallDirection);
        cmbWaterDir->addItem(QString());
        cmbWaterDir->addItem(QString());
        cmbWaterDir->setObjectName(QString::fromUtf8("cmbWaterDir"));
        QFont font4;
        font4.setPointSize(10);
        cmbWaterDir->setFont(font4);

        horizontalLayout_2->addWidget(cmbWaterDir);


        FFTWaterfallLayout->addWidget(wgtWaterfallDirection);

        sldWaterRange = new ctkRangeSlider(widgetBox);
        sldWaterRange->setObjectName(QString::fromUtf8("sldWaterRange"));
        sldWaterRange->setStyleSheet(QString::fromUtf8(".QSlider {\n"
"    min-height: 20x;\n"
"    max-height: 20px;\n"
"}\n"
"\n"
".QSlider::groove:horizontal {\n"
"    border: 1px solid #262626;\n"
"    height: 5px;\n"
"    background: #505050;\n"
"    margin: 0 12px;\n"
"}\n"
"\n"
".QSlider::handle:horizontal {\n"
"    background: rgb(252, 252, 252);\n"
"    border: 2px solid black;\n"
"    width: 20px;\n"
"    height: 20px;\n"
"    margin: -7px -7px;\n"
"}\n"
"QSlider::sub-page\n"
"{\n"
"    background: rgb(41, 128, 218);\n"
"}\n"
"\n"
"QSlider::add-page \n"
"{\n"
"    background: rgb(186, 186, 186);\n"
"}\n"
"\n"
"QSlider {\n"
"    height: 20px;\n"
"}"));
        sldWaterRange->setMinimum(-150);
        sldWaterRange->setMaximum(-30);
        sldWaterRange->setValue(-90);
        sldWaterRange->setOrientation(Qt::Horizontal);

        FFTWaterfallLayout->addWidget(sldWaterRange);

        chkAutoRange = new QCheckBox(widgetBox);
        chkAutoRange->setObjectName(QString::fromUtf8("chkAutoRange"));
        chkAutoRange->setChecked(true);

        FFTWaterfallLayout->addWidget(chkAutoRange);

        cmdClearMax = new QPushButton(widgetBox);
        cmdClearMax->setObjectName(QString::fromUtf8("cmdClearMax"));

        FFTWaterfallLayout->addWidget(cmdClearMax);


        verticalLayout_6->addLayout(FFTWaterfallLayout);

        TimeFreqStampLayout = new QVBoxLayout();
        TimeFreqStampLayout->setSpacing(0);
        TimeFreqStampLayout->setObjectName(QString::fromUtf8("TimeFreqStampLayout"));
        TimeFreqStampLayout->setContentsMargins(0, 0, 0, 0);
        lblPlaybackTimestamp = new QLabel(widgetBox);
        lblPlaybackTimestamp->setObjectName(QString::fromUtf8("lblPlaybackTimestamp"));
        lblPlaybackTimestamp->setFont(font1);

        TimeFreqStampLayout->addWidget(lblPlaybackTimestamp);

        lblPlaybackIndex = new QLabel(widgetBox);
        lblPlaybackIndex->setObjectName(QString::fromUtf8("lblPlaybackIndex"));
        lblPlaybackIndex->setFont(font1);

        TimeFreqStampLayout->addWidget(lblPlaybackIndex);

        lblMOTime = new QLabel(widgetBox);
        lblMOTime->setObjectName(QString::fromUtf8("lblMOTime"));
        lblMOTime->setFont(font2);

        TimeFreqStampLayout->addWidget(lblMOTime);

        lblMOFreq = new QLabel(widgetBox);
        lblMOFreq->setObjectName(QString::fromUtf8("lblMOFreq"));
        lblMOFreq->setFont(font2);

        TimeFreqStampLayout->addWidget(lblMOFreq);


        verticalLayout_6->addLayout(TimeFreqStampLayout);


        verticalLayout_7->addWidget(widgetBox);

        chkWindowFilter = new QCheckBox(tbInfo);
        chkWindowFilter->setObjectName(QString::fromUtf8("chkWindowFilter"));
        chkWindowFilter->setChecked(false);

        verticalLayout_7->addWidget(chkWindowFilter);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer_4);

        wgtShowControls = new QWidget(tbInfo);
        wgtShowControls->setObjectName(QString::fromUtf8("wgtShowControls"));
        horizontalLayout_14 = new QHBoxLayout(wgtShowControls);
        horizontalLayout_14->setSpacing(2);
        horizontalLayout_14->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        horizontalLayout_14->setContentsMargins(2, 2, 2, 2);
        chkShowFFT = new QCheckBox(wgtShowControls);
        chkShowFFT->setObjectName(QString::fromUtf8("chkShowFFT"));
        chkShowFFT->setChecked(true);

        horizontalLayout_14->addWidget(chkShowFFT);

        chkShowScope = new QCheckBox(wgtShowControls);
        chkShowScope->setObjectName(QString::fromUtf8("chkShowScope"));

        horizontalLayout_14->addWidget(chkShowScope);

        chkShowConstellation = new QCheckBox(wgtShowControls);
        chkShowConstellation->setObjectName(QString::fromUtf8("chkShowConstellation"));

        horizontalLayout_14->addWidget(chkShowConstellation);


        verticalLayout_7->addWidget(wgtShowControls);

        wgtShowControls2 = new QWidget(tbInfo);
        wgtShowControls2->setObjectName(QString::fromUtf8("wgtShowControls2"));
        horizontalLayout_6 = new QHBoxLayout(wgtShowControls2);
        horizontalLayout_6->setSpacing(2);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(2, 2, 2, 2);
        chkMap = new QCheckBox(wgtShowControls2);
        chkMap->setObjectName(QString::fromUtf8("chkMap"));

        horizontalLayout_6->addWidget(chkMap);

        chkMarkers = new QCheckBox(wgtShowControls2);
        chkMarkers->setObjectName(QString::fromUtf8("chkMarkers"));

        horizontalLayout_6->addWidget(chkMarkers);

        chkShowWaterfall = new QCheckBox(wgtShowControls2);
        chkShowWaterfall->setObjectName(QString::fromUtf8("chkShowWaterfall"));
        chkShowWaterfall->setChecked(true);

        horizontalLayout_6->addWidget(chkShowWaterfall);


        verticalLayout_7->addWidget(wgtShowControls2);

        widget_5 = new QWidget(tbInfo);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        widget_5->setMinimumSize(QSize(0, 55));
        horizontalLayout_12 = new QHBoxLayout(widget_5);
        horizontalLayout_12->setSpacing(1);
        horizontalLayout_12->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        horizontalLayout_12->setContentsMargins(1, 1, 1, 1);
        cmdSettings = new QPushButton(widget_5);
        cmdSettings->setObjectName(QString::fromUtf8("cmdSettings"));
        cmdSettings->setEnabled(false);
        cmdSettings->setMinimumSize(QSize(56, 56));
        cmdSettings->setMaximumSize(QSize(56, 56));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/settings"), QSize(), QIcon::Normal, QIcon::Off);
        cmdSettings->setIcon(icon);
        cmdSettings->setIconSize(QSize(48, 48));

        horizontalLayout_12->addWidget(cmdSettings);

        cmdHelp = new QPushButton(widget_5);
        cmdHelp->setObjectName(QString::fromUtf8("cmdHelp"));
        cmdHelp->setEnabled(true);
        cmdHelp->setMinimumSize(QSize(56, 56));
        cmdHelp->setMaximumSize(QSize(56, 56));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/help"), QSize(), QIcon::Normal, QIcon::Off);
        cmdHelp->setIcon(icon1);
        cmdHelp->setIconSize(QSize(48, 48));

        horizontalLayout_12->addWidget(cmdHelp);

        cmdWorkshop = new QPushButton(widget_5);
        cmdWorkshop->setObjectName(QString::fromUtf8("cmdWorkshop"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/analyst"), QSize(), QIcon::Normal, QIcon::Off);
        cmdWorkshop->setIcon(icon2);
        cmdWorkshop->setIconSize(QSize(48, 48));

        horizontalLayout_12->addWidget(cmdWorkshop);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer);

        cmdLoad = new QPushButton(widget_5);
        cmdLoad->setObjectName(QString::fromUtf8("cmdLoad"));
        cmdLoad->setMinimumSize(QSize(56, 56));
        cmdLoad->setMaximumSize(QSize(56, 56));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/load"), QSize(), QIcon::Normal, QIcon::Off);
        cmdLoad->setIcon(icon3);
        cmdLoad->setIconSize(QSize(48, 48));

        horizontalLayout_12->addWidget(cmdLoad);


        verticalLayout_7->addWidget(widget_5);

        tabSelectors->addTab(tbInfo, QString());
        tbClassifier = new QWidget();
        tbClassifier->setObjectName(QString::fromUtf8("tbClassifier"));
        verticalLayout_3 = new QVBoxLayout(tbClassifier);
        verticalLayout_3->setSpacing(2);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(2, 2, 2, 2);
        wgtClassifiers = new wgtClassifier(tbClassifier);
        wgtClassifiers->setObjectName(QString::fromUtf8("wgtClassifiers"));

        verticalLayout_3->addWidget(wgtClassifiers);

        widget_2 = new QWidget(tbClassifier);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setMinimumSize(QSize(0, 150));
        widget_2->setMaximumSize(QSize(16777215, 150));
        horizontalLayout_5 = new QHBoxLayout(widget_2);
        horizontalLayout_5->setSpacing(2);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(2, 2, 2, 2);
        groupBox = new QGroupBox(widget_2);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setFlat(false);
        cmbClassifySel = new QComboBox(groupBox);
        cmbClassifySel->setObjectName(QString::fromUtf8("cmbClassifySel"));
        cmbClassifySel->setGeometry(QRect(10, 20, 85, 26));
        cmbClassifySel->setMinimumSize(QSize(67, 0));
        cmdClassify = new QPushButton(groupBox);
        cmdClassify->setObjectName(QString::fromUtf8("cmdClassify"));
        cmdClassify->setGeometry(QRect(110, 20, 85, 26));
        lblClsRslt = new QLabel(groupBox);
        lblClsRslt->setObjectName(QString::fromUtf8("lblClsRslt"));
        lblClsRslt->setGeometry(QRect(10, 60, 261, 31));

        horizontalLayout_5->addWidget(groupBox);


        verticalLayout_3->addWidget(widget_2);

        tabSelectors->addTab(tbClassifier, QString());
        tbTools = new QWidget();
        tbTools->setObjectName(QString::fromUtf8("tbTools"));
        verticalLayout_8 = new QVBoxLayout(tbTools);
        verticalLayout_8->setSpacing(2);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(2, 2, 2, 2);
        PluginLayout = new QVBoxLayout();
        PluginLayout->setSpacing(0);
        PluginLayout->setObjectName(QString::fromUtf8("PluginLayout"));
        PluginLayout->setContentsMargins(0, 0, 0, 0);
        cmbTool = new QComboBox(tbTools);
        cmbTool->setObjectName(QString::fromUtf8("cmbTool"));
        QFont font5;
        font5.setPointSize(9);
        cmbTool->setFont(font5);

        PluginLayout->addWidget(cmbTool);

        wgt_tool_parent = new QWidget(tbTools);
        wgt_tool_parent->setObjectName(QString::fromUtf8("wgt_tool_parent"));
        wgt_tool_parent->setMinimumSize(QSize(0, 225));

        PluginLayout->addWidget(wgt_tool_parent);

        plgControl = new QWidget(tbTools);
        plgControl->setObjectName(QString::fromUtf8("plgControl"));
        horizontalLayout_4 = new QHBoxLayout(plgControl);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(9, 1, 9, 1);
        cmdDecode = new QPushButton(plgControl);
        cmdDecode->setObjectName(QString::fromUtf8("cmdDecode"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/play"), QSize(), QIcon::Normal, QIcon::Off);
        cmdDecode->setIcon(icon4);
        cmdDecode->setIconSize(QSize(32, 32));

        horizontalLayout_4->addWidget(cmdDecode);

        cmdProcess = new QPushButton(plgControl);
        cmdProcess->setObjectName(QString::fromUtf8("cmdProcess"));
        cmdProcess->setIcon(icon4);
        cmdProcess->setIconSize(QSize(32, 32));

        horizontalLayout_4->addWidget(cmdProcess);


        PluginLayout->addWidget(plgControl);

        cmdDetect = new QPushButton(tbTools);
        cmdDetect->setObjectName(QString::fromUtf8("cmdDetect"));

        PluginLayout->addWidget(cmdDetect);

        cmdEnergyDetect2 = new QPushButton(tbTools);
        cmdEnergyDetect2->setObjectName(QString::fromUtf8("cmdEnergyDetect2"));

        PluginLayout->addWidget(cmdEnergyDetect2);

        sldDetectSensitivity = new QSlider(tbTools);
        sldDetectSensitivity->setObjectName(QString::fromUtf8("sldDetectSensitivity"));
        sldDetectSensitivity->setMinimum(1);
        sldDetectSensitivity->setMaximum(20);
        sldDetectSensitivity->setPageStep(2);
        sldDetectSensitivity->setValue(11);
        sldDetectSensitivity->setOrientation(Qt::Horizontal);

        PluginLayout->addWidget(sldDetectSensitivity);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        PluginLayout->addItem(verticalSpacer_3);


        verticalLayout_8->addLayout(PluginLayout);

        tabSelectors->addTab(tbTools, QString());

        verticalLayout_2->addWidget(tabSelectors);


        horizontalLayout->addWidget(wgtLeftTool);

        wgtRightMain = new QWidget(wgtMainTop);
        wgtRightMain->setObjectName(QString::fromUtf8("wgtRightMain"));
        vboxLayout = new QVBoxLayout(wgtRightMain);
        vboxLayout->setSpacing(3);
        vboxLayout->setContentsMargins(11, 11, 11, 11);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        vboxLayout->setContentsMargins(0, 0, 0, 3);
        wgtScope_Const = new QWidget(wgtRightMain);
        wgtScope_Const->setObjectName(QString::fromUtf8("wgtScope_Const"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(1);
        sizePolicy2.setHeightForWidth(wgtScope_Const->sizePolicy().hasHeightForWidth());
        wgtScope_Const->setSizePolicy(sizePolicy2);
        horizontalLayout_15 = new QHBoxLayout(wgtScope_Const);
        horizontalLayout_15->setSpacing(0);
        horizontalLayout_15->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        horizontalLayout_15->setContentsMargins(0, 0, 0, 0);
        wgtScope2 = new wgt_Scope(wgtScope_Const);
        wgtScope2->setObjectName(QString::fromUtf8("wgtScope2"));

        horizontalLayout_15->addWidget(wgtScope2);

        wgtConst = new QConstellationPlot(wgtScope_Const);
        wgtConst->setObjectName(QString::fromUtf8("wgtConst"));

        horizontalLayout_15->addWidget(wgtConst);


        vboxLayout->addWidget(wgtScope_Const);

        wgtFFT2 = new wgt_FFT(wgtRightMain);
        wgtFFT2->setObjectName(QString::fromUtf8("wgtFFT2"));
        sizePolicy2.setHeightForWidth(wgtFFT2->sizePolicy().hasHeightForWidth());
        wgtFFT2->setSizePolicy(sizePolicy2);

        vboxLayout->addWidget(wgtFFT2);

        wgtWaterfall = new wgt_waterfall(wgtRightMain);
        wgtWaterfall->setObjectName(QString::fromUtf8("wgtWaterfall"));
        sizePolicy2.setHeightForWidth(wgtWaterfall->sizePolicy().hasHeightForWidth());
        wgtWaterfall->setSizePolicy(sizePolicy2);

        vboxLayout->addWidget(wgtWaterfall);

        wgtMapDoc = new QWidget(wgtRightMain);
        wgtMapDoc->setObjectName(QString::fromUtf8("wgtMapDoc"));
        sizePolicy2.setHeightForWidth(wgtMapDoc->sizePolicy().hasHeightForWidth());
        wgtMapDoc->setSizePolicy(sizePolicy2);
        wgtMapDoc->setMinimumSize(QSize(0, 0));

        vboxLayout->addWidget(wgtMapDoc);

        wgtMarkerTable = new wgt_marker_table(wgtRightMain);
        wgtMarkerTable->setObjectName(QString::fromUtf8("wgtMarkerTable"));
        sizePolicy2.setHeightForWidth(wgtMarkerTable->sizePolicy().hasHeightForWidth());
        wgtMarkerTable->setSizePolicy(sizePolicy2);

        vboxLayout->addWidget(wgtMarkerTable);


        horizontalLayout->addWidget(wgtRightMain);

        widget = new QWidget(wgtMainTop);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(50, 0));
        widget->setMaximumSize(QSize(52, 16777215));
        verticalLayout_5 = new QVBoxLayout(widget);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        verticalSpacer_2 = new QSpacerItem(20, 94, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_2);

        widget_6 = new QWidget(widget);
        widget_6->setObjectName(QString::fromUtf8("widget_6"));

        verticalLayout_5->addWidget(widget_6);

        widget_3 = new QWidget(widget);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        widget_3->setMinimumSize(QSize(0, 0));
        verticalLayout_9 = new QVBoxLayout(widget_3);
        verticalLayout_9->setSpacing(0);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        verticalLayout_9->setContentsMargins(0, 1, 0, 1);
        cmdPageup = new QPushButton(widget_3);
        cmdPageup->setObjectName(QString::fromUtf8("cmdPageup"));
        cmdPageup->setMaximumSize(QSize(50, 60));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icons/up2"), QSize(), QIcon::Normal, QIcon::Off);
        cmdPageup->setIcon(icon5);
        cmdPageup->setIconSize(QSize(48, 48));
        cmdPageup->setAutoRepeat(true);

        verticalLayout_9->addWidget(cmdPageup);

        cmdUp = new QPushButton(widget_3);
        cmdUp->setObjectName(QString::fromUtf8("cmdUp"));
        cmdUp->setMaximumSize(QSize(50, 60));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icons/up1"), QSize(), QIcon::Normal, QIcon::Off);
        cmdUp->setIcon(icon6);
        cmdUp->setIconSize(QSize(48, 48));
        cmdUp->setAutoRepeat(true);
        cmdUp->setAutoRepeatDelay(250);

        verticalLayout_9->addWidget(cmdUp);

        cmdUp_Small = new QPushButton(widget_3);
        cmdUp_Small->setObjectName(QString::fromUtf8("cmdUp_Small"));
        cmdUp_Small->setMaximumSize(QSize(50, 60));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/icons/upsmall"), QSize(), QIcon::Normal, QIcon::Off);
        cmdUp_Small->setIcon(icon7);
        cmdUp_Small->setIconSize(QSize(48, 48));
        cmdUp_Small->setAutoRepeat(true);
        cmdUp_Small->setAutoRepeatDelay(250);

        verticalLayout_9->addWidget(cmdUp_Small);

        cmdDown_Small = new QPushButton(widget_3);
        cmdDown_Small->setObjectName(QString::fromUtf8("cmdDown_Small"));
        cmdDown_Small->setMaximumSize(QSize(50, 60));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/icons/downsmall"), QSize(), QIcon::Normal, QIcon::Off);
        cmdDown_Small->setIcon(icon8);
        cmdDown_Small->setIconSize(QSize(48, 48));
        cmdDown_Small->setAutoRepeat(true);

        verticalLayout_9->addWidget(cmdDown_Small);

        cmdDown = new QPushButton(widget_3);
        cmdDown->setObjectName(QString::fromUtf8("cmdDown"));
        cmdDown->setMaximumSize(QSize(50, 60));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/icons/down1"), QSize(), QIcon::Normal, QIcon::Off);
        cmdDown->setIcon(icon9);
        cmdDown->setIconSize(QSize(48, 48));
        cmdDown->setAutoRepeat(true);

        verticalLayout_9->addWidget(cmdDown);

        cmdPageDown = new QPushButton(widget_3);
        cmdPageDown->setObjectName(QString::fromUtf8("cmdPageDown"));
        cmdPageDown->setMaximumSize(QSize(50, 60));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/icons/down2"), QSize(), QIcon::Normal, QIcon::Off);
        cmdPageDown->setIcon(icon10);
        cmdPageDown->setIconSize(QSize(48, 48));
        cmdPageDown->setAutoRepeat(true);

        verticalLayout_9->addWidget(cmdPageDown);


        verticalLayout_5->addWidget(widget_3);


        horizontalLayout->addWidget(widget);


        verticalLayout->addWidget(wgtMainTop);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        tabSelectors->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        lblIcon->setText(QString());
        lblTitle->setText(QCoreApplication::translate("MainWindow", "Analyst", nullptr));
        widgetBox->setProperty("pageTitle", QVariant(QCoreApplication::translate("MainWindow", "FFT / Waterfall", nullptr)));
        lblName->setText(QCoreApplication::translate("MainWindow", "Name", nullptr));
        lblDuration->setText(QCoreApplication::translate("MainWindow", "Duration", nullptr));
        lblCenterFreq->setText(QCoreApplication::translate("MainWindow", "Center Frequency ", nullptr));
        lblFreqRange->setText(QCoreApplication::translate("MainWindow", "Frequency Range", nullptr));
        lblBandwidth->setText(QCoreApplication::translate("MainWindow", "Bandwidth", nullptr));
        lblGain->setText(QCoreApplication::translate("MainWindow", "Gain", nullptr));
        lblNumBinsRBW->setText(QCoreApplication::translate("MainWindow", "#Bins ", nullptr));
        lblRBW->setText(QCoreApplication::translate("MainWindow", " RBW ", nullptr));
        lblFFT_TimeRes->setText(QCoreApplication::translate("MainWindow", "FFT Time Resolution", nullptr));
        lblFFT_LineTime->setText(QCoreApplication::translate("MainWindow", "FFT Line Time", nullptr));
        lblWaterfallColorScheme->setText(QCoreApplication::translate("MainWindow", "Waterfall Color ", nullptr));
        cmbWaterfallScheme->setItemText(0, QCoreApplication::translate("MainWindow", "Grayscale", nullptr));
        cmbWaterfallScheme->setItemText(1, QCoreApplication::translate("MainWindow", "Hot", nullptr));
        cmbWaterfallScheme->setItemText(2, QCoreApplication::translate("MainWindow", "Cold", nullptr));
        cmbWaterfallScheme->setItemText(3, QCoreApplication::translate("MainWindow", "Night", nullptr));
        cmbWaterfallScheme->setItemText(4, QCoreApplication::translate("MainWindow", "Candy", nullptr));
        cmbWaterfallScheme->setItemText(5, QCoreApplication::translate("MainWindow", "Geography", nullptr));
        cmbWaterfallScheme->setItemText(6, QCoreApplication::translate("MainWindow", "Ion", nullptr));
        cmbWaterfallScheme->setItemText(7, QCoreApplication::translate("MainWindow", "Thermal", nullptr));
        cmbWaterfallScheme->setItemText(8, QCoreApplication::translate("MainWindow", "Polar", nullptr));
        cmbWaterfallScheme->setItemText(9, QCoreApplication::translate("MainWindow", "Spectrum", nullptr));
        cmbWaterfallScheme->setItemText(10, QCoreApplication::translate("MainWindow", "Jet", nullptr));
        cmbWaterfallScheme->setItemText(11, QCoreApplication::translate("MainWindow", "Hues", nullptr));

        lblWaterDir->setText(QCoreApplication::translate("MainWindow", "Waterfall Direction", nullptr));
        cmbWaterDir->setItemText(0, QCoreApplication::translate("MainWindow", "Top Down", nullptr));
        cmbWaterDir->setItemText(1, QCoreApplication::translate("MainWindow", "Bottom Up", nullptr));

        chkAutoRange->setText(QCoreApplication::translate("MainWindow", "Auto Range", nullptr));
        cmdClearMax->setText(QCoreApplication::translate("MainWindow", "Clear Max", nullptr));
        lblPlaybackTimestamp->setText(QCoreApplication::translate("MainWindow", "Playback Timestamp", nullptr));
        lblPlaybackIndex->setText(QCoreApplication::translate("MainWindow", "Playback Index", nullptr));
        lblMOTime->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        lblMOFreq->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        chkWindowFilter->setText(QCoreApplication::translate("MainWindow", "Window Filter", nullptr));
        chkShowFFT->setText(QCoreApplication::translate("MainWindow", "FFT", nullptr));
        chkShowScope->setText(QCoreApplication::translate("MainWindow", "Scope", nullptr));
        chkShowConstellation->setText(QCoreApplication::translate("MainWindow", "Constellation", nullptr));
        chkMap->setText(QCoreApplication::translate("MainWindow", "Map", nullptr));
        chkMarkers->setText(QCoreApplication::translate("MainWindow", "Markers", nullptr));
        chkShowWaterfall->setText(QCoreApplication::translate("MainWindow", "Waterfall", nullptr));
        cmdSettings->setText(QString());
        cmdHelp->setText(QString());
        cmdWorkshop->setText(QString());
        cmdLoad->setText(QString());
        tabSelectors->setTabText(tabSelectors->indexOf(tbInfo), QCoreApplication::translate("MainWindow", "Info", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "ML Classifier", nullptr));
        cmdClassify->setText(QCoreApplication::translate("MainWindow", "Classify", nullptr));
        lblClsRslt->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        tabSelectors->setTabText(tabSelectors->indexOf(tbClassifier), QCoreApplication::translate("MainWindow", "ML Classifier", nullptr));
        cmdDecode->setText(QCoreApplication::translate("MainWindow", "Decode", nullptr));
        cmdProcess->setText(QCoreApplication::translate("MainWindow", "Process", nullptr));
        cmdDetect->setText(QCoreApplication::translate("MainWindow", "Energy Detect", nullptr));
        cmdEnergyDetect2->setText(QCoreApplication::translate("MainWindow", "ED2", nullptr));
        tabSelectors->setTabText(tabSelectors->indexOf(tbTools), QCoreApplication::translate("MainWindow", "Tools", nullptr));
        cmdPageup->setText(QString());
        cmdUp->setText(QString());
        cmdUp_Small->setText(QString());
        cmdDown_Small->setText(QString());
        cmdDown->setText(QString());
        cmdPageDown->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
