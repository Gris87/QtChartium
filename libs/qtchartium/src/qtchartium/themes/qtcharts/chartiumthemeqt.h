#pragma once



#include "src/qtchartium/themes/chartiumtheme.h"



class IChartiumThemeManager;



class ChartiumThemeQt : public ChartiumTheme
{
public:
    explicit ChartiumThemeQt(IChartiumThemeManager* themeManager);
    ~ChartiumThemeQt() override = default;

    ChartiumThemeQt(const ChartiumThemeQt& another)            = delete;
    ChartiumThemeQt& operator=(const ChartiumThemeQt& another) = delete;
};
