#pragma once



#include <QGraphicsWidget>

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

    virtual IChartiumLegend* legend()                           = 0;
    virtual void             addSeries(IChartiumSeries* series) = 0;
    virtual void             createDefaultAxes()                = 0;
    virtual void             setTitle(const QString& title)     = 0;
};
