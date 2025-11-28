#pragma once



#include "src/qtchartium/axis/chartiumaxiselement.h"



class IChartiumCartesianAxis : public ChartiumAxisElement
{
    Q_OBJECT

public:
    explicit IChartiumCartesianAxis(
        IChartiumAxis*       axis,
        IChartiumPresenter*  presenter,
        bool                 intervalAxis = false,
        QGraphicsItem*       item         = nullptr,
        QGraphicsLayoutItem* parent       = nullptr
    ) :
        ChartiumAxisElement(axis, presenter, intervalAxis, item, parent)
    {
    }
    ~IChartiumCartesianAxis() override = default;

    IChartiumCartesianAxis(const IChartiumCartesianAxis& another)            = delete;
    IChartiumCartesianAxis& operator=(const IChartiumCartesianAxis& another) = delete;
};
