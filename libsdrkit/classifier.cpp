#include "classifier.h"
#include "data_exporter.h"
#include <QDir>
#include <QFile>
#include <QApplication>

static int cl_name_cnt = 0;
#define TRAINPORT 5005
#define CLASSIFYPORT 5006

Classifier::Classifier(QObject *parent) : QObject(parent)
{
    m_name = "Classifier" + QString::number(cl_name_cnt++);
    m_method = eRawIQ;
    m_isbuilt = false;
    m_trainproc = 0;
    m_classifyproc = 0;
    m_trainsock = 0;
    m_classifysocket = 0;
    m_classifying = false;
    m_training = false;
}

void Classifier::Load(QSettings *settings)
{
    m_name = settings->value("Name","name").toString();
    m_isbuilt = settings->value("Built",false).toBool();
    m_method = (eClassifierMethod)settings->value("Method",false).toInt();
    m_BWKHz = (eClassifierMethod)settings->value("BW",250000).toInt();
}


void Classifier::Save(QSettings *settings)
{
    settings->setValue("Name",m_name);
    settings->setValue("Built",m_isbuilt);
    settings->setValue("Method",(int)m_method);
    settings->setValue("BW",(int)m_BWKHz);
}
/*
void Classifier::AddMarkerData(ftmarker *marker)
{

    // add the data from this tagged marker to the training set
}
*/
// start the training of the system
bool Classifier::StartTraining()
{
    if(m_training) // we're already training
        return false;

    QString ap = QApplication::applicationDirPath();
    QString clpath = ap + "/classifiers/" + m_name + "/";
    //change to this path
    QDir::setCurrent(clpath);
    QString app = "";
    if(m_method == eFFT)
    {
        app = "./trainFFT.py";
    }else if (m_method == eRawIQ)
    {
        app = "./trainIQ.py";
    }
    // create a socket to listen
    m_trainsock = new QUdpSocket(this);
    connect(m_trainsock,SIGNAL(readyRead()),this,SLOT(ReceiveUDPTraining()));
    m_trainsock->bind(QHostAddress::LocalHost, TRAINPORT);

    // create a new process
    m_trainproc = new QProcess(this);
    QString app_call = "python " + app;
    m_trainproc->start(app_call);
    m_trainproc->waitForStarted(5000);

    m_training = true;
    //start a QProcess to start and monitor data
    return true;
}

bool Classifier::StartClassify(QVRT_FileInfo *fi, ftmarker *ftm,QString inputfilename, int StreamID)
{
 //   if(m_classifying)
   //     return false;
    // export this markers iq data to a numpy file

    QString ap = QApplication::applicationDirPath();
    QString clpath = ap + "/classifiers/" + m_name + "/";
    //change to this path
    QDir::setCurrent(clpath);
    QString app = "";
    QString samplename = clpath + "smp_cls.npy";

    //remove the old one
    QFile fl(samplename);
    fl.remove();

    data_exporter *exporter = new data_exporter(this);
    double bandwidth = m_BWKHz * 1000;
    exporter->SingleExport(fi,ftm,inputfilename,samplename,StreamID,bandwidth);
    delete exporter;

    QFile fl2(samplename);
    if(fl2.exists() == false)
    {
        //didn't export for some reason, raise an error
        return false;
    }

    if(m_method == eFFT)
    {
        app = "./predictFFT.py";
    }else if (m_method == eRawIQ)
    {
        app = "./predictIQ.py";
    }

    m_classifying = true;
    m_cl_mrk = ftm;
    // use that numpy file name to call a python script
    // get the results of that script
    m_classifysocket = new QUdpSocket(this);
    connect(m_classifysocket,SIGNAL(readyRead()),this,SLOT(ReceiveUDPClassify()));
    m_classifysocket->bind(QHostAddress::LocalHost, CLASSIFYPORT);

    // create a new process
    m_classifyproc = new QProcess(this);
    QString app_call = "python " + app + " " + samplename;
    m_classifyproc->start(app_call);
    m_classifyproc->waitForStarted(5000);

    return true;

}

void Classifier::EndClassify()
{
    m_cl_mrk = 0;
    m_classifying = false;
    if(m_classifyproc != 0)
    {
        m_classifyproc->close();
        delete m_classifyproc;
    }
    if(m_classifysocket != 0)
    {
        delete m_classifysocket;
        m_classifysocket = 0;
    }
}

void Classifier::EndTraining()
{
    m_training = false;
    //stop the training process
    if(m_trainproc!=0)
    {
        m_trainproc->close();
        delete m_trainproc;
        m_trainproc = 0;
    }

    if(m_trainsock !=0)
    {
        delete m_trainsock;
        m_trainsock = 0;
    }

    emit(TrainingComplete());
}

void Classifier::ReceiveUDPTraining()
{

    while (m_trainsock->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(m_trainsock->pendingDatagramSize());
        m_trainsock->readDatagram(datagram.data(), datagram.size());
        QString msg(datagram);
        emit(TrainingMessage(msg));
    }
}

void Classifier::ReceiveUDPClassify()
{
    QString finalmsg = "";
    ftmarker *tmp = m_cl_mrk;
    while (m_classifysocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(m_classifysocket->pendingDatagramSize());
        m_classifysocket->readDatagram(datagram.data(), datagram.size());
        QString msg(datagram);        
        finalmsg += msg;
    }
    QMap<QString, float> mapresults;
    //if (ended)
     {
         QStringList sl = finalmsg.split(':');
         if(sl.count() > 1)
         {
             //parse classes
             QString classes = sl[0];
             QStringList slcl = classes.split(',');
             QString results = sl[1];
             results = results.replace('[',' ');
             results = results.replace(']',' ');
             results = results.trimmed();
             QStringList  slrs = results.split(' ');
             for(int c =0 ; c < slcl.size(); c++)
             {
                 QString t = slrs[c];
                 float val = t.toFloat();
                mapresults[slcl[c]] = val;
             }

         }
         EndClassify(); // clean up resources
         emit(ClassificationComplete(tmp,finalmsg,mapresults));

     }

}

Classifier *Classifiers::NewClassifier(QString name)
{
    Classifier *cl = new Classifier();
    cl->m_name = name;
    m_list.push_back(cl);
    return cl;
}

void Classifiers::RemoveClassifier(Classifier *item)
{
    int idx = m_list.indexOf(item);
    if(idx == -1)
        return;
    m_list.remove(idx);
}

void Classifiers::RemoveClassifier(int idx)
{
    m_list.remove(idx);
}

bool Classifiers::Load(QString filename)
{
    QSettings settings(filename);
    int nentries;
    nentries = settings.beginReadArray("Classifiers");
    for(int c= 0; c< nentries; c++)
    {
        settings.setArrayIndex(c);
        Classifier *cl = new Classifier();
        cl->Load(&settings);
        m_list.push_back(cl);
    }
    settings.endArray();
    return true;
}


bool Classifiers::Save(QString filename)
{
     QSettings settings(filename);
    int nentries = m_list.size();
    settings.beginWriteArray("Classifiers",nentries);
    for(int c = 0; c < m_list.size(); c++ )
    {
        settings.setArrayIndex(c);
        m_list.at(c)->Save(&settings);
    }
    settings.endArray();
    return true;
}
