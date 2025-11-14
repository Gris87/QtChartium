#include "src/qtchartium/chartiumchart.h"



ChartiumChart::ChartiumChart(QGraphicsItem* parent, Qt::WindowFlags wFlags) :
    IChartiumChart(parent, wFlags),
    mLegend(new ChartiumLegend())
{
}

ChartiumChart::~ChartiumChart()
{
    delete mLegend;
}

IChartiumLegend* ChartiumChart::legend()
{
    return mLegend;
}

void ChartiumChart::addSeries(IChartiumSeries* /*series*/)
{
}

void ChartiumChart::createDefaultAxes()
{
}

void ChartiumChart::setTitle(const QString& /*title*/)
{
}
