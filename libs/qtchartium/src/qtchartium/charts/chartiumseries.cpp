#include "src/qtchartium/charts/chartiumseries.h"

#include "src/qtchartium/domain/chartiumxydomain.h"
#include "src/qtchartium/ichartiumdataset.h"



ChartiumSeries::ChartiumSeries(QObject* parent) :
    IChartiumSeries(parent),
    mChart(),
    mItem(),
    mAxes(),
    mDomain(new ChartiumXYDomain()),
    mPresenter(),
    mName(),
    mVisible(true),
    mOpacity(1.00)
{
}

ChartiumSeries::~ChartiumSeries()
{
}

IChartiumSeries::SeriesType ChartiumSeries::type() const
{
    return IChartiumSeries::SeriesTypeLine;
}

void ChartiumSeries::setName(const QString& name)
{
    if (name != mName)
    {
        mName = name;

        emit nameChanged();
    }
}

QString ChartiumSeries::name() const
{
    return mName;
}

void ChartiumSeries::setVisible(bool visible)
{
    if (visible != mVisible)
    {
        mVisible = visible;

        emit visibleChanged();
    }
}

bool ChartiumSeries::isVisible() const
{
    return mVisible;
}

qreal ChartiumSeries::opacity() const
{
    return mOpacity;
}

void ChartiumSeries::setOpacity(qreal opacity)
{
    if (opacity != mOpacity)
    {
        mOpacity = opacity;

        emit opacityChanged();
    }
}

IChartiumChart* ChartiumSeries::chart() const
{
    return mChart;
}

void ChartiumSeries::setChart(IChartiumChart* chart)
{
    mChart = chart;
}

bool ChartiumSeries::attachAxis(IChartiumAxis* axis)
{
    if (mChart != nullptr)
    {
        return mChart->dataset()->attachAxis(this, axis);
    }

    return false;
}

bool ChartiumSeries::detachAxis(IChartiumAxis* axis)
{
    if (mChart != nullptr)
    {
        return mChart->dataset()->detachAxis(this, axis);
    }

    return false;
}

QList<IChartiumAxis*> ChartiumSeries::attachedAxes()
{
    return mAxes;
}

void ChartiumSeries::show()
{
    setVisible(true);
}

void ChartiumSeries::hide()
{
    setVisible(false);
}

void ChartiumSeries::initializeDomain()
{
}

void ChartiumSeries::initializeAxes()
{
}

void ChartiumSeries::initializeTheme(int index, IChartiumTheme* theme)
{
}

void ChartiumSeries::initializeGraphics(QGraphicsItem* parent)
{
    QObject::connect(mDomain, SIGNAL(updated()), mItem, SLOT(handleDomainUpdated()));
}

QList<IChartiumLegendMarker*> ChartiumSeries::createLegendMarkers(IChartiumLegend* legend)
{
    QList<IChartiumLegendMarker*> res;

    return res;
}

IChartiumAxis::AxisType ChartiumSeries::defaultAxisType(Qt::Orientation) const
{
    return IChartiumAxis::AxisTypeValue;
}

IChartiumAxis* ChartiumSeries::createDefaultAxis(Qt::Orientation) const
{
    return nullptr;
}

IChartiumItem* ChartiumSeries::chartItem()
{
    return nullptr;
}

void ChartiumSeries::setDomain(IChartiumDomain* domain)
{
    Q_ASSERT(domain);

    if (mDomain != domain)
    {
        if (mItem != nullptr)
        {
            QObject::disconnect(mDomain, SIGNAL(updated()), mItem, SLOT(handleDomainUpdated()));
        }

        mDomain = domain;

        if (mItem != nullptr)
        {
            QObject::connect(mDomain, SIGNAL(updated()), mItem, SLOT(handleDomainUpdated()));
            mItem->handleDomainUpdated();
        }
    }
}

IChartiumDomain* ChartiumSeries::domain()
{
    return mDomain;
}

void ChartiumSeries::setPresenter(IChartiumPresenter* presenter)
{
    mPresenter = presenter;
}

IChartiumPresenter* ChartiumSeries::presenter() const
{
    return mPresenter;
}

void ChartiumSeries::appendAxis(IChartiumAxis* axis)
{
    mAxes.append(axis);
}

void ChartiumSeries::removeAxis(IChartiumAxis* axis)
{
    mAxes.removeAll(axis);
}
