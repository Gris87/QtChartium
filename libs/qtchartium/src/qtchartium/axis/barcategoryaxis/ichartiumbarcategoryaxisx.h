#pragma once



#include "src/qtchartium/axis/chartiumhorizontalaxis.h"



class IChartiumBarCategoryAxisX : public ChartiumHorizontalAxis
{
    Q_OBJECT

public:
    explicit IChartiumBarCategoryAxisX(
        IChartiumAxis* axis, IChartiumPresenter* presenter, QGraphicsItem* item = nullptr, QGraphicsLayoutItem* parent = nullptr
    ) :
        ChartiumHorizontalAxis(axis, presenter, true, item, parent)
    {
    }
    ~IChartiumBarCategoryAxisX() override = default;

    IChartiumBarCategoryAxisX(const IChartiumBarCategoryAxisX& another)            = delete;
    IChartiumBarCategoryAxisX& operator=(const IChartiumBarCategoryAxisX& another) = delete;

    virtual QStringList createCategoryLabels(const QList<qreal>& layout) const = 0;

public slots:
    virtual void handleCategoriesChanged() = 0;
};
