#pragma once



#include "src/qtchartium/charts/xychart/ichartiumxychart.h"



class ChartiumXYChart : public IChartiumXYChart
{
    Q_OBJECT

public:
    explicit ChartiumXYChart(IChartiumXYSeries* series, QGraphicsItem* item = nullptr);
    ~ChartiumXYChart() override;

    ChartiumXYChart(const ChartiumXYChart& another)            = delete;
    ChartiumXYChart& operator=(const ChartiumXYChart& another) = delete;

    void           setGeometryPoints(const QList<QPointF>& points) override;
    QList<QPointF> geometryPoints() const override;

    void updateGeometry() override;

    bool isDirty() const override;
    void setDirty(bool dirty) override;

    void        getSeriesRanges(qreal& minX, qreal& maxX, qreal& minY, qreal& maxY) override;
    QList<bool> offGridStatusVector() override;

    void updateChart(const QList<QPointF>& oldPoints, const QList<QPointF>& newPoints, int index = -1) override;

    QPointF matchForLightMarker(const QPointF& eventPos) const override;

    bool isEmpty() override;

    QPointF hoverPoint(const QPointF& eventPos) const override;
    bool    fuzzyComparePointF(const QPointF& p1, const QPointF& p2) override;

public slots:
    void handlePointAdded(int index) override;
    void handlePointRemoved(int index) override;
    void handlePointsRemoved(int index, int count) override;
    void handlePointReplaced(int index) override;
    void handlePointsReplaced() override;
    void handleDomainUpdated() override;
    void handleSeriesUpdated() override;

protected:
    IChartiumXYSeries*                                                 m_series;
    QList<QPointF>                                                     m_points;
    QList<int>                                                         m_selectedPoints;
    QColor                                                             m_selectedColor;
    bool                                                               m_dirty;
    QHash<int, QHash<IChartiumXYSeries::PointConfiguration, QVariant>> m_pointsConfiguration;
};
