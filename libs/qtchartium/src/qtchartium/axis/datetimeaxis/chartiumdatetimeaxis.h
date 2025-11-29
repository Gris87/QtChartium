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
};
