#include "src/qtchartium/chartiumdataset.h"



ChartiumDataSet::ChartiumDataSet(IChartiumChart* chart) :
    IChartiumDataSet(chart),
    mSeriesList(),
    mAxisList(),
    mChart(chart)
{
}

ChartiumDataSet::~ChartiumDataSet()
{
}

void ChartiumDataSet::addSeries(IChartiumSeries* series)
{
}

void ChartiumDataSet::removeSeries(IChartiumSeries* series)
{
}

QList<IChartiumSeries*> ChartiumDataSet::series() const
{
    QList<IChartiumSeries*> res;

    return res;
}

void ChartiumDataSet::addAxis(IChartiumAxis* axis, Qt::Alignment alignment)
{
}

void ChartiumDataSet::removeAxis(IChartiumAxis* axis)
{
}

QList<IChartiumAxis*> ChartiumDataSet::axes() const
{
    QList<IChartiumAxis*> res;

    return res;
}

bool ChartiumDataSet::attachAxis(IChartiumSeries* series, IChartiumAxis* axis)
{
    return false;
}

bool ChartiumDataSet::detachAxis(IChartiumSeries* series, IChartiumAxis* axis)
{
    return false;
}

void ChartiumDataSet::createDefaultAxes()
{
}

void ChartiumDataSet::zoomInDomain(const QRectF& rect)
{
}

void ChartiumDataSet::zoomOutDomain(const QRectF& rect)
{
}

void ChartiumDataSet::zoomResetDomain()
{
}

bool ChartiumDataSet::isZoomedDomain()
{
    return false;
}

void ChartiumDataSet::scrollDomain(qreal dx, qreal dy)
{
}

QPointF ChartiumDataSet::mapToValue(const QPointF& position, IChartiumSeries* series)
{
    return QPointF();
}

QPointF ChartiumDataSet::mapToPosition(const QPointF& value, IChartiumSeries* series)
{
    return QPointF();
}

IChartiumDomain* ChartiumDataSet::createDomain(IChartiumDomain::DomainType type)
{
    return nullptr;
}

IChartiumDomain* ChartiumDataSet::domainForSeries(IChartiumSeries* series) const
{
    return nullptr;
}

void ChartiumDataSet::handleReverseChanged()
{
}

void ChartiumDataSet::createAxes(IChartiumAxis::AxisTypes type, Qt::Orientation orientation)
{
}

IChartiumAxis* ChartiumDataSet::createAxis(IChartiumAxis::AxisType type, Qt::Orientation orientation)
{
    return nullptr;
}

IChartiumDomain::DomainType ChartiumDataSet::selectDomain(const QList<IChartiumAxis*>& axes)
{
    return IChartiumDomain::XYDomain;
}

void ChartiumDataSet::deleteAllAxes()
{
}

void ChartiumDataSet::deleteAllSeries()
{
}

void
ChartiumDataSet::findMinMaxForSeries(const QList<IChartiumSeries*>& series, Qt::Orientations orientation, qreal& min, qreal& max)
{
}
