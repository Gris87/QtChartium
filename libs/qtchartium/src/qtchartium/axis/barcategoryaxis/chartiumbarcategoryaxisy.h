#pragma once



#include "src/qtchartium/axis/barcategoryaxis/ichartiumbarcategoryaxisy.h"

#include "src/qtchartium/axis/barcategoryaxis/ichartiumbarcategoryaxis.h"



class ChartiumBarCategoryAxisY : public IChartiumBarCategoryAxisY
{
    Q_OBJECT

public:
    explicit ChartiumBarCategoryAxisY(
        IChartiumBarCategoryAxis* axis,
        IChartiumPresenter*       presenter,
        QGraphicsItem*            item   = nullptr,
        QGraphicsLayoutItem*      parent = nullptr
    );
    ~ChartiumBarCategoryAxisY() override;

    ChartiumBarCategoryAxisY(const ChartiumBarCategoryAxisY& another)            = delete;
    ChartiumBarCategoryAxisY& operator=(const ChartiumBarCategoryAxisY& another) = delete;

    QStringList createCategoryLabels(const QList<qreal>& layout) const override;

    QSizeF sizeHint(Qt::SizeHint which, const QSizeF& constraint) const override;

    QList<qreal> calculateLayout() const override;
    void         updateGeometry() override;

public slots:
    void handleCategoriesChanged() override;

protected:
    IChartiumBarCategoryAxis* mAxis;
};
