#pragma once



#include "src/qtchartium/axis/ichartiumeditableaxislabel.h"



class ChartiumEditableAxisLabel : public IChartiumEditableAxisLabel
{
    Q_OBJECT

public:
    explicit ChartiumEditableAxisLabel(QGraphicsItem* parent = nullptr);
    ~ChartiumEditableAxisLabel() override;

    ChartiumEditableAxisLabel(const ChartiumEditableAxisLabel& another)            = delete;
    ChartiumEditableAxisLabel& operator=(const ChartiumEditableAxisLabel& another) = delete;
};
