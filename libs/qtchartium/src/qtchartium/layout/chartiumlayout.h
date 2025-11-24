#pragma once



#include "src/qtchartium/layout/ichartiumlayout.h"



class IChartiumPresenter;



class ChartiumLayout : public IChartiumLayout
{
public:
    explicit ChartiumLayout(IChartiumPresenter* presenter, QGraphicsLayoutItem* parent = nullptr);
    ~ChartiumLayout() override;

    ChartiumLayout(const ChartiumLayout& another)            = delete;
    ChartiumLayout& operator=(const ChartiumLayout& another) = delete;

    void     setMargins(const QMargins& margins) override;
    QMargins margins() const override;

    void setGeometry(const QRectF& rect) override;

    QRectF
    calculateBackgroundGeometry(const QRectF& geometry, IChartiumBackground* background, bool update = true) const override;
    QRectF calculateBackgroundMinimum(const QRectF& minimum) const override;
    QRectF calculateContentGeometry(const QRectF& geometry) const override;
    QRectF calculateContentMinimum(const QRectF& minimum) const override;
    QRectF calculateTitleGeometry(const QRectF& geometry, IChartiumTitle* title, bool update = true) const override;
    QRectF calculateTitleMinimum(const QRectF& minimum, IChartiumTitle* title) const override;
    QRectF calculateLegendGeometry(const QRectF& geometry, IChartiumLegend* legend, bool update = true) const override;
    QRectF calculateLegendMinimum(const QRectF& minimum, IChartiumLegend* legend) const override;

    QRectF
    calculateAxisGeometry(const QRectF& geometry, const QList<IChartiumAxisElement*>& axes, bool update = true) const override;
    QRectF calculateAxisMinimum(const QRectF& minimum, const QList<IChartiumAxisElement*>& axes) const override;

    QSizeF sizeHint(Qt::SizeHint which, const QSizeF& constraint = QSizeF()) const override;
    int    count() const override;
    QGraphicsLayoutItem* itemAt(int i) const override;
    void   removeAt(int) override;

protected:
    IChartiumPresenter* mPresenter;
    QMargins            mMargins;
    QRectF              mMinAxisRect;
};
