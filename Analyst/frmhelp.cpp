#include "frmhelp.h"
#include "ui_frmhelp.h"
#include <QTextDocument>

frmHelp::frmHelp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frmHelp)
{
    ui->setupUi(this);
    setWindowTitle("Help");
    QString apppath = QApplication::applicationDirPath();
    QString helpname = apppath + "/docs/Features.html";

    QUrl url(helpname);
    ui->txtHelp->setSource(url);
}

frmHelp::~frmHelp()
{
    delete ui;
}

void frmHelp::on_cmdClose_clicked()
{
    close();
}
