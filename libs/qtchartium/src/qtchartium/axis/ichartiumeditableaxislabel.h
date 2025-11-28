#pragma once



#include <QGraphicsTextItem>



class IChartiumEditableAxisLabel : public QGraphicsTextItem
{
    Q_OBJECT

public:
    explicit IChartiumEditableAxisLabel(QGraphicsItem* parent = nullptr) :
        QGraphicsTextItem(parent)
    {
    }
    ~IChartiumEditableAxisLabel() override = default;

    IChartiumEditableAxisLabel(const IChartiumEditableAxisLabel& another)            = delete;
    IChartiumEditableAxisLabel& operator=(const IChartiumEditableAxisLabel& another) = delete;
};
