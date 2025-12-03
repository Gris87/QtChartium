#include "src/qtchartium/charts/xychart/chartiumxyseries.h"

#include "src/qtchartium/axis/valueaxis/chartiumvalueaxis.h"
#include "src/qtchartium/chartiumhelpers.h"
#include "src/qtchartium/legend/chartiumlegendmarkerxy.h"



ChartiumXYSeries::ChartiumXYSeries(QObject* parent) :
    IChartiumXYSeries(parent),
    m_points(),
    m_selectedPoints(),
    m_pen(),
    m_selectedColor(),
    m_brush(),
    m_pointsVisible(),
    m_pointLabelsFormat("@xPoint, @yPoint"),
    m_pointLabelsVisible(),
    m_pointLabelsFont(),
    m_pointLabelsColor(),
    m_pointLabelsClipping(true),
    m_lightMarker(),
    m_selectedLightMarker(),
    m_bestFitLinePen(),
    m_bestFitLineVisible(),
    m_markerSize(15.0),
    m_markerSizeDefault(true),
    m_pointsConfiguration(),
    m_colorByData()
{
}

ChartiumXYSeries::~ChartiumXYSeries()
{
}

ChartiumXYSeries& ChartiumXYSeries::operator<<(const QPointF& point)
{
    append(point);

    return *this;
}

ChartiumXYSeries& ChartiumXYSeries::operator<<(const QList<QPointF>& points)
{
    append(points);

    return *this;
}

void ChartiumXYSeries::append(qreal x, qreal y)
{
    append(QPointF(x, y));
}

void ChartiumXYSeries::append(const QPointF& point)
{
    if (isValidValue(point))
    {
        m_points.append(point);

        emit pointAdded(m_points.size() - 1);
    }
}

void ChartiumXYSeries::append(const QList<QPointF>& points)
{
    for (const QPointF& point : points)
    {
        append(point);
    }
}

void ChartiumXYSeries::replace(qreal oldX, qreal oldY, qreal newX, qreal newY)
{
    replace(QPointF(oldX, oldY), QPointF(newX, newY));
}

void ChartiumXYSeries::replace(const QPointF& oldPoint, const QPointF& newPoint)
{
    int index = m_points.indexOf(oldPoint);

    if (index == -1)
    {
        return;
    }

    replace(index, newPoint);
}

void ChartiumXYSeries::replace(int index, qreal newX, qreal newY)
{
    replace(index, QPointF(newX, newY));
}

void ChartiumXYSeries::replace(int index, const QPointF& newPoint)
{
    if (isValidValue(newPoint))
    {
        m_points[index] = newPoint;

        emit pointReplaced(index);
    }
}

void ChartiumXYSeries::remove(qreal x, qreal y)
{
    remove(QPointF(x, y));
}

void ChartiumXYSeries::remove(const QPointF& point)
{
    int index = m_points.indexOf(point);

    if (index > 0)
    {
        remove(index);
    }
}

void ChartiumXYSeries::remove(int index)
{
    m_points.remove(index);

    bool callSignal = false;
    setPointSelected(index, false, callSignal);

    emit pointRemoved(index);

    if (callSignal)
    {
        emit selectedPointsChanged();
    }
}

void ChartiumXYSeries::removePoints(int index, int count)
{
    if (count > 0)
    {
        m_points.remove(index, count);

        bool callSignal = false;

        if (!m_selectedPoints.empty())
        {
            QSet<int> selectedAfterRemoving;

            for (const int& selectedPointIndex : std::as_const(m_selectedPoints))
            {
                if (selectedPointIndex < index)
                {
                    selectedAfterRemoving << selectedPointIndex;
                }
                else if (selectedPointIndex >= index + count)
                {
                    selectedAfterRemoving << selectedPointIndex - count;
                    callSignal = true;
                }
                else
                {
                    callSignal = true;
                }
            }

            m_selectedPoints = selectedAfterRemoving;
        }

        emit pointsRemoved(index, count);

        if (callSignal)
        {
            emit selectedPointsChanged();
        }
    }
}

void ChartiumXYSeries::insert(int index, const QPointF& point)
{
    if (isValidValue(point))
    {
        index = qMax(0, qMin(index, m_points.size()));

        m_points.insert(index, point);

        bool callSignal = false;

        if (!m_selectedPoints.isEmpty())
        {
            // if point was inserted we need to move already selected points by 1
            QSet<int> selectedAfterInsert;
            for (const auto& value : std::as_const(m_selectedPoints))
            {
                if (value >= index)
                {
                    selectedAfterInsert << value + 1;
                    callSignal = true;
                }
                else
                {
                    selectedAfterInsert << value;
                }
            }
            m_selectedPoints = selectedAfterInsert;
        }

        emit pointAdded(index);
        if (callSignal)
        {
            emit selectedPointsChanged();
        }
    }
}

void ChartiumXYSeries::clear()
{
    removePoints(0, m_points.size());
}

int ChartiumXYSeries::count() const
{
    return m_points.size();
}

QList<QPointF> ChartiumXYSeries::points() const
{
    return m_points;
}

const QPointF& ChartiumXYSeries::at(int index) const
{
    return m_points.at(index);
}

void ChartiumXYSeries::setPen(const QPen& pen)
{
    if (m_pen != pen)
    {
        bool emitColorChanged = m_pen.color() != pen.color();
        m_pen                 = pen;

        emit seriesUpdated();

        if (emitColorChanged)
        {
            emit colorChanged(pen.color());
        }

        emit penChanged(pen);
    }
}

QPen ChartiumXYSeries::pen() const
{
    return m_pen;
}

void ChartiumXYSeries::setBrush(const QBrush& brush)
{
    if (m_brush != brush)
    {
        m_brush = brush;

        emit seriesUpdated();
    }
}

QBrush ChartiumXYSeries::brush() const
{
    return m_brush;
}

void ChartiumXYSeries::setColor(const QColor& color)
{
    QPen p = pen();

    if (p.color() != color)
    {
        p.setColor(color);
        setPen(p);
    }
}

QColor ChartiumXYSeries::color() const
{
    return pen().color();
}

void ChartiumXYSeries::setSelectedColor(const QColor& color)
{
    if (selectedColor() != color)
    {
        m_selectedColor = color;

        emit selectedColorChanged(color);
    }
}

QColor ChartiumXYSeries::selectedColor() const
{
    return m_selectedColor;
}

void ChartiumXYSeries::setPointsVisible(bool visible)
{
    if (m_pointsVisible != visible)
    {
        m_pointsVisible = visible;

        emit seriesUpdated();
    }
}

bool ChartiumXYSeries::pointsVisible() const
{
    return m_pointsVisible;
}

void ChartiumXYSeries::setPointLabelsFormat(const QString& format)
{
    if (m_pointLabelsFormat != format)
    {
        m_pointLabelsFormat = format;

        emit pointLabelsFormatChanged(format);
    }
}

QString ChartiumXYSeries::pointLabelsFormat() const
{
    return m_pointLabelsFormat;
}

void ChartiumXYSeries::setPointLabelsVisible(bool visible)
{
    if (m_pointLabelsVisible != visible)
    {
        m_pointLabelsVisible = visible;

        emit pointLabelsVisibilityChanged(visible);
    }
}

bool ChartiumXYSeries::pointLabelsVisible() const
{
    return m_pointLabelsVisible;
}

void ChartiumXYSeries::setPointLabelsFont(const QFont& font)
{
    if (m_pointLabelsFont != font)
    {
        m_pointLabelsFont = font;

        emit pointLabelsFontChanged(font);
    }
}

QFont ChartiumXYSeries::pointLabelsFont() const
{
    return m_pointLabelsFont;
}

void ChartiumXYSeries::setPointLabelsColor(const QColor& color)
{
    if (m_pointLabelsColor != color)
    {
        m_pointLabelsColor = color;

        emit pointLabelsColorChanged(color);
    }
}

QColor ChartiumXYSeries::pointLabelsColor() const
{
    return m_pointLabelsColor;
}

void ChartiumXYSeries::setPointLabelsClipping(bool enabled)
{
    if (m_pointLabelsClipping != enabled)
    {
        m_pointLabelsClipping = enabled;

        emit pointLabelsClippingChanged(enabled);
    }
}

bool ChartiumXYSeries::pointLabelsClipping() const
{
    return m_pointLabelsClipping;
}

void ChartiumXYSeries::replace(const QList<QPointF>& points)
{
    const bool needUpdateSelection = m_points.size() > points.size();
    m_points                       = points;

    if (needUpdateSelection)
    {
        m_selectedPoints.removeIf([maxIdx = points.size() - 1](int idx) { return idx > maxIdx; });
    }

    emit pointsReplaced();

    if (needUpdateSelection)
    {
        emit selectedPointsChanged();
    }
}

bool ChartiumXYSeries::isPointSelected(int index)
{
    return m_selectedPoints.contains(index);
}

void ChartiumXYSeries::selectPoint(int index)
{
    setPointSelected(index, true);
}

void ChartiumXYSeries::deselectPoint(int index)
{
    setPointSelected(index, false);
}

void ChartiumXYSeries::setPointSelected(int index, bool selected)
{
    bool callSignal = false;
    setPointSelected(index, selected, callSignal);

    if (callSignal)
    {
        emit selectedPointsChanged();
    }
}

void ChartiumXYSeries::selectAllPoints()
{
    bool callSignal = false;

    for (int i = 0; i < m_points.size(); ++i)
    {
        setPointSelected(i, true, callSignal);
    }

    if (callSignal)
    {
        emit selectedPointsChanged();
    }
}

void ChartiumXYSeries::deselectAllPoints()
{
    bool callSignal = false;

    for (int i = 0; i < m_points.size(); ++i)
    {
        setPointSelected(i, false, callSignal);
    }

    if (callSignal)
    {
        emit selectedPointsChanged();
    }
}

void ChartiumXYSeries::selectPoints(const QList<int>& indexes)
{
    bool callSignal = false;

    for (int index : indexes)
    {
        setPointSelected(index, true, callSignal);
    }

    if (callSignal)
    {
        emit selectedPointsChanged();
    }
}

void ChartiumXYSeries::deselectPoints(const QList<int>& indexes)
{
    bool callSignal = false;

    for (int index : indexes)
    {
        setPointSelected(index, false, callSignal);
    }

    if (callSignal)
    {
        emit selectedPointsChanged();
    }
}

void ChartiumXYSeries::toggleSelection(const QList<int>& indexes)
{
    bool callSignal = false;

    for (int index : indexes)
    {
        setPointSelected(index, !isPointSelected(index), callSignal);
    }

    if (callSignal)
    {
        emit selectedPointsChanged();
    }
}

QList<int> ChartiumXYSeries::selectedPoints() const
{
    return QList<int>(m_selectedPoints.begin(), m_selectedPoints.end());
}

void ChartiumXYSeries::setLightMarker(const QImage& lightMarker)
{
    if (m_lightMarker != lightMarker)
    {
        m_lightMarker = lightMarker;

        emit seriesUpdated();
        emit lightMarkerChanged(m_lightMarker);
    }
}

const QImage& ChartiumXYSeries::lightMarker() const
{
    return m_lightMarker;
}

void ChartiumXYSeries::setSelectedLightMarker(const QImage& selectedLightMarker)
{
    if (m_selectedLightMarker != selectedLightMarker)
    {
        m_selectedLightMarker = selectedLightMarker;

        emit seriesUpdated();
        emit selectedLightMarkerChanged(m_selectedLightMarker);
    }
}

const QImage& ChartiumXYSeries::selectedLightMarker() const
{
    return m_selectedLightMarker;
}

void ChartiumXYSeries::setMarkerSize(qreal size)
{
    if (!qFuzzyCompare(m_markerSize, size))
    {
        m_markerSizeDefault = false;
        m_markerSize        = size;

        emit seriesUpdated();
        emit markerSizeChanged(size);
    }
}

qreal ChartiumXYSeries::markerSize() const
{
    return m_markerSize;
}

void ChartiumXYSeries::setBestFitLineVisible(bool visible)
{
    if (m_bestFitLineVisible != visible)
    {
        m_bestFitLineVisible = visible;

        emit bestFitLineVisibilityChanged(visible);
        emit seriesUpdated();
    }
}

bool ChartiumXYSeries::bestFitLineVisible() const
{
    return m_bestFitLineVisible;
}

QPair<qreal, qreal> ChartiumXYSeries::bestFitLineEquation(bool& ok) const
{
    if (m_points.size() <= 1)
    {
        ok = false;
        return {0, 0};
    }

    ok         = true;
    qreal xSum = 0.0, x2Sum = 0.0, ySum = 0.0, xySum = 0.0;
    for (const auto& point : m_points)
    {
        xSum  += point.x();
        ySum  += point.y();
        x2Sum += qPow(point.x(), 2);
        xySum += point.x() * point.y();
    }

    const qreal divisor = m_points.size() * x2Sum - xSum * xSum;
    // To prevent crashes in unusual cases
    if (divisor == 0.0)
    {
        ok = false;
        return {0, 0};
    }

    qreal a = (m_points.size() * xySum - xSum * ySum) / divisor;
    qreal b = (x2Sum * ySum - xSum * xySum) / divisor;

    return {a, b};
}

void ChartiumXYSeries::setBestFitLinePen(const QPen& pen)
{
    if (m_bestFitLinePen != pen)
    {
        bool emitColorChanged = m_bestFitLinePen.color() != pen.color();
        m_bestFitLinePen      = pen;

        emit seriesUpdated();

        if (emitColorChanged)
        {
            bestFitLineColorChanged(pen.color());
        }

        emit bestFitLinePenChanged(pen);
    }
}

QPen ChartiumXYSeries::bestFitLinePen() const
{
    return m_bestFitLinePen;
}

void ChartiumXYSeries::setBestFitLineColor(const QColor& color)
{
    QPen p = bestFitLinePen();

    if (p.color() != color)
    {
        p.setColor(color);
        setBestFitLinePen(p);
    }
}

QColor ChartiumXYSeries::bestFitLineColor() const
{
    return bestFitLinePen().color();
}

void ChartiumXYSeries::clearPointConfiguration(const int index)
{
    if (m_pointsConfiguration.contains(index))
    {
        m_pointsConfiguration.remove(index);
        emit pointsConfigurationChanged(m_pointsConfiguration);
    }
}

void ChartiumXYSeries::clearPointConfiguration(const int index, const PointConfiguration key)
{
    if (m_pointsConfiguration.contains(index))
    {
        auto& conf = m_pointsConfiguration[index];
        if (conf.contains(key))
        {
            conf.remove(key);
            m_pointsConfiguration[index] = conf;
            emit pointsConfigurationChanged(m_pointsConfiguration);
        }
    }
}

void ChartiumXYSeries::clearPointsConfiguration()
{
    m_pointsConfiguration.clear();

    emit pointsConfigurationChanged(m_pointsConfiguration);
}

void ChartiumXYSeries::clearPointsConfiguration(const PointConfiguration key)
{
    bool needsUpdate = false;
    for (const int& index : m_pointsConfiguration.keys())
    {
        auto& conf = m_pointsConfiguration[index];
        if (conf.contains(key))
        {
            conf.remove(key);
            m_pointsConfiguration[index] = conf;
            needsUpdate                  = true;
        }
    }

    if (needsUpdate)
    {
        emit pointsConfigurationChanged(m_pointsConfiguration);
    }
}

void ChartiumXYSeries::setPointConfiguration(const int index, const QHash<PointConfiguration, QVariant>& configuration)
{
    if (m_pointsConfiguration[index] != configuration)
    {
        m_pointsConfiguration[index] = configuration;
        emit pointsConfigurationChanged(m_pointsConfiguration);
    }
}

void ChartiumXYSeries::setPointConfiguration(const int index, const PointConfiguration key, const QVariant& value)
{
    if (setPointConfigurationInternal(index, key, value))
    {
        emit pointsConfigurationChanged(m_pointsConfiguration);
    }
}

void ChartiumXYSeries::setPointsConfiguration(const QHash<int, QHash<PointConfiguration, QVariant>>& pointsConfiguration)
{
    if (m_pointsConfiguration != pointsConfiguration)
    {
        m_pointsConfiguration = pointsConfiguration;
        emit pointsConfigurationChanged(m_pointsConfiguration);
    }
}

QHash<IChartiumXYSeries::PointConfiguration, QVariant> ChartiumXYSeries::pointConfiguration(const int index) const
{
    QHash<IChartiumXYSeries::PointConfiguration, QVariant> res;

    return m_pointsConfiguration[index];
}

IChartiumXYSeries::PointsConfigurationHash ChartiumXYSeries::pointsConfiguration() const
{
    return m_pointsConfiguration;
}

void ChartiumXYSeries::sizeBy(const QList<qreal>& sourceData, const qreal minSize, const qreal maxSize)
{
    Q_ASSERT(minSize <= maxSize);
    Q_ASSERT(minSize >= 0);

    qreal min = std::numeric_limits<qreal>::max();
    qreal max = -std::numeric_limits<qreal>::max();
    for (const auto& p : sourceData)
    {
        min = qMin(min, p);
        max = qMax(max, p);
    }

    const qreal range     = max - min;
    const qreal sizeRange = maxSize - minSize;
    bool        changed   = false;

    for (int i = 0; i < sourceData.size() && i < m_points.size(); ++i)
    {
        qreal pointSize = minSize;
        if (range != 0)
        {
            const qreal startValue = sourceData.at(i) - min;
            const qreal percentage = startValue / range;
            pointSize              = minSize + (percentage * sizeRange);
        }
        if (setPointConfigurationInternal(i, PointConfiguration::Size, pointSize))
        {
            changed = true;
        }
    }

    if (changed)
    {
        emit pointsConfigurationChanged(m_pointsConfiguration);
    }
}

void ChartiumXYSeries::colorBy(const QList<qreal>& sourceData, const QLinearGradient& gradient)
{
    m_colorByData = sourceData;
    if (m_colorByData.isEmpty())
    {
        return;
    }

    const qreal imgSize = 100.0;

    qreal min = std::numeric_limits<qreal>::max();
    qreal max = std::numeric_limits<qreal>::min();
    for (const auto& p : sourceData)
    {
        min = qMin(min, p);
        max = qMax(max, p);
    }

    qreal range = max - min;

    QLinearGradient usedGradient = gradient;

    // Gradient will be taked from the first attached color axis.
    // If there are more color axis, they will have just changed range.
    bool       axisFound = false;
    const auto axes      = attachedAxes();
    for (const auto& axis : axes)
    {
    }

    QImage   image(imgSize, imgSize, QImage::Format_ARGB32);
    QPainter painter(&image);
    painter.fillRect(image.rect(), usedGradient);

    // To ensure that negative values will be well handled, distance from min to 0
    // will be added to min and every single value. This will move entire values
    // list to positive only values.
    const qreal diff  = min < 0 ? qAbs(min) : 0;
    min              += diff;

    bool changed = false;

    for (int i = 0; i < sourceData.size() && i < m_points.size(); ++i)
    {
        const qreal startValue = qMax(0.0, sourceData.at(i) + diff - min);
        const qreal percentage = startValue / range;
        QColor      color      = image.pixelColor(0, qMin(percentage * imgSize, imgSize - 1));

        if (setPointConfigurationInternal(i, PointConfiguration::Color, color))
        {
            changed = true;
        }
    }

    if (changed)
    {
        emit pointsConfigurationChanged(m_pointsConfiguration);
    }
}

void ChartiumXYSeries::drawPointLabels(QPainter* painter, const QList<QPointF>& allPoints, const int offset)
{
    if (m_pointLabelsVisible || !m_pointsConfiguration.isEmpty())
    {
        if (m_pointLabelsClipping)
        {
            painter->setClipping(true);
        }
        else
        {
            painter->setClipping(false);
        }

        QList<int>          pointsToSkip;
        QHash<int, QString> labelFormats;
        QHash<int, int>     offsets;

        if (!m_pointsConfiguration.isEmpty())
        {
            for (int i = 0; i < allPoints.size(); ++i)
            {
                bool drawLabel = m_pointLabelsVisible;

                if (m_pointsConfiguration.contains(i))
                {
                    const auto& conf = m_pointsConfiguration[i];
                    auto        key  = PointConfiguration::LabelVisibility;

                    if (conf.contains(key))
                    {
                        drawLabel = m_pointsConfiguration[i][key].toBool();
                        key       = PointConfiguration::Size;
                        if (drawLabel && conf.contains(key))
                        {
                            offsets[i] = conf[key].toReal();
                        }
                    }

                    key = PointConfiguration::LabelFormat;
                    if (conf.contains(key) && !conf[key].toString().isEmpty())
                    {
                        labelFormats[i] = conf[key].toString();
                    }
                }

                if (!drawLabel)
                {
                    pointsToSkip << i;
                }
            }
        }

        drawSeriesPointLabels(painter, allPoints, offset, offsets, pointsToSkip, labelFormats);
    }
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
    if (points.size() == 0)
    {
        return;
    }

    static const QString xPointTag(QLatin1String("@xPoint"));
    static const QString yPointTag(QLatin1String("@yPoint"));
    static const QString indexTag(QLatin1String("@index"));

    QFont f(m_pointLabelsFont);
    f.setPixelSize(QFontInfo(m_pointLabelsFont).pixelSize());
    painter->setFont(f);
    painter->setPen(QPen(m_pointLabelsColor));
    QFontMetrics fm(painter->font());
    // m_points is used for the label here as it has the series point information
    // points variable passed is used for positioning because it has the coordinates
    const int pointCount = qMin(points.size(), m_points.size());
    for (int i(0); i < pointCount; i++)
    {
        if (indexesToSkip.contains(i))
        {
            continue;
        }

        QString pointLabel = customLabels.contains(i) ? customLabels[i] : m_pointLabelsFormat;
        pointLabel.replace(xPointTag, presenter()->numberToString(m_points.at(i).x()));
        pointLabel.replace(yPointTag, presenter()->numberToString(m_points.at(i).y()));
        pointLabel.replace(indexTag, presenter()->numberToString(i));

        int currOffset = offset;
        if (offsets.contains(i))
        {
            currOffset = offsets[i];
        }

        const int labelOffset = currOffset + 2;

        // Position text in relation to the point
        int     pointLabelWidth = fm.horizontalAdvance(pointLabel);
        QPointF position(points.at(i));
        position.setX(position.x() - pointLabelWidth / 2);
        position.setY(position.y() - labelOffset);

        painter->drawText(position, pointLabel);
    }
}

void ChartiumXYSeries::drawBestFitLine(QPainter* painter, const QRectF& clipRect)
{
    bool        ok                = false;
    const auto& bestFitLineParams = bestFitLineEquation(ok);

    if (!ok)
    {
        return;
    }

    auto*      domain       = this->domain();
    const auto clipOriginX  = domain->isReverseX() ? clipRect.right() : clipRect.left();
    const auto clipOriginY  = domain->isReverseY() ? clipRect.top() : clipRect.bottom();
    const auto domainOrigin = domain->calculateDomainPoint({clipOriginX, clipOriginY});

    const qreal x1 = domainOrigin.x();
    const qreal y1 = bestFitLineParams.first * x1 + bestFitLineParams.second;
    QPointF     p1 = domain->calculateGeometryPoint(QPointF(x1, y1), ok);

    const qreal x2 = domainOrigin.x() + 1;
    const qreal y2 = bestFitLineParams.first * x2 + bestFitLineParams.second;
    QPointF     p2 = domain->calculateGeometryPoint(QPointF(x2, y2), ok);

    if (ok)
    {
        QLineF bestFitLine{p1, p2};
        // maxLength is length of the diagonal, no line can be longer
        const qreal maxLength = qSqrt(qPow(clipRect.width(), 2) * qPow(clipRect.height(), 2));
        bestFitLine.setLength(maxLength);

        painter->save();
        painter->setPen(m_bestFitLinePen);
        painter->drawLine(bestFitLine);
        painter->restore();
    }
}

void ChartiumXYSeries::setPointSelected(int index, bool selected, bool& callSignal)
{
    if (index < 0 || index > m_points.size() - 1)
    {
        return;
    }

    if (selected)
    {
        if (!isPointSelected(index))
        {
            m_selectedPoints << index;
            callSignal = true;
        }
    }
    else
    {
        if (isPointSelected(index))
        {
            m_selectedPoints.remove(index);
            callSignal = true;
        }
    }
}

bool ChartiumXYSeries::isMarkerSizeDefault()
{
    return m_markerSizeDefault;
}

QList<qreal> ChartiumXYSeries::colorByData() const
{
    return m_colorByData;
}

bool ChartiumXYSeries::setPointConfigurationInternal(const int index, const PointConfiguration key, const QVariant& value)
{
    QHash<PointConfiguration, QVariant> conf;
    if (m_pointsConfiguration.contains(index))
    {
        conf = m_pointsConfiguration[index];
    }

    bool changed = false;
    if (conf.contains(key))
    {
        if (conf[key] != value)
        {
            changed = true;
        }
    }
    else
    {
        changed = true;
    }

    conf[key]                    = value;
    m_pointsConfiguration[index] = conf;

    return changed;
}

void ChartiumXYSeries::initializeDomain()
{
    qreal minX = 0;
    qreal minY = 0;
    qreal maxX = 1;
    qreal maxY = 1;

    if (!m_points.isEmpty())
    {
        minX = m_points.at(0).x();
        minY = m_points.at(0).y();
        maxX = minX;
        maxY = minY;

        for (int i = 0; i < m_points.size(); i++)
        {
            qreal x = m_points.at(i).x();
            qreal y = m_points.at(i).y();

            minX = qMin(minX, x);
            minY = qMin(minY, y);
            maxX = qMax(maxX, x);
            maxY = qMax(maxY, y);
        }
    }

    domain()->setRange(minX, maxX, minY, maxY);
}

void ChartiumXYSeries::initializeAxes()
{
}

QList<IChartiumLegendMarker*> ChartiumXYSeries::createLegendMarkers(IChartiumLegend* legend)
{
    QList<IChartiumLegendMarker*> res;
    res.append(new ChartiumLegendMarkerXY(this, legend));

    return res;
}

IChartiumAxis::AxisType ChartiumXYSeries::defaultAxisType(Qt::Orientation orientation) const
{
    return IChartiumAxis::AxisTypeValue;
}

IChartiumAxis* ChartiumXYSeries::createDefaultAxis(Qt::Orientation orientation) const
{
    return new ChartiumValueAxis();
}
