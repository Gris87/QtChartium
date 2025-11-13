#pragma once



#include "src/qtchartium/ichartiumlineseries.h"



class ChartiumLineSeries : public IChartiumLineSeries
{
public:
    explicit ChartiumLineSeries();
    ~ChartiumLineSeries() override;

    ChartiumLineSeries(const ChartiumLineSeries& another)            = delete;
    ChartiumLineSeries& operator=(const ChartiumLineSeries& another) = delete;
};
