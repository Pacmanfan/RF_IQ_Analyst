#include "wgt_scope.h"
#include "ui_wgt_scope.h"
#include <leveltrigger.h>
#include <dsp_utils.h>

bool GUIUpdate = false;

wgt_Scope::wgt_Scope(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::wgt_Scope)
{
    ui->setupUi(this);
    Initialize();
}

wgt_Scope::~wgt_Scope()
{
    delete ui;
    freqdem_destroy(fmdemod);
}

void wgt_Scope::UpdateGraphTable()
{
    GUIUpdate = true;
    QList<QString> keys = graphs.keys();
    QStringList headers;
    headers << "Visible" << "Channel" << "Color";
    ui->tblTraces->setColumnCount(headers.count());
    ui->tblTraces->setRowCount(keys.size());
    ui->tblTraces->setHorizontalHeaderLabels(headers);
    for(int c = 0; c< keys.size(); c++)
    {
        QCPGraph *graph = graphs[keys[c]]; // get the graph
        bool vis = graph->visible();
        QString name = keys[c];
        QTableWidgetItem *checkItem = new QTableWidgetItem();
        if(vis)
            checkItem->setCheckState(Qt::Checked);
        else
            checkItem->setCheckState(Qt::Unchecked);

        ui->tblTraces->setItem(c, 0, checkItem);
        ui->tblTraces->setItem(c,1,new QTableWidgetItem(name));
        QTableWidgetItem *twicolor = new QTableWidgetItem();
        twicolor->setBackgroundColor(graph->pen().color());
        ui->tblTraces->setItem(c,2, twicolor);
    }
    ui->tblTraces->resizeRowsToContents();
    ui->tblTraces->resizeColumnToContents(0);

    GUIUpdate = false;
}

QCPGraph *wgt_Scope::AddGraph(QString tracename, QColor color)
{
    QCPGraph * ret = wgt_Sig_Base::AddGraph(tracename,color);
    UpdateGraphTable();
    return ret;
}

//override these to get notification when a graph is added or removed
QCPGraph *wgt_Scope::AddGraph(QString tracename, QCPAxis *axis, QColor color)
{
    QCPGraph * ret = wgt_Sig_Base::AddGraph(tracename,axis,color);
    UpdateGraphTable();
    return ret;
}

void wgt_Scope::RemoveGraph(QString tracename)
{
    wgt_Sig_Base::RemoveGraph(tracename);
    UpdateGraphTable();
}

void wgt_Scope::TestAddTrigger()
{
    LevelTrigger *lt = new LevelTrigger(plot);
    lt->setPowerlevel(.25);
}

void wgt_Scope::SetAvLen(int val)
{
    avarlen = val;
    if(minAVAR!=0)
    {
        delete []minAVAR;
        delete []maxAVAR;
        minAVAR = 0;
        maxAVAR = 0;
    }
    minAVAR = new double[val];
    maxAVAR = new double[val];
    for(int c= 0; c < val; c++)
    {
        //need to set to some new val
        minAVAR[c] = curAvMin; // set to the current average
        maxAVAR[c] = curAvMax;
    }
}

void wgt_Scope::UpdateAv(double minv, double maxv)
{
    double *dst;

    dst = minAVAR;
    dst++;
    memmove(dst,minAVAR,sizeof(double) * (avarlen - 1)); // move everything down 1
    dst = maxAVAR;
    dst++;
    memmove(dst,maxAVAR,sizeof(double) * (avarlen - 1)); // move everything down 1
    //put in new vals
    minAVAR[0] = minv;
    maxAVAR[0] = maxv;
    //now average
    curAvMin = curAvMax = 0;
    for(int c= 0; c < avarlen; c++)
    {
        curAvMin += minAVAR[c];
        curAvMax += maxAVAR[c];
    }
    curAvMin /= (double) avarlen;
    curAvMax /= (double) avarlen;


}

void wgt_Scope::FindMinMax(float *data, int numsamp)
{
    float minv,maxv;
    for(int c = 0 ; c < numsamp; c++)
    {
        if(c == 0)
        {
            minv = maxv = data[c];
        }else
        {
            if(data[c] < minv)minv = data[c];
            if(data[c] > maxv)maxv = data[c];
        }
    }
    curAvMin = minv;
    curAvMax = maxv;
}



void wgt_Scope::UpdateScope(float *fvals, QString graphname, int _periodsamples, double tps, double absstarttime)
{
    float timeframe = absstarttime + ((double)_periodsamples * tps);//  MAX_TIMEFRAME_MS; // 10 seconds

    plot->xAxis2->setRange(absstarttime,timeframe);
    plot->xAxis->setRange(absstarttime,timeframe);

    static QVector<float> timescale(_periodsamples);
    static QVector<float> data1(_periodsamples);

    for (long c = 0; c < _periodsamples; c++)
    {
        double tm = absstarttime + (tps * ((double)c));// * 1000);
        timescale[c] = tm;
        data1[c] = fvals[c];
    }

    QCPGraph *graph;
    graph = GetGraph(graphname);
    if(graph)
        graph->setData(timescale,data1,true);

    plot->yAxis->setRange(curAvMin - (curAvMin * .1f),curAvMax * 1.25f );
    plot->yAxis2->setRange(curAvMin - (curAvMin * .1f),curAvMax * 1.25f);
}


/*
The  QVector<float> timescale goes from 0 .. (_periodsamples * time per sample) in uS
This is on the XAxis
typical rng would be low = 1940..  high = 4500 for looking near the beginning of a stream
double endtime = (_periodsamples * tps * 1000000);
rng.high is meaningless in this contact, it's really how much data is verticall on the waterfall
*/



void wgt_Scope::UpdateScope(complex<float> *samples, int _periodsamples, double tps, double absstarttime)
{
    //detect if any parameters changed from the last call, this will re-set the view
    static double lasttps;
    static int lastperiodsamples;

    double endtime = (_periodsamples * tps * 1000000);

    bool changed = false;

    if(lastperiodsamples != _periodsamples) changed = true;
    if(lasttps != tps) changed = true;

    lasttps = tps;
    lastperiodsamples = _periodsamples;

    _abs_start_time = absstarttime; // absolute start time in uS
    _abs_end_time = absstarttime + endtime; // absolute end time in uS

    if(changed)
    {
        plot->xAxis2->setRange(absstarttime,endtime + absstarttime);
        plot->xAxis->setRange(0,endtime);
    }

    QVector<float> timescale;
    QVector<float> dataI;
    QVector<float> dataQ;
    QVector<float> dataExt;
    QVector<float> dataMag;
    QVector<float> dataFM;
    QVector<float> dataFMAV;
    float tempphasein[_periodsamples];
    float tempphaseout[_periodsamples];

    bool showI = GraphVisible("I");
    bool showQ = GraphVisible("Q");
    bool showPhase = GraphVisible("phase");
    bool showMag = GraphVisible("magnitude");
    bool showFM = GraphVisible("FM demod");

    double lower = 0;
    double upper = 0;

    float *idata = (float *)samples; // cast to array of interleaved floats

    //double tps = 1.0 / ipo.SampleRateHz; // time per sample

    for (long c = 0; c < _periodsamples; c++)
    {
        float Id,Qd;
        Id = idata[c * 2];
        Qd = idata[(c * 2) + 1];
        double tm = (tps * ((double)c)* 1000000);
        timescale.append(tm);
        if(showI)
            dataI.append(Id);
        if(showQ)
            dataQ.append(Qd);

        if(c > _periodsamples / 4)
        {
            if(Id < lower) lower = Id;
            if(Id > upper) upper = Id;
            if(Qd > upper) upper = Qd;
            if(Qd < lower) lower = Qd;
        }

        if(showPhase)
        {
            float phase = atan2(Id,Qd);
            //dataExt.append(phase);
            tempphasein[c] = phase;
            if(c > _periodsamples / 4)
            {
                if(phase < lower) lower = phase;
                if(phase > upper) upper = phase;
            }
        }
        if(showMag)
        {
            float mag = sqrt((Id*Id) + (Qd*Qd));// * 1000;
            dataMag.append(mag);
            if(c > _periodsamples / 4)
            {
                if(mag < lower) lower = mag;
                if(mag > upper) upper = mag;
            }
        }
    }

    if(showFM)
    {
        //calculate the FM signal for the given samples - _periodsamples
        if(dataFM.length() != _periodsamples)
        {
            dataFM.resize(_periodsamples);
            dataFMAV.resize(_periodsamples);
        }
        freqdem_demodulate_block(fmdemod,(liquid_float_complex *) idata, _periodsamples, dataFM.data());
        float *tmp = dataFM.data();
       // float *tmpAV = dataFMAV.data();

        if(useMovingAverage)
        {
            tmp = dataFMAV.data();
            float sum;
            int sumlen;
            for (int c =0 ; c< dataFM.length(); c++)
            {
                sum = 0;
                sumlen = 0;
                for (int d =  c ; d < (c + movingAverageVal) ; d ++ )
                {
                    if(d < dataFM.length())
                    {
                        sum += dataFM.data()[d];
                        sumlen ++;
                    }
                }
                sum /= sumlen;
                dataFMAV.data()[c] = sum;
            }
        }

        //calc some upper and lower bounds
        for(int c= 0; c < _periodsamples ; c++)
        {
            if(c > _periodsamples / 4)
            {
                if(*tmp < lower) lower = *tmp;
                if(*tmp > upper) upper = *tmp;
            }
            tmp ++;
        }

    }
    //scale the bounds back a bit
    lower = lower + (lower / 6);
    upper = upper + (upper / 6);

    // new Scope
    QCPGraph *graph;
    graph = GetGraph("I");
    if(graph && showI)
        graph->setData(timescale,dataI,true);

    graph = GetGraph("Q");
    if(graph && showQ)
        graph->setData(timescale,dataQ,true);

    if(dataFM.length() > 0)
    {
        graph = GetGraph("FM demod");
        if(graph && showFM)
        {
            if(useMovingAverage)
            {
                graph->setData(timescale,dataFMAV,true);

            }else
            {
                graph->setData(timescale,dataFM,true);
            }
        }
    }
    graph = GetGraph("phase");
    if(showPhase && graph)
    {
        DSP_Utils::unwrap_phase(tempphasein,tempphaseout,_periodsamples,3.14159265358979323846,-3.14159265358979323846);
        for(int c= 0 ; c < _periodsamples; c++)
        {
            dataExt.append(tempphaseout[c]);
            if(c > _periodsamples / 4)
            {
                if(tempphaseout[c] < lower) lower = tempphaseout[c];
                if(tempphaseout[c] > upper) upper = tempphaseout[c];
            }
        }
        graph->setData(timescale,dataExt,true);
    }

    graph = GetGraph("magnitude");
    if(showMag && graph)
    {
        graph->setData(timescale,dataMag,true);
    }

    //update the average

    UpdateAv(lower,upper);

    plot->yAxis->setRange(curAvMin, curAvMax);
    plot->yAxis2->setRange(curAvMin, curAvMax);
    //curAvMin
    plot->replot();


}

void wgt_Scope::Initialize()
{
    useMovingAverage = false;
    plot = ui->plotScope;//customPlot_SWT_PLOT_TOP;
    plot->axisRect()->setAutoMargins(QCP::MarginSides());
//    plot->axisRect()->setMargins(QMargins(75,20,12,0));
    plot->axisRect()->setMargins(QMargins(75,20,12,20));

    plot->xAxis2->setVisible(true);  //Upper X-Axis
    plot->xAxis2->setTickLabels(true);
    plot->xAxis2->setLabel("Time");
    plot->xAxis2->setNumberFormat("f");
    plot->xAxis2->setNumberPrecision(3);

    plot->xAxis->setVisible(true);  //Lower X-Axis
    plot->xAxis->setTickLabels(true);
    plot->xAxis->setLabel("Time");
    plot->xAxis->setNumberFormat("f");
    plot->xAxis->setNumberPrecision(3);

    //Y AXIS (ON LEFT)
    plot->yAxis->setVisible(true);
    plot->yAxis->setLabel("Power");
    plot->yAxis->setNumberPrecision(3);

    //Y AXIS (ON RIGHT)
    plot->yAxis2->setVisible(false);
    // make left and bottom axes always transfer their ranges to right and top axes:
  //  connect(plotScope->xAxis, SIGNAL(rangeChanged(QCPRange)), plotScope->xAxis2, SLOT(setRange(QCPRange)));
    connect(plot->yAxis, SIGNAL(rangeChanged(QCPRange)), plot->yAxis2, SLOT(setRange(QCPRange)));

    // this is for limiting the time range on the x - axis
    //connect(plot->xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(ScopeTimeRangeChanged(QCPRange)));

        //make things selectable:
    plot->setInteractions( QCP::iRangeZoom | QCP::iRangeDrag);
    plot->axisRect()->setRangeZoomFactor(1.25,1);
    plot->axisRect()->setRangeDrag(Qt::Horizontal);

    plot->axisRect()->setBackground(Qt::black);

    //now set up mouse handlers
    // mouse move
    connect(plot, SIGNAL(mouseMove(QMouseEvent*)), this,
        SLOT(OnMouseMove(QMouseEvent*)));

    //SINGLE MOUSE CLICK (used for INPUTING threshold)
    connect(plot, SIGNAL(mousePress(QMouseEvent*)), this,
            SLOT(OnMousePressed(QMouseEvent*)));

    //Mouse Release
    connect(plot, SIGNAL(mouseRelease(QMouseEvent*)), this,
            SLOT(OnMouseReleased(QMouseEvent*)));


    //QColor colphase = QColor::fromRgb(255,0,0);
    /*
    _ScopeTracer = new QCPItemTracer(plot);
    _ScopeTracer->setGraph(graph);
    _ScopeTracer->setVisible(true);
    _ScopeTracer->setStyle(QCPItemTracer::tsSquare);
    _ScopeTracer->setPen(QPen(colphase));   //DOT color
    _ScopeTracer->setBrush(colphase);
    _ScopeTracer->setSize(7);
    */
    minAVAR = 0; //min average array
    maxAVAR = 0; //max average array
    curAvMin = -100; // current average min
    curAvMax = 100; // current average min
    avarlen = 0; //avergae array len
    SetAvLen(20);


    float FSK_DEVIATION_HZ = 3500;//ui->spnFMDev->value();
    double sps = 10;// lfi.highF - lfi.lowF;
    sps *= 1000000;
    float kf = FSK_DEVIATION_HZ/sps; // modulation factor
    fmdemod = freqdem_create(kf);
    ui->spnAverage->setEnabled(false);
    movingAverageVal = 1;
    ui->cmbnumSamples->setCurrentIndex(2);
}


/*
newrange is the relative time window that we're currently viewing

*/
void  wgt_Scope::ScopeTimeRangeChanged(const QCPRange &newRange)
{
    static bool protect;
    if(protect == true)
        return;

    protect = true;
    // newRange is the visual time range in relative
    double range = newRange.upper - newRange.lower;
    double view_abs_start_time = _abs_start_time + newRange.lower;
    double view_abs_end_time = _abs_start_time + newRange.upper;

    if(view_abs_start_time < _abs_start_time)
    {
        view_abs_start_time = _abs_start_time;
        plot->xAxis->setRange(0,range );
        emit(Pan(-1));
    }

    if(view_abs_end_time > _abs_end_time)
    {
        view_abs_end_time = _abs_end_time;
        double absdur = _abs_end_time -  _abs_start_time;
        plot->xAxis->setRange( absdur - range, absdur);
        emit(Pan(1));
    }

    double endtime = view_abs_start_time +  range;
    plot->xAxis2->setRange(view_abs_start_time,endtime );
    //plot->xAxis2->setRange(view_start_time,view_end_time );
    protect = false;

}

void wgt_Scope::OnMouseMove(QMouseEvent *evt)
{
    Q_UNUSED(evt)
}

void wgt_Scope::OnMousePressed(QMouseEvent *evt)
{
    Q_UNUSED(evt)

}

void wgt_Scope::OnMouseReleased(QMouseEvent *evt)
{
    Q_UNUSED(evt)

}


void wgt_Scope::on_tblTraces_cellChanged(int row, int column)
{
    if(GUIUpdate)return; // ignore this message if we're updating the GUI from the table update code.
    if(column != 0) // not a checkbox column
        return;
    //get the graph
    QList<QString> keys = graphs.keys();
    QCPGraph *graph = graphs[keys[row]]; // get the graph

    //get the checkbox
    QTableWidgetItem *chkbox = ui->tblTraces->item(row,column);
    bool ischecked = chkbox->checkState() == Qt::Checked ? true: false;
    graph->setVisible(ischecked);
    UpdateGraphTable();

    emit(CellChanged(row,column)); // let the parent control know something changed
    plot->replot();
}


void wgt_Scope::on_chkAverage_clicked()
{
    ui->spnAverage->setEnabled(ui->chkAverage->isChecked());
    useMovingAverage = ui->chkAverage->isChecked();
    movingAverageVal = ui->spnAverage->value();
}

void wgt_Scope::on_spnAverage_valueChanged(int arg1)
{
    movingAverageVal = arg1;
}

void wgt_Scope::on_cmbnumSamples_currentIndexChanged(int index)
{
    int len = ui->cmbnumSamples->itemText(index).toInt();
    emit(SetPeriodSamples(len));
}
