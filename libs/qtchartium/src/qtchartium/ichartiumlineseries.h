#pragma once



class IChartiumLineSeries
{
public:
    IChartiumLineSeries()          = default;
    virtual ~IChartiumLineSeries() = default;

    IChartiumLineSeries(const IChartiumLineSeries& another)            = delete;
    IChartiumLineSeries& operator=(const IChartiumLineSeries& another) = delete;
};
