#include "src/qtchartium/axis/datetimeaxis/chartiumdatetimeaxis.h"

#include "src/qtchartium/axis/ichartiumcartesianaxis.h"
#include "src/qtchartium/ichartiumchart.h"



ChartiumDateTimeAxis::ChartiumDateTimeAxis(QObject* parent) :
    IChartiumDateTimeAxis(parent),
    mMin(),
    mMax(),
    mTickCount(5),
    mFormat("dd-MM-yyyy\nh:mm")
{
}

ChartiumDateTimeAxis::~ChartiumDateTimeAxis()
{
    if (mChart != nullptr)
    {
        mChart->removeAxis(this);
    }
}

IChartiumAxis::AxisType ChartiumDateTimeAxis::type() const
{
    return IChartiumAxis::AxisTypeDateTime;
}

void ChartiumDateTimeAxis::setMin(QDateTime min)
{
    if (min.isValid())
    {
        setRange(min.toMSecsSinceEpoch(), qMax(mMax, qreal(min.toMSecsSinceEpoch())));
    }
}

QDateTime ChartiumDateTimeAxis::min() const
{
    return QDateTime::fromMSecsSinceEpoch(mMin);
}

void ChartiumDateTimeAxis::setMax(QDateTime max)
{
    if (max.isValid())
    {
        setRange(qMin(mMin, qreal(max.toMSecsSinceEpoch())), max.toMSecsSinceEpoch());
    }
}

QDateTime ChartiumDateTimeAxis::max() const
{
    return QDateTime::fromMSecsSinceEpoch(mMax);
}

void ChartiumDateTimeAxis::setRange(QDateTime min, QDateTime max)
{
    if (!min.isValid() || !max.isValid() || min > max)
    {
        return;
    }

    setRange(min.toMSecsSinceEpoch(), max.toMSecsSinceEpoch());
}

void ChartiumDateTimeAxis::setFormat(QString format)
{
    if (mFormat != format)
    {
        mFormat = format;

        if (axisItem() != nullptr)
        {
            static_cast<IChartiumCartesianAxis*>(axisItem())->setDateTimeLabelsFormat(format);
        }

        emit formatChanged(format);
    }
}

QString ChartiumDateTimeAxis::format() const
{
    return mFormat;
}

void ChartiumDateTimeAxis::setTickCount(int count)
{
    if (mTickCount != count && count >= 2)
    {
        mTickCount = count;

        emit tickCountChanged(count);
    }
}

int ChartiumDateTimeAxis::tickCount() const
{
    return mTickCount;
}

void ChartiumDateTimeAxis::initializeGraphics(QGraphicsItem* parent)
{
    IChartiumAxisElement* axis = nullptr;

    if (mChart->chartType() == IChartiumChart::ChartTypeCartesian)
    {
        // TODO: Uncomment
        /*
        if (orientation() == Qt::Vertical)
        {
            axis = new ChartDateTimeAxisY(q, parent);
        }
        else if (orientation() == Qt::Horizontal)
        {
            axis = new ChartDateTimeAxisX(q, parent);
        }
        else
        {
            qFatal() << "Unexpected behaviour";
        }
        */

        axis->setLabelsEditable(labelsEditable());
    }

    mItem = axis;
    IChartiumDateTimeAxis::initializeGraphics(parent);
}

void ChartiumDateTimeAxis::initializeDomain(IChartiumDomain* domain)
{
    if (mMax == mMin)
    {
        if (orientation() == Qt::Vertical)
        {
            setRange(domain->minY(), domain->maxY());
        }
        else
        {
            setRange(domain->minX(), domain->maxX());
        }
    }
    else
    {
        if (orientation() == Qt::Vertical)
        {
            domain->setRangeY(mMin, mMax);
        }
        else
        {
            domain->setRangeX(mMin, mMax);
        }
    }
}

void ChartiumDateTimeAxis::setMin(const QVariant& min)
{
    if (min.canConvert<QDateTime>())
    {
        setMin(min.toDateTime());
    }
}

void ChartiumDateTimeAxis::setMax(const QVariant& max)
{
    if (max.canConvert<QDateTime>())
    {
        setMax(max.toDateTime());
    }
}

void ChartiumDateTimeAxis::setRange(const QVariant& min, const QVariant& max)
{
    if (min.canConvert<QDateTime>() && max.canConvert<QDateTime>())
    {
        setRange(min.toDateTime(), max.toDateTime());
    }
}

qreal ChartiumDateTimeAxis::minReal()
{
    return mMin;
}

qreal ChartiumDateTimeAxis::maxReal()
{
    return mMax;
}

void ChartiumDateTimeAxis::setRange(qreal min, qreal max)
{
    bool changed = false;

    if (mMin != min)
    {
        mMin    = min;
        changed = true;

        emit minChanged(QDateTime::fromMSecsSinceEpoch(min));
    }

    if (mMax != max)
    {
        mMax    = max;
        changed = true;

        emit maxChanged(QDateTime::fromMSecsSinceEpoch(max));
    }

    if (changed)
    {
        emit rangeChanged(QDateTime::fromMSecsSinceEpoch(min), QDateTime::fromMSecsSinceEpoch(max));
        emit rangeRealChanged(mMin, mMax);
    }
}
