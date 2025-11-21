#pragma once



#include <QObject>

#include <QPointF>
#include <QRectF>
#include <QSizeF>



class IChartiumAxis;



class IChartiumDomain : public QObject
{
    Q_OBJECT

public:
    enum DomainType : quint8
    {
        UndefinedDomain,
        XYDomain,
        XLogYDomain,
        LogXYDomain,
        LogXLogYDomain,
        XYPolarDomain,
        XLogYPolarDomain,
        LogXYPolarDomain,
        LogXLogYPolarDomain
    };

    explicit IChartiumDomain(QObject* parent = nullptr) :
        QObject(parent)
    {
    }
    ~IChartiumDomain() override = default;

    IChartiumDomain(const IChartiumDomain& another)            = delete;
    IChartiumDomain& operator=(const IChartiumDomain& another) = delete;

    virtual void   setSize(const QSizeF& size) = 0;
    virtual QSizeF size() const                = 0;

    virtual DomainType type() = 0;

    virtual void setRange(qreal minX, qreal maxX, qreal minY, qreal maxY) = 0;
    virtual void setRangeX(qreal min, qreal max)                          = 0;
    virtual void setRangeY(qreal min, qreal max)                          = 0;
    virtual void setMinX(qreal min)                                       = 0;
    virtual void setMaxX(qreal max)                                       = 0;
    virtual void setMinY(qreal min)                                       = 0;
    virtual void setMaxY(qreal max)                                       = 0;

    virtual qreal minX() const = 0;
    virtual qreal maxX() const = 0;
    virtual qreal minY() const = 0;
    virtual qreal maxY() const = 0;

    virtual qreal spanX() const   = 0;
    virtual qreal spanY() const   = 0;
    virtual bool  isEmpty() const = 0;

    virtual void blockRangeSignals(bool block) = 0;
    virtual bool rangeSignalsBlocked() const   = 0;

    virtual void zoomReset()      = 0;
    virtual void storeZoomReset() = 0;
    virtual bool isZoomed()       = 0;

    virtual void zoomIn(const QRectF& rect)  = 0;
    virtual void zoomOut(const QRectF& rect) = 0;
    virtual void move(qreal dx, qreal dy)    = 0;

    virtual QPointF        calculateGeometryPoint(const QPointF& point, bool& ok) const = 0;
    virtual QPointF        calculateDomainPoint(const QPointF& point) const             = 0;
    virtual QList<QPointF> calculateGeometryPoints(const QList<QPointF>& list) const    = 0;

    virtual bool attachAxis(IChartiumAxis* axis) = 0;
    virtual bool detachAxis(IChartiumAxis* axis) = 0;

    virtual void  looseNiceNumbers(qreal& min, qreal& max, int& ticksCount) = 0;
    virtual qreal niceNumber(qreal x, bool ceiling)                         = 0;

    virtual void setReverseX(bool reverse) = 0;
    virtual void setReverseY(bool reverse) = 0;

    virtual bool isReverseX() const = 0;
    virtual bool isReverseY() const = 0;

    virtual void   adjustLogDomainRanges(qreal& min, qreal& max) = 0;
    virtual QRectF fixZoomRect(const QRectF& rect)               = 0;

public slots:
    virtual void handleVerticalAxisRangeChanged(qreal min, qreal max)   = 0;
    virtual void handleHorizontalAxisRangeChanged(qreal min, qreal max) = 0;
    virtual void handleReverseXChanged(bool reverse)                    = 0;
    virtual void handleReverseYChanged(bool reverse)                    = 0;

signals:
    void updated();
    void rangeHorizontalChanged(qreal min, qreal max);
    void rangeVerticalChanged(qreal min, qreal max);
};
