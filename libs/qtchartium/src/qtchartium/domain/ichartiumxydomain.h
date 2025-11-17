#pragma once



#include "src/qtchartium/domain/ichartiumdomain.h"



class IChartiumXYDomain : public IChartiumDomain
{
public:
    IChartiumXYDomain() :
        IChartiumDomain()
    {
    }
    ~IChartiumXYDomain() override = default;

    IChartiumXYDomain(const IChartiumXYDomain& another)            = delete;
    IChartiumXYDomain& operator=(const IChartiumXYDomain& another) = delete;
};
