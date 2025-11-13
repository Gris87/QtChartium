#pragma once



class IChartiumChart
{
public:
    IChartiumChart()          = default;
    virtual ~IChartiumChart() = default;

    IChartiumChart(const IChartiumChart& another)            = delete;
    IChartiumChart& operator=(const IChartiumChart& another) = delete;
};
