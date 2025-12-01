#pragma once



#include "src/qtchartium/themes/ichartiumtheme.h"



class ChartiumTheme : public IChartiumTheme
{
public:
    explicit ChartiumTheme(IChartiumChart::ChartTheme id = IChartiumChart::ChartThemeLight);
    ~ChartiumTheme() override;

    ChartiumTheme(const ChartiumTheme& another)            = delete;
    ChartiumTheme& operator=(const ChartiumTheme& another) = delete;

    IChartiumChart::ChartTheme id() const override;
    QList<QGradient> seriesGradients() const override;
    QList<QColor> seriesColors() const override;
    QLinearGradient chartBackgroundGradient() const override;
    QFont masterFont() const override;
    QFont labelFont() const override;
    QBrush labelBrush() const override;
    QPen axisLinePen() const override;
    QPen backgroundShadesPen() const override;
    QPen outlinePen() const override;
    QBrush backgroundShadesBrush() const override;
    BackgroundShadesMode backgroundShades() const override;
    bool isBackgroundDropShadowEnabled() const override;
    QPen gridLinePen() const override;
    QPen minorGridLinePen() const override;

protected:
    IChartiumChart::ChartTheme mId;
    QList<QColor>              mSeriesColors;
    QList<QGradient>           mSeriesGradients;
    QLinearGradient            mChartBackgroundGradient;
    QFont                      mMasterFont;
    QFont                      mLabelFont;
    QBrush                     mLabelBrush;
    QPen                       mAxisLinePen;
    QPen                       mBackgroundShadesPen;
    QPen                       mOutlinePen;
    QBrush                     mBackgroundShadesBrush;
    BackgroundShadesMode       mBackgroundShades;
    bool                       mBackgroundDropShadowEnabled;
    QPen                       mGridLinePen;
    QPen                       mMinorGridLinePen;
};
