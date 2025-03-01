#ifndef WGT_TIMEEDITOR_H
#define WGT_TIMEEDITOR_H

#include <QFrame>

namespace Ui {
class wgt_timeeditor;
}

class wgt_timeeditor : public QFrame
{
    Q_OBJECT

public:
    explicit wgt_timeeditor(QWidget *parent = nullptr);
    ~wgt_timeeditor();

private:
    Ui::wgt_timeeditor *ui;
};

#endif // WGT_TIMEEDITOR_H
