#pragma once



#include "src/qtchartium/ichartiumthememanager.h"



class ChartiumThemeManager : public IChartiumThemeManager
{
public:
    explicit ChartiumThemeManager(IChartiumChart* chart);
    ~ChartiumThemeManager() override;

    ChartiumThemeManager(const ChartiumThemeManager& another)            = delete;
    ChartiumThemeManager& operator=(const ChartiumThemeManager& another) = delete;

    void                        setTheme(IChartiumChart::ChartTheme theme) override;
    IChartiumTheme*             theme() const override;
    void                        decorateChart(IChartiumChart* chart, IChartiumTheme* theme) const override;
    void                        decorateLegend(IChartiumLegend* legend, IChartiumTheme* theme) const override;
    void                        updateSeries(IChartiumSeries* series) override;
    QMap<IChartiumSeries*, int> seriesMap() const override;

    QList<QGradient> generateSeriesGradients(const QList<QColor>& colors) override;
    QColor           colorAt(const QColor& start, const QColor& end, qreal pos) override;
    QColor           colorAt(const QGradient& gradient, qreal pos) override;

    int createIndexKey(const QList<int>& keys) const override;
    int seriesCount(IChartiumSeries::SeriesType type) const override;

public slots:
    void handleSeriesAdded(IChartiumSeries* series) override;
    void handleSeriesRemoved(IChartiumSeries* series) override;
    void handleAxisAdded(IChartiumAxis* axis) override;
    void handleAxisRemoved(IChartiumAxis* axis) override;

protected:
    IChartiumChart*                mChart;
    QScopedPointer<IChartiumTheme> mTheme;
    QMap<IChartiumSeries*, int>    mSeriesMap;
    QList<IChartiumAxis*>          mAxisList;
};
