#pragma once



#include "src/qtchartium/themes/chartiumtheme.h"



class IChartiumThemeManager;



class ChartiumThemeDark : public ChartiumTheme
{
public:
    explicit ChartiumThemeDark(IChartiumThemeManager* themeManager);
    ~ChartiumThemeDark() override = default;

    ChartiumThemeDark(const ChartiumThemeDark& another)            = delete;
    ChartiumThemeDark& operator=(const ChartiumThemeDark& another) = delete;
};
