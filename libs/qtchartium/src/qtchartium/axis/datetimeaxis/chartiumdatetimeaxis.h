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
};
