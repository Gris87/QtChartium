#pragma once



#include "src/qtchartium/axis/valueaxis/ichartiumvalueaxisy.h"



class ChartiumValueAxisY : public IChartiumValueAxisY
{
    Q_OBJECT

public:
    explicit ChartiumValueAxisY(
        IChartiumValueAxis*  axis,
        IChartiumPresenter*  presenter,
        QGraphicsItem*       item   = nullptr,
        QGraphicsLayoutItem* parent = nullptr
    );
    ~ChartiumValueAxisY() override;

    ChartiumValueAxisY(const ChartiumValueAxisY& another)            = delete;
    ChartiumValueAxisY& operator=(const ChartiumValueAxisY& another) = delete;

    QSizeF sizeHint(Qt::SizeHint which, const QSizeF& constraint) const override;

    QList<qreal> calculateLayout() const override;
    void         updateGeometry() override;

public slots:
    void handleTickCountChanged(int tick) override;
    void handleMinorTickCountChanged(int tick) override;
    void handleLabelFormatChanged(const QString& format) override;
    void handleTickIntervalChanged(qreal interval) override;
    void handleTickAnchorChanged(qreal anchor) override;
    void handleTickTypeChanged(IChartiumValueAxis::TickType type) override;

protected:
    IChartiumValueAxis* mAxis;
};
