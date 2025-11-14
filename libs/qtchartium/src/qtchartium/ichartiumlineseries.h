#pragma once



#include "src/qtchartium/ichartiumseries.h"

#include <QList>
#include <QPointF>



class IChartiumLineSeries : public IChartiumSeries
{
public:
    explicit IChartiumLineSeries() :
        IChartiumSeries()
    {
    }
    ~IChartiumLineSeries() override = default;

    IChartiumLineSeries(const IChartiumLineSeries& another)            = delete;
    IChartiumLineSeries& operator=(const IChartiumLineSeries& another) = delete;

    virtual void append(qreal x, qreal y)             = 0;
    virtual void append(const QPointF& point)         = 0;
    virtual void append(const QList<QPointF>& points) = 0;
};
