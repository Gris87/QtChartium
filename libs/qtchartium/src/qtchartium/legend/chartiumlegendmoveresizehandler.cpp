#include "src/qtchartium/legend/chartiumlegendmoveresizehandler.h"



ChartiumLegendMoveResizeHandler::ChartiumLegendMoveResizeHandler(IChartiumLegend* legend) :
    IChartiumLegendMoveResizeHandler(),
    m_legend(),
    m_moveOffset(),
    m_action(Action::Idle),
    m_mode(MousePosition::Nowhere),
    m_reattachThreshold()
{
}

ChartiumLegendMoveResizeHandler::~ChartiumLegendMoveResizeHandler()
{
}

bool ChartiumLegendMoveResizeHandler::shouldShowMoveHint() const
{
    return m_mode == MousePosition::Top;
}

void ChartiumLegendMoveResizeHandler::reset()
{
}

void ChartiumLegendMoveResizeHandler::handleMousePressEvent(QGraphicsSceneMouseEvent* event)
{
}

void ChartiumLegendMoveResizeHandler::handleMouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
}

void ChartiumLegendMoveResizeHandler::handleMouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
}

void ChartiumLegendMoveResizeHandler::handleHoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
}

void ChartiumLegendMoveResizeHandler::handleHoverMoveEvent(QGraphicsSceneHoverEvent* event)
{
}

void ChartiumLegendMoveResizeHandler::handleHoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
}

void ChartiumLegendMoveResizeHandler::setMouseCursor()
{
}

void ChartiumLegendMoveResizeHandler::setMouseCursor(MousePosition mpos)
{
}

void ChartiumLegendMoveResizeHandler::determineMousePosition(QPointF fromPoint)
{
}
