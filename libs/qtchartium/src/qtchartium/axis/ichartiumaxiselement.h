#pragma once



#include "src/qtchartium/chartiumelement.h"
#include <QGraphicsLayoutItem>



class IChartiumAxisElement : public ChartiumElement,
                             public QGraphicsLayoutItem
{
    Q_OBJECT

public:
    explicit IChartiumAxisElement(QGraphicsItem* item = nullptr, QGraphicsLayoutItem* parent = nullptr) :
        ChartiumElement(item),
        QGraphicsLayoutItem(parent)
    {
    }
    ~IChartiumAxisElement() override = default;

    IChartiumAxisElement(const IChartiumAxisElement& another)            = delete;
    IChartiumAxisElement& operator=(const IChartiumAxisElement& another) = delete;
};
