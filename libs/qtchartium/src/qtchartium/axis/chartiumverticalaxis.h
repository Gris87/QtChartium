#pragma once



#include "src/qtchartium/axis/ichartiumverticalaxis.h"



class ChartiumVerticalAxis : public IChartiumVerticalAxis
{
    Q_OBJECT

public:
    explicit ChartiumVerticalAxis(
        IChartiumAxis*       axis,
        IChartiumPresenter*  presenter,
        bool                 intervalAxis = false,
        QGraphicsItem*       item         = nullptr,
        QGraphicsLayoutItem* parent       = nullptr
    );
    ~ChartiumVerticalAxis() override;

    ChartiumVerticalAxis(const ChartiumVerticalAxis& another)            = delete;
    ChartiumVerticalAxis& operator=(const ChartiumVerticalAxis& another) = delete;

    void updateMinorTickGeometry() override;

    QSizeF sizeHint(Qt::SizeHint which, const QSizeF& constraint = QSizeF()) const override;

    void updateGeometry() override;

protected:
    IChartiumPresenter* mPresenter;
};
