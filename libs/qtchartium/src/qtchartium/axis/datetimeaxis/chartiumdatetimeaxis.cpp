#include "src/qtchartium/axis/datetimeaxis/chartiumdatetimeaxis.h"



ChartiumDateTimeAxis::ChartiumDateTimeAxis(QObject* parent) :
    IChartiumDateTimeAxis(parent)
{
}

ChartiumDateTimeAxis::~ChartiumDateTimeAxis()
{
}

IChartiumAxis::AxisType ChartiumDateTimeAxis::type() const
{
    return IChartiumAxis::AxisTypeDateTime;
}

void ChartiumDateTimeAxis::setMin(QDateTime min)
{
}

QDateTime ChartiumDateTimeAxis::min() const
{
    return QDateTime();
}

void ChartiumDateTimeAxis::setMax(QDateTime max)
{
}

QDateTime ChartiumDateTimeAxis::max() const
{
    return QDateTime();
}

void ChartiumDateTimeAxis::setRange(QDateTime min, QDateTime max)
{
}

void ChartiumDateTimeAxis::setFormat(QString format)
{
}

QString ChartiumDateTimeAxis::format() const
{
    return "";
}

void ChartiumDateTimeAxis::setTickCount(int count)
{
}

int ChartiumDateTimeAxis::tickCount() const
{
    return 0;
}
