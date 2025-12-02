#include "src/qtchartium/charts/xychart/chartiumxychart.h"



ChartiumXYChart::ChartiumXYChart(IChartiumXYSeries* series, QGraphicsItem* item) :
    IChartiumXYChart(series, item)
{
}

ChartiumXYChart::~ChartiumXYChart()
{
}

void ChartiumXYChart::setGeometryPoints(const QList<QPointF>& points)
{
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
}

void ChartiumXYChart::getSeriesRanges(qreal& minX, qreal& maxX, qreal& minY, qreal& maxY)
{
}

QList<bool> ChartiumXYChart::offGridStatusVector()
{
    QList<bool> res;

    return res;
}

void ChartiumXYChart::updateChart(const QList<QPointF>& oldPoints, const QList<QPointF>& newPoints, int index)
{
}

QPointF ChartiumXYChart::matchForLightMarker(const QPointF& eventPos) const
{
    return QPointF();
}

bool ChartiumXYChart::isEmpty()
{
    return false;
}

QPointF ChartiumXYChart::hoverPoint(const QPointF& eventPos) const
{
    return QPointF();
}

bool ChartiumXYChart::fuzzyComparePointF(const QPointF& p1, const QPointF& p2)
{
    return false;
}

void ChartiumXYChart::handlePointAdded(int index)
{
}

void ChartiumXYChart::handlePointRemoved(int index)
{
}

void ChartiumXYChart::handlePointsRemoved(int index, int count)
{
}

void ChartiumXYChart::handlePointReplaced(int index)
{
}

void ChartiumXYChart::handlePointsReplaced()
{
}

void ChartiumXYChart::handleDomainUpdated()
{
}

void ChartiumXYChart::handleSeriesUpdated()
{
}
