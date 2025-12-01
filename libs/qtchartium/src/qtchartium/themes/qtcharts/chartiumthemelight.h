#pragma once



#include "src/qtchartium/themes/chartiumtheme.h"



class IChartiumThemeManager;



class ChartiumThemeLight : public ChartiumTheme
{
public:
    explicit ChartiumThemeLight(IChartiumThemeManager* themeManager);
    ~ChartiumThemeLight() override = default;

    ChartiumThemeLight(const ChartiumThemeLight& another)            = delete;
    ChartiumThemeLight& operator=(const ChartiumThemeLight& another) = delete;
};
