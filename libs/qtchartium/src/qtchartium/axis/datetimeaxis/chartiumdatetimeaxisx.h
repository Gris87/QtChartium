#pragma once



#include "src/qtchartium/axis/datetimeaxis/ichartiumdatetimeaxisx.h"

#include "src/qtchartium/axis/datetimeaxis/ichartiumdatetimeaxis.h"



class ChartiumDateTimeAxisX : public IChartiumDateTimeAxisX
{
    Q_OBJECT

public:
    explicit ChartiumDateTimeAxisX(
        IChartiumDateTimeAxis* axis,
        IChartiumPresenter*    presenter,
        QGraphicsItem*         item   = nullptr,
        QGraphicsLayoutItem*   parent = nullptr
    );
    ~ChartiumDateTimeAxisX() override;

    ChartiumDateTimeAxisX(const ChartiumDateTimeAxisX& another)            = delete;
    ChartiumDateTimeAxisX& operator=(const ChartiumDateTimeAxisX& another) = delete;

    QSizeF sizeHint(Qt::SizeHint which, const QSizeF& constraint) const override;

    QList<qreal> calculateLayout() const override;
    void         updateGeometry() override;

public slots:
    void handleTickCountChanged(int tick) override;
    void handleFormatChanged(const QString& format) override;

protected:
    IChartiumDateTimeAxis* mAxis;
};
