#pragma once



#include "src/qtchartium/axis/ichartiumhorizontalaxis.h"



class ChartiumHorizontalAxis : public IChartiumHorizontalAxis
{
    Q_OBJECT

public:
    explicit ChartiumHorizontalAxis(
        IChartiumAxis*       axis,
        IChartiumPresenter*  presenter,
        bool                 intervalAxis = false,
        QGraphicsItem*       item         = nullptr,
        QGraphicsLayoutItem* parent       = nullptr
    );
    ~ChartiumHorizontalAxis() override;

    ChartiumHorizontalAxis(const ChartiumHorizontalAxis& another)            = delete;
    ChartiumHorizontalAxis& operator=(const ChartiumHorizontalAxis& another) = delete;

    void updateMinorTickGeometry() override;

    QSizeF sizeHint(Qt::SizeHint which, const QSizeF& constraint = QSizeF()) const override;

    void updateGeometry() override;

protected:
    IChartiumPresenter* mPresenter;
};
