#include "src/qtchartium/axis/valueaxis/chartiumvalueaxis.h"

#include "src/qtchartium/axis/ichartiumaxiselement.h"
#include "src/qtchartium/chartiumhelpers.h"
#include "src/qtchartium/ichartiumchart.h"



ChartiumValueAxis::ChartiumValueAxis(QObject* parent) :
    IChartiumValueAxis(parent),
    mMin(0),
    mMax(0),
    mTickCount(5),
    mMinorTickCount(0),
    mFormat(),
    mApplying(false),
    mTickInterval(0.0),
    mTickAnchor(0.0),
    mTickType(TicksFixed)
{
}

ChartiumValueAxis::~ChartiumValueAxis()
{
    if (mChart)
    {
        mChart->removeAxis(this);
    }
}

IChartiumAxis::AxisType ChartiumValueAxis::type() const
{
    return IChartiumAxis::AxisTypeValue;
}

void ChartiumValueAxis::setMin(qreal min)
{
    setRange(min, qMax(mMax, min));
}

qreal ChartiumValueAxis::min() const
{
    return mMin;
}

void ChartiumValueAxis::setMax(qreal max)
{
    setRange(qMin(mMin, max), max);
}

qreal ChartiumValueAxis::max() const
{
    return mMax;
}

void ChartiumValueAxis::setRange(qreal min, qreal max)
{
    bool changed = false;

    if (min > max)
    {
        return;
    }

    if (!isValidValue(min, max))
    {
        return;
    }

    if (mMin != min)
    {
        mMin    = min;
        changed = true;

        emit minChanged(min);
    }

    if (mMax != max)
    {
        mMax    = max;
        changed = true;

        emit maxChanged(max);
    }

    if (changed)
    {
        emit rangeChanged(min, max);
    }
}

void ChartiumValueAxis::setTickCount(int count)
{
    if (mTickCount != count && count >= 2)
    {
        mTickCount = count;

        emit tickCountChanged(count);
    }
}

int ChartiumValueAxis::tickCount() const
{
    return mTickCount;
}

void ChartiumValueAxis::setMinorTickCount(int count)
{
    if (mMinorTickCount != count && count >= 0)
    {
        mMinorTickCount = count;

        emit minorTickCountChanged(count);
    }
}

int ChartiumValueAxis::minorTickCount() const
{
    return mMinorTickCount;
}

void ChartiumValueAxis::setTickAnchor(qreal anchor)
{
    if (mTickAnchor != anchor)
    {
        mTickAnchor = anchor;

        emit tickAnchorChanged(anchor);
    }
}

qreal ChartiumValueAxis::tickAnchor() const
{
    return mTickAnchor;
}

void ChartiumValueAxis::setTickInterval(qreal interval)
{
    if (mTickInterval != interval)
    {
        mTickInterval = interval;

        emit tickIntervalChanged(interval);
    }
}

qreal ChartiumValueAxis::tickInterval() const
{
    return mTickInterval;
}

void ChartiumValueAxis::setTickType(TickType type)
{
    if (mTickType != type)
    {
        mTickType = type;

        emit tickTypeChanged(type);
    }
}

IChartiumValueAxis::TickType ChartiumValueAxis::tickType() const
{
    return mTickType;
}

void ChartiumValueAxis::setLabelFormat(const QString& format)
{
    mFormat = format;

    emit labelFormatChanged(format);
}

QString ChartiumValueAxis::labelFormat() const
{
    return mFormat;
}

void ChartiumValueAxis::applyNiceNumbers()
{
    if (mApplying)
    {
        return;
    }

    qreal min   = mMin;
    qreal max   = mMax;
    int   ticks = mTickCount;

    mDomain->looseNiceNumbers(min, max, ticks);

    mApplying = true;

    setRange(min, max);
    setTickCount(ticks);

    mApplying = false;
}

void ChartiumValueAxis::initializeGraphics(QGraphicsItem* parent)
{
    IChartiumAxisElement* axis = nullptr;

    if (mChart->chartType() == IChartiumChart::ChartTypeCartesian)
    {
        // TODO: Uncomment
        /*
        if (orientation() == Qt::Vertical)
        {
            axis = new ChartValueAxisY(q, parent);
        }
        else
        if (orientation() == Qt::Horizontal)
        {
            axis = new ChartValueAxisX(q, parent);
        }
        else
        {
            qFatal() << "Unexpected behaviour";
        }
        */

        axis->setLabelsEditable(labelsEditable());
    }

    mItem = axis;
    IChartiumValueAxis::initializeGraphics(parent);
}

void ChartiumValueAxis::initializeDomain(IChartiumDomain* domain)
{
    if (orientation() == Qt::Vertical)
    {
        if (!qFuzzyIsNull(mMax - mMin))
        {
            domain->setRangeY(mMin, mMax);
        }
        else
        {
            setRange(domain->minY(), domain->maxY());
        }
    }
    if (orientation() == Qt::Horizontal)
    {
        if (!qFuzzyIsNull(mMax - mMin))
        {
            domain->setRangeX(mMin, mMax);
        }
        else
        {
            setRange(domain->minX(), domain->maxX());
        }
    }
}

void ChartiumValueAxis::setMin(const QVariant& min)
{
    bool  ok;
    qreal value = min.toReal(&ok);

    if (ok)
    {
        setMin(value);
    }
}

void ChartiumValueAxis::setMax(const QVariant& max)
{
    bool  ok;
    qreal value = max.toReal(&ok);

    if (ok)
    {
        setMax(value);
    }
}

void ChartiumValueAxis::setRange(const QVariant& min, const QVariant& max)
{
    bool  ok1;
    bool  ok2;
    qreal value1 = min.toReal(&ok1);
    qreal value2 = max.toReal(&ok2);

    if (ok1 && ok2)
    {
        setRange(value1, value2);
    }
}
