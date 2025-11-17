#pragma once



#include "src/qtchartium/domain/ichartiumdomain.h"



class ChartiumDomain : public IChartiumDomain
{
public:
    explicit ChartiumDomain();
    ~ChartiumDomain() override;

    ChartiumDomain(const ChartiumDomain& another)            = delete;
    ChartiumDomain& operator=(const ChartiumDomain& another) = delete;
};
