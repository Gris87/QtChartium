#include "src/qtchartium/legend/chartiumlegendmarkeritem.h"

#include <QGraphicsSceneHoverEvent>
#include <QTextDocument>

#include "src/qtchartium/charts/xychart/ichartiumxyseries.h"
#include "src/qtchartium/ichartiumpresenter.h"
#include "src/qtchartium/legend/ichartiumlegendmarker.h"



ChartiumLegendMarkerItem::ChartiumLegendMarkerItem(
    IChartiumLegendMarker* marker,
    IChartiumPresenter*    presenter,
    QGraphicsItem*         parent,
    QGraphicsLayoutItem*   parent2,
    bool                   isLayout
) :
    IChartiumLegendMarkerItem(parent, parent2, isLayout),
    m_marker(marker),
    mPresenter(presenter),
    m_defaultMarkerRect(0.0, 0.0, 10.0, 10.0),
    m_markerRect(0.0, 0.0, -1.0, -1.0),
    m_boundingRect(),
    m_textItem(new QGraphicsTextItem(this)),
    m_markerItem(),
    m_margin(3),
    m_space(4),
    m_label(),
    m_markerShape(IChartiumLegend::MarkerShapeDefault),
    m_seriesLightMarker(),
    m_labelBrush(),
    m_pen(),
    m_brush(),
    m_seriesPen(),
    m_seriesBrush(),
    m_font(),
    m_hovering(),
    m_itemType(IChartiumLegendMarkerItem::TypeRect)
{
    m_textItem->document()->setDocumentMargin(presenter->textMargin());
    setAcceptHoverEvents(true);
}

ChartiumLegendMarkerItem::~ChartiumLegendMarkerItem()
{
    if (m_hovering)
    {
        emit m_marker->hovered(false);
    }
}

void ChartiumLegendMarkerItem::setPen(const QPen& pen)
{
    m_pen = pen;
    setItemBrushAndPen();
}

QPen ChartiumLegendMarkerItem::pen() const
{
    return m_pen;
}

void ChartiumLegendMarkerItem::setBrush(const QBrush& brush)
{
    m_brush = brush;
    setItemBrushAndPen();
}

QBrush ChartiumLegendMarkerItem::brush() const
{
    return m_brush;
}

void ChartiumLegendMarkerItem::setSeriesPen(const QPen& pen)
{
    m_seriesPen = pen;
    setItemBrushAndPen();
}

void ChartiumLegendMarkerItem::setSeriesBrush(const QBrush& brush)
{
    m_seriesBrush = brush;
    setItemBrushAndPen();
}

void ChartiumLegendMarkerItem::setSeriesLightMarker(const QImage& image)
{
    m_seriesLightMarker = image;

    if (m_markerItem)
    {
        if (image.isNull())
        {
            m_markerItem->setFlag(QGraphicsItem::ItemStacksBehindParent, false);
        }
        else
        {
            m_markerItem->setFlag(
                QGraphicsItem::ItemStacksBehindParent, (effectiveMarkerShape() == IChartiumLegend::MarkerShapeFromSeries)
            );
        }
    }

    updateMarkerShapeAndSize();
}

void ChartiumLegendMarkerItem::setFont(const QFont& font)
{
    QFontMetrics fn(font);
    m_font = font;

    m_defaultMarkerRect = QRectF(0, 0, fn.height() / 2, fn.height() / 2);

    if (effectiveMarkerShape() != IChartiumLegend::MarkerShapeFromSeries)
    {
        updateMarkerShapeAndSize();
    }

    m_marker->invalidateLegend();
}

QFont ChartiumLegendMarkerItem::font() const
{
    return m_font;
}

void ChartiumLegendMarkerItem::setLabel(const QString label)
{
    m_label = label;
    m_marker->invalidateLegend();
}

QString ChartiumLegendMarkerItem::label() const
{
    return m_label;
}

void ChartiumLegendMarkerItem::setLabelBrush(const QBrush& brush)
{
    m_textItem->setDefaultTextColor(brush.color());
}

QBrush ChartiumLegendMarkerItem::labelBrush() const
{
    return QBrush(m_textItem->defaultTextColor());
}

void ChartiumLegendMarkerItem::setGeometry(const QRectF& rect)
{
    if (!m_markerItem)
    {
        updateMarkerShapeAndSize();
    }

    const qreal   width       = rect.width();
    const qreal   markerWidth = effectiveMarkerWidth();
    const qreal   x           = m_margin + markerWidth + m_space + m_margin;
    QRectF        truncatedRect;
    const QString html = mPresenter->truncatedText(m_font, m_label, qreal(0.0), width - x, rect.height(), truncatedRect);
    m_textItem->setHtml(html.compare(QLatin1String("...")) ? html : QString());

    if (m_marker->legend()->showToolTips() && html != m_label)
    {
        m_textItem->setToolTip(m_label);
        m_markerItem->setToolTip(m_label);
    }
    else
    {
        m_textItem->setToolTip(QString());
        m_markerItem->setToolTip(QString());
    }

    m_textItem->setFont(m_font);
    m_textItem->setTextWidth(truncatedRect.width());

    qreal y = qMax(m_markerRect.height() + 2 * m_margin, truncatedRect.height() + 2 * m_margin);

    const QRectF& textRect = m_textItem->boundingRect();

    m_textItem->setPos(x - m_margin, y / 2 - textRect.height() / 2);
    setItemRect();

    // The textMargin adjustments to position are done to make default case rects less blurry with anti-aliasing
    m_markerItem->setPos(
        m_margin - mPresenter->textMargin() + (markerWidth - m_markerRect.width()) / 2.0,
        y / 2.0 - m_markerRect.height() / 2.0 + mPresenter->textMargin()
    );

    prepareGeometryChange();
    m_boundingRect = QRectF(0, 0, x + textRect.width() + m_margin, y);
}

QRectF ChartiumLegendMarkerItem::boundingRect() const
{
    return m_boundingRect;
}

QRectF ChartiumLegendMarkerItem::markerRect() const
{
    return m_markerRect;
}

void ChartiumLegendMarkerItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    // Draw the light marker, if it is present.
    if (!m_seriesLightMarker.isNull())
    {
        QRectF rect(m_markerItem->pos(), m_markerRect.size());

        // shrink the image so the line is visible behind the marker
        if (m_itemType == TypeLine && rect.width() > 4 && rect.height() > 4)
        {
            rect.adjust(1.0, 1.0, -1.0, -1.0);
        }

        painter->drawImage(rect, m_seriesLightMarker);
    }
}

QSizeF ChartiumLegendMarkerItem::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
{
    Q_UNUSED(constraint);

    QSizeF      sh;
    const qreal markerWidth = effectiveMarkerWidth();

    switch (which)
    {
        case Qt::MinimumSize:
        {
            const QRectF labelRect = mPresenter->textBoundingRect(m_font, QStringLiteral("..."));
            sh                     = QSizeF(
                labelRect.width() + (2.0 * m_margin) + m_space + markerWidth,
                qMax(m_markerRect.height(), labelRect.height()) + (2.0 * m_margin)
            );
            break;
        }
        case Qt::PreferredSize:
        {
            const QRectF labelRect = mPresenter->textBoundingRect(m_font, m_label);
            sh                     = QSizeF(
                labelRect.width() + (2.0 * m_margin) + m_space + markerWidth + 1,
                qMax(m_markerRect.height(), labelRect.height()) + (2.0 * m_margin)
            );
            break;
        }
        default:
            break;
    }

    return sh;
}

void ChartiumLegendMarkerItem::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    event->setAccepted(false);
    m_hovering = true;
    emit m_marker->hovered(true);

    QGraphicsObject::hoverEnterEvent(event);
}

void ChartiumLegendMarkerItem::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
    event->setAccepted(false);
    m_hovering = false;
    emit m_marker->hovered(false);

    QGraphicsObject::hoverLeaveEvent(event);
}

QString ChartiumLegendMarkerItem::displayedLabel() const
{
    return m_textItem->toHtml();
}

void ChartiumLegendMarkerItem::setToolTip(const QString& tooltip)
{
    m_textItem->setToolTip(tooltip);
    m_markerItem->setToolTip(tooltip);
}

IChartiumLegend::MarkerShape ChartiumLegendMarkerItem::markerShape() const
{
    return m_markerShape;
}

void ChartiumLegendMarkerItem::setMarkerShape(IChartiumLegend::MarkerShape shape)
{
    m_markerShape = shape;
}

void ChartiumLegendMarkerItem::updateMarkerShapeAndSize()
{
    const IChartiumLegend::MarkerShape shape = effectiveMarkerShape();

    ItemType           itemType = IChartiumLegendMarkerItem::TypeRect;
    QRectF             newRect  = m_defaultMarkerRect;
    IChartiumXYSeries* xySeries = qobject_cast<IChartiumXYSeries*>(m_marker->series());

    switch (shape)
    {
        case IChartiumLegend::MarkerShapeFromSeries:
        {
            if (xySeries)
            {
                m_seriesLightMarker = xySeries->lightMarker();
                switch (xySeries->type())
                {
                    case IChartiumSeries::SeriesTypeLine:
                    case IChartiumSeries::SeriesTypeSpline:
                    {
                        if (m_seriesLightMarker.isNull())
                        {
                            newRect.setHeight(m_seriesPen.width());
                            newRect.setWidth(qRound(m_defaultMarkerRect.width() * 1.5));
                        }
                        else
                        {
                            newRect.setSize(QSizeF(xySeries->markerSize(), xySeries->markerSize()));
                        }
                        itemType = IChartiumLegendMarkerItem::TypeLine;
                    }
                    break;
                    default:
                        // Use defaults specified above.
                        break;
                }
            }
        }
        break;
        case IChartiumLegend::MarkerShapeCircle:
            itemType = IChartiumLegendMarkerItem::TypeCircle;
            break;
        case IChartiumLegend::MarkerShapeRotatedRectangle:
            itemType = IChartiumLegendMarkerItem::TypeRotatedRect;
            break;
        case IChartiumLegend::MarkerShapeTriangle:
            itemType = IChartiumLegendMarkerItem::TypeTriangle;
            break;
        case IChartiumLegend::MarkerShapeStar:
            itemType = IChartiumLegendMarkerItem::TypeStar;
            break;
        case IChartiumLegend::MarkerShapePentagon:
            itemType = IChartiumLegendMarkerItem::TypePentagon;
            break;
        default:
            break;
    }

    if (!m_markerItem || m_itemType != itemType)
    {
        m_itemType = itemType;
        QPointF oldPos;
        if (m_markerItem)
        {
            oldPos = m_markerItem->pos();
            delete m_markerItem;
        }

        switch (itemType)
        {
            case IChartiumLegendMarkerItem::TypeRect:
            {
                m_markerItem = new QGraphicsRectItem(this);
                break;
            }
            case IChartiumLegendMarkerItem::TypeCircle:
            {
                m_markerItem = new QGraphicsEllipseItem(this);
                break;
            }
            default:
                m_markerItem = new QGraphicsLineItem(this);
                break;
        }

        if (xySeries && shape == IChartiumLegend::MarkerShapeFromSeries && !m_seriesLightMarker.isNull())
        {
            m_markerItem->setFlag(QGraphicsItem::ItemStacksBehindParent, true);
        }

        // Immediately update the position to the approximate correct position to avoid marker
        // jumping around when changing markers
        m_markerItem->setPos(oldPos);
    }
    setItemBrushAndPen();

    if (newRect != m_markerRect)
    {
        if (useMaxWidth() && m_marker->legend()->maxMarkerWidth() < newRect.width())
        {
            m_marker->invalidateAllItems();
        }
        m_markerRect = newRect;
        setItemRect();
        emit markerRectChanged();
        updateGeometry();
    }
}

IChartiumLegend::MarkerShape ChartiumLegendMarkerItem::effectiveMarkerShape() const
{
    IChartiumLegend::MarkerShape shape = m_markerShape;

    if (shape == IChartiumLegend::MarkerShapeDefault)
    {
        shape = m_marker->legend()->markerShape();
    }

    return shape;
}

qreal ChartiumLegendMarkerItem::effectiveMarkerWidth() const
{
    return useMaxWidth() ? m_marker->legend()->maxMarkerWidth() : m_markerRect.width();
}

IChartiumLegendMarkerItem::ItemType ChartiumLegendMarkerItem::itemType() const
{
    return IChartiumLegendMarkerItem::TypeRect;
}

void ChartiumLegendMarkerItem::setItemBrushAndPen()
{
    if (m_markerItem)
    {
        QAbstractGraphicsShapeItem* shapeItem = qgraphicsitem_cast<QGraphicsRectItem*>(m_markerItem);
        if (!shapeItem)
        {
            shapeItem = qgraphicsitem_cast<QGraphicsEllipseItem*>(m_markerItem);
        }

        if (!shapeItem)
        {
            shapeItem = qgraphicsitem_cast<QGraphicsPolygonItem*>(m_markerItem);
        }

        if (shapeItem)
        {
            if (effectiveMarkerShape() == IChartiumLegend::MarkerShapeFromSeries)
            {
                QPen   pen   = m_seriesPen;
                QBrush brush = m_seriesBrush;
                if (!m_seriesLightMarker.isNull())
                {
                    // If there's a light marker set, don't draw the regular marker.
                    pen.setColor(Qt::transparent);
                    brush = QBrush();
                    brush.setColor(Qt::transparent);
                }

                shapeItem->setPen(pen);
                shapeItem->setBrush(brush);
            }
            else
            {
                shapeItem->setPen(m_pen);
                shapeItem->setBrush(m_brush);
            }
        }
        else
        {
            // Must be line item, it has no brush.
            QGraphicsLineItem* lineItem = qgraphicsitem_cast<QGraphicsLineItem*>(m_markerItem);
            if (lineItem)
            {
                lineItem->setPen(m_seriesPen);
            }
        }
    }
}

void ChartiumLegendMarkerItem::setItemRect()
{
    switch (m_itemType)
    {
        case IChartiumLegendMarkerItem::TypeRect:
        {
            static_cast<QGraphicsRectItem*>(m_markerItem)->setRect(m_markerRect);
            break;
        }
        case IChartiumLegendMarkerItem::TypeCircle:
        {
            static_cast<QGraphicsEllipseItem*>(m_markerItem)->setRect(m_markerRect);
            break;
        }
        default:
        {
            qreal  y = m_markerRect.height() / 2.0;
            QLineF line(0.0, y, m_markerRect.width(), y);
            static_cast<QGraphicsLineItem*>(m_markerItem)->setLine(line);
            break;
        }
    }
}

bool ChartiumLegendMarkerItem::useMaxWidth() const
{
    return (m_marker->legend()->alignment() == Qt::AlignLeft || m_marker->legend()->alignment() == Qt::AlignRight);
}

qreal ChartiumLegendMarkerItem::margin() const
{
    return m_margin;
}

qreal ChartiumLegendMarkerItem::preferredItemWidth() const
{
    return sizeHint(Qt::PreferredSize, QSize()).width();
}
