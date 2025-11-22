#pragma once



#include "src/qtchartium/axis/chartiumaxis.h"



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
};
