#include "src/qtchartium/legend/chartiumlegendmarkerxy.h"

#include "src/qtchartium/legend/ichartiumlegendmarkeritem.h"



ChartiumLegendMarkerXY::ChartiumLegendMarkerXY(IChartiumXYSeries* series, IChartiumLegend* legend, QObject* parent) :
    IChartiumLegendMarkerXY(legend, parent),
    mSeries(series)
{
    // clang-format off
    connect(mSeries, SIGNAL(seriesUpdated()), this, SLOT(updated()));
    connect(mSeries, SIGNAL(nameChanged()),   this, SLOT(updated()));
    // clang-format on

    updated();
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
    bool isLabelChanged = false;
    bool isBrushChanged = false;

    if (!mCustomLabel && (mItem->label() != mSeries->name()))
    {
        mItem->setLabel(mSeries->name());
        isLabelChanged = true;
    }

    QBrush emptyBrush;

    if (!mCustomBrush && (mItem->brush() == emptyBrush || mItem->brush().color() != mSeries->pen().color()))
    {
        mItem->setBrush(QBrush(mSeries->pen().color()));
        isBrushChanged = true;
    }

    if (mItem->effectiveMarkerShape() == IChartiumLegend::MarkerShapeFromSeries &&
        mSeries->markerSize() != mItem->markerRect().width())
    {
        mItem->updateMarkerShapeAndSize();
    }

    mItem->setSeriesBrush(mSeries->brush());
    mItem->setSeriesPen(mSeries->pen());

    if (mItem->effectiveMarkerShape() == IChartiumLegend::MarkerShapeFromSeries)
    {
        mItem->setSeriesLightMarker(mSeries->lightMarker());
    }

    invalidateLegend();

    if (isLabelChanged)
    {
        emit labelChanged();
    }

    if (isBrushChanged)
    {
        emit brushChanged();
    }
}
