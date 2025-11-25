#include "src/qtchartium/chartiumdataset.h"

#include "src/qtchartium/axis/barcategoryaxis/chartiumbarcategoryaxis.h"
#include "src/qtchartium/axis/datetimeaxis/chartiumdatetimeaxis.h"
#include "src/qtchartium/axis/valueaxis/chartiumvalueaxis.h"
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
    return mSeriesList;
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

        return;
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
    return mAxisList;
}

bool ChartiumDataSet::attachAxis(IChartiumSeries* series, IChartiumAxis* axis)
{
    Q_ASSERT(axis);

    if (!series)
    {
        return false;
    }

    QList<IChartiumSeries*> attachedSeriesList = axis->getSeries();
    QList<IChartiumAxis*>   attachedAxisList   = series->attachedAxes();

    if (!mSeriesList.contains(series))
    {
        return false;
    }

    if (!mAxisList.contains(axis))
    {
        return false;
    }

    if (attachedAxisList.contains(axis))
    {
        return false;
    }

    if (attachedSeriesList.contains(series))
    {
        return false;
    }

    IChartiumDomain*            domain = series->domain();
    IChartiumDomain::DomainType type   = selectDomain(attachedAxisList << axis);

    if (type == IChartiumDomain::UndefinedDomain)
    {
        return false;
    }

    if (domain->type() != type)
    {
        IChartiumDomain* old = domain;
        domain               = createDomain(type);

        domain->setRange(old->minX(), old->maxX(), old->minY(), old->maxY());
        // Initialize domain size to old domain size, as it won't get updated
        // unless geometry changes.
        domain->setSize(old->size());
    }

    if (!domain)
    {
        return false;
    }

    if (!domain->attachAxis(axis))
    {
        return false;
    }

    domain->blockRangeSignals(true);
    QList<IChartiumDomain*> blockedDomains{domain};

    if (domain != series->domain())
    {
        foreach(IChartiumAxis* axis, series->attachedAxes())
        {
            series->domain()->detachAxis(axis);
            domain->attachAxis(axis);

            foreach(IChartiumSeries* otherSeries, axis->getSeries())
            {
                if (otherSeries != series && otherSeries->domain())
                {
                    if (!otherSeries->domain()->rangeSignalsBlocked())
                    {
                        otherSeries->domain()->blockRangeSignals(true);
                        blockedDomains << otherSeries->domain();
                    }
                }
            }
        }
        series->setDomain(domain);
        series->initializeDomain();

        // Reinitialize domain based on old axes, as the series domain initialization above
        // has trashed the old ranges, if there were any.
        for (IChartiumAxis* oldAxis : series->attachedAxes())
        {
            oldAxis->initializeDomain(domain);
        }
    }

    series->appendAxis(axis);
    axis->appendSeries(series);

    series->initializeAxes();
    axis->initializeDomain(domain);

    foreach(IChartiumDomain* blockedDomain, blockedDomains)
    {
        blockedDomain->blockRangeSignals(false);
    }

    return true;
}

bool ChartiumDataSet::detachAxis(IChartiumSeries* series, IChartiumAxis* axis)
{
    Q_ASSERT(series);
    Q_ASSERT(axis);

    QList<IChartiumAxis*> attachedAxisList = series->attachedAxes();
    IChartiumDomain*      domain           = series->domain();

    if (!mSeriesList.contains(series))
    {
        return false;
    }

    if (axis && !mAxisList.contains(axis))
    {
        return false;
    }

    if (!attachedAxisList.contains(axis))
    {
        return false;
    }

    Q_ASSERT(axis->getSeries().contains(series));

    domain->detachAxis(axis);
    series->removeAxis(axis);
    axis->removeSeries(series);

    return true;
}

void ChartiumDataSet::createDefaultAxes()
{
    if (mSeriesList.isEmpty())
    {
        return;
    }

    IChartiumAxis::AxisTypes typeX;
    IChartiumAxis::AxisTypes typeY;

    // Remove possibly existing axes
    deleteAllAxes();

    Q_ASSERT(mAxisList.isEmpty());

    // Select the required axis x and axis y types based on the types of the current series
    foreach(IChartiumSeries* s, mSeriesList)
    {
        typeX |= s->defaultAxisType(Qt::Horizontal);
        typeY |= s->defaultAxisType(Qt::Vertical);
    }

    createAxes(typeX, Qt::Horizontal);
    createAxes(typeY, Qt::Vertical);
}

void ChartiumDataSet::zoomInDomain(const QRectF& rect)
{
    QList<IChartiumDomain*> domains;

    for (IChartiumSeries* s : mSeriesList)
    {
        IChartiumDomain* domain = s->domain();
        domain->blockRangeSignals(true);
        domains.append(domain);
    }

    for (IChartiumDomain* domain : domains)
    {
        domain->zoomIn(rect);
    }

    for (IChartiumDomain* domain : domains)
    {
        domain->blockRangeSignals(false);
    }
}

void ChartiumDataSet::zoomOutDomain(const QRectF& rect)
{
    QList<IChartiumDomain*> domains;

    for (IChartiumSeries* s : mSeriesList)
    {
        IChartiumDomain* domain = s->domain();
        domain->blockRangeSignals(true);
        domains.append(domain);
    }

    for (IChartiumDomain* domain : domains)
    {
        domain->zoomOut(rect);
    }

    for (IChartiumDomain* domain : domains)
    {
        domain->blockRangeSignals(false);
    }
}

void ChartiumDataSet::zoomResetDomain()
{
    QList<IChartiumDomain*> domains;

    for (IChartiumSeries* s : mSeriesList)
    {
        IChartiumDomain* domain = s->domain();
        domain->blockRangeSignals(true);
        domains.append(domain);
    }

    for (IChartiumDomain* domain : domains)
    {
        domain->zoomReset();
    }

    for (IChartiumDomain* domain : domains)
    {
        domain->blockRangeSignals(false);
    }
}

bool ChartiumDataSet::isZoomedDomain()
{
    for (IChartiumSeries* s : mSeriesList)
    {
        if (s->domain()->isZoomed())
        {
            return true;
        }
    }

    return false;
}

void ChartiumDataSet::scrollDomain(qreal dx, qreal dy)
{
    QList<IChartiumDomain*> domains;

    for (IChartiumSeries* s : mSeriesList)
    {
        IChartiumDomain* domain = s->domain();
        domain->blockRangeSignals(true);
        domains.append(domain);
    }

    for (IChartiumDomain* domain : domains)
    {
        domain->move(dx, dy);
    }

    for (IChartiumDomain* domain : domains)
    {
        domain->blockRangeSignals(false);
    }
}

QPointF ChartiumDataSet::mapToValue(const QPointF& position, IChartiumSeries* series)
{
    QPointF point;

    if (series == nullptr && !mSeriesList.isEmpty())
    {
        series = mSeriesList.first();
    }

    if (series != nullptr && series->type() == IChartiumSeries::SeriesTypePie)
    {
        return point;
    }

    if (series && mSeriesList.contains(series))
    {
        point = series->domain()->calculateDomainPoint(position - mChart->plotArea().topLeft());
    }

    return point;
}

QPointF ChartiumDataSet::mapToPosition(const QPointF& value, IChartiumSeries* series)
{
    QPointF point = mChart->plotArea().topLeft();

    if (series == nullptr && !mSeriesList.isEmpty())
    {
        series = mSeriesList.first();
    }

    if (series != nullptr && series->type() == IChartiumSeries::SeriesTypePie)
    {
        return QPoint(0, 0);
    }

    bool ok;

    if (series && mSeriesList.contains(series))
    {
        point += series->domain()->calculateGeometryPoint(value, ok);
    }

    return point;
}

IChartiumDomain* ChartiumDataSet::createDomain(IChartiumDomain::DomainType type)
{
    switch (type)
    {
        case IChartiumDomain::XYDomain:
            return new ChartiumXYDomain();
        default:
            qFatal() << "Other domains is unsupported";

            return nullptr;
    }
}

IChartiumDomain* ChartiumDataSet::domainForSeries(IChartiumSeries* series) const
{
    return series->domain();
}

void ChartiumDataSet::createAxes(IChartiumAxis::AxisTypes type, Qt::Orientation orientation)
{
    IChartiumAxis* axis = 0;

    switch (type)
    {
        case IChartiumAxis::AxisTypeValue:
            axis = new ChartiumValueAxis(this);
            break;
        case IChartiumAxis::AxisTypeBarCategory:
            axis = new ChartiumBarCategoryAxis(this);
            break;
        case IChartiumAxis::AxisTypeDateTime:
            axis = new ChartiumDateTimeAxis(this);
            break;
        default:
            axis = nullptr;
            break;
    }

    if (axis != nullptr)
    {
        addAxis(axis, orientation == Qt::Horizontal ? Qt::AlignBottom : Qt::AlignLeft);

        qreal min = 0;
        qreal max = 0;
        findMinMaxForSeries(mSeriesList, orientation, min, max);

        foreach(IChartiumSeries* s, mSeriesList)
        {
            attachAxis(s, axis);
        }

        axis->setRange(min, max);
    }
    else
    {
        // Create separate axis for each series
        foreach(IChartiumSeries* s, mSeriesList)
        {
            IChartiumAxis* axis = s->createDefaultAxis(orientation);

            if (axis)
            {
                addAxis(axis, orientation == Qt::Horizontal ? Qt::AlignBottom : Qt::AlignLeft);
                attachAxis(s, axis);
            }
        }
    }
}

IChartiumDomain::DomainType ChartiumDataSet::selectDomain(const QList<IChartiumAxis*>& axes)
{
    enum Type
    {
        Undefined = 0,
        LogType   = 0x1,
        ValueType = 0x2
    };

    int horizontal(Undefined);
    int vertical(Undefined);

    IChartiumChart::ChartType chartType(IChartiumChart::ChartTypeCartesian);

    if (mChart != nullptr)
    {
        chartType = mChart->chartType();
    }

    for (IChartiumAxis* axis : axes)
    {
        switch (axis->type())
        {
            case IChartiumAxis::AxisTypeLogValue:
                if (axis->orientation() == Qt::Horizontal)
                {
                    horizontal |= LogType;
                }
                if (axis->orientation() == Qt::Vertical)
                {
                    vertical |= LogType;
                }
                break;
            case IChartiumAxis::AxisTypeValue:
            case IChartiumAxis::AxisTypeBarCategory:
            case IChartiumAxis::AxisTypeCategory:
            case IChartiumAxis::AxisTypeColor:
            case IChartiumAxis::AxisTypeDateTime:
                if (axis->orientation() == Qt::Horizontal)
                {
                    horizontal |= ValueType;
                }
                if (axis->orientation() == Qt::Vertical)
                {
                    vertical |= ValueType;
                }
                break;
            default:
                qWarning() << "Undefined type";
                break;
        }
    }

    if (vertical == Undefined)
    {
        vertical = ValueType;
    }

    if (horizontal == Undefined)
    {
        horizontal = ValueType;
    }

    if (vertical == ValueType && horizontal == ValueType)
    {
        if (chartType == IChartiumChart::ChartTypeCartesian)
        {
            return IChartiumDomain::XYDomain;
        }
        else if (chartType == IChartiumChart::ChartTypePolar)
        {
            return IChartiumDomain::XYPolarDomain;
        }
    }

    if (vertical == LogType && horizontal == ValueType)
    {
        if (chartType == IChartiumChart::ChartTypeCartesian)
        {
            return IChartiumDomain::XLogYDomain;
        }
        if (chartType == IChartiumChart::ChartTypePolar)
        {
            return IChartiumDomain::XLogYPolarDomain;
        }
    }

    if (vertical == ValueType && horizontal == LogType)
    {
        if (chartType == IChartiumChart::ChartTypeCartesian)
        {
            return IChartiumDomain::LogXYDomain;
        }
        else if (chartType == IChartiumChart::ChartTypePolar)
        {
            return IChartiumDomain::LogXYPolarDomain;
        }
    }

    if (vertical == LogType && horizontal == LogType)
    {
        if (chartType == IChartiumChart::ChartTypeCartesian)
        {
            return IChartiumDomain::LogXLogYDomain;
        }
        else if (chartType == IChartiumChart::ChartTypePolar)
        {
            return IChartiumDomain::LogXLogYPolarDomain;
        }
    }

    return IChartiumDomain::UndefinedDomain;
}

void ChartiumDataSet::deleteAllAxes()
{
    for (IChartiumAxis* a : mAxisList)
    {
        removeAxis(a);
        delete a;
    }

    Q_ASSERT(mAxisList.size() == 0);
}

void ChartiumDataSet::deleteAllSeries()
{
    for (IChartiumSeries* s : mSeriesList)
    {
        removeSeries(s);
        delete s;
    }

    Q_ASSERT(mSeriesList.size() == 0);
}

void
ChartiumDataSet::findMinMaxForSeries(const QList<IChartiumSeries*>& series, Qt::Orientations orientation, qreal& min, qreal& max)
{
    Q_ASSERT(!series.isEmpty());

    IChartiumDomain* domain = series.first()->domain();
    min                     = (orientation == Qt::Vertical) ? domain->minY() : domain->minX();
    max                     = (orientation == Qt::Vertical) ? domain->maxY() : domain->maxX();

    for (int i = 1; i < series.size(); i++)
    {
        IChartiumDomain* domain = series.at(i)->domain();
        min                     = qMin((orientation == Qt::Vertical) ? domain->minY() : domain->minX(), min);
        max                     = qMax((orientation == Qt::Vertical) ? domain->maxY() : domain->maxX(), max);
    }

    if (min == max)
    {
        min -= 0.5;
        max += 0.5;
    }
}
