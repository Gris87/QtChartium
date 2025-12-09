#include "src/qtchartium/legend/chartiumlegend.h"

#include <QPainter>

#include "src/qtchartium/ichartiumchart.h"
#include "src/qtchartium/ichartiumdataset.h"
#include "src/qtchartium/ichartiumpresenter.h"
#include "src/qtchartium/legend/chartiumlegendlayout.h"
#include "src/qtchartium/legend/chartiumlegendmoveresizehandler.h"



ChartiumLegend::ChartiumLegend(IChartiumChart* chart, QGraphicsItem* parent, Qt::WindowFlags wFlags) :
    IChartiumLegend(parent, wFlags),
    m_presenter(chart->presenter()),
    m_layout(new ChartiumLegendLayout(this)),
    m_resizer(new ChartiumLegendMoveResizeHandler(this)),
    m_chart(chart),
    m_items(new QGraphicsItemGroup(this)),
    m_alignment(Qt::AlignTop),
    m_brush(),
    m_pen(),
    m_font(),
    m_labelBrush(),
    m_diameter(5),
    m_attachedToChart(true),
    m_backgroundVisible(),
    m_reverseMarkers(),
    m_showToolTips(),
    m_interactive(),
    m_markerShape(IChartiumLegend::MarkerShapeRectangle),
    m_markers(),
    m_series(),
    m_markerHash()
{
    m_items->setHandlesChildEvents(false);

    setZValue(IChartiumPresenter::LegendZValue);
    setFlags(QGraphicsItem::ItemClipsChildrenToShape);

    // clang-format off
    connect(m_chart->dataset(), SIGNAL(seriesAdded(IChartiumSeries*)),   this, SLOT(handleSeriesAdded(IChartiumSeries*)));
    connect(m_chart->dataset(), SIGNAL(seriesRemoved(IChartiumSeries*)), this, SLOT(handleSeriesRemoved(IChartiumSeries*)));
    // clang-format on

    setLayout(m_layout);
}

ChartiumLegend::~ChartiumLegend()
{
    delete m_resizer;
}

void ChartiumLegend::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    if (!m_backgroundVisible)
    {
        return;
    }

    painter->setOpacity(opacity());
    painter->setPen(m_pen);
    painter->setBrush(m_brush);
    painter->drawRoundedRect(rect(), roundness(rect().width()), roundness(rect().height()), Qt::RelativeSize);
}

void ChartiumLegend::setBrush(const QBrush& brush)
{
    if (m_brush != brush)
    {
        m_brush = brush;
        update();

        emit colorChanged(brush.color());
    }
}

QBrush ChartiumLegend::brush() const
{
    return m_brush;
}

void ChartiumLegend::setColor(QColor color)
{
    QBrush b = brush();

    if (b.style() != Qt::SolidPattern || b.color() != color)
    {
        b.setStyle(Qt::SolidPattern);
        b.setColor(color);

        setBrush(b);
    }
}

QColor ChartiumLegend::color()
{
    return m_brush.color();
}

void ChartiumLegend::setPen(const QPen& pen)
{
    if (m_pen != pen)
    {
        m_pen = pen;
        update();

        emit borderColorChanged(pen.color());
    }
}

QPen ChartiumLegend::pen() const
{
    return m_pen;
}

void ChartiumLegend::setBorderColor(QColor color)
{
    QPen p = pen();
    if (p.color() != color)
    {
        p.setColor(color);
        setPen(p);
    }
}

QColor ChartiumLegend::borderColor()
{
    return m_pen.color();
}

void ChartiumLegend::setFont(const QFont& font)
{
    if (m_font != font)
    {
        // Hide items to avoid flickering
        items()->setVisible(false);
        m_font = font;

        for (IChartiumLegendMarker* marker : markers())
        {
            marker->setFont(m_font);
        }

        layout()->invalidate();
        emit fontChanged(font);
    }
}

QFont ChartiumLegend::font() const
{
    return m_font;
}

void ChartiumLegend::setLabelBrush(const QBrush& brush)
{
    if (m_labelBrush != brush)
    {
        m_labelBrush = brush;

        for (IChartiumLegendMarker* marker : markers())
        {
            marker->setLabelBrush(m_labelBrush);
            // Note: The pen of the marker rectangle could be exposed in the public QLegend API
            // instead of mapping it from label brush color
            marker->setPen(brush.color());
        }

        emit labelColorChanged(brush.color());
    }
}

QBrush ChartiumLegend::labelBrush() const
{
    return m_labelBrush;
}

void ChartiumLegend::setLabelColor(QColor color)
{
    QBrush b = labelBrush();
    if (b.style() != Qt::SolidPattern || b.color() != color)
    {
        b.setStyle(Qt::SolidPattern);
        b.setColor(color);
        setLabelBrush(b);
    }
}

QColor ChartiumLegend::labelColor() const
{
    return m_labelBrush.color();
}

void ChartiumLegend::setAlignment(Qt::Alignment alignment)
{
    if (m_alignment != alignment)
    {
        m_alignment = alignment;
        layout()->invalidate();
    }
}

Qt::Alignment ChartiumLegend::alignment() const
{
    return m_alignment;
}

void ChartiumLegend::detachFromChart()
{
    bool changed      = m_attachedToChart == true;
    m_attachedToChart = false;
    m_chart->layout()->invalidate();
    setParent(0);

    if (changed)
    {
        emit attachedToChartChanged(false);
    }
}

void ChartiumLegend::attachToChart()
{
    bool changed      = m_attachedToChart == false;
    m_attachedToChart = true;
    m_chart->layout()->invalidate();
    setParent(m_chart);

    if (changed)
    {
        emit attachedToChartChanged(true);
    }
}

bool ChartiumLegend::isAttachedToChart()
{
    return m_attachedToChart;
}

void ChartiumLegend::setBackgroundVisible(bool visible)
{
    if (m_backgroundVisible != visible)
    {
        m_backgroundVisible = visible;
        update();
        emit backgroundVisibleChanged(visible);
    }
}

bool ChartiumLegend::isBackgroundVisible() const
{
    return m_backgroundVisible;
}

QList<IChartiumLegendMarker*> ChartiumLegend::markers(IChartiumSeries* series) const
{
    QList<IChartiumLegendMarker*> res;

    return res;
}

bool ChartiumLegend::reverseMarkers()
{
    return m_reverseMarkers;
}

void ChartiumLegend::setReverseMarkers(bool reverseMarkers)
{
    if (m_reverseMarkers != reverseMarkers)
    {
        m_reverseMarkers = reverseMarkers;
        layout()->invalidate();

        emit reverseMarkersChanged(reverseMarkers);
    }
}

bool ChartiumLegend::showToolTips() const
{
    return m_showToolTips;
}

void ChartiumLegend::setShowToolTips(bool show)
{
    if (m_showToolTips != show)
    {
        m_showToolTips = show;
        updateToolTips();

        emit showToolTipsChanged(show);
    }
}

bool ChartiumLegend::isInteractive() const
{
    return m_interactive;
}

void ChartiumLegend::setInteractive(bool interactive)
{
    if (m_interactive != interactive)
    {
        m_interactive = interactive;
        update();

        emit interactiveChanged(interactive);
    }
}

IChartiumLegend::MarkerShape ChartiumLegend::markerShape() const
{
    return m_markerShape;
}

void ChartiumLegend::setMarkerShape(MarkerShape shape)
{
    IChartiumLegend::MarkerShape newShape = shape;

    if (newShape == MarkerShapeDefault)
    {
        newShape = MarkerShapeRectangle;
    }

    if (m_markerShape != newShape)
    {
        m_markerShape = newShape;
        layout()->invalidate();
        emit markerShapeChanged(newShape);
    }
}

void ChartiumLegend::hideEvent(QHideEvent* event)
{
    if (isAttachedToChart())
    {
        m_presenter->layout()->invalidate();
    }

    QGraphicsWidget::hideEvent(event);
}

void ChartiumLegend::showEvent(QShowEvent* event)
{
    if (isAttachedToChart())
    {
        layout()->invalidate();
    }

    QGraphicsWidget::showEvent(event);
    //layout activation will show the items
}

void ChartiumLegend::setOffset(const QPointF& offset)
{
    m_layout->setOffset(offset.x(), offset.y());
}

QPointF ChartiumLegend::offset() const
{
    return m_layout->offset();
}

int ChartiumLegend::roundness(qreal size)
{
    return 100 * m_diameter / int(size);
}

QGraphicsItemGroup* ChartiumLegend::items()
{
    return m_items;
}

QList<IChartiumLegendMarker*> ChartiumLegend::markers(IChartiumSeries* series)
{
    // Return all markers
    if (!series)
    {
        return m_markers;
    }

    // Create filtered list
    QList<IChartiumLegendMarker*> markers;
    foreach(IChartiumLegendMarker* marker, m_markers)
    {
        if (marker->series() == series)
        {
            markers.append(marker);
        }
    }
    return markers;
}

qreal ChartiumLegend::maxMarkerWidth() const
{
    qreal maxWidth = 0.0;
    for (int i = 0; i < m_markers.size(); i++)
    {
        IChartiumLegendMarkerItem* item = m_markers.at(i)->item();

        if (item)
        {
            maxWidth = qMax(item->markerRect().width(), maxWidth);
        }
    }
    return maxWidth;
}

void ChartiumLegend::insertMarkerHelper(IChartiumLegendMarker* marker)
{
    IChartiumLegendMarkerItem* item = marker->item();

    m_items->addToGroup(item);
    m_markerHash.insert(item, marker);
}

void ChartiumLegend::addMarkers(const QList<IChartiumLegendMarker*>& markers)
{
    for (auto* marker : markers)
    {
        insertMarkerHelper(marker);
        m_markers << marker;
    }
}

void ChartiumLegend::removeMarkerHelper(IChartiumLegendMarker* marker)
{
    IChartiumLegendMarkerItem* item = marker->item();
    item->setVisible(false);
    m_items->removeFromGroup(item);
    m_markerHash.remove(item);
    delete marker;
}

void ChartiumLegend::removeMarkers(const QList<IChartiumLegendMarker*>& markers)
{
    for (auto* marker : markers)
    {
        m_markers.removeOne(marker);
        removeMarkerHelper(marker);
    }
}

void ChartiumLegend::decorateMarker(IChartiumLegendMarker* marker)
{
    marker->setFont(m_font);
    marker->setLabelBrush(m_labelBrush);
}

void ChartiumLegend::decorateMarkers(const QList<IChartiumLegendMarker*>& markers)
{
    for (auto* marker : markers)
    {
        decorateMarker(marker);
    }
}

void ChartiumLegend::updateToolTips()
{
    for (IChartiumLegendMarker* m : m_markers)
    {
        if (m->item()->displayedLabel() != m->label())
        {
            m->item()->setToolTip(m->label());
        }
        else
        {
            m->item()->setToolTip(QString());
        }
    }
}

int ChartiumLegend::indexOfEquivalent(IChartiumLegendMarker* needle, const QList<IChartiumLegendMarker*>& hayStack) const
{
    const QObject* needleObject = needle->relatedObject();

    for (int i = 0, size = hayStack.size(); i < size; ++i)
    {
        if (hayStack.at(i)->relatedObject() == needleObject)
        {
            return i;
        }
    }

    return -1;
}

int ChartiumLegend::indexOfSeries(IChartiumSeries* series, const QList<IChartiumLegendMarker*>& hayStack) const
{
    for (int i = 0, size = hayStack.size(); i < size; ++i)
    {
        if (hayStack.at(i)->series() == series)
        {
            return i;
        }
    }

    return -1;
}

IChartiumPresenter* ChartiumLegend::presenter() const
{
    return m_presenter;
}

IChartiumLegendLayout* ChartiumLegend::layout() const
{
    return m_layout;
}

void ChartiumLegend::handleSeriesAdded(IChartiumSeries* series)
{
    if (m_series.contains(series))
    {
        return;
    }

    QList<IChartiumLegendMarker*> newMarkers = series->createLegendMarkers(this);
    decorateMarkers(newMarkers);
    addMarkers(newMarkers);

    // clang-format off
    connect(series, SIGNAL(countChanged()),   this, SLOT(handleCountChanged()));
    connect(series, SIGNAL(visibleChanged()), this, SLOT(handleSeriesVisibleChanged()));
    // clang-format on

    m_series.append(series);
    m_items->setVisible(false);
    m_layout->invalidate();
}

void ChartiumLegend::handleSeriesRemoved(IChartiumSeries* series)
{
    if (m_series.contains(series))
    {
        m_series.removeOne(series);
    }

    // Find out, which markers to remove
    QList<IChartiumLegendMarker*> removed;
    foreach(IChartiumLegendMarker* m, m_markers)
    {
        if (m->series() == series)
        {
            removed << m;
        }
    }
    removeMarkers(removed);

    // clang-format off
    disconnect(series, SIGNAL(countChanged()),   this, SLOT(handleCountChanged()));
    disconnect(series, SIGNAL(visibleChanged()), this, SLOT(handleSeriesVisibleChanged()));
    // clang-format on

    m_layout->invalidate();
}

void ChartiumLegend::handleSeriesVisibleChanged()
{
    IChartiumSeries* series = qobject_cast<IChartiumSeries*>(sender());
    Q_ASSERT(series);

    foreach(IChartiumLegendMarker* marker, m_markers)
    {
        if (marker->series() == series)
        {
            marker->setVisible(series->isVisible());
        }
    }

    if (m_chart->isVisible())
    {
        m_layout->invalidate();
    }
}

void ChartiumLegend::handleCountChanged()
{
    // Here we handle the changes in marker count.
    // Can happen for example when pieslice(s) have been added to or removed from pieseries.

    IChartiumSeries*              series         = qobject_cast<IChartiumSeries*>(sender());
    QList<IChartiumLegendMarker*> createdMarkers = series->createLegendMarkers(this);
    QList<bool>                   isNew(createdMarkers.size(), true);

    const int pos = indexOfSeries(series, m_markers);

    // Remove markers of the series from m_markers and check against the newly
    // created ones.
    if (pos != -1)
    {
        while (pos < m_markers.size() && m_markers.at(pos)->series() == series)
        {
            IChartiumLegendMarker* oldMarker = m_markers.takeAt(pos);

            const int newIndex = indexOfEquivalent(oldMarker, createdMarkers);

            if (newIndex == -1)
            {
                removeMarkerHelper(oldMarker); // no longer exists
            }
            else
            {
                // Replace newly created marker by its equivalent
                delete createdMarkers[newIndex];
                createdMarkers[newIndex] = oldMarker;
                isNew[newIndex]          = false;
            }
        }
    }

    for (int i = 0, size = createdMarkers.size(); i < size; ++i)
    {
        if (isNew.at(i))
        {
            insertMarkerHelper(createdMarkers.at(i));
            decorateMarker(createdMarkers.at(i));
        }
    }

    // Re-insert createdMarkers into m_markers in correct order.
    if (pos == -1 || pos == m_markers.size())
    {
        m_markers.append(createdMarkers);
    }
    else
    {
        for (int c = createdMarkers.size() - 1; c >= 0; --c)
        {
            m_markers.insert(pos, createdMarkers.at(c));
        }
    }

    layout()->invalidate();
}
