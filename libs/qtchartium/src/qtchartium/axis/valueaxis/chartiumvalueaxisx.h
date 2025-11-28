#pragma once



#include "src/qtchartium/axis/valueaxis/ichartiumvalueaxisx.h"



class ChartiumValueAxisX : public IChartiumValueAxisX
{
    Q_OBJECT

public:
    explicit ChartiumValueAxisX(
        IChartiumAxis* axis, IChartiumPresenter* presenter, QGraphicsItem* item = nullptr, QGraphicsLayoutItem* parent = nullptr
    );
    ~ChartiumValueAxisX() override;

    ChartiumValueAxisX(const ChartiumValueAxisX& another)            = delete;
    ChartiumValueAxisX& operator=(const ChartiumValueAxisX& another) = delete;
};
