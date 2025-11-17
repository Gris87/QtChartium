#pragma once



#include <QObject>

#include <QGraphicsItem>

#include "src/qtchartium/domain/ichartiumdomain.h"
#include "src/qtchartium/ichartiumaxis.h"



class IChartiumChart;



class IChartiumSeries : public QObject
{
    Q_OBJECT

public:
    enum SeriesType
    {
        SeriesTypeLine,
        SeriesTypeArea,
        SeriesTypeBar,
        SeriesTypeStackedBar,
        SeriesTypePercentBar,
        SeriesTypePie,
        SeriesTypeScatter,
        SeriesTypeSpline,
        SeriesTypeHorizontalBar,
        SeriesTypeHorizontalStackedBar,
        SeriesTypeHorizontalPercentBar,
        SeriesTypeBoxPlot,
        SeriesTypeCandlestick
    };

    IChartiumSeries()          = default;
    virtual ~IChartiumSeries() = default;

    IChartiumSeries(const IChartiumSeries& another)            = delete;
    IChartiumSeries& operator=(const IChartiumSeries& another) = delete;

    virtual SeriesType type() const = 0;

    virtual void    setName(const QString& name) = 0;
    virtual QString name() const                 = 0;

    virtual void setVisible(bool visible = true) = 0;
    virtual bool isVisible() const               = 0;

    virtual qreal opacity() const           = 0;
    virtual void  setOpacity(qreal opacity) = 0;

    virtual IChartiumChart* chart() const                   = 0;
    virtual void            setChart(IChartiumChart* chart) = 0;

    virtual bool                  attachAxis(IChartiumAxis* axis) = 0;
    virtual bool                  detachAxis(IChartiumAxis* axis) = 0;
    virtual QList<IChartiumAxis*> attachedAxes()                  = 0;

    virtual void show() = 0;
    virtual void hide() = 0;

    virtual void initializeDomain()                        = 0;
    virtual void initializeAxes()                          = 0;
    virtual void initializeGraphics(QGraphicsItem* parent) = 0;

    virtual IChartiumAxis::AxisType defaultAxisType(Qt::Orientation) const   = 0;
    virtual IChartiumAxis*          createDefaultAxis(Qt::Orientation) const = 0;

    virtual void             setDomain(IChartiumDomain* domain) = 0;
    virtual IChartiumDomain* domain()                           = 0;

signals:
    void nameChanged();
    void visibleChanged();
    void opacityChanged();
};
