#pragma once



#include "src/qtchartium/legend/ichartiumlegendmoveresizehandler.h"



class ChartiumLegendMoveResizeHandler : public IChartiumLegendMoveResizeHandler
{
public:
    explicit ChartiumLegendMoveResizeHandler();
    ~ChartiumLegendMoveResizeHandler() override;

    ChartiumLegendMoveResizeHandler(const ChartiumLegendMoveResizeHandler& another)            = delete;
    ChartiumLegendMoveResizeHandler& operator=(const ChartiumLegendMoveResizeHandler& another) = delete;
};
