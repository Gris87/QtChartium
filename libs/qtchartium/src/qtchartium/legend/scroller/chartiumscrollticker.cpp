#include "src/qtchartium/legend/scroller/chartiumscrollticker.h"



ChartiumScrollTicker::ChartiumScrollTicker(IChartiumScroller* scroller, QObject* parent) :
    IChartiumScrollTicker(parent),
    m_scroller(scroller),
    m_timer()
{
}

ChartiumScrollTicker::~ChartiumScrollTicker()
{
}

void ChartiumScrollTicker::start(int interval)
{
    if (!m_timer.isActive())
    {
        m_timer.start(interval, this);
    }
}

void ChartiumScrollTicker::stop()
{
    m_timer.stop();
}

void ChartiumScrollTicker::timerEvent(QTimerEvent* event)
{
    m_scroller->scrollTick();
}
