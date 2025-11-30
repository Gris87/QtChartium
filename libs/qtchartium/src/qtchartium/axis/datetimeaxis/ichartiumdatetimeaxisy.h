#pragma once



#include "src/qtchartium/axis/chartiumverticalaxis.h"



class IChartiumDateTimeAxisY : public ChartiumVerticalAxis
{
    Q_OBJECT

public:
    explicit IChartiumDateTimeAxisY(
        IChartiumAxis* axis, IChartiumPresenter* presenter, QGraphicsItem* item = nullptr, QGraphicsLayoutItem* parent = nullptr
    ) :
        ChartiumVerticalAxis(axis, presenter, false, item, parent)
    {
    }
    ~IChartiumDateTimeAxisY() override = default;

    IChartiumDateTimeAxisY(const IChartiumDateTimeAxisY& another)            = delete;
    IChartiumDateTimeAxisY& operator=(const IChartiumDateTimeAxisY& another) = delete;

public slots:
    virtual void handleTickCountChanged(int tick)           = 0;
    virtual void handleFormatChanged(const QString& format) = 0;
};
