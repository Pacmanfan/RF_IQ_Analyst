#ifndef LEVELTRIGGER_H
#define LEVELTRIGGER_H
#include "ftmarker.h"
#include <qcustomplot.h>
#include <wgt_util.h>

/*
This is a power level trigger used in the scope class.
We'll set up 1 or move triggers, and when the associated graph data exceeds the specified
level, we can make something happen
This is the GUI representation that will live on the vertical scope graph as a horizontal line.
*/

enum LevelTriggerType
{
    eRisingEdge,
    eFallingEdge,
    eRisingFalling // trigger on both
};

class LevelTrigger
{
public:
    LevelTrigger(QCustomPlot *parentplot);
    double powerlevel() const;
    void setPowerlevel(double powerlevel);

    QString name() const;
    void setName(const QString &name);

    bool visible() const;
    void setVisible(bool visible);

    bool enabled() const;
    void setEnabled(bool enabled);

    QColor color() const;
    void setColor(const QColor &color);

    LevelTriggerType triggertype() const;
    void setTriggertype(const LevelTriggerType &triggertype);

private:
    double m_powerlevel; // scaler power level
   // movingline m_ml_state; // moving line state
    QColor m_color;
    QString m_name;
    bool m_visible; // is this trigger visible on the screen
    bool m_enabled; // is this trigger enabled?
    LevelTriggerType m_triggertype;
    QCPItemStraightLine *m_line; // the horizontal line
    QCustomPlot *m_parentplot; // the plot that this belongs to
};

// the list of level triggers
class LevelTriggers
{
public:
    QVector<LevelTrigger *> m_triggers;
    void Add(QString triggername);
    void Remove(QString triggername);

};

#endif // LEVELTRIGGER_H
