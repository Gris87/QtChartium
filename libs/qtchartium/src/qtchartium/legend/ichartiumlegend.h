#pragma once



#include <QGraphicsWidget>

#include <QPen>



class IChartiumLegendMarker;
class IChartiumSeries;
class IChartiumPresenter;



class IChartiumLegend : public QGraphicsWidget
{
    Q_OBJECT

public:
    enum MarkerShape
    {
        MarkerShapeDefault,
        MarkerShapeRectangle,
        MarkerShapeCircle,
        MarkerShapeFromSeries,
        MarkerShapeRotatedRectangle,
        MarkerShapeTriangle,
        MarkerShapeStar,
        MarkerShapePentagon
    };

    explicit IChartiumLegend(QGraphicsItem* parent = nullptr, Qt::WindowFlags wFlags = Qt::WindowFlags()) :
        QGraphicsWidget(parent, wFlags)
    {
    }
    ~IChartiumLegend() override = default;

    IChartiumLegend(const IChartiumLegend& another)            = delete;
    IChartiumLegend& operator=(const IChartiumLegend& another) = delete;

    virtual void   setBrush(const QBrush& brush) = 0;
    virtual QBrush brush() const                 = 0;
    virtual void   setColor(QColor color)        = 0;
    virtual QColor color()                       = 0;

    virtual void   setPen(const QPen& pen)      = 0;
    virtual QPen   pen() const                  = 0;
    virtual void   setBorderColor(QColor color) = 0;
    virtual QColor borderColor()                = 0;

    virtual void   setFont(const QFont& font)         = 0;
    virtual QFont  font() const                       = 0;
    virtual void   setLabelBrush(const QBrush& brush) = 0;
    virtual QBrush labelBrush() const                 = 0;

    virtual void   setLabelColor(QColor color) = 0;
    virtual QColor labelColor() const          = 0;

    virtual void          setAlignment(Qt::Alignment alignment) = 0;
    virtual Qt::Alignment alignment() const                     = 0;

    virtual void detachFromChart()   = 0;
    virtual void attachToChart()     = 0;
    virtual bool isAttachedToChart() = 0;

    virtual void setBackgroundVisible(bool visible = true) = 0;
    virtual bool isBackgroundVisible() const               = 0;

    virtual QList<IChartiumLegendMarker*> markers(IChartiumSeries* series = nullptr) const = 0;

    virtual bool reverseMarkers()                              = 0;
    virtual void setReverseMarkers(bool reverseMarkers = true) = 0;

    virtual bool showToolTips() const       = 0;
    virtual void setShowToolTips(bool show) = 0;

    virtual bool isInteractive() const            = 0;
    virtual void setInteractive(bool interactive) = 0;

    virtual MarkerShape markerShape() const               = 0;
    virtual void        setMarkerShape(MarkerShape shape) = 0;

    virtual void    setOffset(const QPointF& offset) = 0;
    virtual QPointF offset() const                   = 0;
    virtual int     roundness(qreal size)            = 0;

    virtual QGraphicsItemGroup*           items()                              = 0;
    virtual QList<IChartiumLegendMarker*> markers(IChartiumSeries* series = 0) = 0;
    virtual qreal                         maxMarkerWidth() const               = 0;

    virtual QObject* relatedObject(const IChartiumLegendMarker* l) = 0;

    virtual void insertMarkerHelper(IChartiumLegendMarker* marker)             = 0;
    virtual void addMarkers(const QList<IChartiumLegendMarker*>& markers)      = 0;
    virtual void removeMarkerHelper(IChartiumLegendMarker* marker)             = 0;
    virtual void removeMarkers(const QList<IChartiumLegendMarker*>& markers)   = 0;
    virtual void decorateMarker(IChartiumLegendMarker* marker)                 = 0;
    virtual void decorateMarkers(const QList<IChartiumLegendMarker*>& markers) = 0;
    virtual void updateToolTips()                                              = 0;

    virtual IChartiumPresenter* presenter() const        = 0;
    virtual bool                isReverseMarkers() const = 0;

public slots:
    virtual void handleSeriesAdded(IChartiumSeries* series)   = 0;
    virtual void handleSeriesRemoved(IChartiumSeries* series) = 0;
    virtual void handleSeriesVisibleChanged()                 = 0;
    virtual void handleCountChanged()                         = 0;

signals:
    void backgroundVisibleChanged(bool visible);
    void colorChanged(QColor color);
    void borderColorChanged(QColor color);
    void fontChanged(QFont font);
    void labelColorChanged(QColor color);
    void reverseMarkersChanged(bool reverseMarkers);
    void showToolTipsChanged(bool showToolTips);
    void markerShapeChanged(MarkerShape shape);
    void attachedToChartChanged(bool attachedToChart);
    void interactiveChanged(bool interactive);
};
