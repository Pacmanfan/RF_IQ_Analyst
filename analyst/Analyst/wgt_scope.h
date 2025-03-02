#ifndef WGT_SCOPE_H
#define WGT_SCOPE_H

#include <QWidget>
#include <qcustomplot.h>
#include <QMap>
#include "wgt_sig_base.h"
#include <datarange.h>
#include <complex>
#include <liquid/liquid.h>

using namespace std;

namespace Ui {
class wgt_Scope;
}

/*
Generic scope widget class
this allows you to add new traces and set trace data
We should support triggers,
We can use a trigger level to enable a demod
this way, we only demod bursts above a certain power level


We should also be able to display markers on the scope.
I need to re-vamp my marker class

There should be a business logic class for a frequency and time marker
and then there should be a GUI class that allows the marker to be displayed and manipulated on displays
that holds all the QCP specific display items.


*/

class wgt_Scope : public QWidget, public wgt_Sig_Base
{
    Q_OBJECT

public:
    explicit wgt_Scope(QWidget *parent = 0);
    ~wgt_Scope();
    void Initialize();
    void UpdateGraphTable();
    virtual QCPGraph *AddGraph(QString tracename,QColor color); // defaults to the xaxis
    virtual QCPGraph *AddGraph(QString tracename,QCPAxis *axis,QColor color); // add to a specific axis
    virtual void RemoveGraph(QString tracename);
    //void TestAddTrigger();
    void SetAvLen(int val);
    void UpdateAv(double minv,double maxv);
    void FindMinMax(float *data , int numsamp);
    void UpdateScope(complex<float> *samples, int numsamples, double tps, double absstarttime);
    void UpdateScope(float *fvals, QString graphname, int _periodsamples, double tps, double absstarttime);
    double curAvMin; // current average min
    double curAvMax; // current average min

private:
    Ui::wgt_Scope *ui;
    QCPItemTracer *_ScopeTracer;
    freqdem  fmdemod; // fm demod for the scope control
    double *minAVAR; //min average array
    double *maxAVAR; //max average array
    int avarlen; //avergae array len
    bool useMovingAverage;
    int movingAverageVal;
    double _abs_start_time; // absolute start time of this period in uS
    double _abs_end_time; // absolute end time of this period in uS

public slots:
    void ScopeTimeRangeChanged(const QCPRange &newRange);
    void OnMouseMove(QMouseEvent *evt);
    void OnMousePressed(QMouseEvent *evt);
    void OnMouseReleased(QMouseEvent *evt);
signals:
    void Pan(double val);
    void SetPeriodSamples(int len);
    void CellChanged(int row,int col);
private slots:
    void on_tblTraces_cellChanged(int row, int column);
    void on_chkAverage_clicked();
    void on_spnAverage_valueChanged(int arg1);
    void on_cmbnumSamples_currentIndexChanged(int index);
};

#endif // WGT_SCOPE_H
