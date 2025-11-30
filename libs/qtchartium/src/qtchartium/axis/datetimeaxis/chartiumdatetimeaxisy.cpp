#include "src/qtchartium/axis/datetimeaxis/chartiumdatetimeaxisy.h"



ChartiumDateTimeAxisY::ChartiumDateTimeAxisY(
    IChartiumDateTimeAxis* axis, IChartiumPresenter* presenter, QGraphicsItem* item, QGraphicsLayoutItem* parent
) :
    IChartiumDateTimeAxisY(axis, presenter, item, parent),
    mAxis(axis)
{
}

ChartiumDateTimeAxisY::~ChartiumDateTimeAxisY()
{
}

QSizeF ChartiumDateTimeAxisY::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
{
    return QSizeF();
}

QList<qreal> ChartiumDateTimeAxisY::calculateLayout() const
{
    QList<qreal> res;

    return res;
}

void ChartiumDateTimeAxisY::updateGeometry()
{
}

void ChartiumDateTimeAxisY::handleTickCountChanged(int tick)
{
}

void ChartiumDateTimeAxisY::handleFormatChanged(const QString& format)
{
}
