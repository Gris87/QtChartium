#pragma once



#include "src/qtchartium/axis/ichartiumlinearrowitem.h"



class IChartiumAxisElement;



class ChartiumLineArrowItem : public IChartiumLineArrowItem
{
public:
    explicit ChartiumLineArrowItem(IChartiumAxisElement* axis, QGraphicsItem* parent = nullptr);
    ~ChartiumLineArrowItem() override;

    ChartiumLineArrowItem(const ChartiumLineArrowItem& another)            = delete;
    ChartiumLineArrowItem& operator=(const ChartiumLineArrowItem& another) = delete;
};
