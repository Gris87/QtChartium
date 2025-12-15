#include "src/qtchartium/domain/chartiumdomain.h"



ChartiumDomain::ChartiumDomain(QObject* parent) :
    IChartiumDomain(parent),
    mMinX(),
    mMaxX(),
    mMinY(),
    mMaxY(),
    mSize(),
    mSignalsBlocked(),
    mZoomed(),
    mZoomResetMinX(),
    mZoomResetMaxX(),
    mZoomResetMinY(),
    mZoomResetMaxY(),
    mReverseX(),
    mReverseY()
{
}

ChartiumDomain::~ChartiumDomain()
{
}

void ChartiumDomain::setSize(const QSizeF& size)
{
    if (!size.isValid())
    {
        return;
    }

    if (mSize != size)
    {
        mSize = size;

        emit updated();
    }
}

QSizeF ChartiumDomain::size() const
{
    return mSize;
}

IChartiumDomain::DomainType ChartiumDomain::type()
{
    return IChartiumDomain::XYDomain;
}

void ChartiumDomain::setRange(qreal minX, qreal maxX, qreal minY, qreal maxY)
{
}

void ChartiumDomain::setRangeX(qreal min, qreal max)
{
    setRange(min, max, mMinY, mMaxY);
}

void ChartiumDomain::setRangeY(qreal min, qreal max)
{
    setRange(mMinX, mMaxX, min, max);
}

void ChartiumDomain::setMinX(qreal min)
{
    setRange(min, mMaxX, mMinY, mMaxY);
}

void ChartiumDomain::setMaxX(qreal max)
{
    setRange(mMinX, max, mMinY, mMaxY);
}

void ChartiumDomain::setMinY(qreal min)
{
    setRange(mMinX, mMaxX, min, mMaxY);
}

void ChartiumDomain::setMaxY(qreal max)
{
    setRange(mMinX, mMaxX, mMinY, max);
}

qreal ChartiumDomain::minX() const
{
    return 0;
}

qreal ChartiumDomain::maxX() const
{
    return 0;
}

qreal ChartiumDomain::minY() const
{
    return 0;
}

qreal ChartiumDomain::maxY() const
{
    return 0;
}

qreal ChartiumDomain::spanX() const
{
    Q_ASSERT(mMaxX >= mMinX);

    return mMaxX - mMinX;
}

qreal ChartiumDomain::spanY() const
{
    Q_ASSERT(mMaxY >= mMinY);

    return mMaxY - mMinY;
}

bool ChartiumDomain::isEmpty() const
{
    return qFuzzyCompare(spanX(), 0) || qFuzzyCompare(spanY(), 0) || mSize.isEmpty();
}

void ChartiumDomain::blockRangeSignals(bool block)
{
    if (mSignalsBlocked != block)
    {
        mSignalsBlocked = block;

        if (!mSignalsBlocked)
        {
            emit rangeHorizontalChanged(mMinX, mMaxX);
            emit rangeVerticalChanged(mMinY, mMaxY);
        }
    }
}

bool ChartiumDomain::rangeSignalsBlocked() const
{
    return false;
}

void ChartiumDomain::zoomReset()
{
    if (mZoomed)
    {
        setRange(mZoomResetMinX, mZoomResetMaxX, mZoomResetMinY, mZoomResetMaxY);
        mZoomed = false;
    }
}

void ChartiumDomain::storeZoomReset()
{
    if (!mZoomed)
    {
        mZoomed        = true;
        mZoomResetMinX = mMinX;
        mZoomResetMaxX = mMaxX;
        mZoomResetMinY = mMinY;
        mZoomResetMaxY = mMaxY;
    }
}

bool ChartiumDomain::isZoomed()
{
    return false;
}

void ChartiumDomain::zoomIn(const QRectF& rect)
{
}

void ChartiumDomain::zoomOut(const QRectF& rect)
{
}

void ChartiumDomain::move(qreal dx, qreal dy)
{
}

QPointF ChartiumDomain::calculateGeometryPoint(const QPointF& point, bool& ok) const
{
    return QPointF();
}

QPointF ChartiumDomain::calculateDomainPoint(const QPointF& point) const
{
    return QPointF();
}

QList<QPointF> ChartiumDomain::calculateGeometryPoints(const QList<QPointF>& list) const
{
    QList<QPointF> res;

    return res;
}

bool ChartiumDomain::attachAxis(IChartiumAxis* axis)
{
    if (axis->orientation() == Qt::Vertical)
    {
        // Color axis isn't connected to range-related slots/signals as it doesn't need
        // geometry domain and it doesn't need to handle zooming or scrolling.
        if (axis->type() != IChartiumAxis::AxisTypeColor)
        {
            QObject::connect(axis, SIGNAL(rangeChanged(qreal, qreal)), this, SLOT(handleVerticalAxisRangeChanged(qreal, qreal)));
            QObject::connect(this, SIGNAL(rangeVerticalChanged(qreal, qreal)), axis, SLOT(handleRangeChanged(qreal, qreal)));
        }
        QObject::connect(axis, &IChartiumAxis::reverseChanged, this, &IChartiumDomain::handleReverseYChanged);
        mReverseY = axis->isReverse();
    }

    if (axis->orientation() == Qt::Horizontal)
    {
        if (axis->type() != IChartiumAxis::AxisTypeColor)
        {
            QObject::connect(
                axis, SIGNAL(rangeChanged(qreal, qreal)), this, SLOT(handleHorizontalAxisRangeChanged(qreal, qreal))
            );
            QObject::connect(this, SIGNAL(rangeHorizontalChanged(qreal, qreal)), axis, SLOT(handleRangeChanged(qreal, qreal)));
        }

        QObject::connect(axis, &IChartiumAxis::reverseChanged, this, &IChartiumDomain::handleReverseXChanged);

        mReverseX = axis->isReverse();
    }

    return true;
}

bool ChartiumDomain::detachAxis(IChartiumAxis* axis)
{
    if (axis->orientation() == Qt::Vertical)
    {
        QObject::disconnect(axis, SIGNAL(rangeChanged(qreal, qreal)), this, SLOT(handleVerticalAxisRangeChanged(qreal, qreal)));
        QObject::disconnect(this, SIGNAL(rangeVerticalChanged(qreal, qreal)), axis, SLOT(handleRangeChanged(qreal, qreal)));
        QObject::disconnect(axis, &IChartiumAxis::reverseChanged, this, &IChartiumDomain::handleReverseYChanged);
    }

    if (axis->orientation() == Qt::Horizontal)
    {
        QObject::disconnect(axis, SIGNAL(rangeChanged(qreal, qreal)), this, SLOT(handleHorizontalAxisRangeChanged(qreal, qreal)));
        QObject::disconnect(this, SIGNAL(rangeHorizontalChanged(qreal, qreal)), axis, SLOT(handleRangeChanged(qreal, qreal)));
        QObject::disconnect(axis, &IChartiumAxis::reverseChanged, this, &IChartiumDomain::handleReverseXChanged);
    }

    return true;
}

void ChartiumDomain::looseNiceNumbers(qreal& min, qreal& max, int& ticksCount)
{
    qreal range = niceNumber(max - min, true); //range with ceiling
    qreal step  = niceNumber(range / (ticksCount - 1), false);

    min         = std::floor(min / step);
    max         = std::ceil(max / step);
    ticksCount  = int(max - min) + 1;
    min        *= step;
    max        *= step;
}

qreal ChartiumDomain::niceNumber(qreal x, bool ceiling)
{
    qreal z = qPow(10, qFloor(std::log10(x))); //find corresponding number of the form of 10^n than is smaller than x
    qreal q = x / z;                           //q<10 && q>=1;

    if (ceiling)
    {
        if (q <= 1.0)
        {
            q = 1;
        }
        else if (q <= 2.0)
        {
            q = 2;
        }
        else if (q <= 5.0)
        {
            q = 5;
        }
        else
        {
            q = 10;
        }
    }
    else
    {
        if (q < 1.5)
        {
            q = 1;
        }
        else if (q < 3.0)
        {
            q = 2;
        }
        else if (q < 7.0)
        {
            q = 5;
        }
        else
        {
            q = 10;
        }
    }

    return q * z;
}

void ChartiumDomain::setReverseX(bool reverse)
{
}

void ChartiumDomain::setReverseY(bool reverse)
{
}

bool ChartiumDomain::isReverseX() const
{
    return false;
}

bool ChartiumDomain::isReverseY() const
{
    return false;
}

void ChartiumDomain::adjustLogDomainRanges(qreal& min, qreal& max)
{
    if (min <= 0)
    {
        min = 1.0;

        if (max <= min)
        {
            max = min + 1.0;
        }
    }
}

QRectF ChartiumDomain::fixZoomRect(const QRectF& rect)
{
    QRectF fixRect = rect;

    if (mReverseX || mReverseY)
    {
        QPointF center = rect.center();

        if (mReverseX)
        {
            center.setX(mSize.width() - center.x());
        }

        if (mReverseY)
        {
            center.setY(mSize.height() - center.y());
        }

        fixRect.moveCenter(QPointF(center.x(), center.y()));
    }

    return fixRect;
}

void ChartiumDomain::handleVerticalAxisRangeChanged(qreal min, qreal max)
{
    setRangeY(min, max);
}

void ChartiumDomain::handleHorizontalAxisRangeChanged(qreal min, qreal max)
{
    setRangeX(min, max);
}

void ChartiumDomain::handleReverseXChanged(bool reverse)
{
    mReverseX = reverse;

    emit updated();
}

void ChartiumDomain::handleReverseYChanged(bool reverse)
{
    mReverseY = reverse;

    emit updated();
}
