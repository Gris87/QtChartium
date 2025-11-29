#pragma once



#include "src/qtchartium/axis/ichartiumcartesianaxis.h"



class ChartiumCartesianAxis : public IChartiumCartesianAxis
{
    Q_OBJECT

public:
    explicit ChartiumCartesianAxis(
        IChartiumAxis*       axis,
        IChartiumPresenter*  presenter,
        bool                 intervalAxis = false,
        QGraphicsItem*       item         = nullptr,
        QGraphicsLayoutItem* parent       = nullptr
    );
    ~ChartiumCartesianAxis() override;

    ChartiumCartesianAxis(const ChartiumCartesianAxis& another)            = delete;
    ChartiumCartesianAxis& operator=(const ChartiumCartesianAxis& another) = delete;

    void setDateTimeLabelsFormat(const QString& format) override;

    void updateLabelsValues(IChartiumValueAxis* axis) override;
    void updateLabelsDateTimes() override;

    void createItems(int count) override;
    void deleteItems(int count) override;
    void updateMinorTickItems() override;

    void   setGeometry(const QRectF& axis, const QRectF& grid) override;
    QRectF gridGeometry() const override;
    bool   emptyAxis() const override;

    QSizeF sizeHint(Qt::SizeHint which, const QSizeF& constraint = QSizeF()) const override;

    void setGeometry(const QRectF& size) override;
    void updateGeometry() override;
    void updateLayout(const QList<qreal>& layout) override;

public slots:
    void handleArrowPenChanged(const QPen& pen) override;
    void handleGridPenChanged(const QPen& pen) override;
    void handleShadesBrushChanged(const QBrush& brush) override;
    void handleShadesPenChanged(const QPen& pen) override;
    void handleMinorArrowPenChanged(const QPen& pen) override;
    void handleMinorGridPenChanged(const QPen& pen) override;
    void handleGridLineColorChanged(const QColor& color) override;
    void handleMinorGridLineColorChanged(const QColor& color) override;

protected:
    IChartiumPresenter* mPresenter;
    QRectF mGridRect;
};
