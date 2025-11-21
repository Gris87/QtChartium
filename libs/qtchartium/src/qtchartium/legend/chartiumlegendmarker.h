#pragma once



#include "src/qtchartium/legend/ichartiumlegendmarker.h"



class ChartiumLegendMarker : public IChartiumLegendMarker
{
    Q_OBJECT

public:
    explicit ChartiumLegendMarker(QObject* parent = nullptr);
    ~ChartiumLegendMarker() override;

    ChartiumLegendMarker(const ChartiumLegendMarker& another)            = delete;
    ChartiumLegendMarker& operator=(const ChartiumLegendMarker& another) = delete;
};
