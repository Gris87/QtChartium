#pragma once



#include <QGraphicsLineItem>



class IChartiumLineArrowItem : public QGraphicsLineItem
{
public:
    explicit IChartiumLineArrowItem(QGraphicsItem* parent = nullptr) :
        QGraphicsLineItem(parent)
    {
    }
    ~IChartiumLineArrowItem() override = default;

    IChartiumLineArrowItem(const IChartiumLineArrowItem& another)            = delete;
    IChartiumLineArrowItem& operator=(const IChartiumLineArrowItem& another) = delete;
};
