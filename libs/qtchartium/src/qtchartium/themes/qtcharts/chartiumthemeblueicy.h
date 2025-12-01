#pragma once



#include "src/qtchartium/themes/chartiumtheme.h"



class IChartiumThemeManager;



class ChartiumThemeBlueIcy : public ChartiumTheme
{
public:
    explicit ChartiumThemeBlueIcy(IChartiumThemeManager* themeManager);
    ~ChartiumThemeBlueIcy() override = default;

    ChartiumThemeBlueIcy(const ChartiumThemeBlueIcy& another)            = delete;
    ChartiumThemeBlueIcy& operator=(const ChartiumThemeBlueIcy& another) = delete;
};
