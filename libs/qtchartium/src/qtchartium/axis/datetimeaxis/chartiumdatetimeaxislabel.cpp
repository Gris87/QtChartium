#include "src/qtchartium/axis/datetimeaxis/chartiumdatetimeaxislabel.h"



ChartiumDateTimeAxisLabel::ChartiumDateTimeAxisLabel(QGraphicsItem* parent) :
    IChartiumDateTimeAxisLabel(parent)
{
}

ChartiumDateTimeAxisLabel::~ChartiumDateTimeAxisLabel()
{
}

QDateTime ChartiumDateTimeAxisLabel::value() const
{
    return QDateTime();
}

void ChartiumDateTimeAxisLabel::setValue(const QDateTime& value)
{
}

void ChartiumDateTimeAxisLabel::setFormat(const QString& format)
{
}

void ChartiumDateTimeAxisLabel::keyPressEvent(QKeyEvent* event)
{
}

void ChartiumDateTimeAxisLabel::setInitialEditValue()
{
}

void ChartiumDateTimeAxisLabel::finishEditing()
{
}

void ChartiumDateTimeAxisLabel::resetBeforeEditValue()
{
}
