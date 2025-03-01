#ifndef SAMPLEINDEXER_H
#define SAMPLEINDEXER_H

#include <QString>
#include <QObject>
#include <vector>
#include <qvrt_tools.h>
#include <iq_16t.h>
#include <utils.h>

#ifdef WIN32
#define HAVE_STRUCT_TIMESPEC
#endif
//#include <pthread.h>
#include <thread>

using namespace std;
/*
 * The purpose of this class is to provide fast access to the IQ data in the QVRT file
 * In this Analyst application, we're going to need to be able to retrieve samples from anywhere in the stream
 * very quickly
 *
 * When we open the file, the first thing we;re gonig to do is build an index of the file
 * so we can associate sampleindex with file position in bytes
 *
 *
 * Each item in the m_indexes represents the position of the next X samples
*/

struct sample_idx
{
    uint64_t m_filepos; // where in the file does this correspond to?
    uint64_t m_abs_sample_idx; // the number of sample up to this point, not including the samples in the upcoming block pointed to with m_filepos
};

class SampleIndexer : public QObject
{
     Q_OBJECT

public:
    SampleIndexer(QObject *parent = nullptr);
    ~SampleIndexer();
private:

    vector<sample_idx *> m_samp_idxs; // an array of sampleidx

    IQ_Reader *m_reader; // gets instantiated to the right subclass


    CircBuff<complex<float> > *samplesout; // temp storage
    //pthread_t bit; // build index thread
    std::thread *bit; // build index thread

    //QVRT_FileInfo *m_fi;
    //file_format m_ft;

    StreamInfo *m_si; // stream info
    //int m_streamid; // for QVRT files

public:
    long Index(uint64_t sampleindex, int *remainder);
    //void StartThreadedBuildIndexTable(string fn, QVRT_FileInfo *fi);
    void StartThreadedBuildIndexTable(StreamInfo *si);

    bool Open();
    void Close();
    bool IsOpen();
    void GetSamples(long sample_idx, int numsamples, complex<float> *IQData);
    bool Save(QString filename);
    bool Load(QString filename);
    bool BuildIndexTable();
    double CF_Hz();
    double BW_Hz();
    int streamid() const;
    void setStreamid(int streamid);
    bool PastLength(uint64_t sampleindex); // returns true if we're asking for a sample past the end of the stream

signals:
    void StartBuildIndex();
    void ProgressBuildIndex();
    void EndBuildIndex();

};

#endif // SAMPLEINDEXER_H
