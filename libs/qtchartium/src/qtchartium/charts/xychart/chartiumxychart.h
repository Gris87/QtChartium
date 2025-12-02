#pragma once



#include "src/qtchartium/charts/xychart/ichartiumxychart.h"



class ChartiumXYChart : public IChartiumXYChart
{
    Q_OBJECT

public:
    explicit ChartiumXYChart(IChartiumXYSeries* series, QGraphicsItem* item = nullptr);
    ~ChartiumXYChart() override;

    ChartiumXYChart(const ChartiumXYChart& another)            = delete;
    ChartiumXYChart& operator=(const ChartiumXYChart& another) = delete;
};
