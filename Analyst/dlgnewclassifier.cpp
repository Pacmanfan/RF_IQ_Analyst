#include "dlgnewclassifier.h"
#include "ui_dlgnewclassifier.h"

dlgNewClassifier::dlgNewClassifier(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgNewClassifier)
{
    ui->setupUi(this);
}

dlgNewClassifier::~dlgNewClassifier()
{
    delete ui;
}

void dlgNewClassifier::on_cmdOK_clicked()
{
    //get the data
    m_class->m_name = ui->leName->text();
    if(m_class->m_name.length() == 0)
        m_class->m_name = "Classifier";
    m_class->m_method = (eClassifierMethod)ui->cmbType->currentIndex();
    switch(ui->cmdBW->currentIndex())
    {
        case 0:
        m_class->m_BWKHz = 32;
        break;
        case 1:
        m_class->m_BWKHz = 64;
        break;
        case 2:
        m_class->m_BWKHz = 128;
        break;
        case 3:
        m_class->m_BWKHz = 256;
        break;
        case 4:
        m_class->m_BWKHz = 512;
        break;
    }
    accept();
}
