#include "src/qtchartium/themes/chartiumtheme.h"



ChartiumTheme::ChartiumTheme(IChartiumChart::ChartTheme id) :
    mId(id),
    mBackgroundShadesBrush(Qt::SolidPattern),
    mBackgroundShades(BackgroundShadesNone),
    mBackgroundDropShadowEnabled(false)
{
}

ChartiumTheme::~ChartiumTheme()
{
}

IChartiumChart::ChartTheme ChartiumTheme::id() const
{
    return mId;
}

QList<QGradient> ChartiumTheme::seriesGradients() const
{
    return mSeriesGradients;
}

QList<QColor> ChartiumTheme::seriesColors() const
{
    return mSeriesColors;
}

QLinearGradient ChartiumTheme::chartBackgroundGradient() const
{
    return mChartBackgroundGradient;
}

QFont ChartiumTheme::masterFont() const
{
    return mMasterFont;
}

QFont ChartiumTheme::labelFont() const
{
    return mLabelFont;
}

QBrush ChartiumTheme::labelBrush() const
{
    return mLabelBrush;
}

QPen ChartiumTheme::axisLinePen() const
{
    return mAxisLinePen;
}

QPen ChartiumTheme::backgroundShadesPen() const
{
    return mBackgroundShadesPen;
}

QPen ChartiumTheme::outlinePen() const
{
    return mOutlinePen;
}

QBrush ChartiumTheme::backgroundShadesBrush() const
{
    return mBackgroundShadesBrush;
}

IChartiumTheme::BackgroundShadesMode ChartiumTheme::backgroundShades() const
{
    return mBackgroundShades;
}

bool ChartiumTheme::isBackgroundDropShadowEnabled() const
{
    return mBackgroundDropShadowEnabled;
}

QPen ChartiumTheme::gridLinePen() const
{
    return mGridLinePen;
}

QPen ChartiumTheme::minorGridLinePen() const
{
    return mMinorGridLinePen;
}
