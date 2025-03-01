#ifndef DLGCONFIG_H
#define DLGCONFIG_H

#include <QDialog>

namespace Ui {
class dlgConfig;
}

class dlgConfig : public QDialog
{
    Q_OBJECT

public:
    explicit dlgConfig(QWidget *parent = 0);
    ~dlgConfig();
    void UpdatePluginsView();

private slots:
    void on_tblPlugins_itemSelectionChanged();

private:
    Ui::dlgConfig *ui;
};

#endif // DLGCONFIG_H
