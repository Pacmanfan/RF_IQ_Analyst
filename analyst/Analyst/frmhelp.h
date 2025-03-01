#ifndef FRMHELP_H
#define FRMHELP_H

#include <QDialog>

namespace Ui {
class frmHelp;
}

class frmHelp : public QDialog
{
    Q_OBJECT

public:
    explicit frmHelp(QWidget *parent = nullptr);
    ~frmHelp();

private slots:
    void on_cmdClose_clicked();

private:
    Ui::frmHelp *ui;
};

#endif // FRMHELP_H
