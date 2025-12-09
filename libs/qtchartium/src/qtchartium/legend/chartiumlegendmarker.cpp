#include "src/qtchartium/legend/chartiumlegendmarker.h"

#include "src/qtchartium/charts/ichartiumseries.h"
#include "src/qtchartium/legend/chartiumlegendmarkeritem.h"
#include "src/qtchartium/legend/ichartiumlegendlayout.h"



ChartiumLegendMarker::ChartiumLegendMarker(IChartiumLegend* legend, QObject* parent) :
    IChartiumLegendMarker(parent),
    m_item(new ChartiumLegendMarkerItem(this, legend->presenter())),
    m_legend(legend),
    m_customLabel(),
    m_customBrush(),
    m_customPen()
{
    m_item->setVisible(series()->isVisible());

    connect(legend, SIGNAL(markerShapeChanged()), this, SLOT(handleShapeChange()));
}

ChartiumLegendMarker::~ChartiumLegendMarker()
{
    delete m_item;
}

IChartiumLegendMarker::LegendMarkerType ChartiumLegendMarker::type()
{
    return IChartiumLegendMarker::LegendMarkerTypeXY;
}

QString ChartiumLegendMarker::label() const
{
    return m_item->label();
}

void ChartiumLegendMarker::setLabel(const QString& label)
{
    if (label.isEmpty())
    {
        m_customLabel = false;
    }
    else
    {
        m_customLabel = true;
        m_item->setLabel(label);
    }
}

QBrush ChartiumLegendMarker::labelBrush() const
{
    return m_item->labelBrush();
}

void ChartiumLegendMarker::setLabelBrush(const QBrush& brush)
{
    m_item->setLabelBrush(brush);
}

QFont ChartiumLegendMarker::font() const
{
    return m_item->font();
}

void ChartiumLegendMarker::setFont(const QFont& font)
{
    m_item->setFont(font);
}

QPen ChartiumLegendMarker::pen() const
{
    return m_item->pen();
}

void ChartiumLegendMarker::setPen(const QPen& pen)
{
    if (pen == QPen(Qt::NoPen))
    {
        m_customPen = false;
    }
    else
    {
        m_customPen = true;
        m_item->setPen(pen);
    }
}

QBrush ChartiumLegendMarker::brush() const
{
    return m_item->brush();
}

void ChartiumLegendMarker::setBrush(const QBrush& brush)
{
    if (brush == QBrush(Qt::NoBrush))
    {
        m_customBrush = false;
    }
    else
    {
        m_customBrush = true;
        m_item->setBrush(brush);
    }
}

bool ChartiumLegendMarker::isVisible() const
{
    return m_item->isVisible();
}

void ChartiumLegendMarker::setVisible(bool visible)
{
    m_item->setVisible(visible);
}

IChartiumLegend::MarkerShape ChartiumLegendMarker::shape() const
{
    return m_item->markerShape();
}

void ChartiumLegendMarker::setShape(IChartiumLegend::MarkerShape shape)
{
    if (shape != m_item->markerShape())
    {
        m_item->setMarkerShape(shape);
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
    m_item->updateGeometry();
    m_legend->layout()->invalidate();
}

void ChartiumLegendMarker::invalidateAllItems()
{
    QList<IChartiumLegendMarker*> markers = m_legend->markers();

    for (int i = 0; i < markers.size(); i++)
    {
        markers.at(i)->item()->updateGeometry();
    }

    m_legend->layout()->invalidate();
}

IChartiumLegend* ChartiumLegendMarker::legend() const
{
    return m_legend;
}

void ChartiumLegendMarker::updated()
{
}

void ChartiumLegendMarker::handleShapeChange()
{
    m_item->updateMarkerShapeAndSize();
    m_legend->layout()->invalidate();
}
