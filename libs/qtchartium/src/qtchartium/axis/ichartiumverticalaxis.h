#pragma once



#include "src/qtchartium/axis/chartiumcartesianaxis.h"



class IChartiumVerticalAxis : public ChartiumCartesianAxis
{
    Q_OBJECT

public:
    explicit IChartiumVerticalAxis(
        IChartiumAxis*       axis,
        IChartiumPresenter*  presenter,
        bool                 intervalAxis = false,
        QGraphicsItem*       item         = nullptr,
        QGraphicsLayoutItem* parent       = nullptr
    ) :
        ChartiumCartesianAxis(axis, presenter, intervalAxis, item, parent)
    {
    }
    ~IChartiumVerticalAxis() override = default;

    IChartiumVerticalAxis(const IChartiumVerticalAxis& another)            = delete;
    IChartiumVerticalAxis& operator=(const IChartiumVerticalAxis& another) = delete;
};
