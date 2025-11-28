#pragma once



#include "src/qtchartium/axis/chartiumverticalaxis.h"



class IChartiumValueAxisY : public ChartiumVerticalAxis
{
    Q_OBJECT

public:
    explicit IChartiumValueAxisY(
        IChartiumAxis* axis, IChartiumPresenter* presenter, QGraphicsItem* item = nullptr, QGraphicsLayoutItem* parent = nullptr
    ) :
        ChartiumVerticalAxis(axis, presenter, false, item, parent)
    {
    }
    ~IChartiumValueAxisY() override = default;

    IChartiumValueAxisY(const IChartiumValueAxisY& another)            = delete;
    IChartiumValueAxisY& operator=(const IChartiumValueAxisY& another) = delete;
};
