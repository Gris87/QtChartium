#pragma once



#include "src/qtchartium/charts/linechart/ichartiumlineseries.h"



class ChartiumLineSeries : public IChartiumLineSeries
{
    Q_OBJECT

public:
    explicit ChartiumLineSeries(QObject* parent = nullptr);
    ~ChartiumLineSeries() override;

    ChartiumLineSeries(const ChartiumLineSeries& another)            = delete;
    ChartiumLineSeries& operator=(const ChartiumLineSeries& another) = delete;

    SeriesType type() const override;

    void initializeGraphics(QGraphicsItem* parent) override;
    void initializeTheme(int index, IChartiumTheme* theme) override;
};
