#include "src/qtchartium/axis/chartiumverticalaxis.h"



ChartiumVerticalAxis::ChartiumVerticalAxis(
    IChartiumAxis* axis, IChartiumPresenter* presenter, bool intervalAxis, QGraphicsItem* item, QGraphicsLayoutItem* parent
) :
    IChartiumVerticalAxis(axis, presenter, intervalAxis, item, parent)
{
}

ChartiumVerticalAxis::~ChartiumVerticalAxis()
{
}
