#pragma once



#include "src/qtchartium/charts/xychart/chartiumxyseries.h"



class IChartiumLineSeries : public ChartiumXYSeries
{
    Q_OBJECT

public:
    explicit IChartiumLineSeries(QObject* parent = nullptr) :
        ChartiumXYSeries(parent)
    {
    }
    ~IChartiumLineSeries() override = default;

    IChartiumLineSeries(const IChartiumLineSeries& another)            = delete;
    IChartiumLineSeries& operator=(const IChartiumLineSeries& another) = delete;
};
