#pragma once



#include "src/qtchartium/ichartiumitem.h"

#include "src/qtchartium/charts/ichartiumseries.h"



class ChartiumItem : public IChartiumItem
{
    Q_OBJECT

public:
    explicit ChartiumItem(IChartiumSeries* series, QGraphicsItem* item = nullptr);
    ~ChartiumItem() override;

    ChartiumItem(const ChartiumItem& another)            = delete;
    ChartiumItem& operator=(const ChartiumItem& another) = delete;

    IChartiumDomain* domain() const override;
    void             cleanup() override;

    IChartiumSeries* seriesPrivate() const override;

public slots:
    void handleDomainUpdated() override;

protected:
    bool             mValidData;
    IChartiumSeries* mSeries;
};
