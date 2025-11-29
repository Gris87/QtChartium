#pragma once



#include "src/qtchartium/axis/chartiumeditableaxislabel.h"



class IChartiumValueAxisLabel : public ChartiumEditableAxisLabel
{
    Q_OBJECT

public:
    explicit IChartiumValueAxisLabel(QGraphicsItem* parent = nullptr) :
        ChartiumEditableAxisLabel(parent)
    {
    }
    ~IChartiumValueAxisLabel() override = default;

    IChartiumValueAxisLabel(const IChartiumValueAxisLabel& another)            = delete;
    IChartiumValueAxisLabel& operator=(const IChartiumValueAxisLabel& another) = delete;

    virtual qreal value() const                = 0;
    virtual void  setValue(const qreal& value) = 0;

signals:
    void valueChanged(qreal oldValue, qreal newValue);
};
