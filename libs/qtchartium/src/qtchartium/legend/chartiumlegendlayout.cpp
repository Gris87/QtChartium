#include "src/qtchartium/legend/chartiumlegendlayout.h"

#include "src/qtchartium/ichartiumpresenter.h"
#include "src/qtchartium/legend/ichartiumlegendmarker.h"



ChartiumLegendLayout::ChartiumLegendLayout(IChartiumLegend* legend, QGraphicsLayoutItem* parent) :
    IChartiumLegendLayout(parent),
    m_legend(legend),
    m_offsetX(),
    m_offsetY(),
    m_minOffsetX(),
    m_minOffsetY(),
    m_maxOffsetX(),
    m_maxOffsetY(),
    m_width(),
    m_height()
{
}

ChartiumLegendLayout::~ChartiumLegendLayout()
{
}

void ChartiumLegendLayout::setGeometry(const QRectF& rect)
{
    m_legend->items()->setVisible(m_legend->isVisible());

    IChartiumLegendLayout::setGeometry(rect);

    if (m_legend->isAttachedToChart())
    {
        setAttachedGeometry(rect);
    }
    else
    {
        setDettachedGeometry(rect);
    }
}

void ChartiumLegendLayout::setOffset(qreal x, qreal y)
{
    bool scrollHorizontal = true;
    switch (m_legend->alignment())
    {
        case Qt::AlignTop:
        case Qt::AlignBottom:
            scrollHorizontal = true;
            break;
        case Qt::AlignLeft:
        case Qt::AlignRight:
            scrollHorizontal = false;
            break;
    }

    // If detached, the scrolling direction is vertical instead of horizontal and vice versa.
    if (!m_legend->isAttachedToChart())
    {
        scrollHorizontal = !scrollHorizontal;
    }

    QRectF boundingRect = geometry();
    qreal  left, top, right, bottom;
    getContentsMargins(&left, &top, &right, &bottom);
    boundingRect.adjust(left, top, -right, -bottom);

    // Limit offset between m_minOffset and m_maxOffset
    if (scrollHorizontal)
    {
        if (m_width <= boundingRect.width())
        {
            return;
        }

        if (x != m_offsetX)
        {
            m_offsetX = qBound(m_minOffsetX, x, m_maxOffsetX);
            m_legend->items()->setPos(-m_offsetX, boundingRect.top());
        }
    }
    else
    {
        if (m_height <= boundingRect.height())
        {
            return;
        }

        if (y != m_offsetY)
        {
            m_offsetY = qBound(m_minOffsetY, y, m_maxOffsetY);
            m_legend->items()->setPos(boundingRect.left(), -m_offsetY);
        }
    }
}

QPointF ChartiumLegendLayout::offset() const
{
    return QPointF(m_offsetX, m_offsetY);
}

void ChartiumLegendLayout::invalidate()
{
    IChartiumLegendLayout::invalidate();

    if (m_legend->isAttachedToChart())
    {
        m_legend->presenter()->layout()->invalidate();
    }
}

QSizeF ChartiumLegendLayout::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
{
    QSizeF size(0, 0);
    qreal  left, top, right, bottom;
    getContentsMargins(&left, &top, &right, &bottom);

    if (constraint.isValid())
    {
        const QList<IChartiumLegendMarker*> markers = m_legend->markers();

        for (IChartiumLegendMarker* marker : markers)
        {
            IChartiumLegendMarkerItem* item = marker->item();
            size                            = size.expandedTo(item->effectiveSizeHint(which));
        }
        size = size.boundedTo(constraint);
    }
    else if (constraint.width() >= 0)
    {
        qreal width  = 0;
        qreal height = 0;

        const QList<IChartiumLegendMarker*> markers = m_legend->markers();

        for (IChartiumLegendMarker* marker : markers)
        {
            IChartiumLegendMarkerItem* item  = marker->item();
            width                           += item->effectiveSizeHint(which).width();
            height                           = qMax(height, item->effectiveSizeHint(which).height());
        }

        size = QSizeF(qMin(constraint.width(), width), height);
    }
    else if (constraint.height() >= 0)
    {
        qreal width  = 0;
        qreal height = 0;

        const QList<IChartiumLegendMarker*> markers = m_legend->markers();

        for (IChartiumLegendMarker* marker : markers)
        {
            IChartiumLegendMarkerItem* item  = marker->item();
            width                            = qMax(width, item->effectiveSizeHint(which).width());
            height                          += height, item->effectiveSizeHint(which).height();
        }
        size = QSizeF(width, qMin(constraint.height(), height));
    }
    else
    {
        const QList<IChartiumLegendMarker*> markers = m_legend->markers();

        for (IChartiumLegendMarker* marker : markers)
        {
            IChartiumLegendMarkerItem* item = marker->item();
            size                            = size.expandedTo(item->effectiveSizeHint(which));
        }
    }
    size += QSize(left + right, top + bottom);
    return size;
}

int ChartiumLegendLayout::count() const
{
    return 0;
}

QGraphicsLayoutItem* ChartiumLegendLayout::itemAt(int) const
{
    return nullptr;
}

void ChartiumLegendLayout::removeAt(int)
{
}

void ChartiumLegendLayout::setAttachedGeometry(const QRectF& rect)
{
    if (!rect.isValid())
    {
        return;
    }

    qreal oldOffsetX = m_offsetX;
    qreal oldOffsetY = m_offsetY;
    m_offsetX        = 0;
    m_offsetY        = 0;

    QSizeF size(0, 0);

    if (m_legend->markers().isEmpty())
    {
        return;
    }

    m_width  = 0;
    m_height = 0;

    qreal left, top, right, bottom;
    getContentsMargins(&left, &top, &right, &bottom);

    QRectF geometry = rect.adjusted(left, top, -right, -bottom);

    switch (m_legend->alignment())
    {
        case Qt::AlignTop:
        case Qt::AlignBottom:
        {
            // Calculate the space required for items and add them to a sorted list.
            qreal                     markerItemsWidth = 0;
            qreal                     itemMargins      = 0;
            QList<LegendWidthStruct*> legendWidthList;

            const QList<IChartiumLegendMarker*> markers = m_legend->markers();

            for (IChartiumLegendMarker* marker : markers)
            {
                IChartiumLegendMarkerItem* item = marker->item();

                if (item->isVisible())
                {
                    qreal              itemWidth  = item->preferredItemWidth();
                    LegendWidthStruct* structItem = new LegendWidthStruct();
                    structItem->item              = item;
                    structItem->width             = itemWidth;
                    legendWidthList.append(structItem);
                    markerItemsWidth += itemWidth;
                    itemMargins      += marker->item()->margin();
                }
            }

            std::sort(
                legendWidthList.begin(),
                legendWidthList.end(),
                [](const LegendWidthStruct* item1, const LegendWidthStruct* item2) { return item1->width > item2->width; }
            );

            // If the items would occupy more space than is available, start truncating them
            // from the longest one.
            qreal availableGeometry = geometry.width() - itemMargins;
            if (markerItemsWidth >= availableGeometry && legendWidthList.size() > 0)
            {
                bool truncated(false);
                int  count = legendWidthList.size();
                for (int i = 1; i < count; i++)
                {
                    int truncateIndex = i - 1;

                    while (legendWidthList.at(truncateIndex)->width >= legendWidthList.at(i)->width && !truncated)
                    {
                        legendWidthList.at(truncateIndex)->width--;
                        markerItemsWidth--;
                        if (i > 1)
                        {
                            // Truncate the items that are before the truncated one in the list.
                            for (int j = truncateIndex - 1; j >= 0; j--)
                            {
                                if (legendWidthList.at(truncateIndex)->width < legendWidthList.at(j)->width)
                                {
                                    legendWidthList.at(j)->width--;
                                    markerItemsWidth--;
                                }
                            }
                        }
                        if (markerItemsWidth < availableGeometry)
                        {
                            truncated = true;
                        }
                    }
                    // Truncate the last item if needed.
                    if (i == count - 1)
                    {
                        if (legendWidthList.at(count - 1)->width > legendWidthList.at(truncateIndex)->width)
                        {
                            legendWidthList.at(count - 1)->width--;
                            markerItemsWidth--;
                        }
                    }

                    if (truncated)
                    {
                        break;
                    }
                }

                // Items are of same width and all of them need to be truncated
                // or there is just one item that is truncated.
                while (markerItemsWidth >= availableGeometry)
                {
                    for (int i = 0; i < count; i++)
                    {
                        legendWidthList.at(i)->width--;
                        markerItemsWidth--;
                    }
                }
            }

            QPointF point(0, 0);

            int markerCount = m_legend->markers().size();
            for (int i = 0; i < markerCount; i++)
            {
                IChartiumLegendMarker* marker;

                if (m_legend->reverseMarkers())
                {
                    marker = m_legend->markers().at(markerCount - 1 - i);
                }
                else
                {
                    marker = m_legend->markers().at(i);
                }

                IChartiumLegendMarkerItem* item = marker->item();

                if (item->isVisible())
                {
                    QRectF itemRect       = geometry;
                    qreal  availableWidth = 0;
                    for (int i = 0; i < legendWidthList.size(); ++i)
                    {
                        if (legendWidthList.at(i)->item == item)
                        {
                            availableWidth = legendWidthList.at(i)->width;
                            break;
                        }
                    }
                    itemRect.setWidth(availableWidth);
                    item->setGeometry(itemRect);
                    item->setPos(point.x(), geometry.height() / 2 - item->boundingRect().height() / 2);
                    const QRectF& rect = item->boundingRect();
                    size               = size.expandedTo(rect.size());
                    qreal w            = rect.width();
                    m_width            = m_width + w - item->margin();
                    point.setX(point.x() + w);
                }
            }
            // Delete structs from the container
            qDeleteAll(legendWidthList);

            // Round to full pixel via QPoint to avoid one pixel clipping on the edge in some cases
            if (m_width < geometry.width())
            {
                m_legend->items()->setPos(QPoint(geometry.width() / 2 - m_width / 2, geometry.top()));
            }
            else
            {
                m_legend->items()->setPos(geometry.topLeft().toPoint());
            }
            m_height = size.height();
        }
        break;
        case Qt::AlignLeft:
        case Qt::AlignRight:
        {
            QPointF point(0, 0);
            int     markerCount = m_legend->markers().size();
            for (int i = 0; i < markerCount; i++)
            {
                IChartiumLegendMarker* marker;

                if (m_legend->reverseMarkers())
                {
                    marker = m_legend->markers().at(markerCount - 1 - i);
                }
                else
                {
                    marker = m_legend->markers().at(i);
                }

                IChartiumLegendMarkerItem* item = marker->item();

                if (item->isVisible())
                {
                    item->setGeometry(geometry);
                    item->setPos(point);
                    const QRectF& rect  = item->boundingRect();
                    qreal         h     = rect.height();
                    size                = size.expandedTo(rect.size());
                    m_height           += h;
                    point.setY(point.y() + h);
                }
            }

            // Round to full pixel via QPoint to avoid one pixel clipping on the edge in some cases
            if (m_height < geometry.height())
            {
                m_legend->items()->setPos(QPoint(geometry.left(), geometry.height() / 2 - m_height / 2));
            }
            else
            {
                m_legend->items()->setPos(geometry.topLeft().toPoint());
            }

            m_width = size.width();

            break;
        }
    }

    m_minOffsetX = -left;
    m_minOffsetY = -top;
    m_maxOffsetX = m_width - geometry.width() - right;
    m_maxOffsetY = m_height - geometry.height() - bottom;

    setOffset(oldOffsetX, oldOffsetY);
}

void ChartiumLegendLayout::setDettachedGeometry(const QRectF& rect)
{
    if (!rect.isValid())
    {
        return;
    }

    // Detached layout is different.
    // In detached mode legend may have multiple rows and columns, so layout calculations
    // differ a log from attached mode.
    // Also the scrolling logic is bit different.

    qreal oldOffsetX = m_offsetX;
    qreal oldOffsetY = m_offsetY;
    m_offsetX        = 0;
    m_offsetY        = 0;

    qreal left, top, right, bottom;
    getContentsMargins(&left, &top, &right, &bottom);
    QRectF geometry = rect.adjusted(left, top, -right, -bottom);

    QList<IChartiumLegendMarker*> markers = m_legend->markers();

    if (markers.isEmpty())
    {
        return;
    }

    Qt::Alignment align = m_legend->alignment();
    switch (align)
    {
        case Qt::AlignTop:
        case Qt::AlignBottom:
        {
            QPointF point(0, (align == Qt::AlignTop) ? 0 : geometry.height());
            m_width  = 0;
            m_height = 0;
            for (int i = 0; i < markers.size(); i++)
            {
                IChartiumLegendMarkerItem* item = markers.at(i)->item();

                if (item->isVisible())
                {
                    item->setGeometry(geometry);
                    const QRectF& boundingRect = item->boundingRect();
                    qreal         w            = boundingRect.width();
                    qreal         h            = boundingRect.height();
                    m_width                    = qMax(m_width, w);
                    m_height                   = qMax(m_height, h);
                    item->setPos(point.x(), point.y() - ((align == Qt::AlignTop) ? 0 : h));
                    point.setX(point.x() + w);
                    if (point.x() + w > geometry.left() + geometry.width() - right)
                    {
                        // Next item would go off rect.
                        point.setX(0);
                        point.setY(point.y() + ((align == Qt::AlignTop) ? h : -h));
                        if (i + 1 < markers.size())
                        {
                            m_height += h;
                        }
                    }
                }
            }
            m_legend->items()->setPos(geometry.topLeft());

            m_minOffsetX = -left;
            m_maxOffsetX = m_width - geometry.width() - right;
            if (align == Qt::AlignTop)
            {
                m_minOffsetY = -top;
                m_maxOffsetY = m_height - geometry.height() - bottom;
            }
            else
            {
                m_minOffsetY = -m_height + geometry.height() - top;
                m_maxOffsetY = -bottom;
            }
        }
        break;
        case Qt::AlignLeft:
        case Qt::AlignRight:
        {
            QPointF point((align == Qt::AlignLeft) ? 0 : geometry.width(), 0);
            m_width        = 0;
            m_height       = 0;
            qreal maxWidth = 0;
            for (int i = 0; i < markers.size(); i++)
            {
                IChartiumLegendMarkerItem* item = markers.at(i)->item();

                if (item->isVisible())
                {
                    item->setGeometry(geometry);
                    const QRectF& boundingRect = item->boundingRect();
                    qreal         w            = boundingRect.width();
                    qreal         h            = boundingRect.height();
                    m_height                   = qMax(m_height, h);
                    maxWidth                   = qMax(maxWidth, w);
                    item->setPos(point.x() - ((align == Qt::AlignLeft) ? 0 : w), point.y());
                    point.setY(point.y() + h);
                    if (point.y() + h > geometry.bottom() - bottom)
                    {
                        // Next item would go off rect.
                        point.setX(point.x() + ((align == Qt::AlignLeft) ? maxWidth : -maxWidth));
                        point.setY(0);
                        if (i + 1 < markers.size())
                        {
                            m_width  += maxWidth;
                            maxWidth  = 0;
                        }
                    }
                }
            }
            m_width += maxWidth;
            m_legend->items()->setPos(geometry.topLeft());

            m_minOffsetY = -top;
            m_maxOffsetY = m_height - geometry.height() - bottom;
            if (align == Qt::AlignLeft)
            {
                m_minOffsetX = -left;
                m_maxOffsetX = m_width - geometry.width() - right;
            }
            else
            {
                m_minOffsetX = -m_width + geometry.width() - left;
                m_maxOffsetX = -right;
            }
        }
        break;
        default:
            break;
    }

    setOffset(oldOffsetX, oldOffsetY);
}
