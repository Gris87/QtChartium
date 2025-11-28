#include "src/qtchartium/axis/chartiumcartesianaxis.h"



ChartiumCartesianAxis::ChartiumCartesianAxis(
    IChartiumAxis* axis, IChartiumPresenter* presenter, bool intervalAxis, QGraphicsItem* item, QGraphicsLayoutItem* parent
) :
    IChartiumCartesianAxis(axis, presenter, intervalAxis, item, parent)
{
}

ChartiumCartesianAxis::~ChartiumCartesianAxis()
{
}
