#include "freq_time_marker.h"
static int _markercnt = 0;
freq_time_marker::freq_time_marker(QObject *parent)
{
    Q_UNUSED(parent);
    setFreqLowHz(-1);
    setFreqHighHz(-1);
    setStartTime_S(-1);
    setEndTime_S(-1);
    setName("Marker_" + QString::number(_markercnt++));
    setTags("");
    m_HasStartTime = true;
    m_HasEndTime = true;
}

double freq_time_marker::CF_Hz()
{
    return ((m_FreqHighHz - m_FreqLowHz) /2) + m_FreqLowHz;
}

double freq_time_marker::CF_MHz()
{
    return (((m_FreqHighHz - m_FreqLowHz) /2) + m_FreqLowHz) / 1000000.0;
}


void freq_time_marker::setCF_Hz(double cf)
{
    double bw = BW_Hz();
    setFreqLowHz(cf - (bw/2));
    setFreqHighHz(cf + (bw/2));
    emit(MarkerChanged(this));
}


void freq_time_marker::setCF_MHz(double cf)
{
    double bw = BW_MHz();
    setFreqLowMHz(cf - (bw/2));
    setFreqHighMHz(cf + (bw/2));
    emit(MarkerChanged(this));
}

double freq_time_marker::BW_Hz()
{
    return (m_FreqHighHz - m_FreqLowHz);
}

double freq_time_marker::BW_MHz()
{
    return (m_FreqHighHz - m_FreqLowHz) / 1000000.0;
}

void freq_time_marker::setBW_Hz(double BW)
{
    double CF = CF_Hz();
    setFreqLowHz(CF - (BW/2));
    setFreqHighHz(CF + (BW/2));
    emit(MarkerChanged(this));
}

void freq_time_marker::setBW_MHz(double BW)
{
    double CF = CF_MHz();
    setFreqLowMHz(CF - (BW/2));
    setFreqHighMHz(CF + (BW/2));
    emit(MarkerChanged(this));
}


double freq_time_marker::FreqLowHz() const
{
    return m_FreqLowHz;
}


double freq_time_marker::FreqLowMHz() const
{
    return m_FreqLowHz / 1000000.0;
}

void freq_time_marker::setFreqLowHz(double FreqLowHz)
{
    m_FreqLowHz = FreqLowHz;
    emit(MarkerChanged(this));
}

void freq_time_marker::setFreqLowMHz(double FreqLowMHz)
{
    m_FreqLowHz = FreqLowMHz * 1000000.0;
    emit(MarkerChanged(this));
}


double freq_time_marker::FreqHighHz() const
{
    return m_FreqHighHz;
}

double freq_time_marker::FreqHighMHz() const
{
    return m_FreqHighHz/1000000.0;
}

void freq_time_marker::setFreqHighHz(double FreqHighHz)
{
    m_FreqHighHz = FreqHighHz;
    emit(MarkerChanged(this));
}

void freq_time_marker::setFreqHighMHz(double FreqHighMHz)
{
    m_FreqHighHz = FreqHighMHz / 1000000;
    emit(MarkerChanged(this));
}

double freq_time_marker::StartTime_S() const
{
    return m_StartTimeS;
}

void freq_time_marker::setStartTime_S(double StartTimeS)
{
    m_StartTimeS = StartTimeS;
    emit(MarkerChanged(this));
}

double freq_time_marker::EndTime_S() const
{
    return m_EndTimeS;
}

void freq_time_marker::setEndTime_S(double EndTimeS)
{
    m_EndTimeS = EndTimeS;
    emit(MarkerChanged(this));
}

void freq_time_marker::Load(QSettings *settings)
{
    m_FreqLowHz = settings->value("FreqLowHz",0).toDouble();
    m_FreqHighHz = settings->value("FreqHighHz",0).toDouble();
    m_StartTimeS = settings->value("StartTimeS",0).toDouble();
    m_EndTimeS = settings->value("EndTimeS",0).toDouble();
    m_Name = settings->value("Name",m_Name).toString();
    m_Tags = settings->value("Tags",m_Tags).toString();
    m_HasEndTime = settings->value("HasEndTime",true).toBool();
    m_HasStartTime = settings->value("HasStartTime",true).toBool();
    emit(MarkerChanged(this));

}


void freq_time_marker::Save(QSettings *settings)
{
    settings->setValue("FreqLowHz",m_FreqLowHz);
    settings->setValue("FreqHighHz",m_FreqHighHz);
    settings->setValue("StartTimeS",m_StartTimeS);
    settings->setValue("EndTimeS",m_EndTimeS);
    settings->setValue("Name",m_Name);
    settings->setValue("HasEndTime",m_HasEndTime);
    settings->setValue("HasStartTime",m_HasStartTime);
}

QString freq_time_marker::Name() const
{
    return m_Name;
}

void freq_time_marker::setName(const QString &name)
{
    m_Name = name;
    emit(MarkerChanged(this));
}

QString freq_time_marker::Tags() const
{
    return m_Tags;
}

void freq_time_marker::setTags(const QString &Tags)
{
    m_Tags = Tags;
    emit(MarkerChanged(this));
}



void freq_time_markers::Load(QSettings *settings)
{
    int nentries;
    nentries = settings->beginReadArray("freq_markers");
    for(int c= 0; c< nentries; c++)
    {
        settings->setArrayIndex(c);
        freq_time_marker *fm = new freq_time_marker();
        fm->Load(settings);
        m_markers.push_back(fm);
    }
    settings->endArray();
}


void freq_time_markers::Save(QSettings *settings)
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


void freq_time_markers::OnMarkerChanged(freq_time_marker *mrk)
{
    emit(MarkerChanged(mrk)); // signal to whoever is listening
}

freq_time_markers::freq_time_markers(QObject *parent)
{
    Q_UNUSED(parent);
}

bool freq_time_markers::Load(char *fname)
{
    QSettings settings(fname);
    Load(&settings);
    return true;
}

bool freq_time_markers::Save(char *fname)
{
    QSettings settings(fname);
    Save(&settings);
    return true;
}


void freq_time_markers::AddMarker(freq_time_marker * mrk)
{
    m_markers.append(mrk);
    connect(mrk,SIGNAL(MarkerChanged(freq_time_marker*)),this,SLOT(OnMarkerChanged(freq_time_marker*)));
    emit(MarkerChanged(mrk));
}



void freq_time_markers::RemoveMarker(freq_time_marker *mrk)
{
    m_markers.removeOne(mrk);
    disconnect(mrk,SIGNAL(MarkerChanged(freq_time_marker*)),this,SLOT(OnMarkerChanged(freq_time_marker*)));
}
