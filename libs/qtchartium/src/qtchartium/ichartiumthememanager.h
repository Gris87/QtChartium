#pragma once



#include <QObject>

#include "src/qtchartium/axis/ichartiumaxis.h"
#include "src/qtchartium/ichartiumchart.h"
#include "src/qtchartium/ichartiumseries.h"
#include "src/qtchartium/legend/ichartiumlegend.h"
#include "src/qtchartium/themes/ichartiumtheme.h"



class IChartiumThemeManager : public QObject
{
    Q_OBJECT

public:
    enum BackgroundShadesMode
    {
        BackgroundShadesNone,
        BackgroundShadesVertical,
        BackgroundShadesHorizontal,
        BackgroundShadesBoth
    };

    explicit IChartiumThemeManager(QObject* parent = nullptr) :
        QObject(parent)
    {
    }
    ~IChartiumThemeManager() override = default;

    IChartiumThemeManager(const IChartiumThemeManager& another)            = delete;
    IChartiumThemeManager& operator=(const IChartiumThemeManager& another) = delete;

    virtual void                        setTheme(IChartiumChart::ChartTheme theme)                           = 0;
    virtual IChartiumTheme*             theme() const                                                        = 0;
    virtual void                        decorateChart(IChartiumChart* chart, IChartiumTheme* theme) const    = 0;
    virtual void                        decorateLegend(IChartiumLegend* legend, IChartiumTheme* theme) const = 0;
    virtual void                        updateSeries(IChartiumSeries* series)                                = 0;
    virtual QMap<IChartiumSeries*, int> seriesMap() const                                                    = 0;

    virtual QList<QGradient> generateSeriesGradients(const QList<QColor>& colors)       = 0;
    virtual QColor           colorAt(const QColor& start, const QColor& end, qreal pos) = 0;
    virtual QColor           colorAt(const QGradient& gradient, qreal pos)              = 0;

    virtual int createIndexKey(const QList<int>& keys) const        = 0;
    virtual int seriesCount(IChartiumSeries::SeriesType type) const = 0;

public slots:
    virtual void handleSeriesAdded(IChartiumSeries* series)   = 0;
    virtual void handleSeriesRemoved(IChartiumSeries* series) = 0;
    virtual void handleAxisAdded(IChartiumAxis* axis)         = 0;
    virtual void handleAxisRemoved(IChartiumAxis* axis)       = 0;
};
