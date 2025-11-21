#include "src/qtchartium/chartiumdataset.h"

#include "src/qtchartium/domain/chartiumxydomain.h"



ChartiumDataSet::ChartiumDataSet(IChartiumChart* chart) :
    IChartiumDataSet(chart),
    mChart(chart),
    mSeriesList(),
    mAxisList()
{
}

ChartiumDataSet::~ChartiumDataSet()
{
    deleteAllSeries();
    deleteAllAxes();
}

void ChartiumDataSet::addSeries(IChartiumSeries* series)
{
    if (mSeriesList.contains(series))
    {
        return;
    }

    if (mChart != nullptr && mChart->chartType() == IChartiumChart::ChartTypePolar)
    {
        qFatal() << "Polar chart is unsupported";
    }
    else
    {
        series->setDomain(new ChartiumXYDomain());
    }

    series->initializeDomain();
    mSeriesList.append(series);

    series->setParent(this);
    series->setChart(mChart);

    emit seriesAdded(series);
}

void ChartiumDataSet::removeSeries(IChartiumSeries* series)
{
    if (!mSeriesList.contains(series))
    {
        return;
    }

    QList<IChartiumAxis*> axes = series->attachedAxes();

    for (IChartiumAxis* axis : axes)
    {
        detachAxis(series, axis);
    }

    mSeriesList.removeAll(series);
    emit seriesRemoved(series);

    // Reset domain to default
    series->setDomain(new ChartiumXYDomain());
    series->setParent(nullptr);
    series->setChart(nullptr);
}

QList<IChartiumSeries*> ChartiumDataSet::series() const
{
    QList<IChartiumSeries*> res;

    return res;
}

void ChartiumDataSet::addAxis(IChartiumAxis* axis, Qt::Alignment alignment)
{
    if (mAxisList.contains(axis))
    {
        return;
    }

    axis->setAlignment(alignment);

    if (!axis->alignment())
    {
        return;
    };

    IChartiumDomain* newDomain;

    if (mChart != nullptr && mChart->chartType() == IChartiumChart::ChartTypePolar)
    {
        qFatal() << "Polar chart is unsupported";
    }
    else
    {
        newDomain = new ChartiumXYDomain();
    }

    axis->initializeDomain(newDomain);

    axis->setParent(this);
    axis->setChart(mChart);
    mAxisList.append(axis);

    emit axisAdded(axis);
}

void ChartiumDataSet::removeAxis(IChartiumAxis* axis)
{
    if (!mAxisList.contains(axis))
    {
        return;
    }

    QList<IChartiumSeries*> series = axis->getSeries();

    for (IChartiumSeries* s : series)
    {
        detachAxis(s, axis);
    }

    emit axisRemoved(axis);
    mAxisList.removeAll(axis);

    axis->setParent(nullptr);
    axis->setChart(nullptr);
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
