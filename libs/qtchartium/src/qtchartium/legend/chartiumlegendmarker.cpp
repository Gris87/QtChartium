#include "src/qtchartium/legend/chartiumlegendmarker.h"



ChartiumLegendMarker::ChartiumLegendMarker(IChartiumLegend* legend, QObject* parent) :
    IChartiumLegendMarker(parent)
{
}

ChartiumLegendMarker::~ChartiumLegendMarker()
{
}

IChartiumLegendMarker::LegendMarkerType ChartiumLegendMarker::type()
{
    return IChartiumLegendMarker::LegendMarkerTypeXY;
}

QString ChartiumLegendMarker::label() const
{
    return "";
}

void ChartiumLegendMarker::setLabel(const QString& label)
{
}

QBrush ChartiumLegendMarker::labelBrush() const
{
    return QBrush();
}

void ChartiumLegendMarker::setLabelBrush(const QBrush& brush)
{
}

QFont ChartiumLegendMarker::font() const
{
    return QFont();
}

void ChartiumLegendMarker::setFont(const QFont& font)
{
}

QPen ChartiumLegendMarker::pen() const
{
    return QPen();
}

void ChartiumLegendMarker::setPen(const QPen& pen)
{
}

QBrush ChartiumLegendMarker::brush() const
{
    return QBrush();
}

void ChartiumLegendMarker::setBrush(const QBrush& brush)
{
}

bool ChartiumLegendMarker::isVisible() const
{
    return false;
}

void ChartiumLegendMarker::setVisible(bool visible)
{
}

IChartiumLegend::MarkerShape ChartiumLegendMarker::shape() const
{
    return IChartiumLegend::MarkerShapeDefault;
}

void ChartiumLegendMarker::setShape(IChartiumLegend::MarkerShape shape)
{
}

IChartiumSeries* ChartiumLegendMarker::series()
{
    return nullptr;
}

IChartiumLegendMarkerItem* ChartiumLegendMarker::item() const
{
    return nullptr;
}

QObject* ChartiumLegendMarker::relatedObject()
{
    return nullptr;
}

void ChartiumLegendMarker::invalidateLegend()
{
}

void ChartiumLegendMarker::invalidateAllItems()
{
}

void ChartiumLegendMarker::updated()
{
}

void ChartiumLegendMarker::handleShapeChange()
{
}
