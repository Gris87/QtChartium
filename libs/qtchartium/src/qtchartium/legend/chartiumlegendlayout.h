#pragma once



#include "src/qtchartium/legend/ichartiumlegendlayout.h"

#include "src/qtchartium/legend/ichartiumlegend.h"



class IChartiumChart;



class ChartiumLegendLayout : public IChartiumLegendLayout
{
public:
    explicit ChartiumLegendLayout(IChartiumLegend* legend, QGraphicsLayoutItem* parent = nullptr);
    ~ChartiumLegendLayout() override;

    ChartiumLegendLayout(const ChartiumLegendLayout& another)            = delete;
    ChartiumLegendLayout& operator=(const ChartiumLegendLayout& another) = delete;

    void setGeometry(const QRectF& rect) override;

    void    setOffset(qreal x, qreal y) override;
    QPointF offset() const override;

    void invalidate() override;

    QSizeF               sizeHint(Qt::SizeHint which, const QSizeF& constraint = QSizeF()) const override;
    int                  count() const override;
    QGraphicsLayoutItem* itemAt(int) const override;
    void                 removeAt(int) override;

    void setAttachedGeometry(const QRectF& rect) override;
    void setDettachedGeometry(const QRectF& rect) override;

    bool widthLongerThan(const LegendWidthStruct* item1, const LegendWidthStruct* item2) override;

protected:
    IChartiumLegend* m_legend;
    qreal            m_offsetX;
    qreal            m_offsetY;
    qreal            m_minOffsetX;
    qreal            m_minOffsetY;
    qreal            m_maxOffsetX;
    qreal            m_maxOffsetY;
    qreal            m_width;
    qreal            m_height;
};
