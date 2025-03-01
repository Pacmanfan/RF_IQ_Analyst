#ifndef SRIFILE_H
#define SRIFILE_H

/*
An SRI file is a file that *should accompany a .16T that describes the signal
*/


/*
Reference Level (dB)=-46.8828125
RF Reference Frequency (Hz)=313860106.5390625
Stage 2 Gain (dB)=0.0
Sample Rate (samples/sec)=1000000.0
RF Reference Frequency Offset (Hz)=0.0
Stage 1 Gain (dB)=0.0
Bandwidth (Hz)=1000000.0

*/
#include <QString>

class SRIFile
{
public:
    SRIFile();
    bool Load(QString fn);
    bool Save(QString fn);
    double CF,BW,SPS,RefLevDB;
    double gain1,gain2,offset;
};

#endif // SRIFILE_H

