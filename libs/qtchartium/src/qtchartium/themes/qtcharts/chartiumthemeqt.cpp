#include "src/qtchartium/themes/qtcharts/chartiumthemeqt.h"

#include "src/qtchartium/ichartiumthememanager.h"



ChartiumThemeQt::ChartiumThemeQt(IChartiumThemeManager* themeManager) :
    ChartiumTheme(IChartiumChart::ChartThemeQt)
{
    // Series colors
    mSeriesColors << QRgb(0x80c342);
    mSeriesColors << QRgb(0x328930);
    mSeriesColors << QRgb(0x006325);
    mSeriesColors << QRgb(0x35322f);
    mSeriesColors << QRgb(0x5d5b59);
    mSeriesColors << QRgb(0x868482);
    mSeriesColors << QRgb(0xaeadac);
    mSeriesColors << QRgb(0xd7d6d5);
    mSeriesGradients = themeManager->generateSeriesGradients(mSeriesColors);

    // Background
    QLinearGradient backgroundGradient(0.5, 0.0, 0.5, 1.0);
    backgroundGradient.setColorAt(0.0, QRgb(0xffffff));
    backgroundGradient.setColorAt(1.0, QRgb(0xffffff));
    backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    mChartBackgroundGradient = backgroundGradient;

    // Axes and other
    mLabelBrush  = QBrush(QRgb(0x35322f));
    mAxisLinePen = QPen(QRgb(0xd7d6d5));
    mAxisLinePen.setWidth(1);
    mGridLinePen = QPen(QRgb(0xd7d6d5));
    mGridLinePen.setWidth(1);
    mMinorGridLinePen = QPen(QRgb(0xd7d6d5));
    mMinorGridLinePen.setWidth(1);
    mMinorGridLinePen.setStyle(Qt::DashLine);
    mBackgroundShades = BackgroundShadesNone;
    mOutlinePen       = QPen(QRgb(0x35322f));
    mOutlinePen.setWidthF(2.0);
}
