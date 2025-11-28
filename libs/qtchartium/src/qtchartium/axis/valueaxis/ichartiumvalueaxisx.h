#pragma once



#include "src/qtchartium/axis/chartiumhorizontalaxis.h"



class IChartiumValueAxisX : public ChartiumHorizontalAxis
{
    Q_OBJECT

public:
    explicit IChartiumValueAxisX(
        IChartiumAxis* axis, IChartiumPresenter* presenter, QGraphicsItem* item = nullptr, QGraphicsLayoutItem* parent = nullptr
    ) :
        ChartiumHorizontalAxis(axis, presenter, false, item, parent)
    {
    }
    ~IChartiumValueAxisX() override = default;

    IChartiumValueAxisX(const IChartiumValueAxisX& another)            = delete;
    IChartiumValueAxisX& operator=(const IChartiumValueAxisX& another) = delete;
};
