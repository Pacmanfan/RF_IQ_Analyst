#include <utils.h>
#include <QString>
#include <QFileInfo>

file_format DetermineFormat(QString filename)
{
    //determine input file format
    QFileInfo qfi(filename);
    QString suffix = qfi.suffix().toLower();
    file_format fmt = eQVRT;
    if(suffix == "qvrt")
    {
        fmt = eQVRT;
    }else if (suffix == "16t" || suffix == "s16" )
    {
        fmt = eS16;
    }else if (suffix == "u16")
    {
        fmt = eU16;
    }else if(suffix == "u8")
    {
        fmt = eU8;
    }else if(suffix == "s8")
    {
        fmt = eS8;
    }else if(suffix == "cfile" || suffix == "raw") //(GQRX raw file )
    {
        fmt = e32;
    }else
    {
        fmt = eUNK;
    }
    return fmt;
}
