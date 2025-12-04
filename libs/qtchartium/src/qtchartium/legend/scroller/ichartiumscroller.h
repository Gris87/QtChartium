#pragma once



#include <QGraphicsSceneMouseEvent>



class IChartiumScroller
{
public:
    enum State
    {
        Idle,
        Pressed,
        Move,
        Scroll
    };

    explicit IChartiumScroller() = default;
    virtual ~IChartiumScroller() = default;

    IChartiumScroller(const IChartiumScroller& another)            = delete;
    IChartiumScroller& operator=(const IChartiumScroller& another) = delete;

    virtual void    setOffset(const QPointF& point) = 0;
    virtual QPointF offset() const                  = 0;

    virtual void move(const QPointF& delta)     = 0;
    virtual void scrollTo(const QPointF& delta) = 0;

    virtual void handleMousePressEvent(QGraphicsSceneMouseEvent* event)   = 0;
    virtual void handleMouseMoveEvent(QGraphicsSceneMouseEvent* event)    = 0;
    virtual void handleMouseReleaseEvent(QGraphicsSceneMouseEvent* event) = 0;

    virtual void scrollTick() = 0;

    virtual void startTicker(int interval) = 0;
    virtual void stopTicker()              = 0;

    virtual void calculateSpeed(const QPointF& position)          = 0;
    virtual void lowerSpeed(QPointF& speed, qreal maxSpeed = 100) = 0;
};
