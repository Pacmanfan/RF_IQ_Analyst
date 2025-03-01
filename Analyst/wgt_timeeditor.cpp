#include "wgt_timeeditor.h"
#include "ui_wgt_timeeditor.h"

wgt_timeeditor::wgt_timeeditor(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::wgt_timeeditor)
{
    ui->setupUi(this);
}

wgt_timeeditor::~wgt_timeeditor()
{
    delete ui;
}
