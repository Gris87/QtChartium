#include "src/qtchartium/themes/qtcharts/chartiumthemelight.h"

#include "src/qtchartium/themes/ichartiumthememanager.h"



ChartiumThemeLight::ChartiumThemeLight(IChartiumThemeManager* themeManager) :
    ChartiumTheme(IChartiumChart::ChartThemeLight)
{
    // Series colors
    mSeriesColors << QRgb(0x209fdf);
    mSeriesColors << QRgb(0x99ca53);
    mSeriesColors << QRgb(0xf6a625);
    mSeriesColors << QRgb(0x6d5fd5);
    mSeriesColors << QRgb(0xbf593e);
    mSeriesGradients = themeManager->generateSeriesGradients(mSeriesColors);

    // Background
    QLinearGradient backgroundGradient;
    backgroundGradient.setColorAt(0.0, QRgb(0xffffff));
    backgroundGradient.setColorAt(1.0, QRgb(0xffffff));
    backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    mChartBackgroundGradient = backgroundGradient;
    // There is a performance issue in the drop shadow implementation, so disabled for now
    //        mBackgroundDropShadowEnabled = true;

    // Axes and other
    mLabelBrush  = QBrush(QRgb(0x404044));
    mAxisLinePen = QPen(0xd6d6d6);
    mAxisLinePen.setWidth(1);
    mGridLinePen = QPen(QRgb(0xe2e2e2));
    mGridLinePen.setWidth(1);
    mMinorGridLinePen = QPen(QRgb(0xe2e2e2));
    mMinorGridLinePen.setWidth(1);
    mMinorGridLinePen.setStyle(Qt::DashLine);
    mBackgroundShades = BackgroundShadesNone;
    mOutlinePen       = QPen(0x4d4d4d);
    mOutlinePen.setWidthF(2.0);
}
