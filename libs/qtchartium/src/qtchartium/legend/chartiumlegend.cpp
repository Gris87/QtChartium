#include "src/qtchartium/legend/chartiumlegend.h"

#include "src/qtchartium/ichartiumchart.h"



ChartiumLegend::ChartiumLegend(IChartiumChart* chart, QGraphicsItem* parent, Qt::WindowFlags wFlags) :
    IChartiumLegend(parent, wFlags)
{
}

ChartiumLegend::~ChartiumLegend()
{
}

void ChartiumLegend::setBrush(const QBrush& brush)
{
}

QBrush ChartiumLegend::brush() const
{
    return QBrush();
}

void ChartiumLegend::setColor(QColor color)
{
}

QColor ChartiumLegend::color()
{
    return QColor();
}

void ChartiumLegend::setPen(const QPen& pen)
{
}

QPen ChartiumLegend::pen() const
{
    return QPen();
}

void ChartiumLegend::setBorderColor(QColor color)
{
}

QColor ChartiumLegend::borderColor()
{
    return QColor();
}

void ChartiumLegend::setFont(const QFont& font)
{
}

QFont ChartiumLegend::font() const
{
    return QFont();
}

void ChartiumLegend::setLabelBrush(const QBrush& brush)
{
}

QBrush ChartiumLegend::labelBrush() const
{
    return QBrush();
}

void ChartiumLegend::setLabelColor(QColor color)
{
}

QColor ChartiumLegend::labelColor() const
{
    return QColor();
}

void ChartiumLegend::setAlignment(Qt::Alignment alignment)
{
}

Qt::Alignment ChartiumLegend::alignment() const
{
    return Qt::AlignLeft;
}

void ChartiumLegend::detachFromChart()
{
}

void ChartiumLegend::attachToChart()
{
}

bool ChartiumLegend::isAttachedToChart()
{
    return false;
}

void ChartiumLegend::setBackgroundVisible(bool visible)
{
}

bool ChartiumLegend::isBackgroundVisible() const
{
    return false;
}

QList<IChartiumLegendMarker*> ChartiumLegend::markers(IChartiumSeries* series) const
{
    QList<IChartiumLegendMarker*> res;

    return res;
}

bool ChartiumLegend::reverseMarkers()
{
    return false;
}

void ChartiumLegend::setReverseMarkers(bool reverseMarkers)
{
}

bool ChartiumLegend::showToolTips() const
{
    return false;
}

void ChartiumLegend::setShowToolTips(bool show)
{
}

bool ChartiumLegend::isInteractive() const
{
    return false;
}

void ChartiumLegend::setInteractive(bool interactive)
{
}

IChartiumLegend::MarkerShape ChartiumLegend::markerShape() const
{
    return IChartiumLegend::MarkerShapeDefault;
}

void ChartiumLegend::setMarkerShape(MarkerShape shape)
{
}

void ChartiumLegend::setOffset(const QPointF& offset)
{
}

QPointF ChartiumLegend::offset() const
{
    return QPointF();
}

int ChartiumLegend::roundness(qreal size)
{
    return 0;
}

QGraphicsItemGroup* ChartiumLegend::items()
{
    return nullptr;
}

QList<IChartiumLegendMarker*> ChartiumLegend::markers(IChartiumSeries* series)
{
    QList<IChartiumLegendMarker*> res;

    return res;
}

qreal ChartiumLegend::maxMarkerWidth() const
{
    return 0;
}

QObject* ChartiumLegend::relatedObject(const IChartiumLegendMarker* l)
{
    return nullptr;
}

void ChartiumLegend::insertMarkerHelper(IChartiumLegendMarker* marker)
{
}

void ChartiumLegend::addMarkers(const QList<IChartiumLegendMarker*>& markers)
{
}

void ChartiumLegend::removeMarkerHelper(IChartiumLegendMarker* marker)
{
}

void ChartiumLegend::removeMarkers(const QList<IChartiumLegendMarker*>& markers)
{
}

void ChartiumLegend::decorateMarker(IChartiumLegendMarker* marker)
{
}

void ChartiumLegend::decorateMarkers(const QList<IChartiumLegendMarker*>& markers)
{
}

void ChartiumLegend::updateToolTips()
{
}

void ChartiumLegend::handleSeriesAdded(IChartiumSeries* series)
{
}

void ChartiumLegend::handleSeriesRemoved(IChartiumSeries* series)
{
}

void ChartiumLegend::handleSeriesVisibleChanged()
{
}

void ChartiumLegend::handleCountChanged()
{
}
