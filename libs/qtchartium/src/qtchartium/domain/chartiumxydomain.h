#pragma once



#include "src/qtchartium/domain/ichartiumxydomain.h"



class ChartiumXYDomain : public IChartiumXYDomain
{
    Q_OBJECT

public:
    explicit ChartiumXYDomain(QObject* parent = nullptr);
    ~ChartiumXYDomain() override;

    ChartiumXYDomain(const ChartiumXYDomain& another)            = delete;
    ChartiumXYDomain& operator=(const ChartiumXYDomain& another) = delete;

    DomainType type() override;

    void setRange(qreal minX, qreal maxX, qreal minY, qreal maxY) override;

    void zoomIn(const QRectF& rect) override;
    void zoomOut(const QRectF& rect) override;
    void move(qreal dx, qreal dy) override;

    QPointF        calculateGeometryPoint(const QPointF& point, bool& ok) const override;
    QPointF        calculateDomainPoint(const QPointF& point) const override;
    QList<QPointF> calculateGeometryPoints(const QList<QPointF>& list) const override;
};
