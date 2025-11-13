#pragma once



#include <QString>

#include "src/qtchartium/ichartiumlegend.h"
#include "src/qtchartium/ichartiumseries.h"



class IChartiumChart
{
public:
    IChartiumChart()          = default;
    virtual ~IChartiumChart() = default;

    IChartiumChart(const IChartiumChart& another)            = delete;
    IChartiumChart& operator=(const IChartiumChart& another) = delete;

    virtual IChartiumLegend* legend()                           = 0;
    virtual void             addSeries(IChartiumSeries* series) = 0;
    virtual void             createDefaultAxes()                = 0;
    virtual void             setTitle(const QString& title)     = 0;
};
