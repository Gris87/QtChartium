#pragma once



#include "src/qtchartium/layout/chartiumlayout.h"



class IChartiumCartesianLayout : public ChartiumLayout
{
public:
    explicit IChartiumCartesianLayout(IChartiumPresenter* presenter, QGraphicsLayoutItem* parent = nullptr) :
        ChartiumLayout(presenter, parent)
    {
    }
    ~IChartiumCartesianLayout() override = default;

    IChartiumCartesianLayout(const IChartiumCartesianLayout& another)            = delete;
    IChartiumCartesianLayout& operator=(const IChartiumCartesianLayout& another) = delete;
};
