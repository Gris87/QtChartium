#pragma once



#include "src/qtchartium/domain/ichartiumdomain.h"



class IChartiumXYDomain : public IChartiumDomain
{
    Q_OBJECT

public:
    explicit IChartiumXYDomain(QObject* parent = nullptr) :
        IChartiumDomain(parent)
    {
    }
    ~IChartiumXYDomain() override = default;

    IChartiumXYDomain(const IChartiumXYDomain& another)            = delete;
    IChartiumXYDomain& operator=(const IChartiumXYDomain& another) = delete;
};
