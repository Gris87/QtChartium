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

protected:
    IChartiumLineSeries*      m_series;
    QPainterPath              m_linePath;
    QPainterPath              m_linePathPolarRight;
    QPainterPath              m_linePathPolarLeft;
    QPainterPath              m_fullPath;
    QPainterPath              m_shapePath;
    QList<QPointF>            m_linePoints;
    QRectF                    m_rect;
    QPen                      m_linePen;
    bool                      m_pointsVisible;
    IChartiumChart::ChartType m_chartType;
    bool                      m_pointLabelsVisible;
    qreal                     m_markerSize;
    QString                   m_pointLabelsFormat;
    QFont                     m_pointLabelsFont;
    QColor                    m_pointLabelsColor;
    bool                      m_pointLabelsClipping;
    QPointF                   m_lastMousePos;
    QPointF                   m_lastHoveredMatchedPos;
    bool                      m_mousePressed;
};
