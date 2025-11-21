#include "src/qtchartium/axis/chartiumaxis.h"



ChartiumAxis::ChartiumAxis(QObject* parent) :
    IChartiumAxis(parent),
    mChart(),
    mItem(),
    mSeries(),
    mAlignment(),
    mOrientation(),
    mVisible(true),
    mArrowVisible(true),
    mAxisPen(),
    mAxisBrush(),
    mGridLineVisible(true),
    mGridLinePen(),
    mMinorGridLineVisible(true),
    mMinorGridLinePen(),
    mLabelsVisible(true),
    mLabelsEditable(false),
    mLabelsBrush(),
    mLabelsFont(),
    mLabelsAngle(),
    mLabelsTruncated(),
    mTruncateLabels(true),
    mTitleVisible(true),
    mTitleBrush(),
    mTitleFont(),
    mTitle(),
    mShadesVisible(),
    mShadesPen(),
    mShadesBrush(),
    mShadesOpacity(1),
    mDirty(),
    mReverse()
{
}

ChartiumAxis::~ChartiumAxis()
{
}

IChartiumAxis::AxisType ChartiumAxis::type() const
{
    return IChartiumAxis::AxisTypeNoAxis;
}

bool ChartiumAxis::isVisible() const
{
    return false;
}

void ChartiumAxis::setVisible(bool visible)
{
}

void ChartiumAxis::show()
{
}

void ChartiumAxis::hide()
{
}

IChartiumChart* ChartiumAxis::chart() const
{
    return nullptr;
}

void ChartiumAxis::setChart(IChartiumChart* chart)
{
}

bool ChartiumAxis::isLineVisible() const
{
    return false;
}

void ChartiumAxis::setLineVisible(bool visible)
{
}

void ChartiumAxis::setLinePen(const QPen& pen)
{
}

QPen ChartiumAxis::linePen() const
{
    return QPen();
}

void ChartiumAxis::setLinePenColor(QColor color)
{
}

QColor ChartiumAxis::linePenColor() const
{
    return QColor();
}

bool ChartiumAxis::isGridLineVisible() const
{
    return false;
}

void ChartiumAxis::setGridLineVisible(bool visible)
{
}

void ChartiumAxis::setGridLinePen(const QPen& pen)
{
}

QPen ChartiumAxis::gridLinePen() const
{
    return QPen();
}

bool ChartiumAxis::isMinorGridLineVisible() const
{
    return false;
}

void ChartiumAxis::setMinorGridLineVisible(bool visible)
{
}

void ChartiumAxis::setMinorGridLinePen(const QPen& pen)
{
}

QPen ChartiumAxis::minorGridLinePen() const
{
    return QPen();
}

void ChartiumAxis::setGridLineColor(const QColor& color)
{
}

QColor ChartiumAxis::gridLineColor()
{
    return QColor();
}

void ChartiumAxis::setMinorGridLineColor(const QColor& color)
{
}

QColor ChartiumAxis::minorGridLineColor()
{
    return QColor();
}

bool ChartiumAxis::labelsVisible() const
{
    return false;
}

void ChartiumAxis::setLabelsVisible(bool visible)
{
}

void ChartiumAxis::setLabelsBrush(const QBrush& brush)
{
}

QBrush ChartiumAxis::labelsBrush() const
{
    return QBrush();
}

void ChartiumAxis::setLabelsFont(const QFont& font)
{
}

QFont ChartiumAxis::labelsFont() const
{
    return QFont();
}

void ChartiumAxis::setLabelsAngle(int angle)
{
}

int ChartiumAxis::labelsAngle() const
{
    return 0;
}

void ChartiumAxis::setLabelsColor(QColor color)
{
}

QColor ChartiumAxis::labelsColor() const
{
    return QColor();
}

bool ChartiumAxis::isTitleVisible() const
{
    return false;
}

void ChartiumAxis::setTitleVisible(bool visible)
{
}

void ChartiumAxis::setTitleBrush(const QBrush& brush)
{
}

QBrush ChartiumAxis::titleBrush() const
{
    return QBrush();
}

void ChartiumAxis::setTitleFont(const QFont& font)
{
}

QFont ChartiumAxis::titleFont() const
{
    return QFont();
}

void ChartiumAxis::setTitleText(const QString& title)
{
}

QString ChartiumAxis::titleText() const
{
    return "";
}

bool ChartiumAxis::shadesVisible() const
{
    return false;
}

void ChartiumAxis::setShadesVisible(bool visible)
{
}

void ChartiumAxis::setShadesPen(const QPen& pen)
{
}

QPen ChartiumAxis::shadesPen() const
{
    return QPen();
}

void ChartiumAxis::setShadesBrush(const QBrush& brush)
{
}

QBrush ChartiumAxis::shadesBrush() const
{
    return QBrush();
}

void ChartiumAxis::setShadesColor(QColor color)
{
}

QColor ChartiumAxis::shadesColor() const
{
    return QColor();
}

void ChartiumAxis::setShadesBorderColor(QColor color)
{
}

QColor ChartiumAxis::shadesBorderColor() const
{
    return QColor();
}

Qt::Orientation ChartiumAxis::orientation() const
{
    return Qt::Horizontal;
}

Qt::Alignment ChartiumAxis::alignment() const
{
    return Qt::AlignLeft;
}

void ChartiumAxis::setAlignment(Qt::Alignment alignment)
{
}

void ChartiumAxis::setMin(const QVariant& min)
{
}

void ChartiumAxis::setMax(const QVariant& max)
{
}

void ChartiumAxis::setRange(const QVariant& min, const QVariant& max)
{
}

void ChartiumAxis::setRange(qreal min, qreal max)
{
}

qreal ChartiumAxis::min()
{
    return 0;
}

qreal ChartiumAxis::max()
{
    return 0;
}

void ChartiumAxis::setReverse(bool reverse)
{
}

bool ChartiumAxis::isReverse() const
{
    return false;
}

void ChartiumAxis::setLabelsEditable(bool editable)
{
}

bool ChartiumAxis::labelsEditable() const
{
    return false;
}

bool ChartiumAxis::labelsTruncated() const
{
    return false;
}

void ChartiumAxis::setTruncateLabels(bool truncateLabels)
{
}

bool ChartiumAxis::truncateLabels() const
{
    return false;
}

void ChartiumAxis::initializeDomain(IChartiumDomain* domain)
{
}

void ChartiumAxis::initializeGraphics(QGraphicsItem* parent)
{
}

IChartiumAxisElement* ChartiumAxis::axisItem()
{
    return nullptr;
}

QList<IChartiumSeries*> ChartiumAxis::getSeries() const
{
    return mSeries;
}

void ChartiumAxis::appendSeries(IChartiumSeries* series)
{
    mSeries.append(series);
}

void ChartiumAxis::removeSeries(IChartiumSeries* series)
{
    mSeries.removeAll(series);
}

void ChartiumAxis::handleRangeChanged(qreal min, qreal max)
{
}
