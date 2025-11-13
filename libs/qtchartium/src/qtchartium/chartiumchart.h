#pragma once



#include "src/qtchartium/ichartiumchart.h"

#include "src/qtchartium/chartiumlegend.h"



class ChartiumChart : public IChartiumChart
{
public:
    explicit ChartiumChart();
    ~ChartiumChart() override;

    ChartiumChart(const ChartiumChart& another)            = delete;
    ChartiumChart& operator=(const ChartiumChart& another) = delete;

    IChartiumLegend* legend() override;
    void             addSeries(IChartiumSeries* series) override;
    void             createDefaultAxes() override;
    void             setTitle(const QString& title) override;

private:
    ChartiumLegend* mLegend;
};
