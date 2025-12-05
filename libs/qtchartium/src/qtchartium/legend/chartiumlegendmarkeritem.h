#pragma once



#include "src/qtchartium/legend/ichartiumlegendmarkeritem.h"



class ChartiumLegendMarkerItem : public IChartiumLegendMarkerItem
{
public:
    explicit ChartiumLegendMarkerItem();
    ~ChartiumLegendMarkerItem() override;

    ChartiumLegendMarkerItem(const ChartiumLegendMarkerItem& another)            = delete;
    ChartiumLegendMarkerItem& operator=(const ChartiumLegendMarkerItem& another) = delete;
};
