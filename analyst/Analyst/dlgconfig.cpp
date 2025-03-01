#include "dlgconfig.h"
#include "ui_dlgconfig.h"
#include <iplugininterface.h>
#include <pluginmanager.h>

extern libsdrkitplugins::PluginManager m_plugmgr;

dlgConfig::dlgConfig(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgConfig)
{
    ui->setupUi(this);
    UpdatePluginsView();
}

dlgConfig::~dlgConfig()
{
    delete ui;
}
/*
    ui->tblClassifiers->setColumnCount(3);
    ui->tblClassifiers->setRowCount(m_classifiers->m_list.size());
    QStringList sl;
    sl << "Name" << "BW" << "Method";
    ui->tblClassifiers->setHorizontalHeaderLabels(sl);
    for(int c = 0; c< m_classifiers->m_list.size(); c++)
    {
        Classifier *cl =m_classifiers->m_list[c];
        QString name = cl->m_name;
        ui->tblClassifiers->setItem(c,0,new QTableWidgetItem(name));
        QString BW = QString::number((cl->m_BWKHz )) + " KHz";
        ui->tblClassifiers->setItem(c,1,new QTableWidgetItem(BW));
        QString method = "IQ";
        if(cl->m_method == eFFT)
        {
            method = "FFT";
        }
        ui->tblClassifiers->setItem(c,2,new QTableWidgetItem(method));
    }
    ui->tblClassifiers->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
*/
void dlgConfig::UpdatePluginsView()
{
    //ui->lstPlugins->clear();
    ui->tblPlugins->clear();
    ui->tblPlugins->setColumnCount(2);
    ui->tblPlugins->setRowCount(m_plugmgr.plugins.length());
    QStringList sl;
    sl << "Name" << "Version" ;
    ui->tblPlugins->setHorizontalHeaderLabels(sl);

    for(int c = 0 ; c < m_plugmgr.plugins.length(); c++)
    {
        iPluginInterface *iplg = m_plugmgr.plugins[c];
        QString plugin_name = iplg->Name();

        ui->tblPlugins->setItem(c,0,new QTableWidgetItem(plugin_name));
        QString Version = iplg->Version();
        ui->tblPlugins->setItem(c,1,new QTableWidgetItem(Version));


    }
    ui->tblPlugins->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

void dlgConfig::on_tblPlugins_itemSelectionChanged()
{
    // get the current row
    int idx = ui->tblPlugins->currentRow();
    if(idx == -1)
        return;
    //show info about the currnt plugin
    iPluginInterface *iplg = m_plugmgr.plugins[idx];
    QString message = "";
    message += "Description : " + iplg->Description() + "\r\n";
    message += "Tags : " + iplg->Tags() + "\r\n";
    message += "Configured Input Rate : " + QString::number(iplg->GetInputRate()) + "\r\n";
    message += "Configured Output Rate : " + QString::number(iplg->GetOutputRate()) + "\r\n";
    /*
    ProcessSignature sig = iplg->Signature();
    //iterate and print details about input signatures
    message += "Input Signatures : \r\n";
    for(int c =0; c< sig.numin; c++)
    {
        StreamSig *ss = &sig.insigs[c];
        message += "Stream of : ";
        message += StreamItemStrings[(int)ss->_itemtype][0] + "\r\n";

    }
    message += "Output Signatures : \r\n";
    for(int c =0; c< sig.numout; c++)
    {
        StreamSig *ss = &sig.outsigs[c];
        message += "Stream of : ";
        message += StreamItemStrings[(int)ss->_itemtype][0] + "\r\n";

    }
    */
    ui->textBrowser->setText(message);
}
