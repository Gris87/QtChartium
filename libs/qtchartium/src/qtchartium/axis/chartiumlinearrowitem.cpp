#include "src/qtchartium/axis/chartiumlinearrowitem.h"
#include "src/qtchartium/axis/ichartiumaxiselement.h"



ChartiumLineArrowItem::ChartiumLineArrowItem(IChartiumAxisElement* axis, QGraphicsItem* parent) :
    IChartiumLineArrowItem(parent),
    mAxis(axis),
    mAxisOrientation(axis->axis()->orientation())
{
}

ChartiumLineArrowItem::~ChartiumLineArrowItem()
{
}

void ChartiumLineArrowItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    mAxis->axisSelected();

    IChartiumLineArrowItem::mousePressEvent(event);
}

QRectF ChartiumLineArrowItem::boundingRect() const
{
    return shape().boundingRect();
}

QPainterPath ChartiumLineArrowItem::shape() const
{
    QPainterPath path = QGraphicsLineItem::shape();
    QRectF       rect = path.boundingRect();

    path.addRect(rect.adjusted(0, 0, mAxisOrientation != Qt::Horizontal ? 8 : 0, mAxisOrientation != Qt::Vertical ? 8 : 0));

    return path;
}
