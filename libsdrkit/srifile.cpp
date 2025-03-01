#include "srifile.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>

SRIFile::SRIFile()
{
    memset(this,0,sizeof(SRIFile));
}

/*
Reference Level (dB)=-46.8828125
RF Reference Frequency (Hz)=313860106.5390625
Stage 2 Gain (dB)=0.0
Sample Rate (samples/sec)=1000000.0
RF Reference Frequency Offset (Hz)=0.0
Stage 1 Gain (dB)=0.0
Bandwidth (Hz)=1000000.0
CF,BW,SPS,RefLevDB;
    double gain1,gain2,offset;
*/
bool SRIFile::Load(QString fn)
{
    QFile file(fn);
    if(file.open(QIODevice::ReadOnly))
    {
        QString str;

        QStringList lst;
        QTextStream s1(&file);
        while (!s1.atEnd())
        {
            str = s1.readLine();
            lst = str.split('=');
            if(lst[0].contains("Reference Level"))
            {
                RefLevDB = lst[1].toDouble();
            }else if (lst[0].contains("RF Reference Frequency (Hz)"))
            {
                CF = lst[1].toDouble();
            }else if (lst[0].contains("Stage 2 "))
            {
                gain2 = lst[1].toDouble();
            }else if (lst[0].contains("Sample Rate"))
            {
                SPS = lst[1].toDouble();
            }else if (lst[0].contains("Stage 1"))
            {
                gain1 = lst[1].toDouble();
            }else if (lst[0].contains("Bandwidth"))
            {
                BW = lst[1].toDouble();
            }else if (lst[0].contains("Offset"))
            {
                offset = lst[1].toDouble();
            }
        }
        file.close();
        return true;
    }
    return false;
}

bool SRIFile::Save(QString fn)
{
    QFile file(fn);
    if(file.open(QIODevice::WriteOnly))
    {
        QTextStream s1(&file);
        s1 << "Reference Level (dB)=" << QString::number(RefLevDB,'f',3) << "\r\n";
        s1 << "RF Reference Frequency (Hz)=" << QString::number(CF,'f',3) << "\r\n";
        s1 << "Stage 2 Gain (dB)=" << QString::number(gain2,'f',3) << "\r\n";
        s1 << "Sample Rate (samples/sec)=" << QString::number(SPS,'f',6) << "\r\n";
        s1 << "RF Reference Frequency Offset (Hz)=" << QString::number(offset,'f',3) << "\r\n";
        s1 << "Stage 1 Gain (dB)=" << QString::number(gain1,'f',3) << "\r\n";
        s1 << "Bandwidth (Hz)=" << QString::number(BW,'f',6) << "\r\n";
        file.close();
        return true;
    }
    return false;
}
