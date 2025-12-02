#pragma once



#include "src/qtchartium/charts/xychart/chartiumxyseries.h"



class IChartiumLineSeries : public ChartiumXYSeries
{
public:
    explicit IChartiumLineSeries(QObject* parent = nullptr) :
        ChartiumXYSeries(parent)
    {
    }
    ~IChartiumLineSeries() override = default;

    IChartiumLineSeries(const IChartiumLineSeries& another)            = delete;
    IChartiumLineSeries& operator=(const IChartiumLineSeries& another) = delete;

    virtual void append(qreal x, qreal y)             = 0;
    virtual void append(const QPointF& point)         = 0;
    virtual void append(const QList<QPointF>& points) = 0;
};
