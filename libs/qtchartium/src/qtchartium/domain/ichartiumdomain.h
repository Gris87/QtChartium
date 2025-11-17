#pragma once



class IChartiumDomain
{
public:
    IChartiumDomain()          = default;
    virtual ~IChartiumDomain() = default;

    IChartiumDomain(const IChartiumDomain& another)            = delete;
    IChartiumDomain& operator=(const IChartiumDomain& another) = delete;
};
