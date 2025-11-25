#pragma once



#include "src/qtchartium/legend/ichartiumlegendscroller.h"



class ChartiumLegendScroller : public IChartiumLegendScroller
{
    Q_OBJECT

public:
    explicit ChartiumLegendScroller(
        IChartiumChart* chart, QGraphicsItem* parent = nullptr, Qt::WindowFlags wFlags = Qt::WindowFlags()
    );
    ~ChartiumLegendScroller() override;

    ChartiumLegendScroller(const ChartiumLegendScroller& another)            = delete;
    ChartiumLegendScroller& operator=(const ChartiumLegendScroller& another) = delete;
};
