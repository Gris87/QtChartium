#include "src/qtchartium/themes/qtcharts/chartiumthemedark.h"

#include "src/qtchartium/ichartiumthememanager.h"



ChartiumThemeDark::ChartiumThemeDark(IChartiumThemeManager* themeManager) :
    ChartiumTheme(IChartiumChart::ChartThemeDark)
{
    // Series colors
    mSeriesColors << QRgb(0x38ad6b);
    mSeriesColors << QRgb(0x3c84a7);
    mSeriesColors << QRgb(0xeb8817);
    mSeriesColors << QRgb(0x7b7f8c);
    mSeriesColors << QRgb(0xbf593e);
    mSeriesGradients = themeManager->generateSeriesGradients(mSeriesColors);

    // Background
    QLinearGradient backgroundGradient(0.5, 0.0, 0.5, 1.0);
    backgroundGradient.setColorAt(0.0, QRgb(0x2e303a));
    backgroundGradient.setColorAt(1.0, QRgb(0x121218));
    backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    mChartBackgroundGradient = backgroundGradient;

    // Axes and other
    mLabelBrush  = QBrush(QRgb(0xffffff));
    mAxisLinePen = QPen(QRgb(0x86878c));
    mAxisLinePen.setWidth(2);
    mGridLinePen = QPen(QRgb(0x86878c));
    mGridLinePen.setWidth(1);
    mMinorGridLinePen = QPen(QRgb(0x86878c));
    mMinorGridLinePen.setWidth(1);
    mMinorGridLinePen.setStyle(Qt::DashLine);
    mBackgroundShades = BackgroundShadesNone;
    mOutlinePen       = QPen(QRgb(0xd6d6d6));
    mOutlinePen.setWidthF(2.0);
}
