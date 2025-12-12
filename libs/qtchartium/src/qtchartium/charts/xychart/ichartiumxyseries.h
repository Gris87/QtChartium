#pragma once



#include "src/qtchartium/charts/chartiumseries.h"



class IChartiumXYSeries : public ChartiumSeries
{
    Q_OBJECT

public:
    enum class PointConfiguration : quint8
    {
        Color,
        Size,
        Visibility,
        LabelVisibility,
        LabelFormat
    };
    using PointsConfigurationHash = QHash<int, QHash<PointConfiguration, QVariant>>;

    explicit IChartiumXYSeries(QObject* parent = nullptr) :
        ChartiumSeries(parent)
    {
    }
    ~IChartiumXYSeries() override = default;

    IChartiumXYSeries(const IChartiumXYSeries& another)            = delete;
    IChartiumXYSeries& operator=(const IChartiumXYSeries& another) = delete;

    virtual void append(qreal x, qreal y)                                  = 0;
    virtual void append(const QPointF& point)                              = 0;
    virtual void append(const QList<QPointF>& points)                      = 0;
    virtual void replace(qreal oldX, qreal oldY, qreal newX, qreal newY)   = 0;
    virtual void replace(const QPointF& oldPoint, const QPointF& newPoint) = 0;
    virtual void replace(int index, qreal newX, qreal newY)                = 0;
    virtual void replace(int index, const QPointF& newPoint)               = 0;
    virtual void remove(qreal x, qreal y)                                  = 0;
    virtual void remove(const QPointF& point)                              = 0;
    virtual void remove(int index)                                         = 0;
    virtual void removePoints(int index, int count)                        = 0;
    virtual void insert(int index, const QPointF& point)                   = 0;
    virtual void clear()                                                   = 0;

    virtual int            count() const       = 0;
    virtual QList<QPointF> points() const      = 0;
    virtual const QPointF& at(int index) const = 0;

    virtual void setPen(const QPen& pen) = 0;
    virtual QPen pen() const             = 0;

    virtual void   setBrush(const QBrush& brush) = 0;
    virtual QBrush brush() const                 = 0;

    virtual void   setColor(const QColor& color) = 0;
    virtual QColor color() const                 = 0;

    virtual void   setSelectedColor(const QColor& color) = 0;
    virtual QColor selectedColor() const                 = 0;

    virtual void setPointsVisible(bool visible = true) = 0;
    virtual bool pointsVisible() const                 = 0;

    virtual void    setPointLabelsFormat(const QString& format) = 0;
    virtual QString pointLabelsFormat() const                   = 0;

    virtual void setPointLabelsVisible(bool visible = true) = 0;
    virtual bool pointLabelsVisible() const                 = 0;

    virtual void  setPointLabelsFont(const QFont& font) = 0;
    virtual QFont pointLabelsFont() const               = 0;

    virtual void   setPointLabelsColor(const QColor& color) = 0;
    virtual QColor pointLabelsColor() const                 = 0;

    virtual void setPointLabelsClipping(bool enabled = true) = 0;
    virtual bool pointLabelsClipping() const                 = 0;

    virtual void replace(const QList<QPointF>& points) = 0;

    virtual bool       isPointSelected(int index)                 = 0;
    virtual void       selectPoint(int index)                     = 0;
    virtual void       deselectPoint(int index)                   = 0;
    virtual void       setPointSelected(int index, bool selected) = 0;
    virtual void       selectAllPoints()                          = 0;
    virtual void       deselectAllPoints()                        = 0;
    virtual void       selectPoints(const QList<int>& indexes)    = 0;
    virtual void       deselectPoints(const QList<int>& indexes)  = 0;
    virtual void       toggleSelection(const QList<int>& indexes) = 0;
    virtual QList<int> selectedPoints() const                     = 0;

    virtual void          setLightMarker(const QImage& lightMarker) = 0;
    virtual const QImage& lightMarker() const                       = 0;

    virtual void          setSelectedLightMarker(const QImage& selectedLightMarker) = 0;
    virtual const QImage& selectedLightMarker() const                               = 0;

    virtual void  setMarkerSize(qreal size) = 0;
    virtual qreal markerSize() const        = 0;

    virtual void                setBestFitLineVisible(bool visible = true) = 0;
    virtual bool                bestFitLineVisible() const                 = 0;
    virtual QPair<qreal, qreal> bestFitLineEquation(bool& ok) const        = 0;

    virtual void   setBestFitLinePen(const QPen& pen)       = 0;
    virtual QPen   bestFitLinePen() const                   = 0;
    virtual void   setBestFitLineColor(const QColor& color) = 0;
    virtual QColor bestFitLineColor() const                 = 0;

    virtual void clearPointConfiguration(const int index)                                                           = 0;
    virtual void clearPointConfiguration(const int index, const PointConfiguration key)                             = 0;
    virtual void clearPointsConfiguration()                                                                         = 0;
    virtual void clearPointsConfiguration(const PointConfiguration key)                                             = 0;
    virtual void setPointConfiguration(const int index, const QHash<PointConfiguration, QVariant>& configuration)   = 0;
    virtual void setPointConfiguration(const int index, const PointConfiguration key, const QVariant& value)        = 0;
    virtual void setPointsConfiguration(const QHash<int, QHash<PointConfiguration, QVariant>>& pointsConfiguration) = 0;
    virtual QHash<PointConfiguration, QVariant> pointConfiguration(const int index) const                           = 0;
    virtual PointsConfigurationHash             pointsConfiguration() const                                         = 0;

    virtual void sizeBy(const QList<qreal>& sourceData, const qreal minSize, const qreal maxSize)             = 0;
    virtual void colorBy(const QList<qreal>& sourceData, const QLinearGradient& gradient = QLinearGradient()) = 0;

    virtual void drawPointLabels(QPainter* painter, const QList<QPointF>& allPoints, const int offset = 0) = 0;
    virtual void drawSeriesPointLabels(
        QPainter*                  painter,
        const QList<QPointF>&      points,
        const int                  offset        = 0,
        const QHash<int, int>&     offsets       = {},
        const QList<int>&          indexesToSkip = {},
        const QHash<int, QString>& customLabels  = {}
    ) = 0;

    virtual void drawBestFitLine(QPainter* painter, const QRectF& clipRect) = 0;

    virtual void setPointSelected(int index, bool selected, bool& callSignal) = 0;

    virtual bool isMarkerSizeDefault() = 0;

    virtual QList<qreal> colorByData() const = 0;

    virtual bool setPointConfigurationInternal(const int index, const PointConfiguration key, const QVariant& value) = 0;

signals:
    void clicked(const QPointF& point);
    void hovered(const QPointF& point, bool state);
    void pressed(const QPointF& point);
    void released(const QPointF& point);
    void doubleClicked(const QPointF& point);
    void pointReplaced(int index);
    void pointRemoved(int index);
    void pointAdded(int index);
    void colorChanged(QColor color);
    void selectedColorChanged(const QColor& color);
    void pointsReplaced();
    void pointLabelsFormatChanged(const QString& format);
    void pointLabelsVisibilityChanged(bool visible);
    void pointLabelsFontChanged(const QFont& font);
    void pointLabelsColorChanged(const QColor& color);
    void pointLabelsClippingChanged(bool clipping);
    void pointsRemoved(int index, int count);
    void penChanged(const QPen& pen);
    void selectedPointsChanged();
    void lightMarkerChanged(const QImage& lightMarker);
    void selectedLightMarkerChanged(const QImage& selectedLightMarker);
    void bestFitLineVisibilityChanged(bool visible);
    void bestFitLinePenChanged(const QPen& pen);
    void bestFitLineColorChanged(const QColor& color);
    void pointsConfigurationChanged(const PointsConfigurationHash& configuration);
    void markerSizeChanged(qreal size);
    void seriesUpdated();
};
