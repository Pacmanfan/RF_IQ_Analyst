#ifndef QCONSTELLATIONPLOT_H
#define QCONSTELLATIONPLOT_H

#include <QWidget>
#include <qcustomplot.h>
#include <complex>
using namespace std;

namespace Ui {
class QConstellationPlot;
}

class QConstellationPlot : public QWidget
{
    Q_OBJECT

public:
    explicit QConstellationPlot(QWidget *parent = 0);
    ~QConstellationPlot();
    QCustomPlot *plotConstellation; // the constellation plot
    QCPGraph * graph;
    void Initialize();
    void UpdatePlot(float *data, int num_samples);
private:
    Ui::QConstellationPlot *ui;
};

#endif // QCONSTELLATIONPLOT_H
