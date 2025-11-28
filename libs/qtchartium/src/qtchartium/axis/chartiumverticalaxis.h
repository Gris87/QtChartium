#pragma once



#include "src/qtchartium/axis/iChartiumVerticalAxis.h"



class ChartiumVerticalAxis : public IChartiumVerticalAxis
{
    Q_OBJECT

public:
    explicit ChartiumVerticalAxis(
        IChartiumAxis*       axis,
        IChartiumPresenter*  presenter,
        bool                 intervalAxis = false,
        QGraphicsItem*       item         = nullptr,
        QGraphicsLayoutItem* parent       = nullptr
    );
    ~ChartiumVerticalAxis() override;

    ChartiumVerticalAxis(const ChartiumVerticalAxis& another)            = delete;
    ChartiumVerticalAxis& operator=(const ChartiumVerticalAxis& another) = delete;
};
