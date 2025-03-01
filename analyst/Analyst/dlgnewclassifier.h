#ifndef DLGNEWCLASSIFIER_H
#define DLGNEWCLASSIFIER_H

#include <QDialog>
#include <classifier.h>

namespace Ui {
class dlgNewClassifier;
}

class dlgNewClassifier : public QDialog
{
    Q_OBJECT

public:
    explicit dlgNewClassifier(QWidget *parent = 0);
    ~dlgNewClassifier();
    Classifier *m_class;
    void SetClassifier(Classifier *cls)
    {
        m_class = cls;
    }

private slots:
    void on_cmdOK_clicked();

private:
    Ui::dlgNewClassifier *ui;
};

#endif // DLGNEWCLASSIFIER_H
