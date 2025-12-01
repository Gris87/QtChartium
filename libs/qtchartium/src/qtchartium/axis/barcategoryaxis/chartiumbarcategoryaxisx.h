#pragma once



#include "src/qtchartium/axis/barcategoryaxis/ichartiumbarcategoryaxisx.h"

#include "src/qtchartium/axis/barcategoryaxis/ichartiumbarcategoryaxis.h"



class ChartiumBarCategoryAxisX : public IChartiumBarCategoryAxisX
{
    Q_OBJECT

public:
    explicit ChartiumBarCategoryAxisX(
        IChartiumBarCategoryAxis* axis,
        IChartiumPresenter*       presenter,
        QGraphicsItem*            item   = nullptr,
        QGraphicsLayoutItem*      parent = nullptr
    );
    ~ChartiumBarCategoryAxisX() override;

    ChartiumBarCategoryAxisX(const ChartiumBarCategoryAxisX& another)            = delete;
    ChartiumBarCategoryAxisX& operator=(const ChartiumBarCategoryAxisX& another) = delete;

    QStringList createCategoryLabels(const QList<qreal>& layout) const override;

    QSizeF sizeHint(Qt::SizeHint which, const QSizeF& constraint) const override;

    QList<qreal> calculateLayout() const override;
    void         updateGeometry() override;

public slots:
    void handleCategoriesChanged() override;

protected:
    IChartiumBarCategoryAxis* mAxis;
};
