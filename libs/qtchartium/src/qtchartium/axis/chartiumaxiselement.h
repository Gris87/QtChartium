#pragma once



#include "src/qtchartium/axis/ichartiumaxiselement.h"



class ChartiumAxisElement : public IChartiumAxisElement
{
    Q_OBJECT

public:
    explicit ChartiumAxisElement(QObject* parent = nullptr);
    ~ChartiumAxisElement() override;

    ChartiumAxisElement(const ChartiumAxisElement& another)            = delete;
    ChartiumAxisElement& operator=(const ChartiumAxisElement& another) = delete;
};
