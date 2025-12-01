#include "src/qtchartium/themes/qtcharts/chartiumthemeblueicy.h"

#include "src/qtchartium/ichartiumthememanager.h"



ChartiumThemeBlueIcy::ChartiumThemeBlueIcy(IChartiumThemeManager* themeManager) :
    ChartiumTheme(IChartiumChart::ChartThemeBlueIcy)
{
    // Series colors
    mSeriesColors << QRgb(0x3daeda);
    mSeriesColors << QRgb(0x2685bf);
    mSeriesColors << QRgb(0x0c2673);
    mSeriesColors << QRgb(0x5f3dba);
    mSeriesColors << QRgb(0x2fa3b4);
    mSeriesGradients = themeManager->generateSeriesGradients(mSeriesColors);

    // Background
    QLinearGradient backgroundGradient(0.5, 0.0, 0.5, 1.0);
    backgroundGradient.setColorAt(0.0, QRgb(0xffffff));
    backgroundGradient.setColorAt(1.0, QRgb(0xffffff));
    backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    mChartBackgroundGradient     = backgroundGradient;
    mBackgroundDropShadowEnabled = true;

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
