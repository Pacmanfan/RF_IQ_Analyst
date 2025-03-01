#ifndef DLGSTREAMOPTIONS_H
#define DLGSTREAMOPTIONS_H

#include <QDialog>
#include <qvrt_tools.h>

namespace Ui {
class dlgStreamOptions;
}

class dlgStreamOptions : public QDialog
{
    Q_OBJECT

public:
    explicit dlgStreamOptions(QWidget *parent = nullptr);
    ~dlgStreamOptions();
    StreamInfo &GetStreamInfo(){return m_si;}

private slots:
    void on_cmdOK_clicked();

private:
    Ui::dlgStreamOptions *ui;
    StreamInfo m_si;
};

#endif // DLGSTREAMOPTIONS_H
