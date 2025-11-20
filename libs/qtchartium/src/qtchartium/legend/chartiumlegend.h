#pragma once



#include "src/qtchartium/legend/ichartiumlegend.h"



class ChartiumLegend : public IChartiumLegend
{
    Q_OBJECT

public:
    explicit ChartiumLegend(QObject* parent = nullptr);
    ~ChartiumLegend() override;

    ChartiumLegend(const ChartiumLegend& another)            = delete;
    ChartiumLegend& operator=(const ChartiumLegend& another) = delete;

    void hide() override;
};
