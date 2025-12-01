#pragma once



#include "src/qtchartium/themes/chartiumtheme.h"



class IChartiumThemeManager;



class ChartiumThemeHighContrast : public ChartiumTheme
{
public:
    explicit ChartiumThemeHighContrast(IChartiumThemeManager* themeManager);
    ~ChartiumThemeHighContrast() override = default;

    ChartiumThemeHighContrast(const ChartiumThemeHighContrast& another)            = delete;
    ChartiumThemeHighContrast& operator=(const ChartiumThemeHighContrast& another) = delete;
};
