#include "src/qtchartium/legend/chartiumlegendmarker.h"

#include "src/qtchartium/charts/ichartiumseries.h"
#include "src/qtchartium/legend/chartiumlegendmarkeritem.h"
#include "src/qtchartium/legend/ichartiumlegendlayout.h"



ChartiumLegendMarker::ChartiumLegendMarker(IChartiumLegend* legend, QObject* parent) :
    IChartiumLegendMarker(parent),
    mItem(new ChartiumLegendMarkerItem(this, legend->presenter())),
    mLegend(legend),
    mCustomLabel(),
    mCustomBrush(),
    mCustomPen()
{
    mItem->setVisible(series()->isVisible());

    connect(legend, SIGNAL(markerShapeChanged()), this, SLOT(handleShapeChange()));
}

ChartiumLegendMarker::~ChartiumLegendMarker()
{
    delete mItem;
}

IChartiumLegendMarker::LegendMarkerType ChartiumLegendMarker::type()
{
    return IChartiumLegendMarker::LegendMarkerTypeXY;
}

QString ChartiumLegendMarker::label() const
{
    return mItem->label();
}

void ChartiumLegendMarker::setLabel(const QString& label)
{
    if (label.isEmpty())
    {
        mCustomLabel = false;
    }
    else
    {
        mCustomLabel = true;
        mItem->setLabel(label);
    }
}

QBrush ChartiumLegendMarker::labelBrush() const
{
    return mItem->labelBrush();
}

void ChartiumLegendMarker::setLabelBrush(const QBrush& brush)
{
    mItem->setLabelBrush(brush);
}

QFont ChartiumLegendMarker::font() const
{
    return mItem->font();
}

void ChartiumLegendMarker::setFont(const QFont& font)
{
    mItem->setFont(font);
}

QPen ChartiumLegendMarker::pen() const
{
    return mItem->pen();
}

void ChartiumLegendMarker::setPen(const QPen& pen)
{
    if (pen == QPen(Qt::NoPen))
    {
        mCustomPen = false;
    }
    else
    {
        mCustomPen = true;
        mItem->setPen(pen);
    }
}

QBrush ChartiumLegendMarker::brush() const
{
    return mItem->brush();
}

void ChartiumLegendMarker::setBrush(const QBrush& brush)
{
    if (brush == QBrush(Qt::NoBrush))
    {
        mCustomBrush = false;
    }
    else
    {
        mCustomBrush = true;
        mItem->setBrush(brush);
    }
}

bool ChartiumLegendMarker::isVisible() const
{
    return mItem->isVisible();
}

void ChartiumLegendMarker::setVisible(bool visible)
{
    mItem->setVisible(visible);
}

IChartiumLegend::MarkerShape ChartiumLegendMarker::shape() const
{
    return mItem->markerShape();
}

void ChartiumLegendMarker::setShape(IChartiumLegend::MarkerShape shape)
{
    if (shape != mItem->markerShape())
    {
        mItem->setMarkerShape(shape);
        handleShapeChange();
        emit shapeChanged();
    }
}

IChartiumSeries* ChartiumLegendMarker::series()
{
    return nullptr;
}

QObject* ChartiumLegendMarker::relatedObject()
{
    return nullptr;
}

IChartiumLegendMarkerItem* ChartiumLegendMarker::item() const
{
    return nullptr;
}

void ChartiumLegendMarker::invalidateLegend()
{
    mItem->updateGeometry();
    mLegend->layout()->invalidate();
}

void ChartiumLegendMarker::invalidateAllItems()
{
    QList<IChartiumLegendMarker*> markers = mLegend->markers();

    for (int i = 0; i < markers.size(); i++)
    {
        markers.at(i)->item()->updateGeometry();
    }

    mLegend->layout()->invalidate();
}

IChartiumLegend* ChartiumLegendMarker::legend() const
{
    return mLegend;
}

void ChartiumLegendMarker::updated()
{
}

void ChartiumLegendMarker::handleShapeChange()
{
    mItem->updateMarkerShapeAndSize();
    mLegend->layout()->invalidate();
}
