#pragma once



#include "src/qtchartium/axis/chartiumhorizontalaxis.h"

#include "src/qtchartium/axis/valueaxis/ichartiumvalueaxis.h"



class IChartiumValueAxisX : public ChartiumHorizontalAxis
{
    Q_OBJECT

public:
    explicit IChartiumValueAxisX(
        IChartiumAxis* axis, IChartiumPresenter* presenter, QGraphicsItem* item = nullptr, QGraphicsLayoutItem* parent = nullptr
    ) :
        ChartiumHorizontalAxis(axis, presenter, false, item, parent)
    {
    }
    ~IChartiumValueAxisX() override = default;

    IChartiumValueAxisX(const IChartiumValueAxisX& another)            = delete;
    IChartiumValueAxisX& operator=(const IChartiumValueAxisX& another) = delete;

public slots:
    virtual void handleTickCountChanged(int tick)                         = 0;
    virtual void handleMinorTickCountChanged(int tick)                    = 0;
    virtual void handleLabelFormatChanged(const QString& format)          = 0;
    virtual void handleTickIntervalChanged(qreal interval)                = 0;
    virtual void handleTickAnchorChanged(qreal anchor)                    = 0;
    virtual void handleTickTypeChanged(IChartiumValueAxis::TickType type) = 0;
};
