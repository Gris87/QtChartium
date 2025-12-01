#pragma once



#include "src/qtchartium/axis/chartiumverticalaxis.h"



class IChartiumBarCategoryAxisY : public ChartiumVerticalAxis
{
    Q_OBJECT

public:
    explicit IChartiumBarCategoryAxisY(
        IChartiumAxis* axis, IChartiumPresenter* presenter, QGraphicsItem* item = nullptr, QGraphicsLayoutItem* parent = nullptr
    ) :
        ChartiumVerticalAxis(axis, presenter, true, item, parent)
    {
    }
    ~IChartiumBarCategoryAxisY() override = default;

    IChartiumBarCategoryAxisY(const IChartiumBarCategoryAxisY& another)            = delete;
    IChartiumBarCategoryAxisY& operator=(const IChartiumBarCategoryAxisY& another) = delete;

    virtual QStringList createCategoryLabels(const QList<qreal>& layout) const = 0;

public slots:
    virtual void handleCategoriesChanged() = 0;
};
