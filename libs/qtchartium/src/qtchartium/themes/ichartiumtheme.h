#pragma once



#include "src/qtchartium/ichartiumchart.h"



class IChartiumTheme
{
public:
    enum BackgroundShadesMode
    {
        BackgroundShadesNone = 0,
        BackgroundShadesVertical,
        BackgroundShadesHorizontal,
        BackgroundShadesBoth
    };

    explicit IChartiumTheme() = default;
    virtual ~IChartiumTheme() = default;

    IChartiumTheme(const IChartiumTheme& another)            = delete;
    IChartiumTheme& operator=(const IChartiumTheme& another) = delete;

    virtual IChartiumChart::ChartTheme id() const           = 0;
    virtual QList<QGradient> seriesGradients() const        = 0;
    virtual QList<QColor> seriesColors() const              = 0;
    virtual QLinearGradient chartBackgroundGradient() const = 0;
    virtual QFont masterFont() const                        = 0;
    virtual QFont labelFont() const                         = 0;
    virtual QBrush labelBrush() const                       = 0;
    virtual QPen axisLinePen() const                        = 0;
    virtual QPen backgroundShadesPen() const                = 0;
    virtual QPen outlinePen() const                         = 0;
    virtual QBrush backgroundShadesBrush() const            = 0;
    virtual BackgroundShadesMode backgroundShades() const   = 0;
    virtual bool isBackgroundDropShadowEnabled() const      = 0;
    virtual QPen gridLinePen() const                        = 0;
    virtual QPen minorGridLinePen() const                   = 0;
};
