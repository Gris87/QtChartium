#include "src/qtchartium/chartiumview.h"



ChartiumView::ChartiumView(QWidget* parent) :
    IChartiumView(parent),
    mScene(new QGraphicsScene(this)),
    mChart()
{
    setFrameShape(QFrame::NoFrame);
    setBackgroundRole(QPalette::Window);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    setScene(mScene);
}

ChartiumView::~ChartiumView()
{
}

IChartiumChart* ChartiumView::chart()
{
    return mChart;
}

void ChartiumView::setChart(IChartiumChart* chart)
{
    if (mChart != chart)
    {
        if (mChart != nullptr)
        {
            mScene->removeItem(mChart);
        }

        mChart = chart;
        mScene->addItem(mChart);

        resize();
    }
}

void ChartiumView::resizeEvent(QResizeEvent* event)
{
    IChartiumView::resizeEvent(event);

    resize();
}

void ChartiumView::resize()
{
    const qreal sinA         = qAbs(transform().m21());
    const qreal cosA         = qAbs(transform().m11());
    const QSize originalSize = size();
    QSize       chartSize    = originalSize;

    if (sinA == 1.0)
    {
        chartSize.setHeight(originalSize.width());
        chartSize.setWidth(originalSize.height());
    }
    else if (sinA != 0.0)
    {
        const qreal minDimension = qMin(originalSize.width(), originalSize.height());
        const qreal h            = (minDimension - (minDimension / ((sinA / cosA) + 1.0))) / sinA;

        chartSize.setHeight(h);
        chartSize.setWidth(h);
    }

    mChart->resize(chartSize);
    setMinimumSize(mChart->minimumSize().toSize().expandedTo(minimumSize()));
    setMaximumSize(maximumSize().boundedTo(mChart->maximumSize().toSize()));
    setSceneRect(mChart->geometry());
}
