#include "src/qtchartium/themes/chartiumthememanager.h"

#include "src/qtchartium/themes/custom/chartiumthemecustomdark.h"
#include "src/qtchartium/themes/qtcharts/chartiumthemebluecerulean.h"
#include "src/qtchartium/themes/qtcharts/chartiumthemeblueicy.h"
#include "src/qtchartium/themes/qtcharts/chartiumthemebluencs.h"
#include "src/qtchartium/themes/qtcharts/chartiumthemebrownsand.h"
#include "src/qtchartium/themes/qtcharts/chartiumthemedark.h"
#include "src/qtchartium/themes/qtcharts/chartiumthemehighcontrast.h"
#include "src/qtchartium/themes/qtcharts/chartiumthemelight.h"
#include "src/qtchartium/themes/qtcharts/chartiumthemeqt.h"



ChartiumThemeManager::ChartiumThemeManager(IChartiumChart* chart) :
    IChartiumThemeManager(chart),
    mChart(chart),
    mTheme(),
    mSeriesMap(),
    mAxisList()
{
}

ChartiumThemeManager::~ChartiumThemeManager()
{
}

void ChartiumThemeManager::setTheme(IChartiumChart::ChartTheme theme)
{
    if (mTheme.isNull() || theme != mTheme->id())
    {
        switch (theme)
        {
            case IChartiumChart::ChartThemeLight:
                mTheme.reset(new ChartiumThemeLight(this));
                break;
            case IChartiumChart::ChartThemeBlueCerulean:
                mTheme.reset(new ChartiumThemeBlueCerulean(this));
                break;
            case IChartiumChart::ChartThemeDark:
                mTheme.reset(new ChartiumThemeDark(this));
                break;
            case IChartiumChart::ChartThemeBrownSand:
                mTheme.reset(new ChartiumThemeBrownSand(this));
                break;
            case IChartiumChart::ChartThemeBlueNcs:
                mTheme.reset(new ChartiumThemeBlueNcs(this));
                break;
            case IChartiumChart::ChartThemeHighContrast:
                mTheme.reset(new ChartiumThemeHighContrast(this));
                break;
            case IChartiumChart::ChartThemeBlueIcy:
                mTheme.reset(new ChartiumThemeBlueIcy(this));
                break;
            case IChartiumChart::ChartThemeQt:
                mTheme.reset(new ChartiumThemeQt(this));
                break;
            default:
                mTheme.reset(new ChartiumThemeCustomDark(this));
                break;
        }

        if (mTheme != nullptr)
        {
            decorateChart(mChart, mTheme.data());
            decorateLegend(mChart->legend(), mTheme.data());

            foreach(IChartiumAxis* axis, mAxisList)
            {
                axis->initializeTheme(mTheme.data());
            }

            foreach(IChartiumSeries* series, mSeriesMap.keys())
            {
                series->initializeTheme(mSeriesMap[series], mTheme.data());
            }
        }
    }
}

IChartiumTheme* ChartiumThemeManager::theme() const
{
    return mTheme.data();
}

void ChartiumThemeManager::decorateChart(IChartiumChart* chart, IChartiumTheme* theme) const
{
    chart->setBackgroundBrush(theme->chartBackgroundGradient());

    QPen   pen(Qt::transparent);
    QBrush brush;
    chart->setPlotAreaBackgroundBrush(brush);
    chart->setPlotAreaBackgroundPen(pen);
    chart->setPlotAreaBackgroundVisible(false);

    chart->setTitleFont(theme->masterFont());
    chart->setTitleBrush(theme->labelBrush());
    chart->setDropShadowEnabled(theme->isBackgroundDropShadowEnabled());
}

void ChartiumThemeManager::decorateLegend(IChartiumLegend* legend, IChartiumTheme* theme) const
{
    legend->setPen(theme->axisLinePen());
    legend->setBrush(theme->chartBackgroundGradient());
    legend->setFont(theme->labelFont());
    legend->setLabelBrush(theme->labelBrush());
}

void ChartiumThemeManager::updateSeries(IChartiumSeries* series)
{
    if (mSeriesMap.contains(series))
    {
        series->initializeTheme(mSeriesMap[series], mTheme.data());
    }
}

QMap<IChartiumSeries*, int> ChartiumThemeManager::seriesMap() const
{
    QMap<IChartiumSeries*, int> res;

    return res;
}

QList<QGradient> ChartiumThemeManager::generateSeriesGradients(const QList<QColor>& colors)
{
    QList<QGradient> result;

    // Generate gradients in HSV color space
    foreach(const QColor& color, colors)
    {
        QLinearGradient g;
        qreal           h = color.hsvHueF();
        qreal           s = color.hsvSaturationF();

        QColor start = color;
        start.setHsvF(h, 0.0, 1.0);
        g.setColorAt(0.0, start);

        g.setColorAt(0.5, color);

        QColor end = color;
        end.setHsvF(h, s, 0.25);
        g.setColorAt(1.0, end);

        result.append(g);
    }

    return result;
}

QColor ChartiumThemeManager::colorAt(const QColor& start, const QColor& end, qreal pos)
{
    Q_ASSERT(pos >= 0.0 && pos <= 1.0);
    qreal  r = start.redF() + ((end.redF() - start.redF()) * pos);
    qreal  g = start.greenF() + ((end.greenF() - start.greenF()) * pos);
    qreal  b = start.blueF() + ((end.blueF() - start.blueF()) * pos);
    QColor c;
    c.setRgbF(r, g, b);
    return c;
}

QColor ChartiumThemeManager::colorAt(const QGradient& gradient, qreal pos)
{
    Q_ASSERT(pos >= 0 && pos <= 1.0);

    QGradientStops stops = gradient.stops();
    int            count = stops.size();

    // find previous stop relative to position
    QGradientStop prev = stops.first();
    for (int i = 0; i < count; i++)
    {
        QGradientStop stop = stops.at(i);
        if (pos > stop.first)
        {
            prev = stop;
        }

        // given position is actually a stop position?
        if (pos == stop.first)
        {
            //qDebug() << "stop color" << pos;
            return stop.second;
        }
    }

    // find next stop relative to position
    QGradientStop next = stops.last();
    for (int i = count - 1; i >= 0; i--)
    {
        QGradientStop stop = stops.at(i);
        if (pos < stop.first)
        {
            next = stop;
        }
    }

    //qDebug() << "prev" << prev.first << "pos" << pos << "next" << next.first;

    qreal range       = next.first - prev.first;
    qreal posDelta    = pos - prev.first;
    qreal relativePos = posDelta / range;

    //qDebug() << "range" << range << "posDelta" << posDelta << "relativePos" << relativePos;

    return colorAt(prev.second, next.second, relativePos);
}

int ChartiumThemeManager::createIndexKey(const QList<int>& keys) const
{
    auto keysCopy = keys;
    std::sort(keysCopy.begin(), keysCopy.end());

    int i = 0;
    for (const auto key : keysCopy)
    {
        if (i != key)
        {
            break;
        }
        ++i;
    }
    return i;
}

int ChartiumThemeManager::seriesCount(IChartiumSeries::SeriesType type) const
{
    int                     count  = 0;
    QList<IChartiumSeries*> series = mSeriesMap.keys();

    foreach(IChartiumSeries* s, series)
    {
        if (s->type() == type)
        {
            count++;
        }
    }
    return count;
}

void ChartiumThemeManager::handleSeriesAdded(IChartiumSeries* series)
{
    int key = createIndexKey(mSeriesMap.values());
    mSeriesMap.insert(series, key);
    series->initializeTheme(key, mTheme.data());
}

void ChartiumThemeManager::handleSeriesRemoved(IChartiumSeries* series)
{
    mSeriesMap.remove(series);
}

void ChartiumThemeManager::handleAxisAdded(IChartiumAxis* axis)
{
    mAxisList.append(axis);
    axis->initializeTheme(mTheme.data());
}

void ChartiumThemeManager::handleAxisRemoved(IChartiumAxis* axis)
{
    mAxisList.removeAll(axis);
}
