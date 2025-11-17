#pragma once



#include <QGraphicsView>

#include "src/qtchartium/ichartiumchart.h"



class IChartiumView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit IChartiumView(QWidget* parent = nullptr) :
        QGraphicsView(parent)
    {
    }
    ~IChartiumView() override = default;

    IChartiumView(const IChartiumView& another)            = delete;
    IChartiumView& operator=(const IChartiumView& another) = delete;

    virtual IChartiumChart* chart()                         = 0;
    virtual void            setChart(IChartiumChart* chart) = 0;

    virtual void resize() = 0;
};
