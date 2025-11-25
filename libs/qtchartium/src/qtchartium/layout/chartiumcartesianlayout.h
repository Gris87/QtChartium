#pragma once



#include "src/qtchartium/layout/ichartiumcartesianlayout.h"

#include "src/qtchartium/ichartiumpresenter.h"



class ChartiumCartesianLayout : public IChartiumCartesianLayout
{
public:
    explicit ChartiumCartesianLayout(IChartiumPresenter* presenter, QGraphicsLayoutItem* parent = nullptr);
    ~ChartiumCartesianLayout() override;

    ChartiumCartesianLayout(const ChartiumCartesianLayout& another)            = delete;
    ChartiumCartesianLayout& operator=(const ChartiumCartesianLayout& another) = delete;

    QRectF
    calculateAxisGeometry(const QRectF& geometry, const QList<IChartiumAxisElement*>& axes, bool update = true) const override;
    QRectF calculateAxisMinimum(const QRectF& minimum, const QList<IChartiumAxisElement*>& axes) const override;
};
