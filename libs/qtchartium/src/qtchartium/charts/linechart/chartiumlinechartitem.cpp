#include "src/qtchartium/charts/linechart/chartiumlinechartitem.h"

#include <QGraphicsSceneMouseEvent>



ChartiumLineChartItem::ChartiumLineChartItem(IChartiumLineSeries* series, QGraphicsItem* item) :
    IChartiumLineChartItem(series, item),
    m_series(series),
    m_linePath(),
    m_linePathPolarRight(),
    m_linePathPolarLeft(),
    m_fullPath(),
    m_shapePath(),
    m_linePoints(),
    m_rect(),
    m_linePen(),
    m_pointsVisible(),
    m_chartType(IChartiumChart::ChartTypeUndefined),
    m_pointLabelsVisible(),
    m_markerSize(series->markerSize()),
    m_pointLabelsFormat(series->pointLabelsFormat()),
    m_pointLabelsFont(series->pointLabelsFont()),
    m_pointLabelsColor(series->pointLabelsColor()),
    m_pointLabelsClipping(true),
    m_lastMousePos(qQNaN(), qQNaN()),
    m_lastHoveredMatchedPos(),
    m_mousePressed()
{
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setZValue(IChartiumPresenter::LineChartZValue);

    // clang-format off
    connect(series, &IChartiumLineSeries::seriesUpdated,                this, &IChartiumLineChartItem::handleSeriesUpdated);
    connect(series, &IChartiumLineSeries::lightMarkerChanged,           this, &IChartiumLineChartItem::handleSeriesUpdated);
    connect(series, &IChartiumLineSeries::selectedLightMarkerChanged,   this, &IChartiumLineChartItem::handleSeriesUpdated);
    connect(series, &IChartiumLineSeries::markerSizeChanged,            this, &IChartiumLineChartItem::handleSeriesUpdated);
    connect(series, &IChartiumLineSeries::visibleChanged,               this, &IChartiumLineChartItem::handleSeriesUpdated);
    connect(series, &IChartiumLineSeries::opacityChanged,               this, &IChartiumLineChartItem::handleSeriesUpdated);
    connect(series, &IChartiumLineSeries::pointLabelsFormatChanged,     this, &IChartiumLineChartItem::handleSeriesUpdated);
    connect(series, &IChartiumLineSeries::pointLabelsVisibilityChanged, this, &IChartiumLineChartItem::handleSeriesUpdated);
    connect(series, &IChartiumLineSeries::pointLabelsFontChanged,       this, &IChartiumLineChartItem::handleSeriesUpdated);
    connect(series, &IChartiumLineSeries::pointLabelsColorChanged,      this, &IChartiumLineChartItem::handleSeriesUpdated);
    connect(series, &IChartiumLineSeries::pointLabelsClippingChanged,   this, &IChartiumLineChartItem::handleSeriesUpdated);
    connect(series, &IChartiumLineSeries::selectedColorChanged,         this, &IChartiumLineChartItem::handleSeriesUpdated);
    connect(series, &IChartiumLineSeries::selectedPointsChanged,        this, &IChartiumLineChartItem::handleSeriesUpdated);
    connect(series, &IChartiumLineSeries::pointsConfigurationChanged,   this, &IChartiumLineChartItem::handleSeriesUpdated);
    // clang-format on

    handleSeriesUpdated();
}

ChartiumLineChartItem::~ChartiumLineChartItem()
{
}

QPainterPath ChartiumLineChartItem::path() const
{
    return QPainterPath();
}

void ChartiumLineChartItem::suppressPoints()
{
}

void ChartiumLineChartItem::forceChartType(IChartiumChart::ChartType chartType)
{
}

QRectF ChartiumLineChartItem::boundingRect() const
{
    return m_rect;
}

void ChartiumLineChartItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    QRectF clipRect = QRectF(QPointF(0, 0), domain()->size());

    // Adjust clip rect half a pixel in required dimensions to make it include lines along the
    // plot area edges, but never increase clip so much that any portion of the line is draw beyond
    // the plot area.
    const qreal x1 = pos().x() - int(pos().x());
    const qreal y1 = pos().y() - int(pos().y());
    const qreal x2 = (clipRect.width() + 0.5) - int(clipRect.width() + 0.5);
    const qreal y2 = (clipRect.height() + 0.5) - int(clipRect.height() + 0.5);

    clipRect.adjust(-x1, -y1, qMax(x1, x2), qMax(y1, y2));

    painter->save();
    painter->setPen(m_linePen);

    bool alwaysUsePath = false;

    painter->setClipRect(clipRect);

    if (m_series->bestFitLineVisible())
    {
        m_series->drawBestFitLine(painter, clipRect);
    }

    if (m_linePen.style() != Qt::SolidLine || alwaysUsePath)
    {
        // If pen style is not solid line, use path painting to ensure proper pattern continuity
        painter->drawPath(m_linePath);
    }
    else
    {
        for (int i = 1; i < m_linePoints.size(); ++i)
        {
            painter->drawLine(m_linePoints.at(i - 1), m_linePoints.at(i));
        }
    }

    int pointLabelsOffset = m_linePen.width() / 2;

    // Draw markers if a marker or marker for selected points only has been
    // set (set to QImage() to disable)
    if (!m_series->lightMarker().isNull() || (!m_series->selectedLightMarker().isNull() && !m_series->selectedPoints().isEmpty()))
    {
        const QImage& marker         = m_series->lightMarker();
        const QImage& selectedMarker = m_series->selectedLightMarker();
        qreal         markerHalfSize = m_markerSize / 2.0;
        pointLabelsOffset            = markerHalfSize;

        for (int i = 0; i < m_linePoints.size(); ++i)
        {
            // Documentation of light markers says that points visibility and
            // light markers are independent features. Therefore m_pointsVisible
            // is not used here as light markers are drawn if lightMarker is not null.
            // However points visibility configuration can be still used here.
            bool drawPoint = !m_series->lightMarker().isNull();

            if (m_pointsConfiguration.contains(i))
            {
                const auto& conf = m_pointsConfiguration[i];

                if (conf.contains(IChartiumXYSeries::PointConfiguration::Visibility))
                {
                    drawPoint = m_pointsConfiguration[i][IChartiumXYSeries::PointConfiguration::Visibility].toBool();
                }
            }

            bool drawSelectedPoint = false;

            if (m_series->isPointSelected(i))
            {
                drawPoint         = true;
                drawSelectedPoint = !selectedMarker.isNull();
            }
            if (drawPoint)
            {
                const QRectF rect(
                    m_linePoints[i].x() - markerHalfSize, m_linePoints[i].y() - markerHalfSize, m_markerSize, m_markerSize
                );
                painter->drawImage(rect, drawSelectedPoint ? selectedMarker : marker);
            }
        }
    }

    m_series->drawPointLabels(painter, m_linePoints, pointLabelsOffset);

    const bool simpleDraw = m_selectedPoints.isEmpty() && m_pointsConfiguration.isEmpty();

    painter->setPen(Qt::NoPen);
    painter->setBrush(m_linePen.color());
    painter->setClipping(true);
    if (m_pointsVisible && simpleDraw && m_series->lightMarker().isNull())
    {
        for (int i = 0; i < m_linePoints.size(); ++i)
        {
            painter->drawEllipse(m_linePoints.at(i), m_markerSize, m_markerSize);
        }
    }
    else if (!simpleDraw)
    {
        qreal ptSize = m_markerSize;
        for (int i = 0; i < m_linePoints.size(); ++i)
        {
            if (clipRect.contains(m_linePoints.at(i)))
            {
                painter->save();
                ptSize         = m_markerSize;
                bool drawPoint = m_pointsVisible && m_series->lightMarker().isNull();
                if (m_pointsConfiguration.contains(i))
                {
                    const auto& conf = m_pointsConfiguration[i];
                    if (conf.contains(IChartiumXYSeries::PointConfiguration::Visibility))
                    {
                        drawPoint = m_pointsConfiguration[i][IChartiumXYSeries::PointConfiguration::Visibility].toBool();
                    }

                    if (drawPoint)
                    {
                        if (conf.contains(IChartiumXYSeries::PointConfiguration::Size))
                        {
                            ptSize = m_pointsConfiguration[i][IChartiumXYSeries::PointConfiguration::Size].toReal();
                        }

                        if (conf.contains(IChartiumXYSeries::PointConfiguration::Color))
                        {
                            painter->setBrush(
                                m_pointsConfiguration[i][IChartiumXYSeries::PointConfiguration::Color].value<QColor>()
                            );
                        }
                    }
                }

                if (m_series->isPointSelected(i))
                {
                    // Selected points are drawn regardless of m_pointsVisible settings and
                    // custom point configuration. However, they are not drawn if light markers
                    // are used. The reason of this is to avoid displaying selected point
                    // over selected light marker.
                    drawPoint = m_series->selectedLightMarker().isNull();
                    ptSize    = ptSize * 1.5;
                    if (m_selectedColor.isValid())
                    {
                        painter->setBrush(m_selectedColor);
                    }
                }

                if (drawPoint)
                {
                    painter->drawEllipse(m_linePoints.at(i), ptSize, ptSize);
                }

                painter->restore();
            }
        }
    }

    painter->restore();
}

QPainterPath ChartiumLineChartItem::shape() const
{
    return m_shapePath;
}

void ChartiumLineChartItem::updateGeometry()
{
    // Store the points to a local variable so that the old line gets properly cleared
    // when animation starts.
    m_linePoints                 = geometryPoints();
    const QList<QPointF>& points = m_linePoints;

    if (points.size() == 0)
    {
        prepareGeometryChange();
        m_linePathPolarRight = QPainterPath();
        m_linePathPolarLeft  = QPainterPath();
        m_fullPath           = QPainterPath();
        m_linePath           = QPainterPath();
        m_rect               = QRect();
        return;
    }

    QPainterPath linePath;
    QPainterPath fullPath;
    // Use worst case scenario to determine required margin.
    qreal margin = m_linePen.width() * 1.42;

    linePath.moveTo(points.at(0));
    for (int i = 1; i < points.size(); i++)
    {
        linePath.lineTo(points.at(i));
    }
    fullPath = linePath;

    QPainterPathStroker stroker;
    // QPainter::drawLine does not respect join styles, for example BevelJoin becomes MiterJoin.
    // This is why we are prepared for the "worst case" scenario, i.e. use always MiterJoin and
    // multiply line width with square root of two when defining shape and bounding rectangle.
    stroker.setWidth(margin);
    stroker.setJoinStyle(Qt::MiterJoin);
    stroker.setCapStyle(Qt::SquareCap);
    stroker.setMiterLimit(m_linePen.miterLimit());

    QPainterPath checkShapePath = stroker.createStroke(fullPath);

    // For mouse interactivity, we have to add the rects *after* the 'createStroke',
    // as we don't need the outline - we need it filled up.
    if (!m_series->lightMarker().isNull() || (!m_series->selectedLightMarker().isNull() && !m_series->selectedPoints().isEmpty()))
    {
        // +1, +2: a margin to guarantee we cover all of the pixmap
        qreal markerHalfSize = (m_markerSize / 2.0) + 1;
        qreal markerSize     = m_markerSize + 2;

        for (const auto& point : std::as_const(m_linePoints))
        {
            checkShapePath.addRect(point.x() - markerHalfSize, point.y() - markerHalfSize, markerSize, markerSize);
        }
    }

    // Only zoom in if the bounding rects of the paths fit inside int limits. QWidget::update() uses
    // a region that has to be compatible with QRect.
    if (checkShapePath.boundingRect().height() <= INT_MAX && checkShapePath.boundingRect().width() <= INT_MAX &&
        linePath.boundingRect().height() <= INT_MAX && linePath.boundingRect().width() <= INT_MAX &&
        fullPath.boundingRect().height() <= INT_MAX && fullPath.boundingRect().width() <= INT_MAX)
    {
        prepareGeometryChange();

        m_linePath  = linePath;
        m_fullPath  = fullPath;
        m_shapePath = checkShapePath;

        m_rect = m_shapePath.boundingRect();
    }
    else
    {
        update();
    }
}

void ChartiumLineChartItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QPointF matchedP = matchForLightMarker(event->pos());

    if (!qIsNaN(matchedP.x()))
    {
        emit pressed(matchedP);
    }
    else
    {
        emit pressed(domain()->calculateDomainPoint(event->pos()));
    }

    m_lastMousePos = event->pos();
    m_mousePressed = true;

    QGraphicsItem::mousePressEvent(event);
}

void ChartiumLineChartItem::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    // Identical code in SplineChartItem
    const QPointF matchedP  = hoverPoint(event->pos());
    m_lastHoveredMatchedPos = matchedP;

    emit hovered(matchedP, true);

    //    event->accept();
    QGraphicsItem::hoverEnterEvent(event);
}

void ChartiumLineChartItem::hoverMoveEvent(QGraphicsSceneHoverEvent* event)
{
    const QPointF matchedP = hoverPoint(event->pos());

    if (!fuzzyComparePointF(matchedP, m_lastHoveredMatchedPos))
    {
        emit hovered(matchedP, true);

        m_lastHoveredMatchedPos = matchedP;
    }

    QGraphicsItem::hoverMoveEvent(event);
}

void ChartiumLineChartItem::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
    const QPointF matchedP = hoverPoint(event->pos());
    emit hovered(matchedP, false);

    m_lastHoveredMatchedPos = {qQNaN(), qQNaN()};

    //    event->accept();
    QGraphicsItem::hoverEnterEvent(event);
}

void ChartiumLineChartItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    QPointF result;
    QPointF matchedP = matchForLightMarker(m_lastMousePos);

    if (!qIsNaN(matchedP.x()))
    {
        result = matchedP;
    }
    else
    {
        result = domain()->calculateDomainPoint(m_lastMousePos);
    }

    emit released(result);

    if (m_mousePressed)
    {
        emit clicked(result);
    }

    m_mousePressed = false;

    QGraphicsItem::mouseReleaseEvent(event);
}

void ChartiumLineChartItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
    QPointF matchedP = matchForLightMarker(event->pos());

    if (!qIsNaN(matchedP.x()))
    {
        emit IChartiumLineChartItem::doubleClicked(matchedP);
    }
    else
    {
        emit IChartiumLineChartItem::doubleClicked(domain()->calculateDomainPoint(m_lastMousePos));
    }

    QGraphicsItem::mouseDoubleClickEvent(event);
}

void ChartiumLineChartItem::handleSeriesUpdated()
{
    bool doGeometryUpdate =
        (m_pointsVisible != m_series->pointsVisible()) ||
        (m_series->pointsVisible() && (m_linePen != m_series->pen() || m_selectedColor != m_series->selectedColor() ||
                                       m_selectedPoints != m_series->selectedPoints())) ||
        m_series->pointsConfiguration() != m_pointsConfiguration || (m_markerSize != m_series->markerSize());
    bool visibleChanged = m_series->isVisible() != isVisible();
    setVisible(m_series->isVisible());
    setOpacity(m_series->opacity());
    m_pointsVisible = m_series->pointsVisible();

    qreal seriesPenWidth = m_series->pen().widthF();

    if (m_series->isMarkerSizeDefault() && (!qFuzzyCompare(seriesPenWidth, m_linePen.widthF())))
    {
        m_series->setMarkerSize(seriesPenWidth * 1.5);
    }

    m_linePen                 = m_series->pen();
    m_markerSize              = m_series->markerSize();
    m_pointLabelsFormat       = m_series->pointLabelsFormat();
    m_pointLabelsVisible      = m_series->pointLabelsVisible();
    m_pointLabelsFont         = m_series->pointLabelsFont();
    m_pointLabelsColor        = m_series->pointLabelsColor();
    m_selectedColor           = m_series->selectedColor();
    m_selectedPoints          = m_series->selectedPoints();
    m_pointsConfiguration     = m_series->pointsConfiguration();
    bool labelClippingChanged = m_pointLabelsClipping != m_series->pointLabelsClipping();
    m_pointLabelsClipping     = m_series->pointLabelsClipping();

    if (doGeometryUpdate)
    {
        updateGeometry();
    }

    // Update whole chart in case label clipping changed as labels can be outside series area
    if (labelClippingChanged)
    {
        m_series->chart()->update();
    }
    else
    {
        update();
    }
}
