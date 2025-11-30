#pragma once



#include "src/qtchartium/axis/chartiumverticalaxis.h"

#include "src/qtchartium/axis/valueaxis/ichartiumvalueaxis.h"



class IChartiumValueAxisY : public ChartiumVerticalAxis
{
    Q_OBJECT

public:
    explicit IChartiumValueAxisY(
        IChartiumAxis* axis, IChartiumPresenter* presenter, QGraphicsItem* item = nullptr, QGraphicsLayoutItem* parent = nullptr
    ) :
        ChartiumVerticalAxis(axis, presenter, false, item, parent)
    {
    }
    ~IChartiumValueAxisY() override = default;

    IChartiumValueAxisY(const IChartiumValueAxisY& another)            = delete;
    IChartiumValueAxisY& operator=(const IChartiumValueAxisY& another) = delete;

public slots:
    virtual void handleTickCountChanged(int tick)                         = 0;
    virtual void handleMinorTickCountChanged(int tick)                    = 0;
    virtual void handleLabelFormatChanged(const QString& format)          = 0;
    virtual void handleTickIntervalChanged(qreal interval)                = 0;
    virtual void handleTickAnchorChanged(qreal anchor)                    = 0;
    virtual void handleTickTypeChanged(IChartiumValueAxis::TickType type) = 0;
};
