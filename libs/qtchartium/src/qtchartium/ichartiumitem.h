#pragma once



#include "src/qtchartium/chartiumelement.h"



class IChartiumDomain;
class IChartiumSeries;



class IChartiumItem : public ChartiumElement
{
    Q_OBJECT

public:
    enum ChartItemTypes
    {
        AXIS_ITEM = UserType + 1,
        XYLINE_ITEM
    };

    explicit IChartiumItem(QGraphicsItem* item = nullptr) :
        ChartiumElement(item)
    {
    }
    ~IChartiumItem() override = default;

    IChartiumItem(const IChartiumItem& another)            = delete;
    IChartiumItem& operator=(const IChartiumItem& another) = delete;

    virtual IChartiumDomain* domain() const = 0;
    virtual void             cleanup()      = 0;

    virtual IChartiumSeries* seriesPrivate() const = 0;

public slots:
    virtual void handleDomainUpdated() = 0;
};
