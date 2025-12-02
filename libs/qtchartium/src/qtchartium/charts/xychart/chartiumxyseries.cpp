#include "src/qtchartium/charts/xychart/chartiumxyseries.h"



ChartiumXYSeries::ChartiumXYSeries(QObject* parent) :
    IChartiumXYSeries(parent)
{
}

ChartiumXYSeries::~ChartiumXYSeries()
{
}

ChartiumXYSeries& ChartiumXYSeries::operator<<(const QPointF& point)
{
    return *this;
}

ChartiumXYSeries& ChartiumXYSeries::operator<<(const QList<QPointF>& points)
{
    return *this;
}

void ChartiumXYSeries::append(qreal x, qreal y)
{
}

void ChartiumXYSeries::append(const QPointF& point)
{
}

void ChartiumXYSeries::append(const QList<QPointF>& points)
{
}

void ChartiumXYSeries::replace(qreal oldX, qreal oldY, qreal newX, qreal newY)
{
}

void ChartiumXYSeries::replace(const QPointF& oldPoint, const QPointF& newPoint)
{
}

void ChartiumXYSeries::replace(int index, qreal newX, qreal newY)
{
}

void ChartiumXYSeries::replace(int index, const QPointF& newPoint)
{
}

void ChartiumXYSeries::remove(qreal x, qreal y)
{
}

void ChartiumXYSeries::remove(const QPointF& point)
{
}

void ChartiumXYSeries::remove(int index)
{
}

void ChartiumXYSeries::removePoints(int index, int count)
{
}

void ChartiumXYSeries::insert(int index, const QPointF& point)
{
}

void ChartiumXYSeries::clear()
{
}

int ChartiumXYSeries::count() const
{
    return 0;
}

QList<QPointF> ChartiumXYSeries::points() const
{
    QList<QPointF> res;

    return res;
}

const QPointF& ChartiumXYSeries::at(int index) const
{
    static QPointF res;

    return res;
}

void ChartiumXYSeries::setPen(const QPen& pen)
{
}

QPen ChartiumXYSeries::pen() const
{
    return QPen();
}

void ChartiumXYSeries::setBrush(const QBrush& brush)
{
}

QBrush ChartiumXYSeries::brush() const
{
    return QBrush();
}

void ChartiumXYSeries::setColor(const QColor& color)
{
}

QColor ChartiumXYSeries::color() const
{
    return QColor();
}

void ChartiumXYSeries::setSelectedColor(const QColor& color)
{
}

QColor ChartiumXYSeries::selectedColor() const
{
    return QColor();
}

void ChartiumXYSeries::setPointsVisible(bool visible)
{
}

bool ChartiumXYSeries::pointsVisible() const
{
    return false;
}

void ChartiumXYSeries::setPointLabelsFormat(const QString& format)
{
}

QString ChartiumXYSeries::pointLabelsFormat() const
{
    return "";
}

void ChartiumXYSeries::setPointLabelsVisible(bool visible)
{
}

bool ChartiumXYSeries::pointLabelsVisible() const
{
    return false;
}

void ChartiumXYSeries::setPointLabelsFont(const QFont& font)
{
}

QFont ChartiumXYSeries::pointLabelsFont() const
{
    return QFont();
}

void ChartiumXYSeries::setPointLabelsColor(const QColor& color)
{
}

QColor ChartiumXYSeries::pointLabelsColor() const
{
    return QColor();
}

void ChartiumXYSeries::setPointLabelsClipping(bool enabled)
{
}

bool ChartiumXYSeries::pointLabelsClipping() const
{
    return false;
}

void ChartiumXYSeries::replace(const QList<QPointF>& points)
{
}

bool ChartiumXYSeries::isPointSelected(int index)
{
    return false;
}

void ChartiumXYSeries::selectPoint(int index)
{
}

void ChartiumXYSeries::deselectPoint(int index)
{
}

void ChartiumXYSeries::setPointSelected(int index, bool selected)
{
}

void ChartiumXYSeries::selectAllPoints()
{
}

void ChartiumXYSeries::deselectAllPoints()
{
}

void ChartiumXYSeries::selectPoints(const QList<int>& indexes)
{
}

void ChartiumXYSeries::deselectPoints(const QList<int>& indexes)
{
}

void ChartiumXYSeries::toggleSelection(const QList<int>& indexes)
{
}

QList<int> ChartiumXYSeries::selectedPoints() const
{
    QList<int> res;

    return res;
}

void ChartiumXYSeries::setLightMarker(const QImage& lightMarker)
{
}

const QImage& ChartiumXYSeries::lightMarker() const
{
    static QImage res;

    return res;
}

void ChartiumXYSeries::setSelectedLightMarker(const QImage& selectedLightMarker)
{
}

const QImage& ChartiumXYSeries::selectedLightMarker() const
{
    static QImage res;

    return res;
}

void ChartiumXYSeries::setMarkerSize(qreal size)
{
}

qreal ChartiumXYSeries::markerSize() const
{
    return 0;
}

void ChartiumXYSeries::setBestFitLineVisible(bool visible)
{
}

bool ChartiumXYSeries::bestFitLineVisible() const
{
    return false;
}

QPair<qreal, qreal> ChartiumXYSeries::bestFitLineEquation(bool& ok) const
{
    QPair<qreal, qreal> res;

    return res;
}

void ChartiumXYSeries::setBestFitLinePen(const QPen& pen)
{
}

QPen ChartiumXYSeries::bestFitLinePen() const
{
    return QPen();
}

void ChartiumXYSeries::setBestFitLineColor(const QColor& color)
{
}

QColor ChartiumXYSeries::bestFitLineColor() const
{
    return QColor();
}

void ChartiumXYSeries::clearPointConfiguration(const int index)
{
}

void ChartiumXYSeries::clearPointConfiguration(const int index, const PointConfiguration key)
{
}

void ChartiumXYSeries::clearPointsConfiguration()
{
}

void ChartiumXYSeries::clearPointsConfiguration(const PointConfiguration key)
{
}

void ChartiumXYSeries::setPointConfiguration(const int index, const QHash<PointConfiguration, QVariant>& configuration)
{
}

void ChartiumXYSeries::setPointConfiguration(const int index, const PointConfiguration key, const QVariant& value)
{
}

void ChartiumXYSeries::setPointsConfiguration(const QHash<int, QHash<PointConfiguration, QVariant>>& pointsConfiguration)
{
}

QHash<IChartiumXYSeries::PointConfiguration, QVariant> ChartiumXYSeries::pointConfiguration(const int index) const
{
    QHash<IChartiumXYSeries::PointConfiguration, QVariant> res;

    return res;
}

IChartiumXYSeries::PointsConfigurationHash ChartiumXYSeries::pointsConfiguration() const
{
    PointsConfigurationHash res;

    return res;
}

void ChartiumXYSeries::sizeBy(const QList<qreal>& sourceData, const qreal minSize, const qreal maxSize)
{
}

void ChartiumXYSeries::colorBy(const QList<qreal>& sourceData, const QLinearGradient& gradient)
{
}

void ChartiumXYSeries::drawPointLabels(QPainter* painter, const QList<QPointF>& allPoints, const int offset)
{
}

void ChartiumXYSeries::drawSeriesPointLabels(
    QPainter*                  painter,
    const QList<QPointF>&      points,
    const int                  offset,
    const QHash<int, int>&     offsets,
    const QList<int>&          indexesToSkip,
    const QHash<int, QString>& customLabels
)
{
}

void ChartiumXYSeries::drawBestFitLine(QPainter* painter, const QRectF& clipRect)
{
}

bool ChartiumXYSeries::isMarkerSizeDefault()
{
    return false;
}

QList<qreal> ChartiumXYSeries::colorByData() const
{
    QList<qreal> res;

    return res;
}

void ChartiumXYSeries::initializeDomain()
{
}

void ChartiumXYSeries::initializeAxes()
{
}

QList<IChartiumLegendMarker*> ChartiumXYSeries::createLegendMarkers(IChartiumLegend* legend)
{
    QList<IChartiumLegendMarker*> res;

    return res;
}

IChartiumAxis::AxisType ChartiumXYSeries::defaultAxisType(Qt::Orientation orientation) const
{
    return IChartiumAxis::AxisTypeValue;
}

IChartiumAxis* ChartiumXYSeries::createDefaultAxis(Qt::Orientation orientation) const
{
    return nullptr;
}
