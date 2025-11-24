#include "src/qtchartium/chartiumtitle.h"



ChartiumTitle::ChartiumTitle(QGraphicsItem* parent) :
    IChartiumTitle(parent),
    mText()
{
}

ChartiumTitle::~ChartiumTitle()
{
}

QSizeF ChartiumTitle::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
{
    return QSizeF();
}

void ChartiumTitle::setText(const QString& text)
{
}

QString ChartiumTitle::text() const
{
    return mText;
}

void ChartiumTitle::setGeometry(const QRectF& rect)
{
}
