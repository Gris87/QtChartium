#include "src/qtchartium/axis/datetimeaxis/chartiumdatetimeaxisx.h"



ChartiumDateTimeAxisX::ChartiumDateTimeAxisX(
    IChartiumDateTimeAxis* axis, IChartiumPresenter* presenter, QGraphicsItem* item, QGraphicsLayoutItem* parent
) :
    IChartiumDateTimeAxisX(axis, presenter, item, parent),
    mAxis(axis)
{
}

ChartiumDateTimeAxisX::~ChartiumDateTimeAxisX()
{
}

QSizeF ChartiumDateTimeAxisX::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
{
    return QSizeF();
}

QList<qreal> ChartiumDateTimeAxisX::calculateLayout() const
{
    QList<qreal> res;

    return res;
}

void ChartiumDateTimeAxisX::updateGeometry()
{
}

void ChartiumDateTimeAxisX::handleTickCountChanged(int tick)
{
}

void ChartiumDateTimeAxisX::handleFormatChanged(const QString& format)
{
}
