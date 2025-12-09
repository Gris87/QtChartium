#include "src/qtchartium/legend/chartiumlegendscroller.h"



ChartiumLegendScroller::ChartiumLegendScroller(IChartiumChart* chart, QGraphicsItem* parent, Qt::WindowFlags wFlags) :
    IChartiumLegendScroller(chart, parent, wFlags),
    m_forwardMouseEvents(),
    m_forwardHoverEvents(),
    m_cachedShouldShowMoveEvents()
{
}

ChartiumLegendScroller::~ChartiumLegendScroller()
{
}

void ChartiumLegendScroller::handleInteractiveChanged(bool interactive)
{
}

void ChartiumLegendScroller::updateForResizerChange()
{
}

void ChartiumLegendScroller::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
}

void ChartiumLegendScroller::setOffset(const QPointF& point)
{
}

QPointF ChartiumLegendScroller::offset() const
{
    return QPointF();
}

void ChartiumLegendScroller::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
}

void ChartiumLegendScroller::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
}

void ChartiumLegendScroller::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
}

void ChartiumLegendScroller::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
}

void ChartiumLegendScroller::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
}

void ChartiumLegendScroller::hoverMoveEvent(QGraphicsSceneHoverEvent* event)
{
}

void ChartiumLegendScroller::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
}

void ChartiumLegendScroller::handleDetached(bool attached)
{
}
