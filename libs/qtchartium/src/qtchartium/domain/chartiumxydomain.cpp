#include "src/qtchartium/domain/chartiumxydomain.h"



ChartiumXYDomain::ChartiumXYDomain(QObject* parent) :
    IChartiumXYDomain(parent)
{
}

ChartiumXYDomain::~ChartiumXYDomain()
{
}

IChartiumDomain::DomainType ChartiumXYDomain::type()
{
    return IChartiumDomain::XYDomain;
}

void ChartiumXYDomain::setRange(qreal minX, qreal maxX, qreal minY, qreal maxY)
{
    bool axisXChanged = false;
    bool axisYChanged = false;

    if (!qFuzzyCompare(mMinX, minX) || !qFuzzyCompare(mMaxX, maxX))
    {
        mMinX        = minX;
        mMaxX        = maxX;
        axisXChanged = true;

        if (!mSignalsBlocked)
        {
            emit rangeHorizontalChanged(mMinX, mMaxX);
        }
    }

    if (!qFuzzyCompare(mMinY, minY) || !qFuzzyCompare(mMaxY, maxY))
    {
        mMinY        = minY;
        mMaxY        = maxY;
        axisYChanged = true;

        if (!mSignalsBlocked)
        {
            emit rangeVerticalChanged(mMinY, mMaxY);
        }
    }

    if (axisXChanged || axisYChanged)
    {
        emit updated();
    }
}

void ChartiumXYDomain::zoomIn(const QRectF& rect)
{
    storeZoomReset();

    QRectF fixedRect = fixZoomRect(rect);
    qreal  dx        = spanX() / mSize.width();
    qreal  dy        = spanY() / mSize.height();

    qreal maxX = mMaxX;
    qreal minX = mMinX;
    qreal minY = mMinY;
    qreal maxY = mMaxY;

    maxX = minX + dx * fixedRect.right();
    minX = minX + dx * fixedRect.left();
    minY = maxY - dy * fixedRect.bottom();
    maxY = maxY - dy * fixedRect.top();

    if ((maxX - minX) == spanX())
    {
        minX = mMinX;
        maxX = mMaxX;
    }

    if ((maxY - minY) == spanY())
    {
        minY = mMinY;
        maxY = mMaxY;
    }

    setRange(minX, maxX, minY, maxY);
}

void ChartiumXYDomain::zoomOut(const QRectF& rect)
{
    storeZoomReset();

    QRectF fixedRect = fixZoomRect(rect);
    qreal  dx        = spanX() / rect.width();
    qreal  dy        = spanY() / rect.height();

    qreal maxX = mMaxX;
    qreal minX = mMinX;
    qreal minY = mMinY;
    qreal maxY = mMaxY;

    minX = maxX - dx * fixedRect.right();
    maxX = minX + dx * mSize.width();
    maxY = minY + dy * fixedRect.bottom();
    minY = maxY - dy * mSize.height();

    if ((maxX - minX) == spanX())
    {
        minX = mMinX;
        maxX = mMaxX;
    }

    if ((maxY - minY) == spanY())
    {
        minY = mMinY;
        maxY = mMaxY;
    }

    setRange(minX, maxX, minY, maxY);
}

void ChartiumXYDomain::move(qreal dx, qreal dy)
{
    if (mReverseX)
    {
        dx = -dx;
    }

    if (mReverseY)
    {
        dy = -dy;
    }

    qreal x = spanX() / mSize.width();
    qreal y = spanY() / mSize.height();

    qreal maxX = mMaxX;
    qreal minX = mMinX;
    qreal minY = mMinY;
    qreal maxY = mMaxY;

    if (dx != 0)
    {
        minX = minX + x * dx;
        maxX = maxX + x * dx;
    }

    if (dy != 0)
    {
        minY = minY + y * dy;
        maxY = maxY + y * dy;
    }

    setRange(minX, maxX, minY, maxY);
}

QPointF ChartiumXYDomain::calculateGeometryPoint(const QPointF& point, bool& ok) const
{
    const qreal xd = mMaxX - mMinX;
    const qreal yd = mMaxY - mMinY;

    if (xd == 0.0 || yd == 0.0)
    {
        return QPointF();
    }

    const qreal deltaX = mSize.width() / xd;
    const qreal deltaY = mSize.height() / yd;
    qreal       x      = (point.x() - mMinX) * deltaX;

    if (mReverseX)
    {
        x = mSize.width() - x;
    }

    qreal y = (point.y() - mMinY) * deltaY;

    if (!mReverseY)
    {
        y = mSize.height() - y;
    }

    ok = true;

    return QPointF(x, y);
}

QPointF ChartiumXYDomain::calculateDomainPoint(const QPointF& point) const
{
    const qreal xd = mMaxX - mMinX;
    const qreal yd = mMaxY - mMinY;

    if (xd == 0.0 || yd == 0.0)
    {
        return QPointF();
    }

    const qreal deltaX = mSize.width() / xd;
    const qreal deltaY = mSize.height() / yd;

    qreal x  = mReverseX ? (mSize.width() - point.x()) : point.x();
    x       /= deltaX;
    x       += mMinX;
    qreal y  = mReverseY ? point.y() : (mSize.height() - point.y());
    y       /= deltaY;
    y       += mMinY;

    return QPointF(x, y);
}

QList<QPointF> ChartiumXYDomain::calculateGeometryPoints(const QList<QPointF>& list) const
{
    const qreal xd = mMaxX - mMinX;
    const qreal yd = mMaxY - mMinY;

    if (xd == 0.0 || yd == 0.0)
    {
        return QList<QPointF>();
    }

    const qreal deltaX = mSize.width() / xd;
    const qreal deltaY = mSize.height() / yd;

    QList<QPointF> result;
    result.resize(list.size());

    for (int i = 0; i < list.size(); ++i)
    {
        qreal x = (list[i].x() - mMinX) * deltaX;

        if (mReverseX)
        {
            x = mSize.width() - x;
        }

        qreal y = (list[i].y() - mMinY) * deltaY;

        if (!mReverseY)
        {
            y = mSize.height() - y;
        }

        result[i].setX(x);
        result[i].setY(y);
    }

    return result;
}
