#pragma once



class IChartiumLegend
{
public:
    IChartiumLegend()          = default;
    virtual ~IChartiumLegend() = default;

    IChartiumLegend(const IChartiumLegend& another)            = delete;
    IChartiumLegend& operator=(const IChartiumLegend& another) = delete;

    virtual void hide() = 0;
};
