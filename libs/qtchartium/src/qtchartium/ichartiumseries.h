#pragma once



class IChartiumSeries
{
public:
    IChartiumSeries()          = default;
    virtual ~IChartiumSeries() = default;

    IChartiumSeries(const IChartiumSeries& another)            = delete;
    IChartiumSeries& operator=(const IChartiumSeries& another) = delete;
};
