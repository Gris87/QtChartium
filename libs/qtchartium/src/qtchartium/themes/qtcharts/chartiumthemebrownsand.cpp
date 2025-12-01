#include "src/qtchartium/themes/qtcharts/chartiumthemebrownsand.h"

#include "src/qtchartium/ichartiumthememanager.h"



ChartiumThemeBrownSand::ChartiumThemeBrownSand(IChartiumThemeManager* themeManager) :
    ChartiumTheme(IChartiumChart::ChartThemeBrownSand)
{
    // Series colors
    mSeriesColors << QRgb(0xb39b72);
    mSeriesColors << QRgb(0xb3b376);
    mSeriesColors << QRgb(0xc35660);
    mSeriesColors << QRgb(0x536780);
    mSeriesColors << QRgb(0x494345);
    mSeriesGradients = themeManager->generateSeriesGradients(mSeriesColors);

    // Background
    QLinearGradient backgroundGradient;
    backgroundGradient.setColorAt(0.0, QRgb(0xf3ece0));
    backgroundGradient.setColorAt(1.0, QRgb(0xf3ece0));
    backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    mChartBackgroundGradient = backgroundGradient;

    // Axes and other
    mLabelBrush  = QBrush(QRgb(0x404044));
    mAxisLinePen = QPen(QRgb(0xb5b0a7));
    mAxisLinePen.setWidth(2);
    mGridLinePen = QPen(QRgb(0xd4cec3));
    mGridLinePen.setWidth(1);
    mMinorGridLinePen = QPen(QRgb(0xd4cec3));
    mMinorGridLinePen.setWidth(1);
    mMinorGridLinePen.setStyle(Qt::DashLine);
    mBackgroundShades = BackgroundShadesNone;
    mOutlinePen       = QPen(QRgb(0x222222));
    mOutlinePen.setWidthF(2.0);
}
