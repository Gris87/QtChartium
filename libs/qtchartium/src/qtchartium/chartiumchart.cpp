#include "src/qtchartium/chartiumchart.h"



ChartiumChart::ChartiumChart(QGraphicsItem* parent, Qt::WindowFlags wFlags) :
    IChartiumChart(parent, wFlags),
    mLegend(new ChartiumLegend()),
    mSeries(),
    mAxes()
{
}

ChartiumChart::~ChartiumChart()
{
    delete mLegend;
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

void ChartiumChart::addAxis(IChartiumAxis* axis, Qt::Alignment alignment)
{
    if (mAxes.contains(axis))
    {
        return;
    }

    mAxes.append(axis);
}

void ChartiumChart::removeAxis(IChartiumAxis* axis)
{
    if (!mAxes.contains(axis))
    {
        return;
    }

    mAxes.removeAll(axis);
}

QList<IChartiumAxis*> ChartiumChart::axes(Qt::Orientations orientation, IChartiumSeries* series)
{
    QList<IChartiumAxis*> res;

    return res;
}

void ChartiumChart::createDefaultAxes()
{
    if (mSeries.isEmpty())
    {
        return;
    }
}

IChartiumLegend* ChartiumChart::legend()
{
    return mLegend;
}

void ChartiumChart::setTitle(const QString& /*title*/)
{
}
