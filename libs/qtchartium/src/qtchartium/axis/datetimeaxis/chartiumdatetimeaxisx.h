#pragma once



#include "src/qtchartium/axis/datetimeaxis/ichartiumdatetimeaxisx.h"



class ChartiumDateTimeAxisX : public IChartiumDateTimeAxisX
{
    Q_OBJECT

public:
    explicit ChartiumDateTimeAxisX(
        IChartiumAxis* axis, IChartiumPresenter* presenter, QGraphicsItem* item = nullptr, QGraphicsLayoutItem* parent = nullptr
    );
    ~ChartiumDateTimeAxisX() override;

    ChartiumDateTimeAxisX(const ChartiumDateTimeAxisX& another)            = delete;
    ChartiumDateTimeAxisX& operator=(const ChartiumDateTimeAxisX& another) = delete;
};
