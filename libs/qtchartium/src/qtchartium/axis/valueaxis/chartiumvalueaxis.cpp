#include "src/qtchartium/axis/valueaxis/chartiumvalueaxis.h"



ChartiumValueAxis::ChartiumValueAxis(QObject* parent) :
    IChartiumValueAxis(parent)
{
}

ChartiumValueAxis::~ChartiumValueAxis()
{
}

void ChartiumValueAxis::setTickAnchor(qreal anchor)
{
}

qreal ChartiumValueAxis::tickAnchor() const
{
    return 0;
}

void ChartiumValueAxis::setTickInterval(qreal insterval)
{
}

qreal ChartiumValueAxis::tickInterval() const
{
    return 0;
}
