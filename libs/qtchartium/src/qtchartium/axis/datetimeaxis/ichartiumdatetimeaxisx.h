#pragma once



#include "src/qtchartium/axis/chartiumhorizontalaxis.h"



class IChartiumDateTimeAxisX : public ChartiumHorizontalAxis
{
    Q_OBJECT

public:
    explicit IChartiumDateTimeAxisX(
        IChartiumAxis* axis, IChartiumPresenter* presenter, QGraphicsItem* item = nullptr, QGraphicsLayoutItem* parent = nullptr
    ) :
        ChartiumHorizontalAxis(axis, presenter, false, item, parent)
    {
    }
    ~IChartiumDateTimeAxisX() override = default;

    IChartiumDateTimeAxisX(const IChartiumDateTimeAxisX& another)            = delete;
    IChartiumDateTimeAxisX& operator=(const IChartiumDateTimeAxisX& another) = delete;

public slots:
    virtual void handleTickCountChanged(int tick)           = 0;
    virtual void handleFormatChanged(const QString& format) = 0;
};
