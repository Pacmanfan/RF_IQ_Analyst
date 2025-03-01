#include "wgtclassifier.h"
#include "ui_wgtclassifier.h"
#include <dlgnewclassifier.h>
#include <QDir>
#include <QFile>
#include <QStringList>
#include <QStringList>
#include <QDir>

wgtClassifier::wgtClassifier(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::wgtClassifier)
{
    m_classifiers = 0;
    ui->setupUi(this);
    UpdateButtonStates();
}

wgtClassifier::~wgtClassifier()
{
    delete ui;
}

void wgtClassifier::UpdateTable()
{
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
}

void wgtClassifier::SetClassifiers(Classifiers *cl)
{
    m_classifiers = cl;
    UpdateTable();
}

void wgtClassifier::SaveChanges()
{
    QString apppath = QApplication::applicationDirPath();
    QString clfname = apppath + "/classifiers.ini";
    m_classifiers->Save(clfname); // save the classifiers information

}

void wgtClassifier::on_tblClassifiers_itemSelectionChanged()
{
    UpdateButtonStates();
}

void wgtClassifier::on_cmdAddClassifier_clicked()
{
    QString name = "name" ; // get name from user
    Classifier *cl = m_classifiers->NewClassifier(name);
    dlgNewClassifier *dlgcls = new dlgNewClassifier(this);
    dlgcls->SetClassifier(cl);
    dlgcls->exec(); // do a modal grab of data
    //now set up the paths
    QString ap = QApplication::applicationDirPath();
    QString clpath = ap + "/classifiers/" + cl->m_name;
    QString bpath = ap + "/classifiers/" ;

    if(!QDir(clpath).exists())
    {
        QDir().mkdir(clpath);
        QDir().mkdir(clpath + "/testing_data");
        QDir().mkdir(clpath + "/training_data");
    }
    if(cl->m_method == eRawIQ)
    {
        QFile::copy(bpath + "template/trainIQ.py",clpath + "/trainIQ.py" );
        QFile::copy(bpath + "template/datasetIQ.py",clpath + "/datasetIQ.py" );
        QFile::copy(bpath + "template/predictIQ.py",clpath + "/predictIQ.py" );
    }
    if(cl->m_method == eFFT)
    {
        QFile::copy(bpath + "template/trainFFT.py",clpath + "/trainFFT.py" );
        QFile::copy(bpath + "template/datasetFFT.py",clpath + "/datasetFFT.py" );
        QFile::copy(bpath + "template/predictFFT.py",clpath + "/predictFFT.py" );

    }

    // the directory needs to be set up too with python scripts
    UpdateTable();
    SaveChanges();
    emit(ClassifiersUpdated());
}

void wgtClassifier::on_cmdRemoveClassifier_clicked()
{
    int idx = ui->tblClassifiers->currentRow();
    if(idx == -1)
        return;
    Classifier *cl = m_classifiers->m_list[idx];
    QString ap = QApplication::applicationDirPath();
    QString clpath = ap + "/classifiers/" + cl->m_name;
    QDir dir(clpath);
    dir.removeRecursively();
    m_classifiers->RemoveClassifier(idx);
    SaveChanges();
    UpdateTable();
    UpdateButtonStates();
    emit(ClassifiersUpdated());
}

void wgtClassifier::on_cmdExportMarkerTrainingData_clicked()
{
    bool all = ui->chkAllTaggedMarkers->isChecked();
    int idx = ui->tblClassifiers->currentRow();
    if(idx == -1)
        return;
    Classifier *cl = m_classifiers->m_list[idx];
    QString ap = QApplication::applicationDirPath();
    QString clpath = ap + "/classifiers/" + cl->m_name + "/training_data/" ;
    emit(StartDataExport(all,clpath,cl->m_BWKHz * 1000)); // signal to indicate markers to export

}

void wgtClassifier::UpdateButtonStates()
{
    int idx = ui->tblClassifiers->currentRow();
    if(idx == -1)
    {
        ui->cmdClearTraininData->setEnabled(false);
        ui->cmdExportMarkerTrainingData->setEnabled(false);
        ui->cmdRemoveClassifier->setEnabled(false);
        ui->cmdStartStraining->setEnabled(false);
    }else
    {
        ui->cmdClearTraininData->setEnabled(true);
        ui->cmdExportMarkerTrainingData->setEnabled(true);
        ui->cmdRemoveClassifier->setEnabled(true);
        ui->cmdStartStraining->setEnabled(true);
    }
}

void wgtClassifier::on_cmdStartStraining_clicked()
{
    int idx = ui->tblClassifiers->currentRow();
    //get the classifier
    if(idx == -1)
        return;
    Classifier *cl = m_classifiers->m_list[idx];
    if(cl->IsTraining() == false)
    {
        //make a path
        cl->StartTraining();
        connect(cl,SIGNAL(TrainingMessage(QString)),this,SLOT(onTrainingMessage(QString)));
        ui->cmdStartStraining->setText("Stop Training");
    }else
    {
        cl->EndTraining();
        ui->cmdStartStraining->setText("Start Training");
    }
}

void wgtClassifier::onTrainingMessage(QString msg)
{
    ui->lbltrainingstatus->setText(msg);
}
