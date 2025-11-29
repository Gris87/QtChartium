#pragma once



#include "src/qtchartium/axis/datetimeaxis/ichartiumdatetimeaxisy.h"



class ChartiumDateTimeAxisY : public IChartiumDateTimeAxisY
{
    Q_OBJECT

public:
    explicit ChartiumDateTimeAxisY(
        IChartiumAxis* axis, IChartiumPresenter* presenter, QGraphicsItem* item = nullptr, QGraphicsLayoutItem* parent = nullptr
    );
    ~ChartiumDateTimeAxisY() override;

    ChartiumDateTimeAxisY(const ChartiumDateTimeAxisY& another)            = delete;
    ChartiumDateTimeAxisY& operator=(const ChartiumDateTimeAxisY& another) = delete;
};
