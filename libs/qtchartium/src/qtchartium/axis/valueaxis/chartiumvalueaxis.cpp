#include "src/qtchartium/axis/valueaxis/chartiumvalueaxis.h"

#include "src/qtchartium/axis/ichartiumaxiselement.h"
#include "src/qtchartium/chartiumhelpers.h"
#include "src/qtchartium/ichartiumchart.h"



ChartiumValueAxis::ChartiumValueAxis(QObject* parent) :
    IChartiumValueAxis(parent),
    m_min(0),
    m_max(0),
    m_tickCount(5),
    m_minorTickCount(0),
    m_format(),
    m_applying(false),
    m_tickInterval(0.0),
    m_tickAnchor(0.0),
    m_tickType(TicksFixed)
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
    setRange(min, qMax(m_max, min));
}

qreal ChartiumValueAxis::min() const
{
    return m_min;
}

void ChartiumValueAxis::setMax(qreal max)
{
    setRange(qMin(m_min, max), max);
}

qreal ChartiumValueAxis::max() const
{
    return m_max;
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

    if (m_min != min)
    {
        m_min   = min;
        changed = true;

        emit minChanged(min);
    }

    if (m_max != max)
    {
        m_max   = max;
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
    if (m_tickCount != count && count >= 2)
    {
        m_tickCount = count;

        emit tickCountChanged(count);
    }
}

int ChartiumValueAxis::tickCount() const
{
    return m_tickCount;
}

void ChartiumValueAxis::setMinorTickCount(int count)
{
    if (m_minorTickCount != count && count >= 0)
    {
        m_minorTickCount = count;

        emit minorTickCountChanged(count);
    }
}

int ChartiumValueAxis::minorTickCount() const
{
    return m_minorTickCount;
}

void ChartiumValueAxis::setTickAnchor(qreal anchor)
{
    if (m_tickAnchor != anchor)
    {
        m_tickAnchor = anchor;

        emit tickAnchorChanged(anchor);
    }
}

qreal ChartiumValueAxis::tickAnchor() const
{
    return m_tickAnchor;
}

void ChartiumValueAxis::setTickInterval(qreal interval)
{
    if (m_tickInterval != interval)
    {
        m_tickInterval = interval;

        emit tickIntervalChanged(interval);
    }
}

qreal ChartiumValueAxis::tickInterval() const
{
    return m_tickInterval;
}

void ChartiumValueAxis::setTickType(TickType type)
{
    if (m_tickType != type)
    {
        m_tickType = type;

        emit tickTypeChanged(type);
    }
}

IChartiumValueAxis::TickType ChartiumValueAxis::tickType() const
{
    return m_tickType;
}

void ChartiumValueAxis::setLabelFormat(const QString& format)
{
    m_format = format;

    emit labelFormatChanged(format);
}

QString ChartiumValueAxis::labelFormat() const
{
    return m_format;
}

void ChartiumValueAxis::applyNiceNumbers()
{
    if (m_applying)
    {
        return;
    }

    qreal min   = m_min;
    qreal max   = m_max;
    int   ticks = m_tickCount;

    mDomain->looseNiceNumbers(min, max, ticks);

    m_applying = true;

    setRange(min, max);
    setTickCount(ticks);

    m_applying = false;
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
        if (!qFuzzyIsNull(m_max - m_min))
        {
            domain->setRangeY(m_min, m_max);
        }
        else
        {
            setRange(domain->minY(), domain->maxY());
        }
    }
    if (orientation() == Qt::Horizontal)
    {
        if (!qFuzzyIsNull(m_max - m_min))
        {
            domain->setRangeX(m_min, m_max);
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
