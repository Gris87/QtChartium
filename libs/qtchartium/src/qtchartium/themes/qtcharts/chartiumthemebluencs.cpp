#include "src/qtchartium/themes/qtcharts/chartiumthemebluencs.h"

#include "src/qtchartium/themes/ichartiumthememanager.h"



ChartiumThemeBlueNcs::ChartiumThemeBlueNcs(IChartiumThemeManager* themeManager) :
    ChartiumTheme(IChartiumChart::ChartThemeBlueNcs)
{
    // Series colors
    mSeriesColors << QRgb(0x1db0da);
    mSeriesColors << QRgb(0x1341a6);
    mSeriesColors << QRgb(0x88d41e);
    mSeriesColors << QRgb(0xff8e1a);
    mSeriesColors << QRgb(0x398ca3);
    mSeriesGradients = themeManager->generateSeriesGradients(mSeriesColors);

    // Background
    QLinearGradient backgroundGradient;
    backgroundGradient.setColorAt(0.0, QRgb(0xffffff));
    backgroundGradient.setColorAt(1.0, QRgb(0xffffff));
    backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    mChartBackgroundGradient = backgroundGradient;

    // Axes and other
    mLabelBrush  = QBrush(QRgb(0x404044));
    mAxisLinePen = QPen(QRgb(0xd6d6d6));
    mAxisLinePen.setWidth(2);
    mGridLinePen = QPen(QRgb(0xe2e2e2));
    mGridLinePen.setWidth(1);
    mMinorGridLinePen = QPen(QRgb(0xe2e2e2));
    mMinorGridLinePen.setWidth(1);
    mMinorGridLinePen.setStyle(Qt::DashLine);
    mBackgroundShades = BackgroundShadesNone;
    mOutlinePen       = QPen(QRgb(0x474747));
    mOutlinePen.setWidthF(2.0);
}
