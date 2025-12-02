#pragma once



#include "src/qtchartium/charts/linechart/ichartiumlinechartitem.h"



class ChartiumLineChartItem : public IChartiumLineChartItem
{
    Q_OBJECT

public:
    explicit ChartiumLineChartItem(IChartiumLineSeries* series, QGraphicsItem* item = nullptr);
    ~ChartiumLineChartItem() override;

    ChartiumLineChartItem(const ChartiumLineChartItem& another)            = delete;
    ChartiumLineChartItem& operator=(const ChartiumLineChartItem& another) = delete;
};
