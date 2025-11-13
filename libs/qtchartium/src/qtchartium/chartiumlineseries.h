#pragma once



#include "src/qtchartium/ichartiumlineseries.h"



class ChartiumLineSeries : public IChartiumLineSeries
{
public:
    explicit ChartiumLineSeries();
    ~ChartiumLineSeries() override;

    ChartiumLineSeries(const ChartiumLineSeries& another)            = delete;
    ChartiumLineSeries& operator=(const ChartiumLineSeries& another) = delete;

    void append(qreal x, qreal y) override;
    void append(const QPointF& point) override;
    void append(const QList<QPointF>& points) override;

    ChartiumLineSeries& operator<<(const QPointF& point);
    ChartiumLineSeries& operator<<(const QList<QPointF>& points);
};
