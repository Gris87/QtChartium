#include "src/qtchartium/chartiumhelpers.h"

#include <QDebug>



bool isValidValue(qreal value)
{
    if (qIsNaN(value) || qIsInf(value))
    {
        qWarning() << "Ignored NaN, Inf, or -Inf value.";

        return false;
    }

    return true;
}

bool isValidValue(qreal x, qreal y)
{
    return (isValidValue(x) && isValidValue(y));
}

bool isValidValue(const QPointF point)
{
    return (isValidValue(point.x()) && isValidValue(point.y()));
}
