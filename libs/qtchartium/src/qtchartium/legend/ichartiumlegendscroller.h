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

    virtual void handleInteractiveChanged(bool interactive) = 0;
    virtual void updateForResizerChange()                   = 0;

public slots:
    virtual void handleDetached(bool attached) = 0;
};
