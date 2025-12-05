#pragma once



#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneMouseEvent>



class IChartiumLegendMoveResizeHandler
{
public:
    enum class Action
    {
        Idle     = 0x00,
        Hovered  = 0x01,
        Pressed  = 0x02,
        Moving   = 0x04,
        Resizing = 0x08
    };

    enum class MousePosition
    {
        Nowhere,
        TopLeft,
        BottomRight,
        BottomLeft,
        TopRight,
        Top,
        Bottom,
        Left,
        Right
    };

    explicit IChartiumLegendMoveResizeHandler() = default;
    virtual ~IChartiumLegendMoveResizeHandler() = default;

    IChartiumLegendMoveResizeHandler(const IChartiumLegendMoveResizeHandler& another)            = delete;
    IChartiumLegendMoveResizeHandler& operator=(const IChartiumLegendMoveResizeHandler& another) = delete;

    virtual bool shouldShowMoveHint() const = 0;
    virtual void reset()                    = 0;

    virtual void handleMousePressEvent(QGraphicsSceneMouseEvent* event)   = 0;
    virtual void handleMouseMoveEvent(QGraphicsSceneMouseEvent* event)    = 0;
    virtual void handleMouseReleaseEvent(QGraphicsSceneMouseEvent* event) = 0;
    virtual void handleHoverEnterEvent(QGraphicsSceneHoverEvent* event)   = 0;
    virtual void handleHoverMoveEvent(QGraphicsSceneHoverEvent* event)    = 0;
    virtual void handleHoverLeaveEvent(QGraphicsSceneHoverEvent* event)   = 0;

    virtual void setMouseCursor()                          = 0;
    virtual void setMouseCursor(MousePosition mpos)        = 0;
    virtual void determineMousePosition(QPointF fromPoint) = 0;
};
