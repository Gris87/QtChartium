#pragma once



#include "src/qtchartium/axis/chartiumaxis.h"



class IChartiumValueAxis : public ChartiumAxis
{
    Q_OBJECT

public:
    enum TickType
    {
        TicksDynamic = 0,
        TicksFixed
    };

    explicit IChartiumValueAxis(QObject* parent = nullptr) :
        ChartiumAxis(parent)
    {
    }
    ~IChartiumValueAxis() override = default;

    IChartiumValueAxis(const IChartiumValueAxis& another)            = delete;
    IChartiumValueAxis& operator=(const IChartiumValueAxis& another) = delete;

    virtual void  setTickAnchor(qreal anchor)      = 0;
    virtual qreal tickAnchor() const               = 0;
    virtual void  setTickInterval(qreal insterval) = 0;
    virtual qreal tickInterval() const             = 0;
};
