#ifndef DLGPROGRESS_H
#define DLGPROGRESS_H

#include <QDialog>

namespace Ui {
class dlgProgress;
}

class dlgProgress : public QDialog
{
    Q_OBJECT

public:
    explicit dlgProgress(QWidget *parent = 0);
    ~dlgProgress();
    void SetMessage(QString msg);

private:
    Ui::dlgProgress *ui;
};

#endif // DLGPROGRESS_H
