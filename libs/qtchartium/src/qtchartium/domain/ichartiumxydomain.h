#pragma once



#include "src/qtchartium/domain/chartiumdomain.h"



class IChartiumXYDomain : public ChartiumDomain
{
    Q_OBJECT

public:
    explicit IChartiumXYDomain(QObject* parent = nullptr) :
        ChartiumDomain(parent)
    {
    }
    ~IChartiumXYDomain() override = default;

    IChartiumXYDomain(const IChartiumXYDomain& another)            = delete;
    IChartiumXYDomain& operator=(const IChartiumXYDomain& another) = delete;
};
