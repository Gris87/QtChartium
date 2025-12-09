#include "src/qtchartium/legend/chartiumlegendmarkerxy.h"



ChartiumLegendMarkerXY::ChartiumLegendMarkerXY(IChartiumXYSeries* series, IChartiumLegend* legend, QObject* parent) :
    IChartiumLegendMarkerXY(legend, parent),
    mSeries(series)
{
}

ChartiumLegendMarkerXY::~ChartiumLegendMarkerXY()
{
}

IChartiumLegendMarker::LegendMarkerType ChartiumLegendMarkerXY::type()
{
    return IChartiumLegendMarker::LegendMarkerTypeXY;
}

IChartiumXYSeries* ChartiumLegendMarkerXY::series()
{
    return mSeries;
}

QObject* ChartiumLegendMarkerXY::relatedObject()
{
    return mSeries;
}

void ChartiumLegendMarkerXY::updated()
{
}
