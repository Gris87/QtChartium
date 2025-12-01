#pragma once



#include "src/qtchartium/themes/chartiumtheme.h"



class IChartiumThemeManager;



class ChartiumThemeBlueNcs : public ChartiumTheme
{
public:
    explicit ChartiumThemeBlueNcs(IChartiumThemeManager* themeManager);
    ~ChartiumThemeBlueNcs() override = default;

    ChartiumThemeBlueNcs(const ChartiumThemeBlueNcs& another)            = delete;
    ChartiumThemeBlueNcs& operator=(const ChartiumThemeBlueNcs& another) = delete;
};
