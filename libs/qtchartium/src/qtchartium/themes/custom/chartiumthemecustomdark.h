#pragma once



#include "src/qtchartium/themes/chartiumtheme.h"



class IChartiumThemeManager;



class ChartiumThemeCustomDark : public ChartiumTheme
{
public:
    explicit ChartiumThemeCustomDark(IChartiumThemeManager* themeManager);
    ~ChartiumThemeCustomDark() override = default;

    ChartiumThemeCustomDark(const ChartiumThemeCustomDark& another)            = delete;
    ChartiumThemeCustomDark& operator=(const ChartiumThemeCustomDark& another) = delete;
};
