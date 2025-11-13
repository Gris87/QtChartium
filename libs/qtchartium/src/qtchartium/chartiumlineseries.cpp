#include "src/qtchartium/chartiumlineseries.h"



ChartiumLineSeries::ChartiumLineSeries() :
    IChartiumLineSeries()
{
}

ChartiumLineSeries::~ChartiumLineSeries()
{
}

void ChartiumLineSeries::append(qreal x, qreal y)
{
    append(QPointF(x, y));
}

void ChartiumLineSeries::append(const QPointF& /*point*/)
{
}

void ChartiumLineSeries::append(const QList<QPointF>& points)
{
    for (const QPointF& point : points)
    {
        append(point);
    }
}

ChartiumLineSeries& ChartiumLineSeries::operator<<(const QPointF& point)
{
    append(point);

    return *this;
}

ChartiumLineSeries& ChartiumLineSeries::operator<<(const QList<QPointF>& points)
{
    append(points);

    return *this;
}
