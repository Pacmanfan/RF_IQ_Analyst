#include "ftmarker.h"

ftmarker::ftmarker()
{
    lowFreqLineFFT = 0;
    highFreqLineFFT = 0;
    CenterFreqLineFFT = 0;
    lowFreqLineWaterfall = 0;
    highFreqLineWaterfall = 0;
    CenterFreqLineWaterfall     = 0;

    lowTimeLineWaterfall = 0;
    highTimeLineWaterfall = 0;

    m_ms = eMV_None;
    Sel_lowF = -1.0f;
    Sel_highF = -1.0f;
    Sel_lowT = -1;
    Sel_highT = -1;

    useTimeSel = true;
}

void ftmarker::Reset()
{
    Sel_lowF = -1.0f;
    Sel_highF = -1.0f;
}

void ftmarker::UnselectAll()
{
    lowFreqLineFFT->setSelected(false);
    highFreqLineFFT->setSelected(false);
    CenterFreqLineFFT->setSelected(false);
    lowFreqLineWaterfall->setSelected(false);
    highFreqLineWaterfall->setSelected(false);
    CenterFreqLineWaterfall->setSelected(false);
    m_ms = eMV_None; // reset selection state

}

void ftmarker::Init(QCustomPlot *plotFFT, QCustomPlot *plotWaterfall)
{

    CenterFreqLineFFT = new QCPItemStraightLine(plotFFT);
    CenterFreqLineWaterfall = new QCPItemStraightLine(plotWaterfall);

    lowFreqLineFFT = new QCPItemStraightLine(plotFFT);
    lowFreqLineWaterfall = new QCPItemStraightLine(plotWaterfall);
    Sel_lowF = 100;

    SetupLine(lowFreqLineFFT,Sel_lowF,Qt::green,plotFFT);
    SetupLine(lowFreqLineWaterfall,Sel_lowF,Qt::green,plotWaterfall);

    highFreqLineFFT = new QCPItemStraightLine(plotFFT);
    highFreqLineWaterfall = new QCPItemStraightLine(plotWaterfall);
    Sel_highF = 100;
    Sel_centerf = 100;

    SetupLine(highFreqLineFFT,Sel_highF,Qt::blue,plotFFT);
    SetupLine(highFreqLineWaterfall,Sel_highF,Qt::blue,plotWaterfall);

    lowTimeLineWaterfall = new QCPItemStraightLine(plotWaterfall);
    highTimeLineWaterfall = new QCPItemStraightLine(plotWaterfall);
    Sel_lowT = 0;
    Sel_highT = 0;

//    SetupHLine(lowTimeLineWaterfall,Sel_lowT/1000.0f,Qt::green,plotWaterfall);
//    SetupHLine(highTimeLineWaterfall,Sel_highT/1000.0f,Qt::green,plotWaterfall);
}

//I fear this is incorrect for the waterfall
void ftmarker::SetupLine(QCPItemStraightLine* line, float xv, QColor color,QCustomPlot *customPlot)
{
    line->point1->setType(QCPItemPosition::ptPlotCoords);
    line->point2->setType(QCPItemPosition::ptPlotCoords);
    line->point1->setAxes(customPlot->graph(0)->keyAxis(), customPlot->graph(0)->valueAxis());
    line->point2->setAxes(customPlot->graph(0)->keyAxis(), customPlot->graph(0)->valueAxis());
    line->point1->setCoords(xv, 0);
    line->point2->setCoords(xv, -150);

    line->setPen(QPen(color,2));
    line->setClipAxisRect(customPlot->axisRect());
    line->setSelectable(true);
}

void ftmarker::Load(QSettings *settings)
{
    Sel_lowF = settings->value("Sel_lowF",0).toDouble();
    Sel_highF = settings->value("Sel_highF",0).toDouble();
    Sel_lowT = settings->value("Sel_lowT",0).toDouble();
    Sel_highT = settings->value("Sel_highT",0).toDouble();
    useTimeSel = settings->value("useTimeSel",false).toDouble();

}


void ftmarker::Save(QSettings *settings)
{
    settings->setValue("Sel_lowF",Sel_lowF);
    settings->setValue("Sel_highF",Sel_highF);
    settings->setValue("Sel_lowT",Sel_lowT);
    settings->setValue("Sel_highT",Sel_highT);
    settings->setValue("useTimeSel",useTimeSel);
}

void ftmarker::SetupHLine(QCPItemLine* line,float xlow, float xhigh, float yv, QColor color,QCustomPlot *plotFFT)
{
    line->start->setType(QCPItemPosition::ptPlotCoords);
    line->end->setType(QCPItemPosition::ptPlotCoords);
    line->start->setAxes(plotFFT->graph(0)->keyAxis(), plotFFT->graph(0)->valueAxis());
    line->end->setAxes(plotFFT->graph(0)->keyAxis(), plotFFT->graph(0)->valueAxis());

   // printf("MainWindow::SetupHLine %f %f\r\n",xlow,xhigh);
    line->start->setCoords(xlow, yv);
    line->end->setCoords(xhigh, yv);

    line->setPen(QPen(color,2));
    line->setClipAxisRect(plotFFT->axisRect());
   // line->setSelectable(true);

}


freq_markers::freq_markers()
{

}

void freq_markers::Load(QSettings *settings)
{
    int nentries;
    nentries = settings->beginReadArray("freq_markers");
    for(int c= 0; c< nentries; c++)
    {
        settings->setArrayIndex(c);
        ftmarker *fm = new ftmarker();
        fm->Load(settings);
        m_markers.push_back(fm);
    }
    settings->endArray();
}


void freq_markers::Save(QSettings *settings)
{
    int nentries = m_markers.size();
    settings->beginWriteArray("freq_markers",nentries);
    for(int c = 0; c < m_markers.size(); c++ )
    {
        settings->setArrayIndex(c);
        m_markers.at(c)->Save(settings);
    }
    settings->endArray();
}

bool freq_markers::FindMatch(ftmarker *mrk)
{
    /*
    // iterate through all the markers
    for(int c = 0; c < m_freqs.size(); c++ )
    {
        if(m_freqs.at(c)->Matches(mrk))
        {
            return true;

  }
    }
    */
    return false;
}

bool freq_markers::Load(char *fname)
{
    QSettings settings(fname);
    Load(&settings);
    return true;
}

bool freq_markers::Save(char *fname)
{
    QSettings settings(fname);
    Save(&settings);
    return true;
}


void freq_markers::AddMarker(ftmarker * mrk, bool allowduplicates)
{
    /*
    if(allowduplicates == false)
    {
        if(!FindMatch(mrk))
        {
            fmarker *copy = mrk->Copy();
            m_freqs.append(copy);
        }
    }else
    {
        fmarker *copy = mrk->Copy();
        m_freqs.append(copy);
    }
    */
}
/*
    Add all markers from source to this
    allowduplicates indicates if duplicates should be copied
*/
void freq_markers::AddMarkers(freq_markers * source, bool allowduplicates)
{
    /*
    printf("Adding Markers source count = %d: dest count = %d",source->m_freqs.size(),m_freqs.size());
    //iterate through all markers from the source
    for(int c = 0; c < source->m_freqs.size(); c++ )
    {
        fmarker* marker = source->m_freqs.at(c);
        if(allowduplicates)
        {
            //just copy
            fmarker *copy = marker->Copy();
            m_freqs.append(copy);
        }else
        {
            printf("Finding Matches");
            if(!FindMatch(marker))
            {
                fmarker *copy = marker->Copy();
                m_freqs.append(copy);
            }
        }
    }
    */
}

