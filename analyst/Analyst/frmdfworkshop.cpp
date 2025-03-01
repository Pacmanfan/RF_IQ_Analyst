#include "frmdfworkshop.h"
#include "ui_frmdfworkshop.h"

frmDFWorkshop::frmDFWorkshop(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frmDFWorkshop)
{
    ui->setupUi(this);
    QColor orangeColor(255,165,0);

    m_scope = ui->wgtDFScope;
    m_scope->AddGraph("Phase", Qt::yellow);
    m_scope->AddGraph("Mag", Qt::green);

    m_scope->AddGraph("Cntr_I", Qt::red);
    m_scope->AddGraph("Cntr_Q", Qt::blue);

    m_scope->AddGraph("Outr_I", Qt::white);
    m_scope->AddGraph("Outr_Q", orangeColor);

    m_scope->AddGraph("Phase_cntr", Qt::cyan);
    m_scope->AddGraph("Phase_outr", Qt::magenta);

    connect(ui->wgtDFScope,SIGNAL(CellChanged(int,int)),this,SLOT(onCellChanged(int,int)));
    m_rawdat = 0;
}

frmDFWorkshop::~frmDFWorkshop()
{
    delete ui;
}

void frmDFWorkshop::UpdatePlotData(retro_df_temp_data *rawdat)
{
    if(!rawdat)return;
    float minv = -999,maxv = -999;
    m_rawdat = rawdat;

    float Cntr_I[rawdat->m_numsamples];
    float Cntr_Q[rawdat->m_numsamples];
    float Outr_I[rawdat->m_numsamples];
    float Outr_Q[rawdat->m_numsamples];

    //de-interleave the IQ here for plotting
    float *tmp =  (float *)rawdat->m_IQ_1;
    float *tmp2 =  (float *)rawdat->m_IQ_2;
    for (long c = 0; c < rawdat->m_numsamples; c++)
    {
        float Id,Qd;
        Id = tmp[c * 2];
        Qd = tmp[(c * 2) + 1];
        Cntr_I[c] = Id;
        Cntr_Q[c] = Qd;

        Id = tmp2[c * 2];
        Qd = tmp2[(c * 2) + 1];
        Outr_I[c] = Id;
        Outr_Q[c] = Qd;
    }

    // include the min /max search only if the graph is visible
    if(m_scope->GraphVisible("Mag"))
        UpdateMinMax(rawdat->m_magdiff,rawdat->m_numsamples,&minv,&maxv);
    if(m_scope->GraphVisible("Phase"))
        UpdateMinMax(rawdat->m_phasediff,rawdat->m_numsamples,&minv,&maxv);
    if(m_scope->GraphVisible("Cntr_I"))
        UpdateMinMax(Cntr_I,rawdat->m_numsamples,&minv,&maxv);
    if(m_scope->GraphVisible("Cntr_Q"))
        UpdateMinMax(Cntr_Q,rawdat->m_numsamples,&minv,&maxv);
    if(m_scope->GraphVisible("Outr_I"))
        UpdateMinMax(Outr_I,rawdat->m_numsamples,&minv,&maxv);
    if(m_scope->GraphVisible("Outr_Q"))
        UpdateMinMax(Outr_Q,rawdat->m_numsamples,&minv,&maxv);
    if(m_scope->GraphVisible("Phase_cntr"))
        UpdateMinMax(rawdat->m_phase_1,rawdat->m_numsamples,&minv,&maxv);
    if(m_scope->GraphVisible("Phase_outr"))
        UpdateMinMax(rawdat->m_phase_2,rawdat->m_numsamples,&minv,&maxv);

    m_scope->curAvMin = minv;
    m_scope->curAvMax = maxv;
    //show the data from rawdat onto the scope on the DF workshop form
    m_scope->UpdateScope(rawdat->m_magdiff,"Mag",rawdat->m_numsamples,1,0);
    m_scope->UpdateScope(rawdat->m_phasediff,"Phase",rawdat->m_numsamples,1,0);
    m_scope->UpdateScope(Cntr_I,"Cntr_I",rawdat->m_numsamples,1,0);
    m_scope->UpdateScope(Cntr_Q,"Cntr_Q",rawdat->m_numsamples,1,0);
    m_scope->UpdateScope(Outr_I,"Outr_I",rawdat->m_numsamples,1,0);
    m_scope->UpdateScope(Outr_Q,"Outr_Q",rawdat->m_numsamples,1,0);
    m_scope->UpdateScope(rawdat->m_phase_1,"Phase_cntr",rawdat->m_numsamples,1,0);
    m_scope->UpdateScope(rawdat->m_phase_2,"Phase_outr",rawdat->m_numsamples,1,0);
    m_scope->plot->replot();

}

void frmDFWorkshop::UpdateMinMax(float *data, int numsamps, float *minv, float *maxv)
{
    for(int c = 0; c < numsamps; c++)
    {
        if(*minv == -999 && c ==0)
            *minv = data[c];
        if(*maxv == -999 && c ==0)
            *maxv = data[c];
        if(data[c] < *minv)
            *minv = data[c];
        if(data[c] > *maxv)
            *maxv = data[c];
    }
}

void frmDFWorkshop::onCellChanged(int row, int col)
{
    if(!m_rawdat)return;
  //recalc  min/max   asnd re-display
    UpdatePlotData(m_rawdat);
}

void frmDFWorkshop::on_cmdTest_clicked()
{
    //run a test
    //maybe update the display based on global vars?

}

