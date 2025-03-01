#include "qconstellationplot.h"
#include "ui_qconstellationplot.h"

QConstellationPlot::QConstellationPlot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QConstellationPlot)
{
    ui->setupUi(this);
    Initialize();
}

QConstellationPlot::~QConstellationPlot()
{
    delete ui;
}

void QConstellationPlot::Initialize()
{
    plotConstellation = ui->wgtPlot;
    plotConstellation->axisRect()->setAutoMargins(QCP::MarginSides());
    plotConstellation->axisRect()->setMargins(QMargins(70,12,12,70));

    plotConstellation->xAxis->setVisible(true);
    plotConstellation->xAxis->setTickLabels(true);
    plotConstellation->xAxis->setLabel("In Phase");
    plotConstellation->xAxis->setNumberFormat("f");
    plotConstellation->xAxis->setNumberPrecision(6);

    //Y AXIS (ON LEFT)
    plotConstellation->yAxis->setVisible(true);
    plotConstellation->yAxis->setLabel("Quadrature");
    plotConstellation->yAxis->setNumberPrecision(6);

    //Y AXIS (ON RIGHT)
    plotConstellation->yAxis2->setVisible(false);

    //ADD GRAPH:
    graph = plotConstellation->addGraph(plotConstellation->xAxis); // top

    graph->setLineStyle(QCPGraph::lsNone);
    graph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));

        //make things selectable:
    plotConstellation->setInteractions( QCP::iRangeZoom );//| QCP::iRangeDrag);
    plotConstellation->axisRect()->setRangeZoomFactor(1.25,1.25);
}

void QConstellationPlot::UpdatePlot(float *data,int num_samples)
{
    QVector<float> dataI;
    QVector<float> dataQ;

    if(data == 0) // prbably no file loaded yet
        return;
   // if(iqdatalen == 0)
     //   return;

    double minx,miny,maxx,maxy = 0;

    for (long c = 0; c < num_samples; c++)
    {
        float Id,Qd;
        Id = data[c * 2];
        Qd = data[(c * 2) + 1];

        dataI.append(Id);
        dataQ.append(Qd);

        if(c == 0)
        {
            minx = Id;
            maxx = Id;
            maxy  = Qd;
            miny = Qd;
        }else
        {
            if(Id < minx) minx = Id;
            if(Id > maxx) maxx = Id;
            if(Qd > maxy) maxy  = Qd;
            if(Qd < miny) miny = Qd;
        }

    }

    if(dataI.length() > 0)
    {
        graph->setData(dataI,dataQ,true);//PLOT DATA:
    }

    fabs(minx) > fabs(maxx) ? maxx = fabs(minx) : minx = fabs(maxx) * -1.0;
    fabs(miny) > fabs(maxy) ? maxy = fabs(miny) : miny = fabs(maxy) * -1.0;
    //fabs(maxx) > fabs(minx) ? maxx = fabs(minx);


    graph->setPen(QPen((Qt::GlobalColor)(int)Qt::blue,1));

    //FIT TO WINDOW

    plotConstellation->yAxis->setRange(miny, maxy);
    plotConstellation->yAxis2->setRange(miny, maxy);
    plotConstellation->xAxis->setRange(minx, maxx);

    plotConstellation->replot();
}
