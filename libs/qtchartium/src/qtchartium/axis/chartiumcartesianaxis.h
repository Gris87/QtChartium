#pragma once



#include "src/qtchartium/axis/ichartiumcartesianaxis.h"



class ChartiumCartesianAxis : public IChartiumCartesianAxis
{
    Q_OBJECT

public:
    explicit ChartiumCartesianAxis(
        IChartiumAxis*       axis,
        IChartiumPresenter*  presenter,
        bool                 intervalAxis = false,
        QGraphicsItem*       item         = nullptr,
        QGraphicsLayoutItem* parent       = nullptr
    );
    ~ChartiumCartesianAxis() override;

    ChartiumCartesianAxis(const ChartiumCartesianAxis& another)            = delete;
    ChartiumCartesianAxis& operator=(const ChartiumCartesianAxis& another) = delete;
};
