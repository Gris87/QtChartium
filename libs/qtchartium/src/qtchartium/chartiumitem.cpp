#include "src/qtchartium/chartiumitem.h"



ChartiumItem::ChartiumItem(IChartiumSeries* series, QGraphicsItem* item) :
    IChartiumItem(item),
    mValidData(true),
    mSeries(series)
{
}

ChartiumItem::~ChartiumItem()
{
}

IChartiumDomain* ChartiumItem::domain() const
{
    return mSeries->domain();
}

void ChartiumItem::cleanup()
{
    disconnect();
}

IChartiumSeries* ChartiumItem::seriesPrivate() const
{
    return mSeries;
}

void ChartiumItem::handleDomainUpdated()
{
    // Nothing
}
