#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include <QObject>
#include <ftmarker.h>
#include <QSettings>
#include <QProcess>
#include <QUdpSocket>
#include <qvrt_tools.h>

/*
This class holds a defintion for a classifier.
The actual classifier resides as a python file to the Tensorflow framework
the data created by the training phase of the tensorflow network is stored on disk as well
*/
enum eClassifierMethod
{
    eRawIQ = 0,
    eFFT = 1
};

class Classifier: public QObject
{
    Q_OBJECT
public:
    QString m_name;
    bool m_training;
    bool m_classifying;
    eClassifierMethod m_method;
    QProcess *m_trainproc;
    QUdpSocket *m_trainsock;
    QProcess *m_classifyproc;
    QUdpSocket *m_classifysocket;
    ftmarker *m_cl_mrk;

    long m_BWKHz; // max bandwidth in Khz
    bool m_isbuilt; // has the classifier been trained and is there a data file for it?

    explicit Classifier(QObject *parent = 0);
    void Save(QSettings *settings);
    void Load(QSettings *settings);
    bool IsTraining(){return m_training;}
    bool IsClassifying(){return m_classifying;}
  //  void AddMarkerData(ftmarker *marker); // add the data from this tagged marker to the training set
    bool StartTraining(); // start the training of the system
    void EndTraining(); // stops the training
    bool StartClassify(QVRT_FileInfo *fi, ftmarker *ftm,QString inputfilenme, int StreamID); // starts a process to classify the data in this marker
    void EndClassify(); // if the user wants to cancel classifcation early prior to results

public slots:
    void ReceiveUDPTraining();
    void ReceiveUDPClassify();
private slots:
signals:
    void ClassificationComplete(ftmarker *ftm,QString message,QMap<QString, float> results);
    void TrainingComplete();
    void TrainingMessage(QString msg); // emitted when training receives a message

};


//this is a simple list class to keep track of all classifiers managed by the system
class Classifiers
{
public:
    QVector<Classifier *> m_list;
    Classifier *NewClassifier(QString name);
    void RemoveClassifier(Classifier *item);
    void RemoveClassifier(int idx);
    bool Load(QString filename);
    bool Save(QString filename);
};

#endif // CLASSIFIER_H
