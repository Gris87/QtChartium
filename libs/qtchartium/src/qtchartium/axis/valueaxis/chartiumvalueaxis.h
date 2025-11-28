#pragma once



#include "src/qtchartium/axis/valueaxis/ichartiumvalueaxis.h"



class ChartiumValueAxis : public IChartiumValueAxis
{
    Q_OBJECT

public:
    explicit ChartiumValueAxis(QObject* parent = nullptr);
    ~ChartiumValueAxis() override;

    ChartiumValueAxis(const ChartiumValueAxis& another)            = delete;
    ChartiumValueAxis& operator=(const ChartiumValueAxis& another) = delete;

    AxisType type() const override;

    void  setMin(qreal min) override;
    qreal min() const override;
    void  setMax(qreal max) override;
    qreal max() const override;
    void  setRange(qreal min, qreal max) override;

    void     setTickCount(int count) override;
    int      tickCount() const override;
    void     setMinorTickCount(int count) override;
    int      minorTickCount() const override;
    void     setTickAnchor(qreal anchor) override;
    qreal    tickAnchor() const override;
    void     setTickInterval(qreal interval) override;
    qreal    tickInterval() const override;
    void     setTickType(TickType type) override;
    TickType tickType() const override;

    void    setLabelFormat(const QString& format) override;
    QString labelFormat() const override;

public slots:
    void applyNiceNumbers() override;

protected:
    void initializeGraphics(QGraphicsItem* parent) override;
    void initializeDomain(IChartiumDomain* domain) override;

    void setMin(const QVariant& min) override;
    void setMax(const QVariant& max) override;
    void setRange(const QVariant& min, const QVariant& max) override;

    IChartiumDomain* mDomain;
    qreal            mMin;
    qreal            mMax;
    int              mTickCount;
    int              mMinorTickCount;
    QString          mFormat;
    bool             mApplying;
    qreal            mTickInterval;
    qreal            mTickAnchor;
    TickType         mTickType;
};
