#pragma once



#include "src/qtchartium/axis/ichartiumaxis.h"



class ChartiumAxis : public IChartiumAxis
{
    Q_OBJECT

public:
    explicit ChartiumAxis(QObject* parent = nullptr);
    ~ChartiumAxis() override;

    ChartiumAxis(const ChartiumAxis& another)            = delete;
    ChartiumAxis& operator=(const ChartiumAxis& another) = delete;
};
