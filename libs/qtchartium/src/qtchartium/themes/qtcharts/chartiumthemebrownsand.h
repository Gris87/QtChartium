#pragma once



#include "src/qtchartium/themes/chartiumtheme.h"



class IChartiumThemeManager;



class ChartiumThemeBrownSand : public ChartiumTheme
{
public:
    explicit ChartiumThemeBrownSand(IChartiumThemeManager* themeManager);
    ~ChartiumThemeBrownSand() override = default;

    ChartiumThemeBrownSand(const ChartiumThemeBrownSand& another)            = delete;
    ChartiumThemeBrownSand& operator=(const ChartiumThemeBrownSand& another) = delete;
};
