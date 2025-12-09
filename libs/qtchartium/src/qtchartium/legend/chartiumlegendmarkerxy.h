#pragma once



#include "src/qtchartium/legend/ichartiumlegendmarkerxy.h"

#include "src/qtchartium/charts/xychart/ichartiumxyseries.h"



class ChartiumLegendMarkerXY : public IChartiumLegendMarkerXY
{
    Q_OBJECT

public:
    explicit ChartiumLegendMarkerXY(IChartiumXYSeries* series, IChartiumLegend* legend, QObject* parent = nullptr);
    ~ChartiumLegendMarkerXY() override;

    ChartiumLegendMarkerXY(const ChartiumLegendMarkerXY& another)            = delete;
    ChartiumLegendMarkerXY& operator=(const ChartiumLegendMarkerXY& another) = delete;

    LegendMarkerType type() override;

    IChartiumXYSeries* series() override;
    QObject*           relatedObject() override;

public slots:
    void updated() override;

protected:
    IChartiumXYSeries* mSeries;
};
