#include "src/qtchartium/charts/xychart/chartiumxychart.h"



ChartiumXYChart::ChartiumXYChart(IChartiumXYSeries* series, QGraphicsItem* item) :
    IChartiumXYChart(series, item),
    m_series(series),
    m_points(),
    m_selectedPoints(),
    m_selectedColor(),
    m_dirty(true),
    m_pointsConfiguration()
{
    // clang-format off
    connect(m_series, &IChartiumXYSeries::seriesUpdated,  this,     &IChartiumXYChart::handleSeriesUpdated);
    connect(m_series, &IChartiumXYSeries::pointReplaced,  this,     &IChartiumXYChart::handlePointReplaced);
    connect(m_series, &IChartiumXYSeries::pointsReplaced, this,     &IChartiumXYChart::handlePointsReplaced);
    connect(m_series, &IChartiumXYSeries::pointAdded,     this,     &IChartiumXYChart::handlePointAdded);
    connect(m_series, &IChartiumXYSeries::pointRemoved,   this,     &IChartiumXYChart::handlePointRemoved);
    connect(m_series, &IChartiumXYSeries::pointsRemoved,  this,     &IChartiumXYChart::handlePointsRemoved);
    connect(this,     &IChartiumXYChart::clicked,         m_series, &IChartiumXYSeries::clicked);
    connect(this,     &IChartiumXYChart::hovered,         m_series, &IChartiumXYSeries::hovered);
    connect(this,     &IChartiumXYChart::pressed,         m_series, &IChartiumXYSeries::pressed);
    connect(this,     &IChartiumXYChart::released,        m_series, &IChartiumXYSeries::released);
    connect(this,     &IChartiumXYChart::doubleClicked,   m_series, &IChartiumXYSeries::doubleClicked);
    // clang-format on
}

ChartiumXYChart::~ChartiumXYChart()
{
}

void ChartiumXYChart::setGeometryPoints(const QList<QPointF>& points)
{
    m_points = points;
}

QList<QPointF> ChartiumXYChart::geometryPoints() const
{
    QList<QPointF> res;

    return res;
}

void ChartiumXYChart::updateGeometry()
{
}

bool ChartiumXYChart::isDirty() const
{
    return false;
}

void ChartiumXYChart::setDirty(bool dirty)
{
    m_dirty = dirty;
}

void ChartiumXYChart::getSeriesRanges(qreal& minX, qreal& maxX, qreal& minY, qreal& maxY)
{
}

QList<bool> ChartiumXYChart::offGridStatusVector()
{
    qreal minX = domain()->minX();
    qreal maxX = domain()->maxX();
    qreal minY = domain()->minY();
    qreal maxY = domain()->maxY();

    QList<bool> returnVector;
    returnVector.resize(m_points.size());

    // During remove animation series may have different number of points,
    // so ensure we don't go over the index. No need to check for zero points, this
    // will not be called in such a situation.
    const int seriesLastIndex = m_series->count() - 1;

    for (int i = 0; i < m_points.size(); i++)
    {
        const QPointF& seriesPoint = m_series->at(qMin(seriesLastIndex, i));

        if (seriesPoint.x() < minX || seriesPoint.x() > maxX || seriesPoint.y() < minY || seriesPoint.y() > maxY)
        {
            returnVector[i] = true;
        }
        else
        {
            returnVector[i] = false;
        }
    }

    return returnVector;
}

void ChartiumXYChart::updateChart(const QList<QPointF>& oldPoints, const QList<QPointF>& newPoints, int index)
{
    m_points = newPoints;
    updateGeometry();
}

QPointF ChartiumXYChart::matchForLightMarker(const QPointF& eventPos) const
{
    if (m_series->lightMarker().isNull() && (m_series->selectedLightMarker().isNull() || m_series->selectedPoints().isEmpty()))
    {
        return QPointF(qQNaN(), qQNaN()); // 0,0 could actually be in points()
    }

    const bool useSelectedMarker = m_series->lightMarker().isNull();

    QList<QPointF> points;
    if (useSelectedMarker)
    {
        const auto selectedPoints = m_series->selectedPoints();
        for (const int& selectedPointIndex : selectedPoints)
        {
            points << m_series->at(selectedPointIndex);
        }
    }
    else
    {
        points = m_series->points();
    }

    for (const QPointF& dp : points)
    {
        bool          ok;
        const QPointF gp = domain()->calculateGeometryPoint(dp, ok);
        if (ok)
        {
            // '+2' and '+4': There is an addRect for the (mouse-)shape
            // in LineChartItem::updateGeometry()
            // This has a margin of 1 to make sure a press in the icon will always be detected,
            // but as there is a bunch of 'translations' and therefore inaccuracies,
            // so it is necessary to increase that margin to 2
            // (otherwise you can click next to an icon, get a click event but not match it)
            QRectF r(
                gp.x() - (m_series->markerSize() / 2 + 2),
                gp.y() - (m_series->markerSize() / 2 + 2),
                m_series->markerSize() + 4,
                m_series->markerSize() + 4
            );

            if (r.contains(eventPos))
            {
                return dp;
            }
        }
    }
    return QPointF(qQNaN(), qQNaN()); // 0,0 could actually be in points()
}

bool ChartiumXYChart::isEmpty()
{
    return domain()->isEmpty() || m_series->points().isEmpty();
}

QPointF ChartiumXYChart::hoverPoint(const QPointF& eventPos) const
{
    const QPointF result = matchForLightMarker(eventPos);
    return qIsNaN(result.x()) ? domain()->calculateDomainPoint(eventPos) : result;
}

bool ChartiumXYChart::fuzzyComparePointF(const QPointF& p1, const QPointF& p2)
{
    // Should normally not be NaN, fail on safe side
    return !qIsNaN(p1.x()) && !qIsNaN(p2.x()) && qFuzzyCompare(p1.x(), p2.x()) && qFuzzyCompare(p1.y(), p2.y());
}

void ChartiumXYChart::handlePointAdded(int index)
{
    Q_ASSERT(index < m_series->count());
    Q_ASSERT(index >= 0);

    QList<QPointF> points;

    if (m_dirty || m_points.isEmpty())
    {
        points = domain()->calculateGeometryPoints(m_series->points());
    }
    else
    {
        points        = m_points;
        QPointF point = domain()->calculateGeometryPoint(m_series->points().at(index), mValidData);

        if (!mValidData)
        {
            m_points.clear();
        }
        else
        {
            points.insert(index, point);
        }
    }

    updateChart(m_points, points, index);
}

void ChartiumXYChart::handlePointRemoved(int index)
{
    Q_ASSERT(index <= m_series->count());
    Q_ASSERT(index >= 0);

    QList<QPointF> points;

    if (m_dirty || m_points.isEmpty())
    {
        points = domain()->calculateGeometryPoints(m_series->points());
    }
    else
    {
        points = m_points;
        points.remove(index);
    }

    updateChart(m_points, points, index);
}

void ChartiumXYChart::handlePointsRemoved(int index, int count)
{
    Q_ASSERT(index <= m_series->count());
    Q_ASSERT(index >= 0);

    QList<QPointF> points;

    if (m_dirty || m_points.isEmpty())
    {
        points = domain()->calculateGeometryPoints(m_series->points());
    }
    else
    {
        points = m_points;
        points.remove(index, count);
    }

    updateChart(m_points, points, index);
}

void ChartiumXYChart::handlePointReplaced(int index)
{
    Q_ASSERT(index < m_series->count());
    Q_ASSERT(index >= 0);

    QList<QPointF> points;

    if (m_dirty || m_points.isEmpty())
    {
        points = domain()->calculateGeometryPoints(m_series->points());
    }
    else
    {
        QPointF point = domain()->calculateGeometryPoint(m_series->points().at(index), mValidData);

        if (!mValidData)
        {
            m_points.clear();
        }

        points = m_points;

        if (mValidData)
        {
            points.replace(index, point);
        }
    }

    updateChart(m_points, points, index);
}

void ChartiumXYChart::handlePointsReplaced()
{
    // All the points were replaced -> recalculate
    QList<QPointF> points = domain()->calculateGeometryPoints(m_series->points());
    updateChart(m_points, points, -1);
}

void ChartiumXYChart::handleDomainUpdated()
{
    if (isEmpty())
    {
        return;
    }

    QList<QPointF> points = domain()->calculateGeometryPoints(m_series->points());
    updateChart(m_points, points);
}

void ChartiumXYChart::handleSeriesUpdated()
{
}
