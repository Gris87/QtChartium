#include "src/qtchartium/charts/linechart/chartiumlineseries.h"

#include "src/qtchartium/charts/linechart/chartiumlinechartitem.h"
#include "src/qtchartium/themes/ichartiumtheme.h"



ChartiumLineSeries::ChartiumLineSeries(QObject* parent) :
    IChartiumLineSeries(parent)
{
    m_markerSize = m_pen.widthF() * 1.5;
}

ChartiumLineSeries::~ChartiumLineSeries()
{
}

IChartiumSeries::SeriesType ChartiumLineSeries::type() const
{
    return IChartiumSeries::SeriesTypeLine;
}

void ChartiumLineSeries::initializeGraphics(QGraphicsItem* parent)
{
    ChartiumLineChartItem* line = new ChartiumLineChartItem(this, parent);
    mItem                       = line;

    IChartiumLineSeries::initializeGraphics(parent);
}

void ChartiumLineSeries::initializeTheme(int index, IChartiumTheme* theme)
{
    const QList<QColor> colors = theme->seriesColors();

    QPen pen;
    pen.setColor(colors.at(index % colors.size()));
    pen.setWidthF(2);
    setPen(pen);

    QColor color = theme->labelBrush().color();
    setPointLabelsColor(color);
}
