#pragma once



#include "src/qtchartium/legend/chartiumlegend.h"



class IChartiumLegendScroller : public ChartiumLegend
{
    Q_OBJECT

public:
    explicit IChartiumLegendScroller(
        IChartiumChart* chart, QGraphicsItem* parent = nullptr, Qt::WindowFlags wFlags = Qt::WindowFlags()
    ) :
        ChartiumLegend(chart, parent, wFlags)
    {
    }
    ~IChartiumLegendScroller() override = default;

    IChartiumLegendScroller(const IChartiumLegendScroller& another)            = delete;
    IChartiumLegendScroller& operator=(const IChartiumLegendScroller& another) = delete;
};
