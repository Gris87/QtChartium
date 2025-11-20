#pragma once



#include "src/qtchartium/domain/ichartiumdomain.h"



class ChartiumDomain : public IChartiumDomain
{
    Q_OBJECT

public:
    explicit ChartiumDomain(QObject* parent = nullptr);
    ~ChartiumDomain() override;

    ChartiumDomain(const ChartiumDomain& another)            = delete;
    ChartiumDomain& operator=(const ChartiumDomain& another) = delete;
};
