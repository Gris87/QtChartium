#pragma once



#include "src/qtchartium/ichartiumseries.h"



class ChartiumSeries : public IChartiumSeries
{
public:
    explicit ChartiumSeries();
    ~ChartiumSeries() override;

    ChartiumSeries(const ChartiumSeries& another)            = delete;
    ChartiumSeries& operator=(const ChartiumSeries& another) = delete;
};
