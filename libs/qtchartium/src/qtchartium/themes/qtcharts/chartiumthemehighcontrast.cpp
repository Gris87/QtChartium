#include "src/qtchartium/themes/qtcharts/chartiumthemehighcontrast.h"

#include "src/qtchartium/ichartiumthememanager.h"



ChartiumThemeHighContrast::ChartiumThemeHighContrast(IChartiumThemeManager* themeManager) :
    ChartiumTheme(IChartiumChart::ChartThemeHighContrast)
{
    // Series colors
    mSeriesColors << QRgb(0x202020);
    mSeriesColors << QRgb(0x596a74);
    mSeriesColors << QRgb(0xffab03);
    mSeriesColors << QRgb(0x038e9b);
    mSeriesColors << QRgb(0xff4a41);
    mSeriesGradients = themeManager->generateSeriesGradients(mSeriesColors);

    // Background
    QLinearGradient backgroundGradient(0.5, 0.0, 0.5, 1.0);
    backgroundGradient.setColorAt(0.0, QRgb(0xffffff));
    backgroundGradient.setColorAt(1.0, QRgb(0xffffff));
    backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    mChartBackgroundGradient     = backgroundGradient;
    mBackgroundDropShadowEnabled = true;

    // Axes and other
    mLabelBrush  = QBrush(QRgb(0x181818));
    mAxisLinePen = QPen(QRgb(0x8c8c8c));
    mAxisLinePen.setWidth(2);
    mGridLinePen = QPen(QRgb(0x8c8c8c));
    mGridLinePen.setWidth(1);
    mMinorGridLinePen = QPen(QRgb(0x8c8c8c));
    mMinorGridLinePen.setWidth(1);
    mMinorGridLinePen.setStyle(Qt::DashLine);
    mBackgroundShadesBrush = QBrush(QRgb(0xffeecd));
    mBackgroundShades      = BackgroundShadesHorizontal;
    mOutlinePen            = QPen(QColor(Qt::black));
    mOutlinePen.setWidthF(2.0);
}
