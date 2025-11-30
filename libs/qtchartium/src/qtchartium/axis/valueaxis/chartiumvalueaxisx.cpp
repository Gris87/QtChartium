#include "src/qtchartium/axis/valueaxis/chartiumvalueaxisx.h"

#include "src/qtchartium/ichartiumpresenter.h"



ChartiumValueAxisX::ChartiumValueAxisX(
    IChartiumValueAxis* axis, IChartiumPresenter* presenter, QGraphicsItem* item, QGraphicsLayoutItem* parent
) :
    IChartiumValueAxisX(axis, presenter, item, parent),
    mAxis(axis)
{
    connect(mAxis, SIGNAL(tickCountChanged(int)), this, SLOT(handleTickCountChanged(int)));
    connect(mAxis, SIGNAL(minorTickCountChanged(int)), this, SLOT(handleMinorTickCountChanged(int)));
    connect(mAxis, SIGNAL(labelFormatChanged(QString)), this, SLOT(handleLabelFormatChanged(QString)));
    connect(mAxis, SIGNAL(tickIntervalChanged(qreal)), this, SLOT(handleTickIntervalChanged(qreal)));
    connect(mAxis, SIGNAL(tickAnchorChanged(qreal)), this, SLOT(handleTickAnchorChanged(qreal)));
    connect(mAxis, SIGNAL(tickTypeChanged(QValueAxis::TickType)), this, SLOT(handleTickTypeChanged(QValueAxis::TickType)));
}

ChartiumValueAxisX::~ChartiumValueAxisX()
{
}

QSizeF ChartiumValueAxisX::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
{
    Q_UNUSED(constraint);

    QSizeF sh;

    QSizeF            base      = IChartiumValueAxisX::sizeHint(which, constraint);
    const QStringList ticksList = createValueLabels(
        min(), max(), mAxis->tickCount(), mAxis->tickInterval(), mAxis->tickAnchor(), mAxis->tickType(), mAxis->labelFormat()
    );
    // Width of horizontal axis sizeHint indicates the maximum distance labels can extend past
    // first and last ticks. Base width is irrelevant.
    qreal width  = 0;
    qreal height = 0;

    switch (which)
    {
        case Qt::MinimumSize:
        {
            if (labelsVisible())
            {
                QRectF boundingRect =
                    presenter()->textBoundingRect(axis()->labelsFont(), QStringLiteral("..."), axis()->labelsAngle());
                width  = boundingRect.width() / 2.0;
                height = boundingRect.height() + labelPadding() + base.height() + 1.0;
            }
            else
            {
                width  = 0;
                height = base.height() + 1.0;
            }
            sh = QSizeF(width, height);
            break;
        }
        case Qt::PreferredSize:
        {
            if (labelsVisible())
            {
                qreal labelHeight = 0.0;
                qreal firstWidth  = -1.0;
                for (const QString& s : ticksList)
                {
                    QRectF rect = presenter()->textBoundingRect(axis()->labelsFont(), s, axis()->labelsAngle());
                    labelHeight = qMax(rect.height(), labelHeight);
                    width       = rect.width();
                    if (firstWidth < 0.0)
                    {
                        firstWidth = width;
                    }
                }
                height = labelHeight + labelPadding() + base.height() + 1.0;
                width  = qMax(width, firstWidth) / 2.0;
            }
            else
            {
                height = base.height() + 1.0;
                width  = 0;
            }
            sh = QSizeF(width, height);
            break;
        }
        default:
            break;
    }
    return sh;
}

QList<qreal> ChartiumValueAxisX::calculateLayout() const
{
    if (mAxis->tickType() == IChartiumValueAxis::TicksFixed)
    {
        int tickCount = mAxis->tickCount();

        Q_ASSERT(tickCount >= 2);

        QList<qreal> points;
        points.resize(tickCount);

        const QRectF& gridRect = gridGeometry();
        const qreal   deltaX   = gridRect.width() / (qreal(tickCount) - 1.0);
        for (int i = 0; i < tickCount; ++i)
        {
            points[i] = qreal(i) * deltaX + gridRect.left();
        }
        return points;
    }
    else
    { // QValueAxis::TicksDynamic
        const qreal interval = mAxis->tickInterval();
        const qreal anchor   = mAxis->tickAnchor();
        const qreal maxValue = max();
        const qreal minValue = min();

        // Find the first major tick right after the min of the range
        const qreal ticksFromAnchor = (anchor - minValue) / interval;
        const qreal firstMajorTick  = anchor - std::floor(ticksFromAnchor) * interval;

        const QRectF& gridRect = gridGeometry();
        const qreal   deltaX   = gridRect.width() / (maxValue - minValue);

        QList<qreal> points;
        const qreal  leftPos = gridRect.left();
        qreal        value   = firstMajorTick;
        while (value <= maxValue)
        {
            points << (value - minValue) * deltaX + leftPos;
            value += interval;
        }

        return points;
    }
}

void ChartiumValueAxisX::updateGeometry()
{
    const QList<qreal>& layout                 = IChartiumValueAxisX::layout();
    const QList<qreal>& dynamicMinorTicklayout = IChartiumValueAxisX::dynamicMinorTicklayout();
    if (layout.isEmpty() && dynamicMinorTicklayout.isEmpty())
    {
        return;
    }
    setLabels(createValueLabels(
        min(), max(), layout.size(), mAxis->tickInterval(), mAxis->tickAnchor(), mAxis->tickType(), mAxis->labelFormat()
    ));
    IChartiumValueAxisX::updateGeometry();
    updateLabelsValues(mAxis);
}

void ChartiumValueAxisX::handleTickCountChanged(int tick)
{
    Q_UNUSED(tick);
    QGraphicsLayoutItem::updateGeometry();
    if (presenter())
    {
        presenter()->layout()->invalidate();
    }
}

void ChartiumValueAxisX::handleMinorTickCountChanged(int tick)
{
    Q_UNUSED(tick);
    QGraphicsLayoutItem::updateGeometry();
    if (presenter())
    {
        presenter()->layout()->invalidate();
    }
}

void ChartiumValueAxisX::handleLabelFormatChanged(const QString& format)
{
    Q_UNUSED(format);
    QGraphicsLayoutItem::updateGeometry();
    if (presenter())
    {
        presenter()->layout()->invalidate();
    }
}

void ChartiumValueAxisX::handleTickIntervalChanged(qreal interval)
{
    Q_UNUSED(interval);
    QGraphicsLayoutItem::updateGeometry();
    if (presenter())
    {
        presenter()->layout()->invalidate();
    }
}

void ChartiumValueAxisX::handleTickAnchorChanged(qreal anchor)
{
    Q_UNUSED(anchor);
    QGraphicsLayoutItem::updateGeometry();
    if (presenter())
    {
        presenter()->layout()->invalidate();
    }
}

void ChartiumValueAxisX::handleTickTypeChanged(IChartiumValueAxis::TickType type)
{
    Q_UNUSED(type);
    QGraphicsLayoutItem::updateGeometry();
    if (presenter())
    {
        presenter()->layout()->invalidate();
    }
}
