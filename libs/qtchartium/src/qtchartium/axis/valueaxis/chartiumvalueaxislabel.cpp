#include "src/qtchartium/axis/valueaxis/chartiumvalueaxislabel.h"



ChartiumValueAxisLabel::ChartiumValueAxisLabel(QGraphicsItem* parent) :
    IChartiumValueAxisLabel(parent)
{
}

ChartiumValueAxisLabel::~ChartiumValueAxisLabel()
{
}

qreal ChartiumValueAxisLabel::value() const
{
    return 0;
}

void ChartiumValueAxisLabel::setValue(const qreal& value)
{
}

void ChartiumValueAxisLabel::keyPressEvent(QKeyEvent* event)
{
}

void ChartiumValueAxisLabel::setInitialEditValue()
{
}

void ChartiumValueAxisLabel::finishEditing()
{
}

void ChartiumValueAxisLabel::resetBeforeEditValue()
{
}
