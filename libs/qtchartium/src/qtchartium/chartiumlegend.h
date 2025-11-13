#pragma once



#include "src/qtchartium/ichartiumlegend.h"



class ChartiumLegend : public IChartiumLegend
{
public:
    explicit ChartiumLegend();
    ~ChartiumLegend() override;

    ChartiumLegend(const ChartiumLegend& another)            = delete;
    ChartiumLegend& operator=(const ChartiumLegend& another) = delete;

    void hide() override;
};
