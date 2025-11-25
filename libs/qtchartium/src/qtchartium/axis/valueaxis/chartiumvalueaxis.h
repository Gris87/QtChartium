#pragma once



#include "src/qtchartium/axis/valueaxis/ichartiumvalueaxis.h"



class ChartiumValueAxis : public IChartiumValueAxis
{
    Q_OBJECT

public:
    explicit ChartiumValueAxis(QObject* parent = nullptr);
    ~ChartiumValueAxis() override;

    ChartiumValueAxis(const ChartiumValueAxis& another)            = delete;
    ChartiumValueAxis& operator=(const ChartiumValueAxis& another) = delete;
};
