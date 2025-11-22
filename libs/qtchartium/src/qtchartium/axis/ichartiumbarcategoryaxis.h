#pragma once



#include "src/qtchartium/axis/chartiumaxis.h"



class IChartiumBarCategoryAxis : public ChartiumAxis
{
    Q_OBJECT

public:
    explicit IChartiumBarCategoryAxis(QObject* parent = nullptr) :
        ChartiumAxis(parent)
    {
    }
    ~IChartiumBarCategoryAxis() override = default;

    IChartiumBarCategoryAxis(const IChartiumBarCategoryAxis& another)            = delete;
    IChartiumBarCategoryAxis& operator=(const IChartiumBarCategoryAxis& another) = delete;
};
