#pragma once



#include "src/qtchartium/chartiumseries.h"



class IChartiumLineSeries : public ChartiumSeries
{
public:
    explicit IChartiumLineSeries() :
        ChartiumSeries()
    {
    }
    ~IChartiumLineSeries() override = default;

    IChartiumLineSeries(const IChartiumLineSeries& another)            = delete;
    IChartiumLineSeries& operator=(const IChartiumLineSeries& another) = delete;

    virtual void append(qreal x, qreal y)             = 0;
    virtual void append(const QPointF& point)         = 0;
    virtual void append(const QList<QPointF>& points) = 0;
};
