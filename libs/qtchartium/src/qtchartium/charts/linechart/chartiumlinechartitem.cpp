#include "src/qtchartium/charts/linechart/chartiumlinechartitem.h"



ChartiumLineChartItem::ChartiumLineChartItem(IChartiumLineSeries* series, QGraphicsItem* item) :
    IChartiumLineChartItem(series, item)
{
}

ChartiumLineChartItem::~ChartiumLineChartItem()
{
}

QPainterPath ChartiumLineChartItem::path() const
{
    return QPainterPath();
}

void ChartiumLineChartItem::suppressPoints()
{
}

void ChartiumLineChartItem::forceChartType(IChartiumChart::ChartType chartType)
{
}

QRectF ChartiumLineChartItem::boundingRect() const
{
    return QRectF();
}

void ChartiumLineChartItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
}

QPainterPath ChartiumLineChartItem::shape() const
{
    return QPainterPath();
}

void ChartiumLineChartItem::updateGeometry()
{
}

void ChartiumLineChartItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
}

void ChartiumLineChartItem::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
}

void ChartiumLineChartItem::hoverMoveEvent(QGraphicsSceneHoverEvent* event)
{
}

void ChartiumLineChartItem::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
}

void ChartiumLineChartItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
}

void ChartiumLineChartItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
}

void ChartiumLineChartItem::handleSeriesUpdated()
{
}
