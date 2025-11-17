#pragma once



#include "src/qtchartium/domain/ichartiumxydomain.h"



class ChartiumXYDomain : public IChartiumXYDomain
{
public:
    explicit ChartiumXYDomain();
    ~ChartiumXYDomain() override;

    ChartiumXYDomain(const ChartiumXYDomain& another)            = delete;
    ChartiumXYDomain& operator=(const ChartiumXYDomain& another) = delete;
};
