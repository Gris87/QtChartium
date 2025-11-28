#include "src/qtchartium/axis/chartiumhorizontalaxis.h"



ChartiumHorizontalAxis::ChartiumHorizontalAxis(
    IChartiumAxis* axis, IChartiumPresenter* presenter, bool intervalAxis, QGraphicsItem* item, QGraphicsLayoutItem* parent
) :
    IChartiumHorizontalAxis(axis, presenter, intervalAxis, item, parent)
{
}

ChartiumHorizontalAxis::~ChartiumHorizontalAxis()
{
}
