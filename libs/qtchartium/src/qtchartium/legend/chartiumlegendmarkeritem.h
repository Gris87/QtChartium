#pragma once



#include "src/qtchartium/legend/ichartiumlegendmarkeritem.h"



class ChartiumLegendMarkerItem : public IChartiumLegendMarkerItem
{
public:
    explicit ChartiumLegendMarkerItem(
        IChartiumLegendMarker* marker,
        QGraphicsItem*         parent   = nullptr,
        QGraphicsLayoutItem*   parent2  = nullptr,
        bool                   isLayout = false
    );
    ~ChartiumLegendMarkerItem() override;

    ChartiumLegendMarkerItem(const ChartiumLegendMarkerItem& another)            = delete;
    ChartiumLegendMarkerItem& operator=(const ChartiumLegendMarkerItem& another) = delete;

    void setPen(const QPen& pen) override;
    QPen pen() const override;

    void   setBrush(const QBrush& brush) override;
    QBrush brush() const override;

    void setSeriesPen(const QPen& pen) override;
    void setSeriesBrush(const QBrush& brush) override;
    void setSeriesLightMarker(const QImage& image) override;

    void  setFont(const QFont& font) override;
    QFont font() const override;

    void    setLabel(const QString label) override;
    QString label() const override;

    void   setLabelBrush(const QBrush& brush) override;
    QBrush labelBrush() const override;

    void   setGeometry(const QRectF& rect) override;
    QRectF boundingRect() const override;
    QRectF markerRect() const override;

    void   paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
    QSizeF sizeHint(Qt::SizeHint which, const QSizeF& constraint) const override;

    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;

    QString displayedLabel() const override;
    void    setToolTip(const QString& tooltip) override;

    IChartiumLegend::MarkerShape markerShape() const override;
    void                         setMarkerShape(IChartiumLegend::MarkerShape shape) override;

    void                         updateMarkerShapeAndSize() override;
    IChartiumLegend::MarkerShape effectiveMarkerShape() const override;
    qreal                        effectiveMarkerWidth() const override;

    ItemType itemType() const override;

    void setItemBrushAndPen() override;
    void setItemRect() override;
    bool useMaxWidth() const override;

    qreal margin() const override;
    qreal preferredItemWidth() const override;

protected:
    IChartiumLegendMarker*       m_marker;
    QRectF                       m_defaultMarkerRect;
    QRectF                       m_markerRect;
    QRectF                       m_boundingRect;
    QGraphicsTextItem*           m_textItem;
    QGraphicsItem*               m_markerItem;
    qreal                        m_margin;
    qreal                        m_space;
    QString                      m_label;
    IChartiumLegend::MarkerShape m_markerShape;
    QImage                       m_seriesLightMarker;
    QBrush                       m_labelBrush;
    QPen                         m_pen;
    QBrush                       m_brush;
    QPen                         m_seriesPen;
    QBrush                       m_seriesBrush;
    QFont                        m_font;
    bool                         m_hovering;
    ItemType                     m_itemType;
};
