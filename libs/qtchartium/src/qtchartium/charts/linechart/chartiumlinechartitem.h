#pragma once



#include "src/qtchartium/charts/linechart/ichartiumlinechartitem.h"



class ChartiumLineChartItem : public IChartiumLineChartItem
{
    Q_OBJECT

public:
    explicit ChartiumLineChartItem(IChartiumLineSeries* series, QGraphicsItem* item = nullptr);
    ~ChartiumLineChartItem() override;

    ChartiumLineChartItem(const ChartiumLineChartItem& another)            = delete;
    ChartiumLineChartItem& operator=(const ChartiumLineChartItem& another) = delete;

    QPainterPath path() const override;

    void suppressPoints() override;
    void forceChartType(IChartiumChart::ChartType chartType) override;

    QRectF       boundingRect() const override;
    void         paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    QPainterPath shape() const override;

    void updateGeometry() override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent* event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;

public slots:
    void handleSeriesUpdated() override;
};
