#pragma once



#include <QGraphicsWidget>

#include "src/qtchartium/ichartiumaxis.h"
#include "src/qtchartium/ichartiumlegend.h"
#include "src/qtchartium/ichartiumseries.h"



class IChartiumChart : public QGraphicsWidget
{
    Q_OBJECT

public:
    explicit IChartiumChart(QGraphicsItem* parent = nullptr, Qt::WindowFlags wFlags = Qt::WindowFlags()) :
        QGraphicsWidget(parent, wFlags)
    {
    }
    virtual ~IChartiumChart() = default;

    IChartiumChart(const IChartiumChart& another)            = delete;
    IChartiumChart& operator=(const IChartiumChart& another) = delete;

    virtual void                    addSeries(IChartiumSeries* series)    = 0;
    virtual void                    removeSeries(IChartiumSeries* series) = 0;
    virtual void                    removeAllSeries()                     = 0;
    virtual QList<IChartiumSeries*> series()                              = 0;

    virtual void addAxis(IChartiumAxis* axis, Qt::Alignment alignment) = 0;
    virtual void removeAxis(IChartiumAxis* axis)                       = 0;
    virtual QList<IChartiumAxis*>
    axes(Qt::Orientations orientation = Qt::Horizontal | Qt::Vertical, IChartiumSeries* series = nullptr) = 0;

    virtual void createDefaultAxes() = 0;

    virtual IChartiumLegend* legend()                       = 0;
    virtual void             setTitle(const QString& title) = 0;
};
