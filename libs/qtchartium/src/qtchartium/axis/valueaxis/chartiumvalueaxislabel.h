#pragma once



#include "src/qtchartium/axis/valueaxis/ichartiumvalueaxislabel.h"



class ChartiumValueAxisLabel : public IChartiumValueAxisLabel
{
    Q_OBJECT

public:
    explicit ChartiumValueAxisLabel(QGraphicsItem* parent = nullptr);
    ~ChartiumValueAxisLabel() override;

    ChartiumValueAxisLabel(const ChartiumValueAxisLabel& another)            = delete;
    ChartiumValueAxisLabel& operator=(const ChartiumValueAxisLabel& another) = delete;

    qreal value() const override;
    void  setValue(const qreal& value) override;

    void keyPressEvent(QKeyEvent* event) override;

    void setInitialEditValue() override;
    void finishEditing() override;
    void resetBeforeEditValue() override;

protected:
    qreal mValue;
    qreal mValueBeforeEdit;
};
