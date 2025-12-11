#pragma once



#include "src/qtchartium/legend/scroller/ichartiumscroller.h"

#include <QElapsedTimer>

#include "src/qtchartium/legend/scroller/ichartiumscrollticker.h"



class ChartiumScroller : public IChartiumScroller
{
public:
    explicit ChartiumScroller();
    ~ChartiumScroller() override;

    ChartiumScroller(const ChartiumScroller& another)            = delete;
    ChartiumScroller& operator=(const ChartiumScroller& another) = delete;

    void    setOffset(const QPointF& point) override;
    QPointF offset() const override;

    void move(const QPointF& delta) override;
    void scrollTo(const QPointF& delta) override;

    void handleMousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void handleMouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void handleMouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

    void scrollTick() override;

    void startTicker(int interval) override;
    void stopTicker() override;

    void calculateSpeed(const QPointF& position) override;
    void lowerSpeed(QPointF& speed, qreal maxSpeed = 100) override;

protected:
    IChartiumScrollTicker* m_ticker;
    QElapsedTimer          m_timeStamp;
    QPointF                m_speed;
    QPointF                m_fraction;
    int                    m_timeTresholdMin;
    int                    m_timeTresholdMax;
    State                  m_state;
    QPointF                m_pressPos;
    QPointF                m_lastPos;
    qreal                  m_treshold;
};
