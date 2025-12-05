#pragma once



#include <QGraphicsLayout>

#include "src/qtchartium/legend/ichartiumlegendmarkeritem.h"



struct LegendWidthStruct
{
    IChartiumLegendMarkerItem* item;
    qreal                      width;
};



class IChartiumLegendLayout : public QGraphicsLayout
{
public:
    explicit IChartiumLegendLayout(QGraphicsLayoutItem* parent = nullptr) :
        QGraphicsLayout(parent)
    {
    }
    ~IChartiumLegendLayout() override = default;

    IChartiumLegendLayout(const IChartiumLegendLayout& another)            = delete;
    IChartiumLegendLayout& operator=(const IChartiumLegendLayout& another) = delete;

    virtual void    setOffset(qreal x, qreal y) = 0;
    virtual QPointF offset() const              = 0;

    virtual void setAttachedGeometry(const QRectF& rect)  = 0;
    virtual void setDettachedGeometry(const QRectF& rect) = 0;

    virtual bool widthLongerThan(const LegendWidthStruct* item1, const LegendWidthStruct* item2) = 0;
};
