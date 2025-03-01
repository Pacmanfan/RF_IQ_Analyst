#ifndef FRMIMPORTOPTIONS_H
#define FRMIMPORTOPTIONS_H

class circ_buff;

#include <QDialog>
#include <string>

#include <QFileInfo>
#include <qvrt_tools.h>

namespace Ui {
class frmImportOptions;
}

/*
    This import options dialog should allow the user to choose the input source - A/B/AB
    What else should it allow for?
    It should show general information about the recording from the QVRT_ExtDataPacket in a tabular list view
    GPS/ tuner settings / firmware and recording info / etc...
*/

using namespace std;

class QVRT_ExtDataPacket;

class frmImportOptions : public QDialog
{
    Q_OBJECT
    
public:
    explicit frmImportOptions(QWidget *parent = 0);
    ~frmImportOptions();
    void Setup(string filename);
    bool GetImportOptions(StreamInfo *ipo,StreamInfo *ipo2);// returns true if combined
    StreamInfo *GetImportOptions();// return currently selected Streaminfo
    string _fileName;
    QList<StreamInfo *> m_lstStreams;

private slots:
    void on_cmbStreamID_currentIndexChanged(int index);

private:
    Ui::frmImportOptions *ui;
    void ShowStreamInfo(StreamInfo *si);
};

#endif // FRMIMPORTOPTIONS_H
