#pragma once



#include "src/qtchartium/ichartiumchart.h"

#include "src/qtchartium/chartiumlegend.h"



class ChartiumChart : public IChartiumChart
{
public:
    explicit ChartiumChart(QGraphicsItem* parent = nullptr, Qt::WindowFlags wFlags = Qt::WindowFlags());
    ~ChartiumChart() override;

    ChartiumChart(const ChartiumChart& another)            = delete;
    ChartiumChart& operator=(const ChartiumChart& another) = delete;

    void                    addSeries(IChartiumSeries* series) override;
    void                    removeSeries(IChartiumSeries* series) override;
    void                    removeAllSeries() override;
    QList<IChartiumSeries*> series() override;

    void addAxis(IChartiumAxis* axis, Qt::Alignment alignment) override;
    void removeAxis(IChartiumAxis* axis) override;
    QList<IChartiumAxis*>
    axes(Qt::Orientations orientation = Qt::Horizontal | Qt::Vertical, IChartiumSeries* series = nullptr) override;

    void createDefaultAxes() override;

    IChartiumLegend* legend() override;
    void             setTitle(const QString& title) override;

private:
    ChartiumLegend*         mLegend;
    QList<IChartiumSeries*> mSeries;
    QList<IChartiumAxis*>   mAxes;
};
