#pragma once



#include "src/qtchartium/legend/ichartiumlegendmoveresizehandler.h"



class IChartiumLegend;



class ChartiumLegendMoveResizeHandler : public IChartiumLegendMoveResizeHandler
{
public:
    explicit ChartiumLegendMoveResizeHandler(IChartiumLegend* legend);
    ~ChartiumLegendMoveResizeHandler() override;

    ChartiumLegendMoveResizeHandler(const ChartiumLegendMoveResizeHandler& another)            = delete;
    ChartiumLegendMoveResizeHandler& operator=(const ChartiumLegendMoveResizeHandler& another) = delete;

    bool shouldShowMoveHint() const override;
    void reset() override;

    void handleMousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void handleMouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void handleMouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void handleHoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    void handleHoverMoveEvent(QGraphicsSceneHoverEvent* event) override;
    void handleHoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;

    void setMouseCursor() override;
    void setMouseCursor(MousePosition mpos) override;
    void determineMousePosition(QPointF fromPoint) override;

protected:
    IChartiumLegend* m_legend;
    QPointF          m_moveOffset;
    Action           m_action;
    MousePosition    m_mode;
    qreal            m_reattachThreshold;
};
