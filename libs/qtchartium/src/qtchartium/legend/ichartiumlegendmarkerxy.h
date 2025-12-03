#pragma once



#include "src/qtchartium/legend/chartiumlegendmarker.h"



class IChartiumLegendMarkerXY : public ChartiumLegendMarker
{
    Q_OBJECT

public:
    explicit IChartiumLegendMarkerXY(QObject* parent = nullptr) :
        ChartiumLegendMarker(parent)
    {
    }
    ~IChartiumLegendMarkerXY() override = default;

    IChartiumLegendMarkerXY(const IChartiumLegendMarkerXY& another)            = delete;
    IChartiumLegendMarkerXY& operator=(const IChartiumLegendMarkerXY& another) = delete;
};
