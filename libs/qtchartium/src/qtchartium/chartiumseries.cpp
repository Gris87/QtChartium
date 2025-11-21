#include "src/qtchartium/chartiumseries.h"



ChartiumSeries::ChartiumSeries(QObject* parent) :
    IChartiumSeries(parent),
    mChart(),
    mItem(),
    mAxes(),
    mDomain(),
    mPresenter(),
    mName(),
    mVisible(),
    mOpacity()
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
}

QString ChartiumSeries::name() const
{
    return "";
}

void ChartiumSeries::setVisible(bool visible)
{
}

bool ChartiumSeries::isVisible() const
{
    return false;
}

qreal ChartiumSeries::opacity() const
{
    return false;
}

void ChartiumSeries::setOpacity(qreal opacity)
{
}

IChartiumChart* ChartiumSeries::chart() const
{
    return nullptr;
}

void ChartiumSeries::setChart(IChartiumChart* chart)
{
}

bool ChartiumSeries::attachAxis(IChartiumAxis* axis)
{
    return false;
}

bool ChartiumSeries::detachAxis(IChartiumAxis* axis)
{
    return false;
}

QList<IChartiumAxis*> ChartiumSeries::attachedAxes()
{
    QList<IChartiumAxis*> res;

    return res;
}

void ChartiumSeries::show()
{
}

void ChartiumSeries::hide()
{
}

void ChartiumSeries::initializeDomain()
{
}

void ChartiumSeries::initializeAxes()
{
}

void ChartiumSeries::initializeGraphics(QGraphicsItem* parent)
{
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
}

IChartiumDomain* ChartiumSeries::domain()
{
    return nullptr;
}

void ChartiumSeries::setPresenter(IChartiumPresenter* presenter)
{
}

IChartiumPresenter* ChartiumSeries::presenter() const
{
    return nullptr;
}
