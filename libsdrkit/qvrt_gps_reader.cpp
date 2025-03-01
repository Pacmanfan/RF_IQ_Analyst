#include "qvrt_gps_reader.h"
#include <QFileInfo>

void *qvrt_gps_reader_threadfn(void *param);

QVRT_GPS_Reader::QVRT_GPS_Reader(QObject *parent) : QObject(parent)
{
    m_readerthread = nullptr;
}

void QVRT_GPS_Reader::stop()
{
    if(m_running)
    {
        if(m_readerthread !=nullptr)
        {
            if(m_readerthread->joinable())
                m_readerthread->join();
            m_readerthread = nullptr;
        }

        m_running = false;
    }
}

bool QVRT_GPS_Reader::start(QString qvrtfile, bool exportkml)
{
    //check if file exists
    QFileInfo check_file(qvrtfile);
    if(!check_file.exists())
        return false;
    if(m_running)
        return false;
    m_running = true;
    file = qvrtfile;
    m_exportkml = exportkml;
    //pthread_create(&m_readerthread, NULL, qvrt_gps_reader_threadfn, this);
    m_readerthread = new std::thread([this]{process();});
    return true;
}

void QVRT_GPS_Reader::process()
{

    QVRT_Reader reader;
    if(!reader.Open(file.toLatin1().data()))
    {
        emit(QVRT_GPS_Message(true,"Could not open QVRT file :" +file ));
        m_running = false;
        return;
    }
    long filesize = reader.FileLength();

    QString kmlfilename;
    FILE *fpkml;
    if(m_exportkml == true)
    {
        //open up a KML file
        QFileInfo info(file);
       kmlfilename = info.path() + info.completeBaseName() + ".kml";
       fpkml = fopen(kmlfilename.toLatin1().data(),"w");
       if (fpkml == 0)
       {
           //flag error
           emit(QVRT_GPS_Message(true,"Could not open KML file for writing :" +kmlfilename ));
           m_running = false;
           return;
       }
    }

    m_coords.clear();

    QVRT_Header *header;
    QVRT_IFContext_Packet ifctx;
    unsigned char *data = 0;

    // read the first chunk
    header = reader.ReadNextPacket();

    if(m_exportkml == true)
    {
        fprintf(fpkml,"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n");
        fprintf(fpkml,"<kml xmlns=\"http://www.opengis.net/kml/2.2\">\r\n");
        fprintf(fpkml,"<Document>\r\n");
        fprintf(fpkml,"<name>Paths</name>\r\n");
        fprintf(fpkml,"<description>Extracted GPS information from QVRT file </description>\r\n");
        fprintf(fpkml,"<Style id=\"yellowLineGreenPoly\">\r\n");
        fprintf(fpkml,"<LineStyle>\r\n");
        fprintf(fpkml,"<color>7f00ffff</color>\r\n");
        fprintf(fpkml,"<width>4</width>\r\n");
        fprintf(fpkml,"</LineStyle>\r\n");
        fprintf(fpkml,"<PolyStyle>\r\n");
        fprintf(fpkml,"<color>7f00ff00</color>\r\n");
        fprintf(fpkml,"</PolyStyle>\r\n");
        fprintf(fpkml,"</Style>\r\n");
        fprintf(fpkml,"<Placemark>\r\n");
        fprintf(fpkml,"<name>Absolute Extruded</name>\r\n");
        fprintf(fpkml,"<description>Transparent green wall with yellow outlines</description>\r\n");
        fprintf(fpkml,"<styleUrl>#yellowLineGreenPoly</styleUrl>\r\n");
        fprintf(fpkml,"<LineString>\r\n");
        fprintf(fpkml,"<extrude>1</extrude>\r\n");
        fprintf(fpkml,"<tessellate>1</tessellate>\r\n");
        fprintf(fpkml,"<altitudeMode>absolute</altitudeMode>\r\n");
        fprintf(fpkml,"<coordinates>\r\n");
    }
    ifctx.StartGPSPrint();
    float percent = 0;
    while(header != 0 && m_running)
    {
        data = reader.CurrentBufferPos();

        switch(header->packetType)
        {

            case QVRT_IF_CONTEXT:
                ifctx.Decode(data);
                if(ifctx.f_FormattedGPSGeolocation)
                {
                    if(m_exportkml)\
                    {
                        fprintf(fpkml,"%f,%f,%f\r\n",ifctx.Longitude,ifctx.Latitude,ifctx.Altitude);
                    }
                    QVRT_GPS_Coord * coord = new QVRT_GPS_Coord(); // make a new coordinate
                    coord->longitude = ifctx.Longitude;
                    coord->latitude = ifctx.Latitude;
                    coord->altitude = ifctx.Altitude;
                    m_coords.append(coord); // add it to the vector for later retrieval


                    percent = ((double)(reader.TellP()) / (double)filesize) * 100.0;

                    emit(QVRT_GPS_Progress(this,percent,false));
                }
                break;

        }
        header = reader.ReadNextPacket();
    }
    if(m_exportkml)
    {
        fprintf(fpkml," </coordinates>\r\n");
        fprintf(fpkml,"</LineString>\r\n");
        fprintf(fpkml,"</Placemark>\r\n");
        fprintf(fpkml,"</Document>\r\n");
        fprintf(fpkml,"</kml>\r\n");

    }
    emit(QVRT_GPS_Progress(this,percent,true));

    return;
}




