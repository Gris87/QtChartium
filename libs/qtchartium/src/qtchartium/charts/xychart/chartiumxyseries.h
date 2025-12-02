#pragma once



#include "src/qtchartium/charts/xychart/ichartiumxyseries.h"



class ChartiumXYSeries : public IChartiumXYSeries
{
    Q_OBJECT

public:
    explicit ChartiumXYSeries(QObject* parent = nullptr);
    ~ChartiumXYSeries() override;

    ChartiumXYSeries(const ChartiumXYSeries& another)            = delete;
    ChartiumXYSeries& operator=(const ChartiumXYSeries& another) = delete;
};
