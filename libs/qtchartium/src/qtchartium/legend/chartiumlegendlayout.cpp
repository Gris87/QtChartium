#include "src/qtchartium/legend/chartiumlegendlayout.h"



ChartiumLegendLayout::ChartiumLegendLayout(IChartiumLegend* legend, QGraphicsLayoutItem* parent) :
    IChartiumLegendLayout(parent)
{
}

ChartiumLegendLayout::~ChartiumLegendLayout()
{
}

void ChartiumLegendLayout::setGeometry(const QRectF& rect)
{
}

void ChartiumLegendLayout::setOffset(qreal x, qreal y)
{
}

QPointF ChartiumLegendLayout::offset() const
{
    return QPointF();
}

void ChartiumLegendLayout::invalidate()
{
}

QSizeF ChartiumLegendLayout::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
{
    return QSizeF();
}

int ChartiumLegendLayout::count() const
{
    return 0;
}

QGraphicsLayoutItem* ChartiumLegendLayout::itemAt(int) const
{
    return nullptr;
}

void ChartiumLegendLayout::removeAt(int)
{
}

void ChartiumLegendLayout::setAttachedGeometry(const QRectF& rect)
{
}

void ChartiumLegendLayout::setDettachedGeometry(const QRectF& rect)
{
}

bool ChartiumLegendLayout::widthLongerThan(const LegendWidthStruct* item1, const LegendWidthStruct* item2)
{
    return false;
}
