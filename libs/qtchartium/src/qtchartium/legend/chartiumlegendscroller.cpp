#include "src/qtchartium/legend/chartiumlegendscroller.h"

#include <QGraphicsScene>

#include "src/qtchartium/ichartiumchart.h"



ChartiumLegendScroller::ChartiumLegendScroller(IChartiumChart* chart, QGraphicsItem* parent, Qt::WindowFlags wFlags) :
    IChartiumLegendScroller(chart, parent, wFlags),
    m_forwardMouseEvents(),
    m_forwardHoverEvents(),
    m_cachedShouldShowMoveEvents()
{
    // clang-format off
    connect(this, SIGNAL(interactiveChanged(bool)),     this, SLOT(handleInteractiveChanged(bool)));
    connect(this, SIGNAL(attachedToChartChanged(bool)), this, SLOT(handleDetached(bool)));
    // clang-format on
}

ChartiumLegendScroller::~ChartiumLegendScroller()
{
}

void ChartiumLegendScroller::updateForResizerChange()
{
    if (m_resizer->shouldShowMoveHint() != m_cachedShouldShowMoveEvents)
    {
        m_cachedShouldShowMoveEvents = m_resizer->shouldShowMoveHint();

        update();
    }
}

void ChartiumLegendScroller::setOffset(const QPointF& point)
{
}

QPointF ChartiumLegendScroller::offset() const
{
    return QPointF();
}

void ChartiumLegendScroller::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (!isInteractive() || isAttachedToChart())
    {
        IChartiumLegendScroller::handleMousePressEvent(event);
        return;
    }

    m_forwardMouseEvents = false;
    m_forwardHoverEvents = false;

    QRectF contentRect = geometry();
    qreal  left, top, right, bottom;
    m_layout->getContentsMargins(&left, &top, &right, &bottom);
    contentRect.adjust(left, top, -right, -bottom);
    contentRect.moveTo(left, top);
    QPointF pt = event->pos();

    if (contentRect.contains(pt))
    {
        IChartiumLegendScroller::handleMousePressEvent(event);
    }
    else
    {
        m_resizer->handleMousePressEvent(event);
        updateForResizerChange();
        m_forwardMouseEvents = event->isAccepted();
    }
}

void ChartiumLegendScroller::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if (m_forwardMouseEvents)
    {
        m_resizer->handleMouseMoveEvent(event);
        updateForResizerChange();
    }
    else
    {
        IChartiumLegendScroller::handleMouseMoveEvent(event);
    }
}

void ChartiumLegendScroller::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    if (m_forwardMouseEvents)
    {
        m_resizer->handleMouseReleaseEvent(event);
        updateForResizerChange();
        m_forwardMouseEvents = false;
    }
    else
    {
        IChartiumLegendScroller::handleMouseReleaseEvent(event);

        if (!event->isAccepted())
        {
            const QList<QGraphicsItem*> items = scene()->items(event->scenePos());

            for (QGraphicsItem* i : items)
            {
                if (m_markerHash.contains(i))
                {
                    IChartiumLegendMarker* marker = m_markerHash.value(i);

                    emit marker->clicked();
                }
            }

            event->accept();
        }
    }
}

void ChartiumLegendScroller::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
    if (isInteractive() && isAttachedToChart())
    {
        detachFromChart();
    }
}

void ChartiumLegendScroller::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    if (isInteractive() && !isAttachedToChart())
    {
        m_forwardHoverEvents = true;
        m_resizer->handleHoverEnterEvent(event);
        updateForResizerChange();
    }
    else
    {
        IChartiumLegendScroller::hoverEnterEvent(event);
    }
}

void ChartiumLegendScroller::hoverMoveEvent(QGraphicsSceneHoverEvent* event)
{
    if (!isInteractive() || isAttachedToChart())
    {
        IChartiumLegendScroller::hoverMoveEvent(event);
        return;
    }

    bool stopForwarding = m_layout->contentsRect().contains(event->pos());
    if (stopForwarding)
    {
        if (m_forwardHoverEvents)
        {
            // the event position is no longer over the border
            // frame, so send a leave. This will set the
            // mouse cursor back to an arrow.
            m_forwardHoverEvents = false;
            m_resizer->handleHoverLeaveEvent(event);
            updateForResizerChange();
        }
    }
    else
    {
        if (!m_forwardHoverEvents)
        {
            // if we're not already forwarding events, and we
            // shouldn't stop forwarding, then we should
            // start forwarding. This would happen if the event
            // position was inside the layout's content rect
            // on the _previous_ move event, and now the position
            // is on the border frame. So, this fakes a hover
            // enter from the _inside_ (which we otherwise
            // would not get).
            m_forwardHoverEvents = true;
            m_resizer->handleHoverEnterEvent(event);
            updateForResizerChange();
        }
    }

    if (m_forwardHoverEvents)
    {
        m_resizer->handleHoverMoveEvent(event);
        updateForResizerChange();
    }
    else
    {
        IChartiumLegendScroller::hoverMoveEvent(event);
    }
}

void ChartiumLegendScroller::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
    if (m_forwardHoverEvents)
    {
        m_forwardHoverEvents = false;
        m_resizer->handleHoverLeaveEvent(event);
        updateForResizerChange();
    }
    else
    {
        IChartiumLegendScroller::hoverLeaveEvent(event);
    }
}

void ChartiumLegendScroller::handleInteractiveChanged(bool interactive)
{
    setAcceptHoverEvents(interactive);
    m_cachedShouldShowMoveEvents = m_resizer->shouldShowMoveHint();
    m_forwardMouseEvents         = false;
    m_forwardHoverEvents         = false;
    m_resizer->reset();
    update();
}

void ChartiumLegendScroller::handleDetached(bool attached)
{
    if (attached)
    {
        return;
    }

    qreal left, top, right, bottom;
    m_layout->getContentsMargins(&left, &top, &right, &bottom);
    QSizeF newSize = QSizeF(left + right, top + bottom);
    qreal  width   = 0;
    qreal  height  = 0;

    for (auto marker : markers())
    {
        IChartiumLegendMarkerItem* item          = marker->item();
        QSizeF                     itemESizeHint = item->effectiveSizeHint(Qt::PreferredSize);

        switch (alignment())
        {
            case Qt::AlignTop:
            case Qt::AlignBottom:
                // + 3 accounts for the margin which is not an accessible member.
                width  += itemESizeHint.width() + 3;
                height  = qMax(height, itemESizeHint.height());
                break;
            case Qt::AlignLeft:
            case Qt::AlignRight:
                width   = qMax(width, itemESizeHint.width());
                height += itemESizeHint.height();
                break;
            default:
                break;
        }
    }

    newSize += QSizeF(width, height);

    QRectF newGeom = QRectF(geometry().topLeft(), newSize);
    setGeometry(newGeom.intersected(QRectF(QPoint(0, 0), m_chart->size())));
}
