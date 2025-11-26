#pragma once



#include "src/qtchartium/domain/ichartiumdomain.h"

#include "src/qtchartium/axis/ichartiumaxis.h"



class ChartiumDomain : public IChartiumDomain
{
    Q_OBJECT

public:
    explicit ChartiumDomain(QObject* parent = nullptr);
    ~ChartiumDomain() override;

    ChartiumDomain(const ChartiumDomain& another)            = delete;
    ChartiumDomain& operator=(const ChartiumDomain& another) = delete;

    void   setSize(const QSizeF& size) override;
    QSizeF size() const override;

    DomainType type() override;

    void setRange(qreal minX, qreal maxX, qreal minY, qreal maxY) override;
    void setRangeX(qreal min, qreal max) override;
    void setRangeY(qreal min, qreal max) override;
    void setMinX(qreal min) override;
    void setMaxX(qreal max) override;
    void setMinY(qreal min) override;
    void setMaxY(qreal max) override;

    qreal minX() const override;
    qreal maxX() const override;
    qreal minY() const override;
    qreal maxY() const override;

    qreal spanX() const override;
    qreal spanY() const override;
    bool  isEmpty() const override;

    void blockRangeSignals(bool block) override;
    bool rangeSignalsBlocked() const override;

    void zoomReset() override;
    void storeZoomReset() override;
    bool isZoomed() override;

    void zoomIn(const QRectF& rect) override;
    void zoomOut(const QRectF& rect) override;
    void move(qreal dx, qreal dy) override;

    QPointF        calculateGeometryPoint(const QPointF& point, bool& ok) const override;
    QPointF        calculateDomainPoint(const QPointF& point) const override;
    QList<QPointF> calculateGeometryPoints(const QList<QPointF>& list) const override;

    bool attachAxis(IChartiumAxis* axis) override;
    bool detachAxis(IChartiumAxis* axis) override;

    void  looseNiceNumbers(qreal& min, qreal& max, int& ticksCount) override;
    qreal niceNumber(qreal x, bool ceiling) override;

    void setReverseX(bool reverse) override;
    void setReverseY(bool reverse) override;

    bool isReverseX() const override;
    bool isReverseY() const override;

    void   adjustLogDomainRanges(qreal& min, qreal& max) override;
    QRectF fixZoomRect(const QRectF& rect) override;

public slots:
    void handleVerticalAxisRangeChanged(qreal min, qreal max) override;
    void handleHorizontalAxisRangeChanged(qreal min, qreal max) override;
    void handleReverseXChanged(bool reverse) override;
    void handleReverseYChanged(bool reverse) override;

protected:
    qreal  mMinX;
    qreal  mMaxX;
    qreal  mMinY;
    qreal  mMaxY;
    QSizeF mSize;
    bool   mSignalsBlocked;
    bool   mZoomed;
    qreal  mZoomResetMinX;
    qreal  mZoomResetMaxX;
    qreal  mZoomResetMinY;
    qreal  mZoomResetMaxY;
    bool   mReverseX;
    bool   mReverseY;
};
