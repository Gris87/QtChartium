#pragma once



#include "src/qtchartium/axis/datetimeaxis/ichartiumdatetimeaxis.h"



class ChartiumDateTimeAxis : public IChartiumDateTimeAxis
{
    Q_OBJECT

public:
    explicit ChartiumDateTimeAxis(QObject* parent = nullptr);
    ~ChartiumDateTimeAxis() override;

    ChartiumDateTimeAxis(const ChartiumDateTimeAxis& another)            = delete;
    ChartiumDateTimeAxis& operator=(const ChartiumDateTimeAxis& another) = delete;

    AxisType type() const override;

    void      setMin(QDateTime min) override;
    QDateTime min() const override;
    void      setMax(QDateTime max) override;
    QDateTime max() const override;
    void      setRange(QDateTime min, QDateTime max) override;

    void    setFormat(QString format) override;
    QString format() const override;

    void setTickCount(int count) override;
    int  tickCount() const override;

    void initializeGraphics(QGraphicsItem* parent) override;
    void initializeDomain(IChartiumDomain* domain) override;

    void setMin(const QVariant& min) override;
    void setMax(const QVariant& max) override;
    void setRange(const QVariant& min, const QVariant& max) override;

    qreal minReal() override;
    qreal maxReal() override;
    void  setRange(qreal min, qreal max) override;

protected:
    qreal   mMin;
    qreal   mMax;
    int     mTickCount;
    QString mFormat;
};
