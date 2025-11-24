#include "src/qtchartium/chartiumpresenter.h"

#include <QRegularExpression>
#include <QTextDocument>

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
    return mBackground;
}

QAbstractGraphicsShapeItem* ChartiumPresenter::plotAreaElement()
{
    return mPlotAreaBackground;
}

IChartiumTitle* ChartiumPresenter::titleElement()
{
    return mTitle;
}

QList<IChartiumAxisElement*> ChartiumPresenter::axisItems() const
{
    return mAxisItems;
}

QList<IChartiumItem*> ChartiumPresenter::chartItems() const
{
    return mChartItems;
}

IChartiumLegend* ChartiumPresenter::legend()
{
    return mChart->legend();
}

void ChartiumPresenter::setBackgroundBrush(const QBrush& brush)
{
    createBackgroundItem();

    mBackground->setBrush(brush);
    mLayout->invalidate();
}

QBrush ChartiumPresenter::backgroundBrush() const
{
    if (mBackground == nullptr)
    {
        return QBrush();
    }

    return mBackground->brush();
}

void ChartiumPresenter::setBackgroundPen(const QPen& pen)
{
    createBackgroundItem();

    mBackground->setPen(pen);
    mLayout->invalidate();
}

QPen ChartiumPresenter::backgroundPen() const
{
    if (mBackground == nullptr)
    {
        return QPen();
    }

    return mBackground->pen();
}

void ChartiumPresenter::setBackgroundRoundness(qreal diameter)
{
    createBackgroundItem();

    mBackground->setDiameter(diameter);
    mLayout->invalidate();
}

qreal ChartiumPresenter::backgroundRoundness() const
{
    if (mBackground == nullptr)
    {
        return 0;
    }

    return mBackground->diameter();
}

void ChartiumPresenter::setPlotAreaBackgroundBrush(const QBrush& brush)
{
    createPlotAreaBackgroundItem();

    mPlotAreaBackground->setBrush(brush);
    mLayout->invalidate();
}

QBrush ChartiumPresenter::plotAreaBackgroundBrush() const
{
    if (mPlotAreaBackground == nullptr)
    {
        return QBrush();
    }

    return mPlotAreaBackground->brush();
}

void ChartiumPresenter::setPlotAreaBackgroundPen(const QPen& pen)
{
    createPlotAreaBackgroundItem();

    mPlotAreaBackground->setPen(pen);
    mLayout->invalidate();
}

QPen ChartiumPresenter::plotAreaBackgroundPen() const
{
    if (mPlotAreaBackground == nullptr)
    {
        return QPen();
    }

    return mPlotAreaBackground->pen();
}

void ChartiumPresenter::setTitle(const QString& title)
{
    createTitleItem();

    mTitle->setText(title);
    mLayout->invalidate();
}

QString ChartiumPresenter::title() const
{
    if (mTitle == nullptr)
    {
        return QString();
    }

    return mTitle->text();
}

void ChartiumPresenter::setTitleFont(const QFont& font)
{
    createTitleItem();

    mTitle->setFont(font);
    mLayout->invalidate();
}

QFont ChartiumPresenter::titleFont() const
{
    if (mTitle == nullptr)
    {
        return QFont();
    }

    return mTitle->font();
}

void ChartiumPresenter::setTitleBrush(const QBrush& brush)
{
    createTitleItem();
    mTitle->setDefaultTextColor(brush.color());
    mLayout->invalidate();
}

QBrush ChartiumPresenter::titleBrush() const
{
    if (mTitle == nullptr)
    {
        return QBrush();
    }

    return QBrush(mTitle->defaultTextColor());
}

void ChartiumPresenter::setBackgroundVisible(bool visible)
{
    createBackgroundItem();
    mBackground->setVisible(visible);
}

bool ChartiumPresenter::isBackgroundVisible() const
{
    if (mBackground == nullptr)
    {
        return false;
    }

    return mBackground->isVisible();
}

void ChartiumPresenter::setPlotAreaBackgroundVisible(bool visible)
{
    createPlotAreaBackgroundItem();

    mPlotAreaBackground->setVisible(visible);
}

bool ChartiumPresenter::isPlotAreaBackgroundVisible() const
{
    if (mPlotAreaBackground == nullptr)
    {
        return false;
    }

    return mPlotAreaBackground->isVisible();
}

void ChartiumPresenter::setBackgroundDropShadowEnabled(bool enabled)
{
    createBackgroundItem();

    mBackground->setDropShadowEnabled(enabled);
}

bool ChartiumPresenter::isBackgroundDropShadowEnabled() const
{
    if (mBackground == nullptr)
    {
        return false;
    }

    return mBackground->isDropShadowEnabled();
}

void ChartiumPresenter::setLocalizeNumbers(bool localize)
{
    mLocalizeNumbers = localize;
    mLayout->invalidate();
}

bool ChartiumPresenter::localizeNumbers() const
{
    return false;
}

void ChartiumPresenter::setLocale(const QLocale& locale)
{
    mLocale = locale;
    mLayout->invalidate();
}

const QLocale& ChartiumPresenter::locale() const
{
    return mLocale;
}

void ChartiumPresenter::setVisible(bool visible)
{
    mChart->setVisible(visible);
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
    return mLayout;
}

IChartiumChart::ChartType ChartiumPresenter::chartType() const
{
    return mChart->chartType();
}

IChartiumChart* ChartiumPresenter::chart()
{
    return mChart;
}

template<int TSize>
struct TextBoundCache
{
    struct element
    {
        quint32 lastUsed;
        QRectF  bounds;
    };

    QHash<QString, element> elements;
    quint32                 usedCounter = 0;
    QGraphicsTextItem       dummyText;

    QRectF bounds(const QFont& font, const QString& text)
    {
        const QString key  = font.key() + text;
        auto          elem = elements.find(key);

        if (elem != elements.end())
        {
            usedCounter++;
            elem->lastUsed = usedCounter;

            return elem->bounds;
        }

        dummyText.setFont(font);
        dummyText.setHtml(text);

        const QRectF bounds = dummyText.boundingRect();

        if (elements.size() >= TSize)
        {
            auto elem = std::min_element(elements.begin(), elements.end(), [](const element& a, const element& b) {
                return a.lastUsed < b.lastUsed;
            });

            if (elem != elements.end())
            {
                const QString key = elem.key();
                elements.remove(key);
            }
        }

        elements.insert(key, {usedCounter++, bounds});

        return bounds;
    }

    QTextDocument* document()
    {
        return dummyText.document();
    }
};


QRectF ChartiumPresenter::textBoundingRect(const QFont& font, const QString& text, qreal angle)
{
    static TextBoundCache<32> textBoundCache;
    static bool               initMargin = true;

    if (initMargin)
    {
        textBoundCache.document()->setDocumentMargin(textMargin());
        initMargin = false;
    }

    QRectF boundingRect = textBoundCache.bounds(font, text);

    if (angle != 0)
    {
        QTransform transform;
        transform.rotate(angle);
        boundingRect = transform.mapRect(boundingRect);
    }

    return boundingRect;
}

QString ChartiumPresenter::truncatedText(
    const QFont& font, const QString& text, qreal angle, qreal maxWidth, qreal maxHeight, QRectF& boundingRect
)
{
    QString truncatedString = text;
    boundingRect            = textBoundingRect(font, truncatedString, angle);

    if (boundingRect.width() > maxWidth || boundingRect.height() > maxHeight)
    {
        // It can be assumed that almost any amount of string manipulation is faster
        // than calculating one bounding rectangle, so first prepare a list of truncated strings
        // to try.
        static QRegularExpression truncateMatcher(QStringLiteral("&#?[0-9a-zA-Z]*;$"));

        QList<QString>       testStrings(text.size());
        int                  count(0);
        static QLatin1Char   closeTag('>');
        static QLatin1Char   openTag('<');
        static QLatin1Char   semiColon(';');
        static QLatin1String ellipsis("...");

        while (truncatedString.size() > 1)
        {
            int   chopIndex(-1);
            int   chopCount(1);
            QChar lastChar(truncatedString.at(truncatedString.size() - 1));

            if (lastChar == closeTag)
            {
                chopIndex = truncatedString.lastIndexOf(openTag);
            }
            else if (lastChar == semiColon)
            {
                chopIndex = truncatedString.indexOf(truncateMatcher);
            }

            if (chopIndex != -1)
            {
                chopCount = truncatedString.size() - chopIndex;
            }

            truncatedString.chop(chopCount);
            testStrings[count] = truncatedString + ellipsis;
            count++;
        }

        // Binary search for best fit
        int    minIndex(0);
        int    maxIndex(count - 1);
        int    bestIndex(count);
        QRectF checkRect;

        while (maxIndex >= minIndex)
        {
            int mid   = (maxIndex + minIndex) / 2;
            checkRect = textBoundingRect(font, testStrings.at(mid), angle);
            if (checkRect.width() > maxWidth || checkRect.height() > maxHeight)
            {
                // Checked index too large, all under this are also too large
                minIndex = mid + 1;
            }
            else
            {
                // Checked index fits, all over this also fit
                maxIndex     = mid - 1;
                bestIndex    = mid;
                boundingRect = checkRect;
            }
        }

        // Default to "..." if nothing fits
        if (bestIndex == count)
        {
            boundingRect    = textBoundingRect(font, ellipsis, angle);
            truncatedString = ellipsis;
        }
        else
        {
            truncatedString = testStrings.at(bestIndex);
        }
    }

    return truncatedString;
}

qreal ChartiumPresenter::textMargin()
{
    return 0;
}

QString ChartiumPresenter::numberToString(double value, char f, int prec)
{
    if (mLocalizeNumbers)
    {
        return mLocale.toString(value, f, prec);
    }
    else
    {
        return QString::number(value, f, prec);
    }
}

QString ChartiumPresenter::numberToString(int value)
{
    if (mLocalizeNumbers)
    {
        return mLocale.toString(value);
    }
    else
    {
        return QString::number(value);
    }
}

void ChartiumPresenter::createBackgroundItem()
{
    if (mBackground == nullptr)
    {
        mBackground = new ChartiumBackground(rootItem());
        mBackground->setZValue(IChartiumPresenter::BackgroundZValue);
    }
}

void ChartiumPresenter::createPlotAreaBackgroundItem()
{
    if (mPlotAreaBackground == nullptr)
    {
        if (mChart->chartType() == IChartiumChart::ChartTypeCartesian)
        {
            mPlotAreaBackground = new QGraphicsRectItem(rootItem());
        }

        mPlotAreaBackground->setAcceptedMouseButtons({});
        mPlotAreaBackground->setPen(QPen(Qt::transparent));
        mPlotAreaBackground->setBrush(Qt::NoBrush);
        mPlotAreaBackground->setZValue(IChartiumPresenter::PlotAreaZValue);
        mPlotAreaBackground->setVisible(false);
    }
}

void ChartiumPresenter::createTitleItem()
{
    if (mTitle == nullptr)
    {
        mTitle = new ChartiumTitle(rootItem());
        mTitle->setZValue(IChartiumPresenter::TitleZValue);
    }
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
