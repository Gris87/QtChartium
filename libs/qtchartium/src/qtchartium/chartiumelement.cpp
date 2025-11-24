#include "src/qtchartium/chartiumelement.h"



ChartiumElement::ChartiumElement(QGraphicsItem* item) :
    IChartiumElement(item),
    mPresenter(),
    mDataSet()
{
}

ChartiumElement::~ChartiumElement()
{
}

void ChartiumElement::setPresenter(IChartiumPresenter* presenter)
{
    mPresenter = presenter;
}

IChartiumPresenter* ChartiumElement::presenter() const
{
    return mPresenter;
}

void ChartiumElement::setDataSet(IChartiumDataSet* dataSet)
{
    mDataSet = dataSet;
}

IChartiumDataSet* ChartiumElement::dataSet() const
{
    return mDataSet;
}
