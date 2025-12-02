#include "src/qtchartium/charts/linechart/chartiumlineseries.h"



ChartiumLineSeries::ChartiumLineSeries(QObject* parent) :
    IChartiumLineSeries(parent)
{
}

ChartiumLineSeries::~ChartiumLineSeries()
{
}

void ChartiumLineSeries::append(qreal x, qreal y)
{
}

void ChartiumLineSeries::append(const QPointF& point)
{
}

void ChartiumLineSeries::append(const QList<QPointF>& points)
{
}

ChartiumLineSeries& ChartiumLineSeries::operator<<(const QPointF& point)
{
    return *this;
}

ChartiumLineSeries& ChartiumLineSeries::operator<<(const QList<QPointF>& points)
{
    return *this;
}
