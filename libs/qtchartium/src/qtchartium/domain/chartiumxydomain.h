#pragma once



#include "src/qtchartium/domain/ichartiumxydomain.h"



class ChartiumXYDomain : public IChartiumXYDomain
{
    Q_OBJECT

public:
    explicit ChartiumXYDomain(QObject* parent = nullptr);
    ~ChartiumXYDomain() override;

    ChartiumXYDomain(const ChartiumXYDomain& another)            = delete;
    ChartiumXYDomain& operator=(const ChartiumXYDomain& another) = delete;
};
