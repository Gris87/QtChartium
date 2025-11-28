#pragma once



#include "src/qtchartium/axis/chartiumaxis.h"



class IChartiumValueAxis : public ChartiumAxis
{
    Q_OBJECT

public:
    enum TickType
    {
        TicksDynamic = 0,
        TicksFixed
    };

    explicit IChartiumValueAxis(QObject* parent = nullptr) :
        ChartiumAxis(parent)
    {
    }
    ~IChartiumValueAxis() override = default;

    IChartiumValueAxis(const IChartiumValueAxis& another)            = delete;
    IChartiumValueAxis& operator=(const IChartiumValueAxis& another) = delete;

    virtual void  setMin(qreal min)              = 0;
    virtual qreal min() const                    = 0;
    virtual void  setMax(qreal max)              = 0;
    virtual qreal max() const                    = 0;
    virtual void  setRange(qreal min, qreal max) = 0;

    virtual void     setTickCount(int count)          = 0;
    virtual int      tickCount() const                = 0;
    virtual void     setMinorTickCount(int count)     = 0;
    virtual int      minorTickCount() const           = 0;
    virtual void     setTickAnchor(qreal anchor)      = 0;
    virtual qreal    tickAnchor() const               = 0;
    virtual void     setTickInterval(qreal insterval) = 0;
    virtual qreal    tickInterval() const             = 0;
    virtual void     setTickType(TickType type)       = 0;
    virtual TickType tickType() const                 = 0;

    virtual void    setLabelFormat(const QString& format) = 0;
    virtual QString labelFormat() const                   = 0;

public slots:
    virtual void applyNiceNumbers() = 0;

signals:
    void minChanged(qreal min);
    void maxChanged(qreal max);
    void rangeChanged(qreal min, qreal max);
    void tickCountChanged(int tickCount);
    void minorTickCountChanged(int tickCount);
    void labelFormatChanged(const QString& format);
    void tickIntervalChanged(qreal interval);
    void tickAnchorChanged(qreal anchor);
    void tickTypeChanged(TickType type);
};
