#pragma once



#include "src/qtchartium/legend/scroller/ichartiumscrollticker.h"

#include <QBasicTimer>

#include "src/qtchartium/legend/scroller/ichartiumscroller.h"



class ChartiumScrollTicker : public IChartiumScrollTicker
{
    Q_OBJECT

public:
    explicit ChartiumScrollTicker(IChartiumScroller* scroller, QObject* parent = nullptr);
    ~ChartiumScrollTicker() override;

    ChartiumScrollTicker(const ChartiumScrollTicker& another)            = delete;
    ChartiumScrollTicker& operator=(const ChartiumScrollTicker& another) = delete;

    void start(int interval) override;
    void stop() override;

protected:
    void timerEvent(QTimerEvent* event) override;

    IChartiumScroller* m_scroller;
    QBasicTimer        m_timer;
};
