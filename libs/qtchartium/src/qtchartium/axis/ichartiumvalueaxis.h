#pragma once



#include "src/qtchartium/axis/chartiumaxis.h"



class IChartiumValueAxis : public ChartiumAxis
{
    Q_OBJECT

public:
    explicit IChartiumValueAxis(QObject* parent = nullptr) :
        ChartiumAxis(parent)
    {
    }
    ~IChartiumValueAxis() override = default;

    IChartiumValueAxis(const IChartiumValueAxis& another)            = delete;
    IChartiumValueAxis& operator=(const IChartiumValueAxis& another) = delete;
};
