#include "src/qtchartium/chartiumbackground.h"



ChartiumBackground::ChartiumBackground(QGraphicsItem* parent) :
    IChartiumBackground(parent),
    mDiameter(5),
    mDropShadow()
{
    setAcceptedMouseButtons({});
}

ChartiumBackground::~ChartiumBackground()
{
}

void ChartiumBackground::setDiameter(qreal diameter)
{
    if (mDiameter != diameter)
    {
        mDiameter = diameter;

        update();
    }
}

qreal ChartiumBackground::diameter() const
{
    return mDiameter;
}

void ChartiumBackground::setDropShadowEnabled(bool enabled)
{
    if (enabled)
    {
        if (mDropShadow == nullptr)
        {
            mDropShadow = new QGraphicsDropShadowEffect();

#ifdef Q_OS_WINDOWS
            mDropShadow->setBlurRadius(10);
            mDropShadow->setOffset(0, 0);
#elif defined(Q_OS_LINUX)
            mDropShadow->setBlurRadius(10);
            mDropShadow->setOffset(5, 5);
#else
            mDropShadow->setBlurRadius(15);
            mDropShadow->setOffset(0, 0);
#endif

            setGraphicsEffect(mDropShadow);
        }
    }
    else
    {
        delete mDropShadow;
        mDropShadow = nullptr;
    }
}

bool ChartiumBackground::isDropShadowEnabled() const
{
    return mDropShadow != nullptr;
}

void ChartiumBackground::paint(QPainter* painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/)
{
    painter->save();

    painter->setPen(pen());
    painter->setBrush(brush());
    painter->drawRoundedRect(rect(), mDiameter, mDiameter);

    painter->restore();
}
