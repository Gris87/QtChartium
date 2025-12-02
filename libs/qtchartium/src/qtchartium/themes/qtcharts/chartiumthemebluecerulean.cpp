#include "src/qtchartium/themes/qtcharts/chartiumthemebluecerulean.h"

#include "src/qtchartium/themes/ichartiumthememanager.h"



ChartiumThemeBlueCerulean::ChartiumThemeBlueCerulean(IChartiumThemeManager* themeManager) :
    ChartiumTheme(IChartiumChart::ChartThemeBlueCerulean)
{
    // Series colors
    mSeriesColors << QRgb(0xc7e85b);
    mSeriesColors << QRgb(0x1cb54f);
    mSeriesColors << QRgb(0x5cbf9b);
    mSeriesColors << QRgb(0x009fbf);
    mSeriesColors << QRgb(0xee7392);
    mSeriesGradients = themeManager->generateSeriesGradients(mSeriesColors);

    // Background
    QLinearGradient backgroundGradient(0.5, 0.0, 0.5, 1.0);
    backgroundGradient.setColorAt(0.0, QRgb(0x056189));
    backgroundGradient.setColorAt(1.0, QRgb(0x101a31));
    backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    mChartBackgroundGradient = backgroundGradient;

    // Axes and other
    mLabelBrush  = QBrush(QRgb(0xffffff));
    mAxisLinePen = QPen(QRgb(0xd6d6d6));
    mAxisLinePen.setWidth(2);
    mGridLinePen = QPen(QRgb(0x84a2b0));
    mGridLinePen.setWidth(1);
    mMinorGridLinePen = QPen(QRgb(0x84a2b0));
    mMinorGridLinePen.setWidth(1);
    mMinorGridLinePen.setStyle(Qt::DashLine);
    mBackgroundShades = BackgroundShadesNone;
    mOutlinePen       = QPen(QRgb(0xebebeb));
    mOutlinePen.setWidthF(2.0);
}
