#pragma once



#include "src/qtchartium/axis/valueaxis/ichartiumvalueaxisy.h"



class ChartiumValueAxisY : public IChartiumValueAxisY
{
    Q_OBJECT

public:
    explicit ChartiumValueAxisY(
        IChartiumAxis* axis, IChartiumPresenter* presenter, QGraphicsItem* item = nullptr, QGraphicsLayoutItem* parent = nullptr
    );
    ~ChartiumValueAxisY() override;

    ChartiumValueAxisY(const ChartiumValueAxisY& another)            = delete;
    ChartiumValueAxisY& operator=(const ChartiumValueAxisY& another) = delete;
};
