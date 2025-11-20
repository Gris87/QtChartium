#include "src/qtchartium/chartiumchart.h"

#include "src/qtchartium/chartiumdataset.h"
#include "src/qtchartium/chartiumpresenter.h"
#include "src/qtchartium/domain/chartiumxydomain.h"
#include "src/qtchartium/legend/chartiumlegend.h"



ChartiumChart::ChartiumChart(QGraphicsItem* parent, Qt::WindowFlags wFlags) :
    IChartiumChart(parent, wFlags),
    mLegend(new ChartiumLegend(this)),
    mDataset(new ChartiumDataSet(this)),
    mPresenter(new ChartiumPresenter(this)),
    mChartType(IChartiumChart::ChartTypeCartesian)
{
}

ChartiumChart::~ChartiumChart()
{
}

void ChartiumChart::addSeries(IChartiumSeries* series)
{
}

void ChartiumChart::removeSeries(IChartiumSeries* series)
{
}

void ChartiumChart::removeAllSeries()
{
}

QList<IChartiumSeries*> ChartiumChart::series() const
{
    QList<IChartiumSeries*> res;

    return res;
}

void ChartiumChart::addAxis(IChartiumAxis* axis, Qt::Alignment alignment)
{
}

void ChartiumChart::removeAxis(IChartiumAxis* axis)
{
}

QList<IChartiumAxis*> ChartiumChart::axes(Qt::Orientations orientation, IChartiumSeries* series) const
{
    QList<IChartiumAxis*> res;

    return res;
}

void ChartiumChart::createDefaultAxes()
{
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
