#pragma once



#include "src/qtchartium/charts/xychart/ichartiumxyseries.h"



class ChartiumXYSeries : public IChartiumXYSeries
{
    Q_OBJECT

public:
    explicit ChartiumXYSeries(QObject* parent = nullptr);
    ~ChartiumXYSeries() override;

    ChartiumXYSeries(const ChartiumXYSeries& another)            = delete;
    ChartiumXYSeries& operator=(const ChartiumXYSeries& another) = delete;

    ChartiumXYSeries& operator<<(const QPointF& point);
    ChartiumXYSeries& operator<<(const QList<QPointF>& points);

    void append(qreal x, qreal y) override;
    void append(const QPointF& point) override;
    void append(const QList<QPointF>& points) override;
    void replace(qreal oldX, qreal oldY, qreal newX, qreal newY) override;
    void replace(const QPointF& oldPoint, const QPointF& newPoint) override;
    void replace(int index, qreal newX, qreal newY) override;
    void replace(int index, const QPointF& newPoint) override;
    void remove(qreal x, qreal y) override;
    void remove(const QPointF& point) override;
    void remove(int index) override;
    void removePoints(int index, int count) override;
    void insert(int index, const QPointF& point) override;
    void clear() override;

    int            count() const override;
    QList<QPointF> points() const override;
    const QPointF& at(int index) const override;

    void setPen(const QPen& pen) override;
    QPen pen() const override;

    void   setBrush(const QBrush& brush) override;
    QBrush brush() const override;

    void   setColor(const QColor& color) override;
    QColor color() const override;

    void   setSelectedColor(const QColor& color) override;
    QColor selectedColor() const override;

    void setPointsVisible(bool visible = true) override;
    bool pointsVisible() const override;

    void    setPointLabelsFormat(const QString& format) override;
    QString pointLabelsFormat() const override;

    void setPointLabelsVisible(bool visible = true) override;
    bool pointLabelsVisible() const override;

    void  setPointLabelsFont(const QFont& font) override;
    QFont pointLabelsFont() const override;

    void   setPointLabelsColor(const QColor& color) override;
    QColor pointLabelsColor() const override;

    void setPointLabelsClipping(bool enabled = true) override;
    bool pointLabelsClipping() const override;

    void replace(const QList<QPointF>& points) override;

    bool       isPointSelected(int index) override;
    void       selectPoint(int index) override;
    void       deselectPoint(int index) override;
    void       setPointSelected(int index, bool selected) override;
    void       selectAllPoints() override;
    void       deselectAllPoints() override;
    void       selectPoints(const QList<int>& indexes) override;
    void       deselectPoints(const QList<int>& indexes) override;
    void       toggleSelection(const QList<int>& indexes) override;
    QList<int> selectedPoints() const override;

    void          setLightMarker(const QImage& lightMarker) override;
    const QImage& lightMarker() const override;

    void          setSelectedLightMarker(const QImage& selectedLightMarker) override;
    const QImage& selectedLightMarker() const override;

    void  setMarkerSize(qreal size) override;
    qreal markerSize() const override;

    void                setBestFitLineVisible(bool visible = true) override;
    bool                bestFitLineVisible() const override;
    QPair<qreal, qreal> bestFitLineEquation(bool& ok) const override;

    void   setBestFitLinePen(const QPen& pen) override;
    QPen   bestFitLinePen() const override;
    void   setBestFitLineColor(const QColor& color) override;
    QColor bestFitLineColor() const override;

    void clearPointConfiguration(const int index) override;
    void clearPointConfiguration(const int index, const PointConfiguration key) override;
    void clearPointsConfiguration() override;
    void clearPointsConfiguration(const PointConfiguration key) override;
    void setPointConfiguration(const int index, const QHash<PointConfiguration, QVariant>& configuration) override;
    void setPointConfiguration(const int index, const PointConfiguration key, const QVariant& value) override;
    void setPointsConfiguration(const QHash<int, QHash<PointConfiguration, QVariant>>& pointsConfiguration) override;
    QHash<PointConfiguration, QVariant> pointConfiguration(const int index) const override;
    PointsConfigurationHash             pointsConfiguration() const override;

    void sizeBy(const QList<qreal>& sourceData, const qreal minSize, const qreal maxSize) override;
    void colorBy(const QList<qreal>& sourceData, const QLinearGradient& gradient = QLinearGradient()) override;

    void drawPointLabels(QPainter* painter, const QList<QPointF>& allPoints, const int offset = 0) override;
    void drawSeriesPointLabels(
        QPainter*                  painter,
        const QList<QPointF>&      points,
        const int                  offset        = 0,
        const QHash<int, int>&     offsets       = {},
        const QList<int>&          indexesToSkip = {},
        const QHash<int, QString>& customLabels  = {}
    ) override;

    void drawBestFitLine(QPainter* painter, const QRectF& clipRect) override;

    bool isMarkerSizeDefault() override;

    QList<qreal> colorByData() const override;

    void initializeDomain() override;
    void initializeAxes() override;

    QList<IChartiumLegendMarker*> createLegendMarkers(IChartiumLegend* legend) override;

    IChartiumAxis::AxisType defaultAxisType(Qt::Orientation orientation) const override;
    IChartiumAxis*          createDefaultAxis(Qt::Orientation orientation) const override;

protected:
    QList<QPointF>                                  m_points;
    QSet<int>                                       m_selectedPoints;
    QPen                                            m_pen;
    QColor                                          m_selectedColor;
    QBrush                                          m_brush;
    bool                                            m_pointsVisible;
    QString                                         m_pointLabelsFormat;
    bool                                            m_pointLabelsVisible;
    QFont                                           m_pointLabelsFont;
    QColor                                          m_pointLabelsColor;
    bool                                            m_pointLabelsClipping;
    QImage                                          m_lightMarker;
    QImage                                          m_selectedLightMarker;
    QPen                                            m_bestFitLinePen;
    bool                                            m_bestFitLineVisible;
    qreal                                           m_markerSize;
    bool                                            m_markerSizeDefault;
    QHash<int, QHash<PointConfiguration, QVariant>> m_pointsConfiguration;
    QList<qreal>                                    m_colorByData;
};
