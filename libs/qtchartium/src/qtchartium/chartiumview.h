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

    IChartiumChart* chart() override;
    void setChart(IChartiumChart* chart) override;

    void resize() override;

protected:
    void resizeEvent(QResizeEvent* event) override;

private:
    QGraphicsScene* mScene;
    IChartiumChart* mChart;
};
