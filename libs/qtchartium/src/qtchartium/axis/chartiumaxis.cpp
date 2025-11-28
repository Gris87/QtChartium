#include "src/qtchartium/axis/chartiumaxis.h"

#include "src/qtchartium/axis/ichartiumaxiselement.h"



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
    return mVisible;
}

void ChartiumAxis::setVisible(bool visible)
{
    if (mVisible != visible)
    {
        mVisible = visible;

        emit visibleChanged(visible);
    }
}

void ChartiumAxis::show()
{
    setVisible(true);
}

void ChartiumAxis::hide()
{
    setVisible(false);
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
    return mArrowVisible;
}

void ChartiumAxis::setLineVisible(bool visible)
{
    if (mArrowVisible != visible)
    {
        mArrowVisible = visible;

        emit lineVisibleChanged(visible);
    }
}

void ChartiumAxis::setLinePen(const QPen& pen)
{
    if (mAxisPen != pen)
    {
        mAxisPen = pen;

        emit linePenChanged(pen);
    }
}

QPen ChartiumAxis::linePen() const
{
    return mAxisPen;
}

void ChartiumAxis::setLinePenColor(QColor color)
{
    QPen p = linePen();

    if (p.color() != color)
    {
        p.setColor(color);
        setLinePen(p);

        emit colorChanged(color);
    }
}

QColor ChartiumAxis::linePenColor() const
{
    return linePen().color();
}

bool ChartiumAxis::isGridLineVisible() const
{
    return mGridLineVisible;
}

void ChartiumAxis::setGridLineVisible(bool visible)
{
    if (mGridLineVisible != visible)
    {
        mGridLineVisible = visible;

        emit gridVisibleChanged(visible);
    }
}

void ChartiumAxis::setGridLinePen(const QPen& pen)
{
    if (mGridLinePen != pen)
    {
        mGridLinePen = pen;

        emit gridLinePenChanged(pen);
    }
}

QPen ChartiumAxis::gridLinePen() const
{
    return mGridLinePen;
}

bool ChartiumAxis::isMinorGridLineVisible() const
{
    return mMinorGridLineVisible;
}

void ChartiumAxis::setMinorGridLineVisible(bool visible)
{
    if (mMinorGridLineVisible != visible)
    {
        mMinorGridLineVisible = visible;

        emit minorGridVisibleChanged(visible);
    }
}

void ChartiumAxis::setMinorGridLinePen(const QPen& pen)
{
    if (mMinorGridLinePen != pen)
    {
        mMinorGridLinePen = pen;

        emit minorGridLinePenChanged(pen);
    }
}

QPen ChartiumAxis::minorGridLinePen() const
{
    return mMinorGridLinePen;
}

void ChartiumAxis::setGridLineColor(const QColor& color)
{
    QPen pen = gridLinePen();

    if (color != pen.color())
    {
        pen.setColor(color);
        setGridLinePen(pen);

        emit gridLineColorChanged(color);
    }
}

QColor ChartiumAxis::gridLineColor()
{
    return gridLinePen().color();
}

void ChartiumAxis::setMinorGridLineColor(const QColor& color)
{
    QPen pen = minorGridLinePen();

    if (color != pen.color())
    {
        pen.setColor(color);
        setMinorGridLinePen(pen);

        emit minorGridLineColorChanged(color);
    }
}

QColor ChartiumAxis::minorGridLineColor()
{
    return minorGridLinePen().color();
}

bool ChartiumAxis::labelsVisible() const
{
    return mLabelsVisible;
}

void ChartiumAxis::setLabelsVisible(bool visible)
{
    if (mLabelsVisible != visible)
    {
        mLabelsVisible = visible;

        emit labelsVisibleChanged(visible);
    }
}

void ChartiumAxis::setLabelsBrush(const QBrush& brush)
{
    if (mLabelsBrush != brush)
    {
        mLabelsBrush = brush;

        emit labelsBrushChanged(brush);
    }
}

QBrush ChartiumAxis::labelsBrush() const
{
    return mLabelsBrush;
}

void ChartiumAxis::setLabelsFont(const QFont& font)
{
    if (mLabelsFont != font)
    {
        mLabelsFont = font;

        emit labelsFontChanged(font);
    }
}

QFont ChartiumAxis::labelsFont() const
{
    return mLabelsFont;
}

void ChartiumAxis::setLabelsAngle(int angle)
{
    if (mLabelsAngle != angle)
    {
        mLabelsAngle = angle;

        emit labelsAngleChanged(angle);
    }
}

int ChartiumAxis::labelsAngle() const
{
    return mLabelsAngle;
}

void ChartiumAxis::setLabelsColor(QColor color)
{
    QBrush b = labelsBrush();

    if (b.color() != color)
    {
        b.setColor(color);
        setLabelsBrush(b);

        emit labelsColorChanged(color);
    }
}

QColor ChartiumAxis::labelsColor() const
{
    return labelsBrush().color();
}

bool ChartiumAxis::isTitleVisible() const
{
    return mTitleVisible;
}

void ChartiumAxis::setTitleVisible(bool visible)
{
    if (mTitleVisible != visible)
    {
        mTitleVisible = visible;

        emit titleVisibleChanged(visible);
    }
}

void ChartiumAxis::setTitleBrush(const QBrush& brush)
{
    if (mTitleBrush != brush)
    {
        mTitleBrush = brush;

        emit titleBrushChanged(brush);
    }
}

QBrush ChartiumAxis::titleBrush() const
{
    return mTitleBrush;
}

void ChartiumAxis::setTitleFont(const QFont& font)
{
    if (mTitleFont != font)
    {
        mTitleFont = font;

        emit titleFontChanged(font);
    }
}

QFont ChartiumAxis::titleFont() const
{
    return mTitleFont;
}

void ChartiumAxis::setTitleText(const QString& title)
{
    if (mTitle != title)
    {
        mTitle = title;

        emit titleTextChanged(title);
    }
}

QString ChartiumAxis::titleText() const
{
    return mTitle;
}

bool ChartiumAxis::shadesVisible() const
{
    return mShadesVisible;
}

void ChartiumAxis::setShadesVisible(bool visible)
{
    if (mShadesVisible != visible)
    {
        mShadesVisible = visible;

        emit shadesVisibleChanged(visible);
    }
}

void ChartiumAxis::setShadesPen(const QPen& pen)
{
    if (mShadesPen != pen)
    {
        mShadesPen = pen;

        emit shadesPenChanged(pen);
    }
}

QPen ChartiumAxis::shadesPen() const
{
    return mShadesPen;
}

void ChartiumAxis::setShadesBrush(const QBrush& brush)
{
    if (mShadesBrush != brush)
    {
        mShadesBrush = brush;

        emit shadesBrushChanged(brush);
    }
}

QBrush ChartiumAxis::shadesBrush() const
{
    return mShadesBrush;
}

void ChartiumAxis::setShadesColor(QColor color)
{
    QBrush b = shadesBrush();

    if (b.color() != color)
    {
        b.setColor(color);
        setShadesBrush(b);

        emit shadesColorChanged(color);
    }
}

QColor ChartiumAxis::shadesColor() const
{
    return shadesBrush().color();
}

void ChartiumAxis::setShadesBorderColor(QColor color)
{
    QPen p = shadesPen();

    if (p.color() != color)
    {
        p.setColor(color);
        setShadesPen(p);

        emit shadesColorChanged(color);
    }
}

QColor ChartiumAxis::shadesBorderColor() const
{
    return shadesPen().color();
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
    switch (alignment)
    {
        case Qt::AlignTop:
        case Qt::AlignBottom:
            mOrientation = Qt::Horizontal;
            break;
        case Qt::AlignLeft:
        case Qt::AlignRight:
            mOrientation = Qt::Vertical;
            break;
        default:
            qWarning("No alignment specified !");
            break;
    }

    mAlignment = alignment;
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
    if (mReverse != reverse && type() != IChartiumAxis::AxisTypeBarCategory)
    {
        mReverse = reverse;

        emit reverseChanged(reverse);
    }
}

bool ChartiumAxis::isReverse() const
{
    return mReverse;
}

void ChartiumAxis::setLabelsEditable(bool editable)
{
    if (mLabelsEditable != editable)
    {
        // In the case if the axis already added to a chart
        // set the labels editability on the axisItem().
        // Otherwise the labels editability will be set in the
        // QValueAxisPrivate::initializeGraphics.
        if (axisItem() != nullptr)
        {
            axisItem()->setLabelsEditable(editable);
        }
        mLabelsEditable = editable;
        emit labelsEditableChanged(editable);
    }
}

bool ChartiumAxis::labelsEditable() const
{
    return mLabelsEditable;
}

void ChartiumAxis::setLabelsTruncated(bool labelsTruncated)
{
    if (mLabelsTruncated != labelsTruncated)
    {
        mLabelsTruncated = labelsTruncated;

        emit labelsTruncatedChanged(mLabelsTruncated);
    }
}

bool ChartiumAxis::labelsTruncated() const
{
    return mLabelsTruncated;
}

void ChartiumAxis::setTruncateLabels(bool truncateLabels)
{
    if (mTruncateLabels != truncateLabels)
    {
        mTruncateLabels = truncateLabels;

        emit truncateLabelsChanged(mTruncateLabels);
    }
}

bool ChartiumAxis::truncateLabels() const
{
    return mTruncateLabels;
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
    setRange(min, max);
}
