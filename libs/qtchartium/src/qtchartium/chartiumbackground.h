#pragma once



#include "src/qtchartium/ichartiumbackground.h"



class ChartiumBackground : public IChartiumBackground
{
    Q_OBJECT

public:
    explicit ChartiumBackground(QObject* parent = nullptr);
    ~ChartiumBackground() override;

    ChartiumBackground(const ChartiumBackground& another)            = delete;
    ChartiumBackground& operator=(const ChartiumBackground& another) = delete;
};
