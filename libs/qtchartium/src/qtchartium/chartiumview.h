#pragma once



#include "src/qtchartium/ichartiumview.h"



class ChartiumView : public IChartiumView
{
    Q_OBJECT

public:
    explicit ChartiumView(QWidget* parent = nullptr);
    ~ChartiumView() override;

    ChartiumView(const ChartiumView& another)            = delete;
    ChartiumView& operator=(const ChartiumView& another) = delete;

    void setChart(IChartiumChart* chart) override;
};
