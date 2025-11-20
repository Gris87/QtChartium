#pragma once



#include "src/qtchartium/layout/ichartiumlayout.h"



class ChartiumLayout : public IChartiumLayout
{
    Q_OBJECT

public:
    explicit ChartiumLayout(QObject* parent = nullptr);
    ~ChartiumLayout() override;

    ChartiumLayout(const ChartiumLayout& another)            = delete;
    ChartiumLayout& operator=(const ChartiumLayout& another) = delete;
};
