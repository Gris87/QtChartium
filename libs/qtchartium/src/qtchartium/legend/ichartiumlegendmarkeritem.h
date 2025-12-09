#pragma once



#include <QGraphicsLayoutItem>
#include <QGraphicsObject>

#include "src/qtchartium/legend/ichartiumlegend.h"



class IChartiumLegendMarkerItem : public QGraphicsObject,
                                  public QGraphicsLayoutItem
{
public:
    enum ItemType : quint8
    {
        TypeRect,
        TypeLine,
        TypeCircle,
        TypeRotatedRect,
        TypeTriangle,
        TypeStar,
        TypePentagon
    };

    explicit IChartiumLegendMarkerItem(
        QGraphicsItem* parent = nullptr, QGraphicsLayoutItem* parent2 = nullptr, bool isLayout = false
    ) :
        QGraphicsObject(parent),
        QGraphicsLayoutItem(parent2, isLayout)
    {
    }
    ~IChartiumLegendMarkerItem() override = default;

    IChartiumLegendMarkerItem(const IChartiumLegendMarkerItem& another)            = delete;
    IChartiumLegendMarkerItem& operator=(const IChartiumLegendMarkerItem& another) = delete;

    virtual void setPen(const QPen& pen) = 0;
    virtual QPen pen() const             = 0;

    virtual void   setBrush(const QBrush& brush) = 0;
    virtual QBrush brush() const                 = 0;

    virtual void setSeriesPen(const QPen& pen)             = 0;
    virtual void setSeriesBrush(const QBrush& brush)       = 0;
    virtual void setSeriesLightMarker(const QImage& image) = 0;

    virtual void  setFont(const QFont& font) = 0;
    virtual QFont font() const               = 0;

    virtual void    setLabel(const QString label) = 0;
    virtual QString label() const                 = 0;

    virtual void   setLabelBrush(const QBrush& brush) = 0;
    virtual QBrush labelBrush() const                 = 0;

    virtual QRectF markerRect() const = 0;

    virtual QString displayedLabel() const             = 0;
    virtual void    setToolTip(const QString& tooltip) = 0;

    virtual IChartiumLegend::MarkerShape markerShape() const                                = 0;
    virtual void                         setMarkerShape(IChartiumLegend::MarkerShape shape) = 0;

    virtual void                         updateMarkerShapeAndSize()   = 0;
    virtual IChartiumLegend::MarkerShape effectiveMarkerShape() const = 0;
    virtual qreal                        effectiveMarkerWidth() const = 0;

    virtual ItemType itemType() const = 0;

    virtual void setItemBrushAndPen() = 0;
    virtual void setItemRect()        = 0;
    virtual bool useMaxWidth() const  = 0;

    virtual qreal margin() const             = 0;
    virtual qreal preferredItemWidth() const = 0;

signals:
    void markerRectChanged();
};
