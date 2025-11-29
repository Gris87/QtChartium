#pragma once



#include "src/qtchartium/axis/chartiumcartesianaxis.h"



class IChartiumHorizontalAxis : public ChartiumCartesianAxis
{
    Q_OBJECT

public:
    explicit IChartiumHorizontalAxis(
        IChartiumAxis*       axis,
        IChartiumPresenter*  presenter,
        bool                 intervalAxis = false,
        QGraphicsItem*       item         = nullptr,
        QGraphicsLayoutItem* parent       = nullptr
    ) :
        ChartiumCartesianAxis(axis, presenter, intervalAxis, item, parent)
    {
    }
    ~IChartiumHorizontalAxis() override = default;

    IChartiumHorizontalAxis(const IChartiumHorizontalAxis& another)            = delete;
    IChartiumHorizontalAxis& operator=(const IChartiumHorizontalAxis& another) = delete;

    virtual void updateMinorTickGeometry() = 0;
};
