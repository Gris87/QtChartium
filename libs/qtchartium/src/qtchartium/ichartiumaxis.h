#pragma once



class IChartiumAxis
{
public:
    enum AxisType
    {
        AxisTypeNoAxis      = 0x0,
        AxisTypeValue       = 0x1,
        AxisTypeBarCategory = 0x2,
        AxisTypeCategory    = 0x4,
        AxisTypeDateTime    = 0x8,
        AxisTypeLogValue    = 0x10,
        AxisTypeColor       = 0x20
    };

    IChartiumAxis()          = default;
    virtual ~IChartiumAxis() = default;

    IChartiumAxis(const IChartiumAxis& another)            = delete;
    IChartiumAxis& operator=(const IChartiumAxis& another) = delete;
};
