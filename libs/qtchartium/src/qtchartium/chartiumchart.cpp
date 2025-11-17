#include "src/qtchartium/chartiumchart.h"

#include "src/qtchartium/domain/chartiumxydomain.h"
#include "src/qtchartium/legend/chartiumlegend.h"



ChartiumChart::ChartiumChart(QGraphicsItem* parent, Qt::WindowFlags wFlags) :
    IChartiumChart(parent, wFlags),
    mLegend(new ChartiumLegend()),
    mSeries(),
    mAxes(),
    mChartType(IChartiumChart::ChartTypeCartesian)
{
}

ChartiumChart::~ChartiumChart()
{
    delete mLegend;
}

void ChartiumChart::addSeries(IChartiumSeries* series)
{
    if (mSeries.contains(series))
    {
        return;
    }

    if (mChartType == IChartiumChart::ChartTypePolar)
    {
        // Polar chart is not supported
    }
    else
    {
        series->setDomain(new ChartiumXYDomain());
    }

    series->initializeDomain();
    mSeries.append(series);

    series->setParent(this);
    series->setChart(this);
}

void ChartiumChart::removeSeries(IChartiumSeries* series)
{
    if (!mSeries.contains(series))
    {
        return;
    }

    mSeries.removeAll(series);
}

void ChartiumChart::removeAllSeries()
{
    const QList<IChartiumSeries*> series = mSeries;

    for (IChartiumSeries* s : series)
    {
        removeSeries(s);

        delete s;
    }
}

QList<IChartiumSeries*> ChartiumChart::series() const
{
    return mSeries;
}

void ChartiumChart::addAxis(IChartiumAxis* axis, Qt::Alignment alignment)
{
    if (mAxes.contains(axis))
    {
        return;
    }

    mAxes.append(axis);
}

void ChartiumChart::removeAxis(IChartiumAxis* axis)
{
    if (!mAxes.contains(axis))
    {
        return;
    }

    mAxes.removeAll(axis);
}

QList<IChartiumAxis*> ChartiumChart::axes(Qt::Orientations orientation, IChartiumSeries* series) const
{
    QList<IChartiumAxis*> res;

    return res;
}

void ChartiumChart::createDefaultAxes()
{
    if (mSeries.isEmpty())
    {
        return;
    }
}

void ChartiumChart::setTitle(const QString& title)
{
}

QString ChartiumChart::title() const
{
    return "";
}

void ChartiumChart::setTitleFont(const QFont& font)
{
}

QFont ChartiumChart::titleFont() const
{
    return QFont();
}

void ChartiumChart::setTitleBrush(const QBrush& brush)
{
}

QBrush ChartiumChart::titleBrush() const
{
    return QBrush();
}

void ChartiumChart::setBackgroundBrush(const QBrush& brush)
{
}

QBrush ChartiumChart::backgroundBrush() const
{
    return QBrush();
}

void ChartiumChart::setBackgroundPen(const QPen& pen)
{
}

QPen ChartiumChart::backgroundPen() const
{
    return QPen();
}

void ChartiumChart::setBackgroundVisible(bool visible)
{
}

bool ChartiumChart::isBackgroundVisible() const
{
    return false;
}

void ChartiumChart::setDropShadowEnabled(bool enabled)
{
}

bool ChartiumChart::isDropShadowEnabled() const
{
    return false;
}

void ChartiumChart::setBackgroundRoundness(qreal diameter)
{
}

qreal ChartiumChart::backgroundRoundness() const
{
    return 0;
}

void ChartiumChart::zoomIn()
{
}

void ChartiumChart::zoomOut()
{
}

void ChartiumChart::zoomIn(const QRectF& rect)
{
}

void ChartiumChart::zoom(qreal factor)
{
}

void ChartiumChart::zoomReset()
{
}

bool ChartiumChart::isZoomed()
{
    return false;
}

void ChartiumChart::scroll(qreal dx, qreal dy)
{
}

IChartiumLegend* ChartiumChart::legend() const
{
    return mLegend;
}

void ChartiumChart::setMargins(const QMargins& margins)
{
}

QMargins ChartiumChart::margins() const
{
    return QMargins();
}

QRectF ChartiumChart::plotArea() const
{
    return QRectF();
}

void ChartiumChart::setPlotArea(const QRectF& rect)
{
}

void ChartiumChart::setPlotAreaBackgroundBrush(const QBrush& brush)
{
}

QBrush ChartiumChart::plotAreaBackgroundBrush() const
{
    return QBrush();
}

void ChartiumChart::setPlotAreaBackgroundPen(const QPen& pen)
{
}

QPen ChartiumChart::plotAreaBackgroundPen() const
{
    return QPen();
}

void ChartiumChart::setPlotAreaBackgroundVisible(bool visible)
{
}

bool ChartiumChart::isPlotAreaBackgroundVisible() const
{
    return false;
}

void ChartiumChart::setLocalizeNumbers(bool localize)
{
}

bool ChartiumChart::localizeNumbers() const
{
    return false;
}

void ChartiumChart::setLocale(const QLocale& locale)
{
}

QLocale ChartiumChart::locale() const
{
    return QLocale();
}

QPointF ChartiumChart::mapToValue(const QPointF& position, IChartiumSeries* series)
{
    return QPointF();
}

QPointF ChartiumChart::mapToPosition(const QPointF& value, IChartiumSeries* series)
{
    return QPointF();
}

IChartiumChart::ChartType ChartiumChart::chartType() const
{
    return IChartiumChart::ChartTypeUndefined;
}
