#include "src/qtchartium/legend/chartiumlegendmarkeritem.h"



ChartiumLegendMarkerItem::ChartiumLegendMarkerItem(
    IChartiumLegendMarker* marker, QGraphicsItem* parent, QGraphicsLayoutItem* parent2, bool isLayout
) :
    IChartiumLegendMarkerItem(parent, parent2, isLayout)
{
}

ChartiumLegendMarkerItem::~ChartiumLegendMarkerItem()
{
}

void ChartiumLegendMarkerItem::setPen(const QPen& pen)
{
}

QPen ChartiumLegendMarkerItem::pen() const
{
    return QPen();
}

void ChartiumLegendMarkerItem::setBrush(const QBrush& brush)
{
}

QBrush ChartiumLegendMarkerItem::brush() const
{
    return QBrush();
}

void ChartiumLegendMarkerItem::setSeriesPen(const QPen& pen)
{
}

void ChartiumLegendMarkerItem::setSeriesBrush(const QBrush& brush)
{
}

void ChartiumLegendMarkerItem::setSeriesLightMarker(const QImage& image)
{
}

void ChartiumLegendMarkerItem::setFont(const QFont& font)
{
}

QFont ChartiumLegendMarkerItem::font() const
{
    return QFont();
}

void ChartiumLegendMarkerItem::setLabel(const QString label)
{
}

QString ChartiumLegendMarkerItem::label() const
{
    return "";
}

void ChartiumLegendMarkerItem::setLabelBrush(const QBrush& brush)
{
}

QBrush ChartiumLegendMarkerItem::labelBrush() const
{
    return QBrush();
}

void ChartiumLegendMarkerItem::setGeometry(const QRectF& rect)
{
}

QRectF ChartiumLegendMarkerItem::boundingRect() const
{
    return QRectF();
}

QRectF ChartiumLegendMarkerItem::markerRect() const
{
    return QRectF();
}

void ChartiumLegendMarkerItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
}

QSizeF ChartiumLegendMarkerItem::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
{
    return QSizeF();
}

void ChartiumLegendMarkerItem::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
}

void ChartiumLegendMarkerItem::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
}

QString ChartiumLegendMarkerItem::displayedLabel() const
{
    return "";
}

void ChartiumLegendMarkerItem::setToolTip(const QString& tooltip)
{
}

IChartiumLegend::MarkerShape ChartiumLegendMarkerItem::markerShape() const
{
    return IChartiumLegend::MarkerShapeDefault;
}

void ChartiumLegendMarkerItem::setMarkerShape(IChartiumLegend::MarkerShape shape)
{
}

void ChartiumLegendMarkerItem::updateMarkerShapeAndSize()
{
}

IChartiumLegend::MarkerShape ChartiumLegendMarkerItem::effectiveMarkerShape() const
{
    return IChartiumLegend::MarkerShapeDefault;
}

qreal ChartiumLegendMarkerItem::effectiveMarkerWidth() const
{
    return 0;
}

IChartiumLegendMarkerItem::ItemType ChartiumLegendMarkerItem::itemType() const
{
    return IChartiumLegendMarkerItem::TypeRect;
}

void ChartiumLegendMarkerItem::setItemBrushAndPen()
{
}

void ChartiumLegendMarkerItem::setItemRect()
{
}

bool ChartiumLegendMarkerItem::useMaxWidth() const
{
    return false;
}

qreal ChartiumLegendMarkerItem::margin() const
{
    return m_margin;
}

qreal ChartiumLegendMarkerItem::preferredItemWidth() const
{
    return sizeHint(Qt::PreferredSize, QSize()).width();
}
