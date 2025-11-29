#pragma once



#include "src/qtchartium/axis/chartiumaxiselement.h"



class IChartiumValueAxis;



class IChartiumCartesianAxis : public ChartiumAxisElement
{
    Q_OBJECT

public:
    explicit IChartiumCartesianAxis(
        IChartiumAxis*       axis,
        IChartiumPresenter*  presenter,
        bool                 intervalAxis = false,
        QGraphicsItem*       item         = nullptr,
        QGraphicsLayoutItem* parent       = nullptr
    ) :
        ChartiumAxisElement(axis, presenter, intervalAxis, item, parent)
    {
    }
    ~IChartiumCartesianAxis() override = default;

    IChartiumCartesianAxis(const IChartiumCartesianAxis& another)            = delete;
    IChartiumCartesianAxis& operator=(const IChartiumCartesianAxis& another) = delete;

    virtual void setDateTimeLabelsFormat(const QString& format) = 0;

    virtual void updateLabelsValues(IChartiumValueAxis* axis) = 0;
    virtual void updateLabelsDateTimes()                      = 0;

    virtual void createItems(int count) = 0;
    virtual void deleteItems(int count) = 0;
    virtual void updateMinorTickItems() = 0;
};
