#pragma once



#include "src/qtchartium/axis/datetimeaxis/ichartiumdatetimeaxisy.h"

#include "src/qtchartium/axis/datetimeaxis/ichartiumdatetimeaxis.h"



class ChartiumDateTimeAxisY : public IChartiumDateTimeAxisY
{
    Q_OBJECT

public:
    explicit ChartiumDateTimeAxisY(
        IChartiumDateTimeAxis* axis,
        IChartiumPresenter*    presenter,
        QGraphicsItem*         item   = nullptr,
        QGraphicsLayoutItem*   parent = nullptr
    );
    ~ChartiumDateTimeAxisY() override;

    ChartiumDateTimeAxisY(const ChartiumDateTimeAxisY& another)            = delete;
    ChartiumDateTimeAxisY& operator=(const ChartiumDateTimeAxisY& another) = delete;

    QSizeF sizeHint(Qt::SizeHint which, const QSizeF& constraint) const override;

    QList<qreal> calculateLayout() const override;
    void         updateGeometry() override;

public slots:
    void handleTickCountChanged(int tick) override;
    void handleFormatChanged(const QString& format) override;

protected:
    IChartiumDateTimeAxis* mAxis;
};
