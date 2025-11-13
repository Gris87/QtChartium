#pragma once



#include "src/qtchartium/ichartiumchart.h"



class ChartiumChart : public IChartiumChart
{
public:
    explicit ChartiumChart();
    ~ChartiumChart() override;

    ChartiumChart(const ChartiumChart& another)            = delete;
    ChartiumChart& operator=(const ChartiumChart& another) = delete;
};
