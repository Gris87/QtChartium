#include "src/qtchartium/axis/chartiumaxiselement.h"

#include <QDateTime>
#include <QRegularExpression>
#include <QTextDocument>

#include "src/qtchartium/ichartiumpresenter.h"



static const QRegularExpression& labelFormatMatcher()
{
    static const QRegularExpression re(QLatin1String("%[\\-\\+#\\s\\d\\.\\'lhjztL]*([dicuoxfegXFEG])"));

    return re;
}

static const QRegularExpression& labelFormatMatcherLocalized()
{
    static const QRegularExpression re(QLatin1String("^([^%]*)%\\.(\\d+)([defgiEG])(.*)$"));

    return re;
}



ChartiumAxisElement::ChartiumAxisElement(
    IChartiumAxis* axis, IChartiumPresenter* presenter, bool intervalAxis, QGraphicsItem* item, QGraphicsLayoutItem* parent
) :
    IChartiumAxisElement(item, parent),
    mAxis(axis),
    mLayout(),
    mDynamicMinorTickLayout(),
    mLabelsList(),
    mAxisRect(),
    mGrid(new QGraphicsItemGroup(item)),
    mArrow(new QGraphicsItemGroup(item)),
    mMinorGrid(new QGraphicsItemGroup(item)),
    mMinorArrow(new QGraphicsItemGroup(item)),
    mShades(new QGraphicsItemGroup(item)),
    mLabels(new QGraphicsItemGroup(item)),
    mTitle(new QGraphicsTextItem(item)),
    mColorScale(nullptr),
    mIntervalAxis(intervalAxis)
{
    //initial initialization
    mArrow->setHandlesChildEvents(false);
    mArrow->setZValue(IChartiumPresenter::AxisZValue);
    mMinorArrow->setHandlesChildEvents(false);
    mMinorArrow->setZValue(IChartiumPresenter::AxisZValue);
    mLabels->setZValue(IChartiumPresenter::AxisZValue);
    mShades->setZValue(IChartiumPresenter::ShadesZValue);
    mGrid->setZValue(IChartiumPresenter::GridZValue);
    mMinorGrid->setZValue(IChartiumPresenter::GridZValue);
    mTitle->setZValue(IChartiumPresenter::GridZValue);
    mTitle->document()->setDocumentMargin(presenter->textMargin());

    if (mAxis->type() == IChartiumAxis::AxisTypeColor)
    {
        mColorScale = std::make_unique<QGraphicsPixmapItem>(new QGraphicsPixmapItem(item));
        mColorScale->setZValue(IChartiumPresenter::GridZValue);
        mColorScale->setVisible(false);
    }

    handleVisibleChanged(axis->isVisible());
    connectSlots();

    setFlag(QGraphicsItem::ItemHasNoContents, true);
}

ChartiumAxisElement::~ChartiumAxisElement()
{
}

QRectF ChartiumAxisElement::gridGeometry() const
{
    return QRectF();
}

void ChartiumAxisElement::setGeometry(const QRectF& axis, const QRectF& grid)
{
}

bool ChartiumAxisElement::emptyAxis() const
{
    return axisGeometry().isEmpty() || gridGeometry().isEmpty() || qFuzzyIsNull(max() - min());
}

IChartiumAxis* ChartiumAxisElement::axis() const
{
    return nullptr;
}

void ChartiumAxisElement::setLayout(const QList<qreal>& layout)
{
}

QList<qreal>& ChartiumAxisElement::layout()
{
    static QList<qreal> res;

    return res;
}

void ChartiumAxisElement::setDynamicMinorTickLayout(const QList<qreal>& layout)
{
}

QList<qreal>& ChartiumAxisElement::dynamicMinorTicklayout()
{
    static QList<qreal> res;

    return res;
}

qreal ChartiumAxisElement::labelPadding() const
{
    return 0;
}

qreal ChartiumAxisElement::titlePadding() const
{
    return 0;
}

qreal ChartiumAxisElement::colorScalePadding() const
{
    return 0;
}

void ChartiumAxisElement::setLabels(const QStringList& labels)
{
}

QStringList ChartiumAxisElement::labels() const
{
    QStringList res;

    return res;
}

qreal ChartiumAxisElement::min() const
{
    return mAxis->minReal();
}

qreal ChartiumAxisElement::max() const
{
    return mAxis->maxReal();
}

qreal ChartiumAxisElement::tickInterval() const
{
    IChartiumValueAxis* valueAxis = qobject_cast<IChartiumValueAxis*>(mAxis);

    if (valueAxis != nullptr)
    {
        return valueAxis->tickInterval();
    }
    else
    {
        return 0.0;
    }
}

qreal ChartiumAxisElement::tickAnchor() const
{
    IChartiumValueAxis* valueAxis = qobject_cast<IChartiumValueAxis*>(mAxis);

    if (valueAxis != nullptr)
    {
        return valueAxis->tickAnchor();
    }
    else
    {
        return 0.0;
    }
}

QRectF ChartiumAxisElement::axisGeometry() const
{
    return QRectF();
}

void ChartiumAxisElement::setAxisGeometry(const QRectF& axisGeometry)
{
}

void ChartiumAxisElement::axisSelected()
{
    emit clicked();
}

bool ChartiumAxisElement::intervalAxis() const
{
    return false;
}

static int precisionDigits(qreal min, qreal max, int ticks)
{
    // How many digits of each tick value should we display after the decimal point ?
    // For example tick marks 1.002 and 1.003 have a difference of 0.001 and need 3 decimals.
    if (ticks > 1)
    {
        // Number of digits after decimal that *don't* change between ticks:
        const int gap = -qFloor(std::log10((max - min) / (ticks - 1)));
        if (gap > 0)
        {
            return gap + 1;
        }
    }
    // We want at least one digit after the decimal point even when digits
    // before are changing, or when we only have a single tick-mark:
    return 1;
}

QStringList ChartiumAxisElement::createValueLabels(
    qreal                        max,
    qreal                        min,
    int                          ticks,
    qreal                        tickInterval,
    qreal                        tickAnchor,
    IChartiumValueAxis::TickType tickType,
    const QString&               format
) const
{
    QStringList labels;

    if (max <= min || ticks < 1)
    {
        return labels;
    }

    if (format.isEmpty())
    {
        const int n = precisionDigits(min, max, ticks);
        if (tickType == IChartiumValueAxis::TicksFixed)
        {
            for (int i = 0; i < ticks; i++)
            {
                qreal value = min + (i * (max - min) / (ticks - 1));
                labels << presenter()->numberToString(value, 'f', n);
            }
        }
        else
        {
            const qreal ticksFromAnchor = (tickAnchor - min) / tickInterval;
            const qreal firstMajorTick  = tickAnchor - std::floor(ticksFromAnchor) * tickInterval;

            qreal value = firstMajorTick;
            while (value <= max)
            {
                labels << presenter()->numberToString(value, 'f', n);
                value += tickInterval;
            }
        }
    }
    else
    {
        QByteArray array = format.toLatin1();
        QString    formatSpec;
        QString    preStr;
        QString    postStr;
        int        precision = 6; // Six is the default precision in Qt API
        if (presenter()->localizeNumbers())
        {
            QRegularExpressionMatch rmatch;
            if (format.indexOf(labelFormatMatcherLocalized(), 0, &rmatch) != -1)
            {
                preStr = rmatch.captured(1);
                if (!rmatch.captured(2).isEmpty())
                {
                    precision = rmatch.captured(2).toInt();
                }
                formatSpec = rmatch.captured(3);
                postStr    = rmatch.captured(4);
            }
        }
        else
        {
            QRegularExpressionMatch rmatch;
            if (format.indexOf(labelFormatMatcher(), 0, &rmatch) != -1)
            {
                formatSpec = rmatch.captured(1);
            }
        }
        if (tickType == IChartiumValueAxis::TicksFixed)
        {
            for (int i = 0; i < ticks; i++)
            {
                qreal value = min + (i * (max - min) / (ticks - 1));
                labels << formatLabel(formatSpec, array, value, precision, preStr, postStr);
            }
        }
        else
        {
            const qreal ticksFromAnchor = (tickAnchor - min) / tickInterval;
            const qreal firstMajorTick  = tickAnchor - std::floor(ticksFromAnchor) * tickInterval;

            qreal value = firstMajorTick;
            while (value <= max)
            {
                labels << formatLabel(formatSpec, array, value, precision, preStr, postStr);
                value += tickInterval;
            }
        }
    }

    return labels;
}

QStringList ChartiumAxisElement::createLogValueLabels(qreal min, qreal max, qreal base, int ticks, const QString& format) const
{
    QStringList labels;

    if (max <= min || ticks < 1)
    {
        return labels;
    }

    const int firstTick = qCeil(qLn(base > 1 ? min : max) / qLn(base));
    if (format.isEmpty())
    {
        const int n = precisionDigits(min, max, ticks);
        for (int i = firstTick; i < ticks + firstTick; i++)
        {
            qreal value = qPow(base, i);
            labels << presenter()->numberToString(value, 'f', n);
        }
    }
    else
    {
        QByteArray array = format.toLatin1();
        QString    formatSpec;
        QString    preStr;
        QString    postStr;
        int        precision = 6; // Six is the default precision in Qt API
        if (presenter()->localizeNumbers())
        {
            QRegularExpressionMatch rmatch;
            if (format.indexOf(labelFormatMatcherLocalized(), 0, &rmatch) != -1)
            {
                preStr = rmatch.captured(1);
                if (!rmatch.captured(2).isEmpty())
                {
                    precision = rmatch.captured(2).toInt();
                }
                formatSpec = rmatch.captured(3);
                postStr    = rmatch.captured(4);
            }
        }
        else
        {
            QRegularExpressionMatch rmatch;
            if (format.indexOf(labelFormatMatcher(), 0, &rmatch) != -1)
            {
                formatSpec = rmatch.captured(1);
            }
        }
        for (int i = firstTick; i < ticks + firstTick; i++)
        {
            qreal value = qPow(base, i);
            labels << formatLabel(formatSpec, array, value, precision, preStr, postStr);
        }
    }

    return labels;
}

QStringList ChartiumAxisElement::createDateTimeLabels(qreal max, qreal min, int ticks, const QString& format) const
{
    QStringList labels;

    if (max <= min || ticks < 1)
    {
        return labels;
    }

    for (int i = 0; i < ticks; i++)
    {
        qreal value = min + (i * (max - min) / (ticks - 1));
        labels << presenter()->locale().toString(QDateTime::fromMSecsSinceEpoch(value), format);
    }

    return labels;
}

QStringList ChartiumAxisElement::createColorLabels(qreal min, qreal max, int ticks) const
{
    QStringList labels;

    if (max <= min || ticks < 1)
    {
        return labels;
    }

    const int n = precisionDigits(min, max, ticks);
    for (int i = 0; i < ticks; ++i)
    {
        qreal value = min + (i * (max - min) / (ticks - 1));
        labels << presenter()->numberToString(value, 'f', n);
    }

    return labels;
}

bool ChartiumAxisElement::labelsEditable() const
{
    return mLabelsEditable;
}

void ChartiumAxisElement::setLabelsEditable(bool labelsEditable)
{
    // TODO: Uncomment
    /*
    if (axis()->type() == IChartiumAxis::AxisTypeValue || axis()->type() == IChartiumAxis::AxisTypeDateTime)
    {
        labelGroup()->setHandlesChildEvents(!labelsEditable);
        const QList<QGraphicsItem*> childItems = labelGroup()->childItems();
        for (auto item : childItems)
        {
            switch (axis()->type())
            {
                case IChartiumAxis::AxisTypeValue:
                    static_cast<ValueAxisLabel*>(item)->setEditable(labelsEditable);
                    break;
                case IChartiumAxis::AxisTypeDateTime:
                    static_cast<DateTimeAxisLabel*>(item)->setEditable(labelsEditable);
                    break;
                default:
                    break;
            }
        }
        mLabelsEditable = labelsEditable;
    }
    */
}

bool ChartiumAxisElement::labelsVisible() const
{
    return mLabels->isVisible();
}

QList<qreal> ChartiumAxisElement::calculateLayout() const
{
    QList<qreal> res;

    return res;
}

void ChartiumAxisElement::updateLayout(const QList<qreal>& layout)
{
}

QList<QGraphicsItem*> ChartiumAxisElement::gridItems()
{
    QList<QGraphicsItem*> res;

    return res;
}

QList<QGraphicsItem*> ChartiumAxisElement::minorGridItems()
{
    QList<QGraphicsItem*> res;

    return res;
}

QList<QGraphicsItem*> ChartiumAxisElement::labelItems()
{
    QList<QGraphicsItem*> res;

    return res;
}

QList<QGraphicsItem*> ChartiumAxisElement::shadeItems()
{
    QList<QGraphicsItem*> res;

    return res;
}

QList<QGraphicsItem*> ChartiumAxisElement::arrowItems()
{
    QList<QGraphicsItem*> res;

    return res;
}

QList<QGraphicsItem*> ChartiumAxisElement::minorArrowItems()
{
    QList<QGraphicsItem*> res;

    return res;
}

QGraphicsTextItem* ChartiumAxisElement::titleItem() const
{
    return nullptr;
}

QGraphicsPixmapItem* ChartiumAxisElement::colorScaleItem() const
{
    return nullptr;
}

QGraphicsItemGroup* ChartiumAxisElement::gridGroup()
{
    return nullptr;
}

QGraphicsItemGroup* ChartiumAxisElement::minorGridGroup()
{
    return nullptr;
}

QGraphicsItemGroup* ChartiumAxisElement::labelGroup()
{
    return nullptr;
}

QGraphicsItemGroup* ChartiumAxisElement::shadeGroup()
{
    return nullptr;
}

QGraphicsItemGroup* ChartiumAxisElement::arrowGroup()
{
    return nullptr;
}

QGraphicsItemGroup* ChartiumAxisElement::minorArrowGroup()
{
    return nullptr;
}

void ChartiumAxisElement::prepareColorScale(const qreal width, const qreal height)
{
    // TODO: remove it
}

void ChartiumAxisElement::connectSlots()
{
    QObject::connect(axis(), SIGNAL(visibleChanged(bool)), this, SLOT(handleVisibleChanged(bool)));
    QObject::connect(axis(), SIGNAL(lineVisibleChanged(bool)), this, SLOT(handleArrowVisibleChanged(bool)));
    QObject::connect(axis(), SIGNAL(gridVisibleChanged(bool)), this, SLOT(handleGridVisibleChanged(bool)));
    QObject::connect(axis(), SIGNAL(labelsVisibleChanged(bool)), this, SLOT(handleLabelsVisibleChanged(bool)));
    QObject::connect(axis(), SIGNAL(shadesVisibleChanged(bool)), this, SLOT(handleShadesVisibleChanged(bool)));
    QObject::connect(axis(), SIGNAL(labelsAngleChanged(int)), this, SLOT(handleLabelsAngleChanged(int)));
    QObject::connect(axis(), SIGNAL(linePenChanged(QPen)), this, SLOT(handleArrowPenChanged(QPen)));
    QObject::connect(axis(), SIGNAL(labelsBrushChanged(QBrush)), this, SLOT(handleLabelsBrushChanged(QBrush)));
    QObject::connect(axis(), SIGNAL(labelsFontChanged(QFont)), this, SLOT(handleLabelsFontChanged(QFont)));
    QObject::connect(axis(), SIGNAL(gridLinePenChanged(QPen)), this, SLOT(handleGridPenChanged(QPen)));
    QObject::connect(axis(), SIGNAL(shadesPenChanged(QPen)), this, SLOT(handleShadesPenChanged(QPen)));
    QObject::connect(axis(), SIGNAL(shadesBrushChanged(QBrush)), this, SLOT(handleShadesBrushChanged(QBrush)));
    QObject::connect(axis(), SIGNAL(titleTextChanged(QString)), this, SLOT(handleTitleTextChanged(QString)));
    QObject::connect(axis(), SIGNAL(titleFontChanged(QFont)), this, SLOT(handleTitleFontChanged(QFont)));
    QObject::connect(axis(), SIGNAL(titleBrushChanged(QBrush)), this, SLOT(handleTitleBrushChanged(QBrush)));
    QObject::connect(axis(), SIGNAL(titleVisibleChanged(bool)), this, SLOT(handleTitleVisibleChanged(bool)));
    QObject::connect(axis(), SIGNAL(rangeRealChanged(qreal, qreal)), this, SLOT(handleRangeRealChanged(qreal, qreal)));
    QObject::connect(axis(), SIGNAL(reverseChanged(bool)), this, SLOT(handleReverseChanged(bool)));
    QObject::connect(axis(), SIGNAL(lineVisibleChanged(bool)), this, SLOT(handleMinorArrowVisibleChanged(bool)));
    QObject::connect(axis(), SIGNAL(linePenChanged(QPen)), this, SLOT(handleMinorArrowPenChanged(QPen)));
    QObject::connect(axis(), SIGNAL(minorGridVisibleChanged(bool)), this, SLOT(handleMinorGridVisibleChanged(bool)));
    QObject::connect(axis(), SIGNAL(minorGridLinePenChanged(QPen)), this, SLOT(handleMinorGridPenChanged(QPen)));
    QObject::connect(axis(), SIGNAL(gridLineColorChanged(QColor)), this, SLOT(handleGridLineColorChanged(QColor)));
    QObject::connect(axis(), SIGNAL(minorGridLineColorChanged(QColor)), this, SLOT(handleMinorGridLineColorChanged(QColor)));
    QObject::connect(axis(), &IChartiumAxis::truncateLabelsChanged, this, &IChartiumAxisElement::handleTruncateLabelsChanged);
}

QString ChartiumAxisElement::formatLabel(
    const QString& formatSpec, const QByteArray& array, qreal value, int precision, const QString& preStr, const QString& postStr
) const
{
    QString retVal;

    if (!formatSpec.isEmpty())
    {
        if (formatSpec.at(0) == QLatin1Char('d') || formatSpec.at(0) == QLatin1Char('i') || formatSpec.at(0) == QLatin1Char('c'))
        {
            if (presenter()->localizeNumbers())
            {
                retVal = preStr + presenter()->locale().toString(qint64(value)) + postStr;
            }
            else
            {
                retVal = QString::asprintf(array.constData(), qint64(value));
            }
        }
        else if (formatSpec.at(0) == QLatin1Char('u') || formatSpec.at(0) == QLatin1Char('o') ||
                 formatSpec.at(0) == QLatin1Char('x') || formatSpec.at(0) == QLatin1Char('X'))
        {
            // These formats are not supported by localized numbers
            retVal = QString::asprintf(array.constData(), quint64(value));
        }
        else if (formatSpec.at(0) == QLatin1Char('f') || formatSpec.at(0) == QLatin1Char('F') ||
                 formatSpec.at(0) == QLatin1Char('e') || formatSpec.at(0) == QLatin1Char('E') ||
                 formatSpec.at(0) == QLatin1Char('g') || formatSpec.at(0) == QLatin1Char('G'))
        {
            if (presenter()->localizeNumbers())
            {
                retVal = preStr + presenter()->locale().toString(value, formatSpec.at(0).toLatin1(), precision) + postStr;
            }
            else
            {
                retVal = QString::asprintf(array.constData(), value);
            }
        }
    }

    return retVal;
}

void ChartiumAxisElement::handleVisibleChanged(bool visible)
{
    setVisible(visible);

    if (!visible)
    {
        mGrid->setVisible(visible);
        mArrow->setVisible(visible);
        mMinorGrid->setVisible(visible);
        mMinorArrow->setVisible(visible);
        mShades->setVisible(visible);
        mLabels->setVisible(visible);
        mTitle->setVisible(visible);

        if (mColorScale)
        {
            mColorScale->setVisible(visible);
        }
    }
    else
    {
        mGrid->setVisible(axis()->isGridLineVisible());
        mArrow->setVisible(axis()->isLineVisible());
        mMinorGrid->setVisible(axis()->isMinorGridLineVisible());
        mMinorArrow->setVisible(axis()->isLineVisible());
        mShades->setVisible(axis()->shadesVisible());
        mLabels->setVisible(axis()->labelsVisible());
        mTitle->setVisible(axis()->isTitleVisible());
    }

    if (presenter())
    {
        if (visible)
        {
            QSizeF before = effectiveSizeHint(Qt::PreferredSize);
            QSizeF after  = sizeHint(Qt::PreferredSize);
            if (before != after)
            {
                QGraphicsLayoutItem::updateGeometry();
            }
        }

        presenter()->layout()->invalidate();
    }
}

void ChartiumAxisElement::handleArrowVisibleChanged(bool visible)
{
    mArrow->setVisible(visible);
}

void ChartiumAxisElement::handleGridVisibleChanged(bool visible)
{
    mGrid->setVisible(visible);
}

void ChartiumAxisElement::handleLabelsVisibleChanged(bool visible)
{
    QGraphicsLayoutItem::updateGeometry();
    presenter()->layout()->invalidate();
    mLabels->setVisible(visible);
}

void ChartiumAxisElement::handleShadesVisibleChanged(bool visible)
{
    mShades->setVisible(visible);
}

void ChartiumAxisElement::handleLabelsAngleChanged(int angle)
{
    const auto items = mLabels->childItems();

    for (QGraphicsItem* item : items)
    {
        item->setRotation(angle);
    }

    QGraphicsLayoutItem::updateGeometry();
    presenter()->layout()->invalidate();
}

void ChartiumAxisElement::handleShadesBrushChanged(const QBrush& brush)
{
}

void ChartiumAxisElement::handleShadesPenChanged(const QPen& pen)
{
}

void ChartiumAxisElement::handleArrowPenChanged(const QPen& pen)
{
}

void ChartiumAxisElement::handleGridPenChanged(const QPen& pen)
{
}

void ChartiumAxisElement::handleMinorArrowPenChanged(const QPen& pen)
{
}

void ChartiumAxisElement::handleMinorGridPenChanged(const QPen& pen)
{
}

void ChartiumAxisElement::handleMinorGridLineColorChanged(const QColor& color)
{
}

void ChartiumAxisElement::handleGridLineColorChanged(const QColor& color)
{
}

void ChartiumAxisElement::handleLabelsBrushChanged(const QBrush& brush)
{
}

void ChartiumAxisElement::handleLabelsFontChanged(const QFont& font)
{
    const auto items = mLabels->childItems();

    for (QGraphicsItem* item : items)
    {
        static_cast<QGraphicsTextItem*>(item)->setFont(font);
    }

    QGraphicsLayoutItem::updateGeometry();
    presenter()->layout()->invalidate();
}

void ChartiumAxisElement::handleTitleBrushChanged(const QBrush& brush)
{
    mTitle->setDefaultTextColor(brush.color());
}

void ChartiumAxisElement::handleTitleFontChanged(const QFont& font)
{
    if (mTitle->font() != font)
    {
        mTitle->setFont(font);
        QGraphicsLayoutItem::updateGeometry();
        presenter()->layout()->invalidate();
    }
}

void ChartiumAxisElement::handleTitleTextChanged(const QString& title)
{
    QGraphicsLayoutItem::updateGeometry();
    presenter()->layout()->invalidate();
    if (title.isEmpty() || !mTitle->isVisible())
    {
        mTitle->setHtml(title);
    }
}

void ChartiumAxisElement::handleTitleVisibleChanged(bool visible)
{
    QGraphicsLayoutItem::updateGeometry();
    presenter()->layout()->invalidate();
    mTitle->setVisible(visible);
}

void ChartiumAxisElement::handleRangeRealChanged(qreal min, qreal max)
{
    Q_UNUSED(min);
    Q_UNUSED(max);

    if (!emptyAxis())
    {
        const QList<qreal> layout = calculateLayout();
        updateLayout(layout);
        QSizeF before = effectiveSizeHint(Qt::PreferredSize);
        QSizeF after  = sizeHint(Qt::PreferredSize);

        if (before != after)
        {
            QGraphicsLayoutItem::updateGeometry();
            // We don't want to call invalidate on layout, since it will change minimum size of
            // component, which we would like to avoid since it causes nasty flips when scrolling
            // or zooming, instead recalculate layout and use plotArea for extra space.
            presenter()->layout()->setGeometry(presenter()->layout()->geometry());
        }
    }
}

void ChartiumAxisElement::handleReverseChanged(bool reverse)
{
    Q_UNUSED(reverse);

    QGraphicsLayoutItem::updateGeometry();
    presenter()->layout()->invalidate();
}

void ChartiumAxisElement::handleMinorArrowVisibleChanged(bool visible)
{
    mMinorArrow->setVisible(visible);
}

void ChartiumAxisElement::handleMinorGridVisibleChanged(bool visible)
{
    mMinorGrid->setVisible(visible);
}

void ChartiumAxisElement::handleLabelsPositionChanged()
{
    QGraphicsLayoutItem::updateGeometry();
    presenter()->layout()->invalidate();
}

void ChartiumAxisElement::handleTruncateLabelsChanged()
{
    QGraphicsLayoutItem::updateGeometry();
    presenter()->layout()->invalidate();
}

void ChartiumAxisElement::handleColorScaleSizeChanged()
{
    QGraphicsLayoutItem::updateGeometry();
}

void ChartiumAxisElement::handleColorScaleGradientChanged()
{
    const QPixmap& pixmap = mColorScale->pixmap();
    prepareColorScale(pixmap.width(), pixmap.height());
}

void ChartiumAxisElement::valueLabelEdited(qreal oldValue, qreal newValue)
{
    // TODO: Uncomment
    /*
    qreal range    = max() - min();
    qreal center   = ((max() - min()) / 2.0) + min();
    qreal newRange = 0.0;
    auto  label    = static_cast<ValueAxisLabel*>(this->sender());
    if ((oldValue >= center && newValue >= min()) || (oldValue < center && newValue >= max() && oldValue != min()))
    {
        newRange = range * ((newValue - min()) / (oldValue - min()));
        if (newRange > 0)
        {
            mAxis->setRange(min(), min() + newRange);
            return;
        }
    }
    else if ((oldValue >= center && newValue <= min() && max() != oldValue) || (oldValue < center && newValue < max()))
    {
        newRange = range * ((max() - newValue) / (max() - oldValue));
        if (newRange > 0)
        {
            mAxis->setRange(max() - newRange, max());
            return;
        }
    }
    label->reloadBeforeEditContent();
*/
}

void ChartiumAxisElement::dateTimeLabelEdited(const QDateTime& oldTime, const QDateTime& newTime)
{
    // TODO: Uncomment
    /*
    qreal  range    = max() - min();
    qreal  center   = ((max() - min()) / 2.0) + min();
    qreal  newRange = 0.0;
    qint64 oldValue = oldTime.toMSecsSinceEpoch();
    qint64 newValue = newTime.toMSecsSinceEpoch();
    if ((oldValue >= center && newValue >= min()) || (oldValue < center && newValue >= max() && oldValue != min()))
    {
        newRange = range * ((newValue - min()) / (oldValue - min()));
        if (newRange > 0)
        {
            mAxis->setRange(QDateTime::fromMSecsSinceEpoch(min()), QDateTime::fromMSecsSinceEpoch(min() + newRange));
            return;
        }
    }
    else if ((oldValue >= center && newValue <= min() && max() != oldValue) || (oldValue < center && newValue < max()))
    {
        newRange = range * ((max() - newValue) / (max() - oldValue));
        if (newRange > 0)
        {
            mAxis->setRange(max() - newRange, max());
            mAxis->setRange(QDateTime::fromMSecsSinceEpoch(max() - newRange), QDateTime::fromMSecsSinceEpoch(max()));
            return;
        }
    }
    static_cast<DateTimeAxisLabel*>(this->sender())->reloadBeforeEditContent();
*/
}
