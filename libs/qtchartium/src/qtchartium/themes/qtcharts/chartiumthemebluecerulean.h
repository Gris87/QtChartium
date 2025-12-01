#pragma once



#include "src/qtchartium/themes/chartiumtheme.h"



class IChartiumThemeManager;



class ChartiumThemeBlueCerulean : public ChartiumTheme
{
public:
    explicit ChartiumThemeBlueCerulean(IChartiumThemeManager* themeManager);
    ~ChartiumThemeBlueCerulean() override = default;

    ChartiumThemeBlueCerulean(const ChartiumThemeBlueCerulean& another)            = delete;
    ChartiumThemeBlueCerulean& operator=(const ChartiumThemeBlueCerulean& another) = delete;
};
