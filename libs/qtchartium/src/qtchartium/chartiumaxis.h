#pragma once



#include "src/qtchartium/ichartiumaxis.h"



class ChartiumAxis : public IChartiumAxis
{
public:
    explicit ChartiumAxis();
    ~ChartiumAxis() override;

    ChartiumAxis(const ChartiumAxis& another)            = delete;
    ChartiumAxis& operator=(const ChartiumAxis& another) = delete;
};
