#pragma once



#include "src/qtchartium/axis/chartiumaxis.h"

#include <QDateTime>



class IChartiumDateTimeAxis : public ChartiumAxis
{
    Q_OBJECT

public:
    explicit IChartiumDateTimeAxis(QObject* parent = nullptr) :
        ChartiumAxis(parent)
    {
    }
    ~IChartiumDateTimeAxis() override = default;

    IChartiumDateTimeAxis(const IChartiumDateTimeAxis& another)            = delete;
    IChartiumDateTimeAxis& operator=(const IChartiumDateTimeAxis& another) = delete;

    virtual void      setMin(QDateTime min)                  = 0;
    virtual QDateTime min() const                            = 0;
    virtual void      setMax(QDateTime max)                  = 0;
    virtual QDateTime max() const                            = 0;
    virtual void      setRange(QDateTime min, QDateTime max) = 0;

    virtual void    setFormat(QString format) = 0;
    virtual QString format() const            = 0;

    virtual void setTickCount(int count) = 0;
    virtual int  tickCount() const       = 0;

signals:
    void minChanged(QDateTime min);
    void maxChanged(QDateTime max);
    void rangeChanged(QDateTime min, QDateTime max);
    void formatChanged(QString format);
    void tickCountChanged(int tick);
};
