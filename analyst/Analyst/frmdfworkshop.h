#ifndef FRMDFWORKSHOP_H
#define FRMDFWORKSHOP_H

#include <QDialog>
#include <wgt_scope.h>
#include <retrodf.h>

namespace Ui {
class frmDFWorkshop;
}

class frmDFWorkshop : public QDialog
{
    Q_OBJECT

public:
    explicit frmDFWorkshop(QWidget *parent = nullptr);
    ~frmDFWorkshop();
    void Init();
    wgt_Scope *m_scope;
    void UpdatePlotData(retro_df_temp_data *dat);
    void UpdateMinMax(float *data, int numsamps, float *minv,float *maxv);
    retro_df_temp_data *m_rawdat;
public slots:
    void onCellChanged(int row,int col);
private slots:
    void on_cmdTest_clicked();

private:
    Ui::frmDFWorkshop *ui;
};

#endif // FRMDFWORKSHOP_H
