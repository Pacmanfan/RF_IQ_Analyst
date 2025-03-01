#include "dlgprogress.h"
#include "ui_dlgprogress.h"

dlgProgress::dlgProgress(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgProgress)
{
    ui->setupUi(this);
}

dlgProgress::~dlgProgress()
{
    delete ui;
}

void dlgProgress::SetMessage(QString msg)
{
    ui->label->setText(msg);
}
