#include "leveltrigger.h"

#define HLINEWIDTH 2 // horizontal line width

LevelTrigger::LevelTrigger(QCustomPlot *parentplot)
{
    m_parentplot = parentplot;
    m_line = new QCPItemStraightLine(m_parentplot);
    setPowerlevel(true);
    setVisible(true);
    setEnabled(true);
    setColor(Qt::blue);
    m_line->setSelectable(true);

    m_line->point1->setType(QCPItemPosition::ptPlotCoords);
    m_line->point2->setType(QCPItemPosition::ptPlotCoords);
    //we may run into som trouble here, because it's associated with a QCPGraph, not just the plot control
    m_line->point1->setAxes(m_parentplot->graph(0)->keyAxis(), m_parentplot->graph(0)->valueAxis());
    m_line->point2->setAxes(m_parentplot->graph(0)->keyAxis(), m_parentplot->graph(0)->valueAxis());

}



double LevelTrigger::powerlevel() const
{
    return m_powerlevel;
}

void LevelTrigger::setPowerlevel(double powerlevel)
{
    m_powerlevel = powerlevel;
    m_line->point1->setCoords(0, powerlevel);
    m_line->point2->setCoords(1000000, powerlevel);
}

QString LevelTrigger::name() const
{
    return m_name;
}

void LevelTrigger::setName(const QString &name)
{
    m_name = name;
}

bool LevelTrigger::visible() const
{
    return m_visible;
}

void LevelTrigger::setVisible(bool visible)
{
    m_visible = visible;
    m_line->setVisible(visible);;
}

bool LevelTrigger::enabled() const
{
    return m_enabled;
}

void LevelTrigger::setEnabled(bool enabled)
{
    m_enabled = enabled;
}

QColor LevelTrigger::color() const
{
    return m_color;
}

void LevelTrigger::setColor(const QColor &color)
{
    m_color = color;
    m_line->setPen(QPen(color,HLINEWIDTH));
}

LevelTriggerType LevelTrigger::triggertype() const
{
    return m_triggertype;
}

void LevelTrigger::setTriggertype(const LevelTriggerType &triggertype)
{
    m_triggertype = triggertype;
}

