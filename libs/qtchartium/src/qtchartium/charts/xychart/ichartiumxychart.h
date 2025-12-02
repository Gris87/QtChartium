#pragma once



#include "src/qtchartium/chartiumitem.h"

#include "src/qtchartium/charts/xychart/ichartiumxyseries.h"



class IChartiumXYChart : public ChartiumItem
{
    Q_OBJECT

public:
    explicit IChartiumXYChart(IChartiumXYSeries* series, QGraphicsItem* item = nullptr) :
        ChartiumItem(series, item)
    {
    }
    ~IChartiumXYChart() override = default;

    IChartiumXYChart(const IChartiumXYChart& another)            = delete;
    IChartiumXYChart& operator=(const IChartiumXYChart& another) = delete;

    virtual void           setGeometryPoints(const QList<QPointF>& points) = 0;
    virtual QList<QPointF> geometryPoints() const                          = 0;

    virtual void updateGeometry() = 0;

    virtual bool isDirty() const      = 0;
    virtual void setDirty(bool dirty) = 0;

    virtual void        getSeriesRanges(qreal& minX, qreal& maxX, qreal& minY, qreal& maxY) = 0;
    virtual QList<bool> offGridStatusVector()                                               = 0;

    virtual void updateChart(const QList<QPointF>& oldPoints, const QList<QPointF>& newPoints, int index = -1) = 0;

    virtual QPointF matchForLightMarker(const QPointF& eventPos) const = 0;

    virtual bool isEmpty() = 0;

    virtual QPointF hoverPoint(const QPointF& eventPos) const                = 0;
    virtual bool    fuzzyComparePointF(const QPointF& p1, const QPointF& p2) = 0;

public slots:
    virtual void handlePointAdded(int index)               = 0;
    virtual void handlePointRemoved(int index)             = 0;
    virtual void handlePointsRemoved(int index, int count) = 0;
    virtual void handlePointReplaced(int index)            = 0;
    virtual void handlePointsReplaced()                    = 0;
    virtual void handleSeriesUpdated()                     = 0;

signals:
    void clicked(const QPointF& point);
    void hovered(const QPointF& point, bool state);
    void pressed(const QPointF& point);
    void released(const QPointF& point);
    void doubleClicked(const QPointF& point);
};
