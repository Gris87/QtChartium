#include "src/qtchartium/chartiumchart.h"

#include "src/qtchartium/chartiumdataset.h"
#include "src/qtchartium/chartiumpresenter.h"
#include "src/qtchartium/domain/chartiumxydomain.h"
#include "src/qtchartium/legend/chartiumlegend.h"



ChartiumChart::ChartiumChart(QGraphicsItem* parent, Qt::WindowFlags wFlags) :
    IChartiumChart(parent, wFlags),
    mLegend(new ChartiumLegend(this)),
    mDataset(new ChartiumDataSet(this)),
    mPresenter(new ChartiumPresenter(this)),
    mChartType(IChartiumChart::ChartTypeCartesian)
{
    setLayout(mPresenter->layout());

    // clang-format off
    QObject::connect(mDataset,   SIGNAL(seriesAdded(QAbstractSeries*)),   mPresenter, SLOT(handleSeriesAdded(QAbstractSeries*)));
    QObject::connect(mDataset,   SIGNAL(seriesRemoved(QAbstractSeries*)), mPresenter, SLOT(handleSeriesRemoved(QAbstractSeries*)));
    QObject::connect(mDataset,   SIGNAL(axisAdded(QAbstractAxis*)),       mPresenter, SLOT(handleAxisAdded(QAbstractAxis*)));
    QObject::connect(mDataset,   SIGNAL(axisRemoved(QAbstractAxis*)),     mPresenter, SLOT(handleAxisRemoved(QAbstractAxis*)));
    QObject::connect(mPresenter, &IChartiumPresenter::plotAreaChanged, this, &IChartiumChart::plotAreaChanged);
    // clang-format on
}

ChartiumChart::~ChartiumChart()
{
}

void ChartiumChart::addSeries(IChartiumSeries* series)
{
    mDataset->addSeries(series);
}

void ChartiumChart::removeSeries(IChartiumSeries* series)
{
    mDataset->removeSeries(series);
}

void ChartiumChart::removeAllSeries()
{
    const QList<IChartiumSeries*> series = mDataset->series();

    for (IChartiumSeries* s : series)
    {
        removeSeries(s);
        delete s;
    }
}

QList<IChartiumSeries*> ChartiumChart::series() const
{
    return mDataset->series();
}

void ChartiumChart::addAxis(IChartiumAxis* axis, Qt::Alignment alignment)
{
    mDataset->addAxis(axis, alignment);
}

void ChartiumChart::removeAxis(IChartiumAxis* axis)
{
    mDataset->removeAxis(axis);
}

QList<IChartiumAxis*> ChartiumChart::axes(Qt::Orientations orientation, IChartiumSeries* series) const
{
    QList<IChartiumAxis*> result;

    if (series)
    {
        const QList<IChartiumAxis*> axes = series->attachedAxes();

        for (IChartiumAxis* axis : axes)
        {
            if (orientation.testFlag(axis->orientation()))
            {
                result.append(axis);
            }
        }
    }
    else
    {
        const QList<IChartiumAxis*> axes = mDataset->axes();

        for (IChartiumAxis* axis : axes)
        {
            if (orientation.testFlag(axis->orientation()) && !result.contains(axis))
            {
                result.append(axis);
            }
        }
    }

    return result;
}

void ChartiumChart::createDefaultAxes()
{
    mDataset->createDefaultAxes();
}

void ChartiumChart::setTitle(const QString& title)
{
    mPresenter->setTitle(title);
}

QString ChartiumChart::title() const
{
    return mPresenter->title();
}

void ChartiumChart::setTitleFont(const QFont& font)
{
    mPresenter->setTitleFont(font);
}

QFont ChartiumChart::titleFont() const
{
    return mPresenter->titleFont();
}

void ChartiumChart::setTitleBrush(const QBrush& brush)
{
    mPresenter->setTitleBrush(brush);
}

QBrush ChartiumChart::titleBrush() const
{
    return mPresenter->titleBrush();
}

void ChartiumChart::setBackgroundBrush(const QBrush& brush)
{
    mPresenter->setBackgroundBrush(brush);
}

QBrush ChartiumChart::backgroundBrush() const
{
    return mPresenter->backgroundBrush();
}

void ChartiumChart::setBackgroundPen(const QPen& pen)
{
    mPresenter->setBackgroundPen(pen);
}

QPen ChartiumChart::backgroundPen() const
{
    return mPresenter->backgroundPen();
}

void ChartiumChart::setBackgroundVisible(bool visible)
{
    mPresenter->setBackgroundVisible(visible);
}

bool ChartiumChart::isBackgroundVisible() const
{
    return mPresenter->isBackgroundVisible();
}

void ChartiumChart::setDropShadowEnabled(bool enabled)
{
    mPresenter->setBackgroundDropShadowEnabled(enabled);
}

bool ChartiumChart::isDropShadowEnabled() const
{
    return mPresenter->isBackgroundDropShadowEnabled();
}

void ChartiumChart::setBackgroundRoundness(qreal diameter)
{
    mPresenter->setBackgroundRoundness(diameter);
}

qreal ChartiumChart::backgroundRoundness() const
{
    return mPresenter->backgroundRoundness();
}

void ChartiumChart::zoomIn()
{
    zoomIn(2.0);
}

void ChartiumChart::zoomOut()
{
    zoomOut(2.0);
}

void ChartiumChart::zoomIn(qreal factor)
{
    QRectF rect = mPresenter->geometry();

    rect.setWidth(rect.width() / factor);
    rect.setHeight(rect.height() / factor);
    rect.moveCenter(mPresenter->geometry().center());

    zoomIn(rect);
}

void ChartiumChart::zoomOut(qreal factor)
{
    const QRectF geometry = mPresenter->geometry();

    QRectF r;

    r.setSize(geometry.size() / factor);
    r.moveCenter(QPointF(geometry.size().width() / 2, geometry.size().height() / 2));

    if (!r.isValid())
    {
        return;
    }

    QPointF zoomPoint(r.center().x() / geometry.width(), r.center().y() / geometry.height());
    mPresenter->setState(IChartiumPresenter::ZoomOutState, zoomPoint);
    mDataset->zoomOutDomain(r);
    mPresenter->setState(IChartiumPresenter::ShowState, QPointF());
}

void ChartiumChart::zoomIn(const QRectF& rect)
{
    if (!rect.isValid())
    {
        return;
    }

    QRectF       r        = rect.normalized();
    const QRectF geometry = mPresenter->geometry();
    r.translate(-geometry.topLeft());

    if (!r.isValid())
    {
        return;
    }

    QPointF zoomPoint(r.center().x() / geometry.width(), r.center().y() / geometry.height());
    mPresenter->setState(IChartiumPresenter::ZoomInState, zoomPoint);
    mDataset->zoomInDomain(r);
    mPresenter->setState(IChartiumPresenter::ShowState, QPointF());
}

void ChartiumChart::zoom(qreal factor)
{
    if (qFuzzyCompare(factor, 0))
    {
        return;
    }

    if (qFuzzyCompare(factor, (qreal)1.0))
    {
        return;
    }

    if (factor < 0)
    {
        return;
    }

    if (factor > 1.0)
    {
        zoomIn(factor);
    }
    else
    {
        zoomOut(1.0 / factor);
    }
}

void ChartiumChart::zoomReset()
{
    mDataset->zoomResetDomain();
}

bool ChartiumChart::isZoomed()
{
    return mDataset->isZoomedDomain();
}

void ChartiumChart::scroll(qreal dx, qreal dy)
{
    if (dx < 0)
    {
        mPresenter->setState(IChartiumPresenter::ScrollLeftState, QPointF());
    }

    if (dx > 0)
    {
        mPresenter->setState(IChartiumPresenter::ScrollRightState, QPointF());
    }

    if (dy < 0)
    {
        mPresenter->setState(IChartiumPresenter::ScrollUpState, QPointF());
    }

    if (dy > 0)
    {
        mPresenter->setState(IChartiumPresenter::ScrollDownState, QPointF());
    }

    mDataset->scrollDomain(dx, dy);
    mPresenter->setState(IChartiumPresenter::ShowState, QPointF());
}

IChartiumLegend* ChartiumChart::legend() const
{
    return mLegend;
}

void ChartiumChart::setMargins(const QMargins& margins)
{
    mPresenter->layout()->setMargins(margins);
}

QMargins ChartiumChart::margins() const
{
    return mPresenter->layout()->margins();
}

QRectF ChartiumChart::plotArea() const
{
    return mPresenter->geometry();
}

void ChartiumChart::setPlotArea(const QRectF& rect)
{
    mPresenter->setFixedGeometry(rect);
}

void ChartiumChart::setPlotAreaBackgroundBrush(const QBrush& brush)
{
    mPresenter->setPlotAreaBackgroundBrush(brush);
}

QBrush ChartiumChart::plotAreaBackgroundBrush() const
{
    return mPresenter->plotAreaBackgroundBrush();
}

void ChartiumChart::setPlotAreaBackgroundPen(const QPen& pen)
{
    mPresenter->setPlotAreaBackgroundPen(pen);
}

QPen ChartiumChart::plotAreaBackgroundPen() const
{
    return mPresenter->plotAreaBackgroundPen();
}

void ChartiumChart::setPlotAreaBackgroundVisible(bool visible)
{
    mPresenter->setPlotAreaBackgroundVisible(visible);
}

bool ChartiumChart::isPlotAreaBackgroundVisible() const
{
    return mPresenter->isPlotAreaBackgroundVisible();
}

void ChartiumChart::setLocalizeNumbers(bool localize)
{
    mPresenter->setLocalizeNumbers(localize);
}

bool ChartiumChart::localizeNumbers() const
{
    return mPresenter->localizeNumbers();
}

void ChartiumChart::setLocale(const QLocale& locale)
{
    mPresenter->setLocale(locale);
}

QLocale ChartiumChart::locale() const
{
    return mPresenter->locale();
}

QPointF ChartiumChart::mapToValue(const QPointF& position, IChartiumSeries* series)
{
    return mDataset->mapToValue(position, series);
}

QPointF ChartiumChart::mapToPosition(const QPointF& value, IChartiumSeries* series)
{
    return mDataset->mapToPosition(value, series);
}

IChartiumChart::ChartType ChartiumChart::chartType() const
{
    return mChartType;
}

IChartiumDataSet* ChartiumChart::dataset() const
{
    return mDataset;
}
