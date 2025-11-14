#pragma once



class IChartiumAxis
{
public:
    IChartiumAxis()          = default;
    virtual ~IChartiumAxis() = default;

    IChartiumAxis(const IChartiumAxis& another)            = delete;
    IChartiumAxis& operator=(const IChartiumAxis& another) = delete;
};
