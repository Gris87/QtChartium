#pragma once



#include "src/qtchartium/legend/ichartiumlegend.h"



class IChartiumChart;



class ChartiumLegend : public IChartiumLegend
{
    Q_OBJECT

public:
    explicit ChartiumLegend(IChartiumChart* chart, QGraphicsItem* parent = nullptr, Qt::WindowFlags wFlags = Qt::WindowFlags());
    ~ChartiumLegend() override;

    ChartiumLegend(const ChartiumLegend& another)            = delete;
    ChartiumLegend& operator=(const ChartiumLegend& another) = delete;

    void   setBrush(const QBrush& brush) override;
    QBrush brush() const override;
    void   setColor(QColor color) override;
    QColor color() override;

    void   setPen(const QPen& pen) override;
    QPen   pen() const override;
    void   setBorderColor(QColor color) override;
    QColor borderColor() override;

    void   setFont(const QFont& font) override;
    QFont  font() const override;
    void   setLabelBrush(const QBrush& brush) override;
    QBrush labelBrush() const override;

    void   setLabelColor(QColor color) override;
    QColor labelColor() const override;

    void          setAlignment(Qt::Alignment alignment) override;
    Qt::Alignment alignment() const override;

    void detachFromChart() override;
    void attachToChart() override;
    bool isAttachedToChart() override;

    void setBackgroundVisible(bool visible = true) override;
    bool isBackgroundVisible() const override;

    QList<IChartiumLegendMarker*> markers(IChartiumSeries* series = nullptr) const override;

    bool reverseMarkers() override;
    void setReverseMarkers(bool reverseMarkers = true) override;

    bool showToolTips() const override;
    void setShowToolTips(bool show) override;

    bool isInteractive() const override;
    void setInteractive(bool interactive) override;

    MarkerShape markerShape() const override;
    void        setMarkerShape(MarkerShape shape) override;

    void    setOffset(const QPointF& offset) override;
    QPointF offset() const override;
    int     roundness(qreal size) override;

    QGraphicsItemGroup*           items() override;
    QList<IChartiumLegendMarker*> markers(IChartiumSeries* series = 0) override;
    qreal                         maxMarkerWidth() const override;

    QObject* relatedObject(const IChartiumLegendMarker* l) override;

    void insertMarkerHelper(IChartiumLegendMarker* marker) override;
    void addMarkers(const QList<IChartiumLegendMarker*>& markers) override;
    void removeMarkerHelper(IChartiumLegendMarker* marker) override;
    void removeMarkers(const QList<IChartiumLegendMarker*>& markers) override;
    void decorateMarker(IChartiumLegendMarker* marker) override;
    void decorateMarkers(const QList<IChartiumLegendMarker*>& markers) override;
    void updateToolTips() override;

public slots:
    void handleSeriesAdded(IChartiumSeries* series) override;
    void handleSeriesRemoved(IChartiumSeries* series) override;
    void handleSeriesVisibleChanged() override;
    void handleCountChanged() override;
};
