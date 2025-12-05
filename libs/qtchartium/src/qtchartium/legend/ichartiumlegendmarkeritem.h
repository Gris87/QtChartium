#pragma once



class IChartiumLegendMarkerItem
{
public:
    explicit IChartiumLegendMarkerItem() = default;
    virtual ~IChartiumLegendMarkerItem() = default;

    IChartiumLegendMarkerItem(const IChartiumLegendMarkerItem& another)            = delete;
    IChartiumLegendMarkerItem& operator=(const IChartiumLegendMarkerItem& another) = delete;
};
