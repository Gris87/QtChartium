#pragma once



#include "src/qtchartium/charts/chartiumseries.h"



class IChartiumXYSeries : public ChartiumSeries
{
    Q_OBJECT

public:
    explicit IChartiumXYSeries(QObject* parent = nullptr) :
        ChartiumSeries(parent)
    {
    }
    ~IChartiumXYSeries() override = default;

    IChartiumXYSeries(const IChartiumXYSeries& another)            = delete;
    IChartiumXYSeries& operator=(const IChartiumXYSeries& another) = delete;
};
