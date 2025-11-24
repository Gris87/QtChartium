#include "src/qtchartium/chartiumpresenter.h"

#include "src/qtchartium/layout/chartiumcartesianlayout.h"



ChartiumPresenter::ChartiumPresenter(IChartiumChart* chart) :
    IChartiumPresenter(chart),
    mChart(chart),
    mChartItems(),
    mAxisItems(),
    mSeries(),
    mAxes(),
    mState(IChartiumPresenter::ShowState),
    mStatePoint(),
    mLayout(),
    mBackground(),
    mPlotAreaBackground(),
    mTitle(),
    mRect(),
    mLocalizeNumbers(),
    mLocale(),
    mFixedRect()
{
    if (chart->type() == IChartiumChart::ChartTypeCartesian)
    {
        mLayout = new ChartiumCartesianLayout(this);
    }

    Q_ASSERT(mLayout);
}

ChartiumPresenter::~ChartiumPresenter()
{
}

bool ChartiumPresenter::isFixedGeometry() const
{
    return false;
}

void ChartiumPresenter::setFixedGeometry(const QRectF& rect)
{
    if (mFixedRect == rect)
    {
        return;
    }

    const bool isSame = mFixedRect == mRect;
    mFixedRect        = rect;

    if (mFixedRect.isNull())
    {
        if (!isSame)
        {
            updateGeometry(mRect);
            mLayout->updateGeometry();
        }
    }
    else
    {
        updateGeometry(mFixedRect);
    }
}

void ChartiumPresenter::setGeometry(QRectF rect)
{
    if (rect.isValid() && mRect != rect)
    {
        mRect = rect;

        if (!mFixedRect.isNull())
        {
            return;
        }

        updateGeometry(rect);
    }
}

QRectF ChartiumPresenter::geometry() const
{
    return !mFixedRect.isNull() ? mFixedRect : mRect;
}

void ChartiumPresenter::updateGeometry(const QRectF& rect)
{
    for (IChartiumItem* chartItem : mChartItems)
    {
        chartItem->domain()->setSize(rect.size());
        chartItem->setPos(rect.topLeft());
    }

    emit plotAreaChanged(rect);
}

QGraphicsItem* ChartiumPresenter::rootItem()
{
    return nullptr;
}

IChartiumBackground* ChartiumPresenter::backgroundElement()
{
    return nullptr;
}

QAbstractGraphicsShapeItem* ChartiumPresenter::plotAreaElement()
{
    return nullptr;
}

IChartiumTitle* ChartiumPresenter::titleElement()
{
    return nullptr;
}

QList<IChartiumAxisElement*> ChartiumPresenter::axisItems() const
{
    QList<IChartiumAxisElement*> res;

    return res;
}

QList<IChartiumItem*> ChartiumPresenter::chartItems() const
{
    QList<IChartiumItem*> res;

    return res;
}

IChartiumLegend* ChartiumPresenter::legend()
{
    return nullptr;
}

void ChartiumPresenter::setBackgroundBrush(const QBrush& brush)
{
}

QBrush ChartiumPresenter::backgroundBrush() const
{
    return QBrush();
}

void ChartiumPresenter::setBackgroundPen(const QPen& pen)
{
}

QPen ChartiumPresenter::backgroundPen() const
{
    return QPen();
}

void ChartiumPresenter::setBackgroundRoundness(qreal diameter)
{
}

qreal ChartiumPresenter::backgroundRoundness() const
{
    return 0;
}

void ChartiumPresenter::setPlotAreaBackgroundBrush(const QBrush& brush)
{
}

QBrush ChartiumPresenter::plotAreaBackgroundBrush() const
{
    return QBrush();
}

void ChartiumPresenter::setPlotAreaBackgroundPen(const QPen& pen)
{
}

QPen ChartiumPresenter::plotAreaBackgroundPen() const
{
    return QPen();
}

void ChartiumPresenter::setTitle(const QString& title)
{
}

QString ChartiumPresenter::title() const
{
    return "";
}

void ChartiumPresenter::setTitleFont(const QFont& font)
{
}

QFont ChartiumPresenter::titleFont() const
{
    return QFont();
}

void ChartiumPresenter::setTitleBrush(const QBrush& brush)
{
}

QBrush ChartiumPresenter::titleBrush() const
{
    return QBrush();
}

void ChartiumPresenter::setBackgroundVisible(bool visible)
{
}

bool ChartiumPresenter::isBackgroundVisible() const
{
    return false;
}

void ChartiumPresenter::setPlotAreaBackgroundVisible(bool visible)
{
}

bool ChartiumPresenter::isPlotAreaBackgroundVisible() const
{
    return false;
}

void ChartiumPresenter::setBackgroundDropShadowEnabled(bool enabled)
{
}

bool ChartiumPresenter::isBackgroundDropShadowEnabled() const
{
    return false;
}

void ChartiumPresenter::setLocalizeNumbers(bool localize)
{
}

bool ChartiumPresenter::localizeNumbers() const
{
    return false;
}

void ChartiumPresenter::setLocale(const QLocale& locale)
{
}

const QLocale& ChartiumPresenter::locale() const
{
    return mLocale;
}

void ChartiumPresenter::setVisible(bool visible)
{
}

void ChartiumPresenter::setState(State state, QPointF point)
{
    mState      = state;
    mStatePoint = point;
}

IChartiumPresenter::State ChartiumPresenter::state() const
{
    return mState;
}

QPointF ChartiumPresenter::statePoint() const
{
    return QPointF();
}

IChartiumLayout* ChartiumPresenter::layout()
{
    return nullptr;
}

IChartiumChart::ChartType ChartiumPresenter::chartType() const
{
    return mChart->chartType();
}

IChartiumChart* ChartiumPresenter::chart()
{
    return mChart;
}

QRectF ChartiumPresenter::textBoundingRect(const QFont& font, const QString& text, qreal angle)
{
    return QRectF();
}

QString ChartiumPresenter::truncatedText(
    const QFont& font, const QString& text, qreal angle, qreal maxWidth, qreal maxHeight, QRectF& boundingRect
)
{
    return "";
}

qreal ChartiumPresenter::textMargin()
{
    return 0;
}

QString ChartiumPresenter::numberToString(double value, char f, int)
{
    return "";
}

QString ChartiumPresenter::numberToString(int value)
{
    return "";
}

void ChartiumPresenter::createBackgroundItem()
{
}

void ChartiumPresenter::createPlotAreaBackgroundItem()
{
}

void ChartiumPresenter::createTitleItem()
{
}

void ChartiumPresenter::handleSeriesAdded(IChartiumSeries* series)
{
    series->initializeGraphics(rootItem());
    series->setPresenter(this);

    IChartiumItem* chartItem = series->chartItem();

    chartItem->setPresenter(this);
    chartItem->setDataSet(mChart->dataset());
    chartItem->domain()->setSize(geometry().size());
    chartItem->setPos(geometry().topLeft());
    chartItem->handleDomainUpdated();

    mChartItems.append(chartItem);
    mSeries.append(series);
    mLayout->invalidate();
}

void ChartiumPresenter::handleSeriesRemoved(IChartiumSeries* series)
{
    IChartiumItem* chartItem = series->chartItem();

    chartItem->hide();
    chartItem->cleanup();
    series->disconnect(chartItem);
    chartItem->deleteLater();

    mChartItems.removeAll(chartItem);
    mSeries.removeAll(series);
    mLayout->invalidate();
}

void ChartiumPresenter::handleAxisAdded(IChartiumAxis* axis)
{
    axis->initializeGraphics(rootItem());

    IChartiumAxisElement* item = axis->axisItem();
    item->setPresenter(this);

    mAxisItems.append(item);
    mAxes.append(axis);

    mLayout->invalidate();
}

void ChartiumPresenter::handleAxisRemoved(IChartiumAxis* axis)
{
    IChartiumAxisElement* item = axis->axisItem();

    item->hide();
    item->disconnect();
    item->deleteLater();

    mAxisItems.removeAll(item);
    mAxes.removeAll(axis);

    mLayout->invalidate();
}
