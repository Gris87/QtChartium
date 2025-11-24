#pragma once



#include "src/qtchartium/layout/ichartiumcartesianlayout.h"



class ChartiumCartesianLayout : public IChartiumCartesianLayout
{
public:
    explicit ChartiumCartesianLayout(IChartiumPresenter* presenter, QGraphicsLayoutItem* parent = nullptr);
    ~ChartiumCartesianLayout() override;

    ChartiumCartesianLayout(const ChartiumCartesianLayout& another)            = delete;
    ChartiumCartesianLayout& operator=(const ChartiumCartesianLayout& another) = delete;
};
