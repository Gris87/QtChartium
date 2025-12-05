#pragma once



class IChartiumLegendMoveResizeHandler
{
public:
    explicit IChartiumLegendMoveResizeHandler() = default;
    virtual ~IChartiumLegendMoveResizeHandler() = default;

    IChartiumLegendMoveResizeHandler(const IChartiumLegendMoveResizeHandler& another)            = delete;
    IChartiumLegendMoveResizeHandler& operator=(const IChartiumLegendMoveResizeHandler& another) = delete;
};
