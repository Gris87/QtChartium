#include "src/qtchartium/chartiumchart.h"



ChartiumChart::ChartiumChart(QGraphicsItem* parent, Qt::WindowFlags wFlags) :
    IChartiumChart(parent, wFlags),
    mLegend(new ChartiumLegend()),
    mSeries()
{
}

ChartiumChart::~ChartiumChart()
{
    delete mLegend;

    for (IChartiumSeries* s : mSeries)
    {
        delete s;
    }
}

void ChartiumChart::addSeries(IChartiumSeries* series)
{
    if (mSeries.contains(series))
    {
        return;
    }

    mSeries.append(series);
}

void ChartiumChart::removeSeries(IChartiumSeries* series)
{
    if (!mSeries.contains(series))
    {
        return;
    }

    mSeries.removeAll(series);
}

void ChartiumChart::removeAllSeries()
{
    const QList<IChartiumSeries*> series = mSeries;

    for (IChartiumSeries* s : series)
    {
        removeSeries(s);

        delete s;
    }
}

QList<IChartiumSeries*> ChartiumChart::series()
{
    return mSeries;
}

IChartiumLegend* ChartiumChart::legend()
{
    return mLegend;
}

void ChartiumChart::createDefaultAxes()
{
}

void ChartiumChart::setTitle(const QString& /*title*/)
{
}
