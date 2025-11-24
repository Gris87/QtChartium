#include "src/qtchartium/layout/chartiumlayout.h"



ChartiumLayout::ChartiumLayout(IChartiumPresenter* presenter, QGraphicsLayoutItem* parent) :
    IChartiumLayout(parent),
    mPresenter(presenter),
    mMargins(20, 20, 20, 20),
    mMinAxisRect()
{
}

ChartiumLayout::~ChartiumLayout()
{
}

void ChartiumLayout::setMargins(const QMargins& margins)
{
}

QMargins ChartiumLayout::margins() const
{
    return QMargins();
}

void ChartiumLayout::setGeometry(const QRectF& rect)
{
}

QRectF ChartiumLayout::calculateBackgroundGeometry(const QRectF& geometry, IChartiumBackground* background, bool update) const
{
    return QRectF();
}

QRectF ChartiumLayout::calculateBackgroundMinimum(const QRectF& minimum) const
{
    return QRectF();
}

QRectF ChartiumLayout::calculateContentGeometry(const QRectF& geometry) const
{
    return QRectF();
}

QRectF ChartiumLayout::calculateContentMinimum(const QRectF& minimum) const
{
    return QRectF();
}

QRectF ChartiumLayout::calculateTitleGeometry(const QRectF& geometry, IChartiumTitle* title, bool update) const
{
    return QRectF();
}

QRectF ChartiumLayout::calculateTitleMinimum(const QRectF& minimum, IChartiumTitle* title) const
{
    return QRectF();
}

QRectF ChartiumLayout::calculateLegendGeometry(const QRectF& geometry, IChartiumLegend* legend, bool update) const
{
    return QRectF();
}

QRectF ChartiumLayout::calculateLegendMinimum(const QRectF& minimum, IChartiumLegend* legend) const
{
    return QRectF();
}

QRectF ChartiumLayout::calculateAxisGeometry(const QRectF& geometry, const QList<IChartiumAxisElement*>& axes, bool update) const
{
    return QRectF();
}

QRectF ChartiumLayout::calculateAxisMinimum(const QRectF& minimum, const QList<IChartiumAxisElement*>& axes) const
{
    return QRectF();
}

QSizeF ChartiumLayout::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
{
    return QSizeF();
}

int ChartiumLayout::count() const
{
    return 0;
}

QGraphicsLayoutItem* ChartiumLayout::itemAt(int i) const
{
    return nullptr;
}

void ChartiumLayout::removeAt(int)
{
}
