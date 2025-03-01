#ifndef WGTCLASSIFIER_H
#define WGTCLASSIFIER_H

#include <QWidget>
#include <classifier.h>
#include <QProcess>

namespace Ui {
class wgtClassifier;
}

class wgtClassifier : public QWidget
{
    Q_OBJECT

public:
    Classifiers *m_classifiers;
    explicit wgtClassifier(QWidget *parent = 0);
    ~wgtClassifier();
    void UpdateTable();
    void SetClassifiers(Classifiers *cl);
    void SaveChanges();
private slots:
    void on_tblClassifiers_itemSelectionChanged();

    void on_cmdAddClassifier_clicked();

    void on_cmdRemoveClassifier_clicked();

    void on_cmdExportMarkerTrainingData_clicked();

    void on_cmdStartStraining_clicked();

    void onTrainingMessage(QString msg);

private:
    Ui::wgtClassifier *ui;
    void UpdateButtonStates();
signals:
    void StartDataExport(bool all,QString path, double bwHz); // signal to indicate markers to export
    void ClassifiersUpdated();
};

#endif // WGTCLASSIFIER_H
