#pragma once



#include "src/qtchartium/chartiumitem.h"

#include "src/qtchartium/charts/xychart/ichartiumxyseries.h"



class IChartiumXYChart : public ChartiumItem
{
    Q_OBJECT

public:
    explicit IChartiumXYChart(IChartiumXYSeries* series, QGraphicsItem* item = nullptr) :
        ChartiumItem(series, item)
    {
    }
    ~IChartiumXYChart() override = default;

    IChartiumXYChart(const IChartiumXYChart& another)            = delete;
    IChartiumXYChart& operator=(const IChartiumXYChart& another) = delete;
};
