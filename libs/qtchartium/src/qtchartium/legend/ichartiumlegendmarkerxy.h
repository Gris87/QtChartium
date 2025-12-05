#pragma once



#include "src/qtchartium/legend/chartiumlegendmarker.h"



class IChartiumLegendMarkerXY : public ChartiumLegendMarker
{
    Q_OBJECT

public:
    explicit IChartiumLegendMarkerXY(IChartiumLegend* legend, QObject* parent = nullptr) :
        ChartiumLegendMarker(legend, parent)
    {
    }
    ~IChartiumLegendMarkerXY() override = default;

    IChartiumLegendMarkerXY(const IChartiumLegendMarkerXY& another)            = delete;
    IChartiumLegendMarkerXY& operator=(const IChartiumLegendMarkerXY& another) = delete;
};
