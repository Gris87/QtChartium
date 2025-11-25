#pragma once



#include "src/qtchartium/axis/barcategoryaxis/ichartiumbarcategoryaxis.h"



class ChartiumBarCategoryAxis : public IChartiumBarCategoryAxis
{
    Q_OBJECT

public:
    explicit ChartiumBarCategoryAxis(QObject* parent = nullptr);
    ~ChartiumBarCategoryAxis() override;

    ChartiumBarCategoryAxis(const ChartiumBarCategoryAxis& another)            = delete;
    ChartiumBarCategoryAxis& operator=(const ChartiumBarCategoryAxis& another) = delete;
};
