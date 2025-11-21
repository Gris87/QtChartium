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
}

QSizeF ChartiumDomain::size() const
{
    return QSizeF();
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
}

void ChartiumDomain::setRangeY(qreal min, qreal max)
{
}

void ChartiumDomain::setMinX(qreal min)
{
}

void ChartiumDomain::setMaxX(qreal max)
{
}

void ChartiumDomain::setMinY(qreal min)
{
}

void ChartiumDomain::setMaxY(qreal max)
{
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
    return 0;
}

qreal ChartiumDomain::spanY() const
{
    return 0;
}

bool ChartiumDomain::isEmpty() const
{
    return false;
}

void ChartiumDomain::blockRangeSignals(bool block)
{
}

bool ChartiumDomain::rangeSignalsBlocked() const
{
    return false;
}

void ChartiumDomain::zoomReset()
{
}

void ChartiumDomain::storeZoomReset()
{
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
    return false;
}

bool ChartiumDomain::detachAxis(IChartiumAxis* axis)
{
    return false;
}

void ChartiumDomain::looseNiceNumbers(qreal& min, qreal& max, int& ticksCount)
{
}

qreal ChartiumDomain::niceNumber(qreal x, bool ceiling)
{
    return 0;
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
}

QRectF ChartiumDomain::fixZoomRect(const QRectF& rect)
{
    return QRectF();
}

void ChartiumDomain::handleVerticalAxisRangeChanged(qreal min, qreal max)
{
}

void ChartiumDomain::handleHorizontalAxisRangeChanged(qreal min, qreal max)
{
}

void ChartiumDomain::handleReverseXChanged(bool reverse)
{
}

void ChartiumDomain::handleReverseYChanged(bool reverse)
{
}
