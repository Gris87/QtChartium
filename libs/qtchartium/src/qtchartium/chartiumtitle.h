#pragma once



#include "src/qtchartium/ichartiumtitle.h"



class ChartiumTitle : public IChartiumTitle
{
    Q_OBJECT

public:
    explicit ChartiumTitle(QObject* parent = nullptr);
    ~ChartiumTitle() override;

    ChartiumTitle(const ChartiumTitle& another)            = delete;
    ChartiumTitle& operator=(const ChartiumTitle& another) = delete;
};
