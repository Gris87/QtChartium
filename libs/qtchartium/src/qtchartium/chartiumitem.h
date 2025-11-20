#pragma once



#include "src/qtchartium/ichartiumitem.h"



class ChartiumItem : public IChartiumItem
{
    Q_OBJECT

public:
    explicit ChartiumItem(QObject* parent = nullptr);
    ~ChartiumItem() override;

    ChartiumItem(const ChartiumItem& another)            = delete;
    ChartiumItem& operator=(const ChartiumItem& another) = delete;
};
