#include "src/qtchartium/axis/chartiumeditableaxislabel.h"



ChartiumEditableAxisLabel::ChartiumEditableAxisLabel(QGraphicsItem* parent) :
    IChartiumEditableAxisLabel(parent)
{
}

ChartiumEditableAxisLabel::~ChartiumEditableAxisLabel()
{
}

void ChartiumEditableAxisLabel::setEditable(bool editable)
{
}

void ChartiumEditableAxisLabel::reloadBeforeEditContent()
{
}

void ChartiumEditableAxisLabel::setInitialEditValue()
{
}

void ChartiumEditableAxisLabel::finishEditing()
{
}

void ChartiumEditableAxisLabel::resetBeforeEditValue()
{
}

bool ChartiumEditableAxisLabel::isEditEndingKeyPress(QKeyEvent* event)
{
    return false;
}

void ChartiumEditableAxisLabel::focusInEvent(QFocusEvent* event)
{
}

void ChartiumEditableAxisLabel::focusOutEvent(QFocusEvent* event)
{
}

bool ChartiumEditableAxisLabel::sceneEvent(QEvent* event)
{
    return false;
}

QRectF ChartiumEditableAxisLabel::boundingRect() const
{
    return QRectF();
}
