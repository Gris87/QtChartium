#pragma once



#include "src/qtchartium/charts/xychart/chartiumxychart.h"

#include "src/qtchartium/charts/linechart/ichartiumlineseries.h"



class IChartiumLineChartItem : public ChartiumXYChart
{
    Q_OBJECT

public:
    explicit IChartiumLineChartItem(IChartiumLineSeries* series, QGraphicsItem* item = nullptr) :
        ChartiumXYChart(series, item)
    {
    }
    ~IChartiumLineChartItem() override = default;

    IChartiumLineChartItem(const IChartiumLineChartItem& another)            = delete;
    IChartiumLineChartItem& operator=(const IChartiumLineChartItem& another) = delete;
};
