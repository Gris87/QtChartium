#pragma once



#include "src/qtchartium/legend/ichartiumlegendscroller.h"



class ChartiumLegendScroller : public IChartiumLegendScroller
{
    Q_OBJECT

public:
    explicit ChartiumLegendScroller(
        IChartiumChart* chart, QGraphicsItem* parent = nullptr, Qt::WindowFlags wFlags = Qt::WindowFlags()
    );
    ~ChartiumLegendScroller() override;

    ChartiumLegendScroller(const ChartiumLegendScroller& another)            = delete;
    ChartiumLegendScroller& operator=(const ChartiumLegendScroller& another) = delete;

    void updateForResizerChange() override;

    void    setOffset(const QPointF& point) override;
    QPointF offset() const override;

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent* event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;

public slots:
    void handleInteractiveChanged(bool interactive) override;
    void handleDetached(bool attached) override;

protected:
    bool m_forwardMouseEvents;
    bool m_forwardHoverEvents;
    bool m_cachedShouldShowMoveEvents;
};
