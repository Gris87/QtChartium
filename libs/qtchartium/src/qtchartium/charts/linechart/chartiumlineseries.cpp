#include "src/qtchartium/charts/linechart/chartiumlineseries.h"



ChartiumLineSeries::ChartiumLineSeries(QObject* parent) :
    IChartiumLineSeries(parent)
{
}

ChartiumLineSeries::~ChartiumLineSeries()
{
}

IChartiumSeries::SeriesType ChartiumLineSeries::type() const
{
    return IChartiumSeries::SeriesTypeLine;
}

void ChartiumLineSeries::initializeGraphics(QGraphicsItem* parent)
{
}

void ChartiumLineSeries::initializeTheme(int index, IChartiumTheme* theme)
{
}
