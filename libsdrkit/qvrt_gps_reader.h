#ifndef QVRT_GPS_READER_H
#define QVRT_GPS_READER_H

#include <QObject>
#include <qvrt_tools.h>
#include <QVector>
#include <thread>

class QVRT_GPS_Coord
{
public:
    double longitude;
    double latitude;
    double altitude;
};

/*
This class extracts GPS information from a QVRT file
*/

class QVRT_GPS_Reader : public QObject
{
    Q_OBJECT
public:
    explicit QVRT_GPS_Reader(QObject *parent = 0);
    bool running(){return m_running;}
    void stop();
    bool start(QString qvrtfile, bool exportkml);
    void process();
    QVector<QVRT_GPS_Coord *> *getcoords(){return &m_coords;}
    bool m_running;
    //pthread_t m_readerthread;
    std::thread *m_readerthread;
signals:
    void QVRT_GPS_Progress(QVRT_GPS_Reader *reader,float percent, bool done); // % complete progress
    void QVRT_GPS_Message(bool error, QString message);
public slots:
private:
    QString file;
    bool m_exportkml;
    QVector<QVRT_GPS_Coord *> m_coords;
};

#endif // QVRT_GPS_READER_H
