#include "src/qtchartium/axis/valueaxis/chartiumvalueaxisy.h"

#include "src/qtchartium/ichartiumpresenter.h"



ChartiumValueAxisY::ChartiumValueAxisY(
    IChartiumValueAxis* axis, IChartiumPresenter* presenter, QGraphicsItem* item, QGraphicsLayoutItem* parent
) :
    IChartiumValueAxisY(axis, presenter, item, parent),
    mAxis(axis)
{
    // clang-format off
    connect(mAxis, SIGNAL(tickCountChanged(int)),                         this, SLOT(handleTickCountChanged(int)));
    connect(mAxis, SIGNAL(minorTickCountChanged(int)),                    this, SLOT(handleMinorTickCountChanged(int)));
    connect(mAxis, SIGNAL(labelFormatChanged(QString)),                   this, SLOT(handleLabelFormatChanged(QString)));
    connect(mAxis, SIGNAL(tickIntervalChanged(qreal)),                    this, SLOT(handleTickIntervalChanged(qreal)));
    connect(mAxis, SIGNAL(tickAnchorChanged(qreal)),                      this, SLOT(handleTickAnchorChanged(qreal)));
    connect(mAxis, SIGNAL(tickTypeChanged(IChartiumValueAxis::TickType)), this, SLOT(handleTickTypeChanged(IChartiumValueAxis::TickType)));
    // clang-format on
}

ChartiumValueAxisY::~ChartiumValueAxisY()
{
}

QSizeF ChartiumValueAxisY::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
{
    Q_UNUSED(constraint);

    QSizeF            sh;
    QSizeF            base      = IChartiumValueAxisY::sizeHint(which, constraint);
    const QStringList ticksList = createValueLabels(
        min(), max(), mAxis->tickCount(), mAxis->tickInterval(), mAxis->tickAnchor(), mAxis->tickType(), mAxis->labelFormat()
    );
    qreal width = 0;
    // Height of vertical axis sizeHint indicates the maximum distance labels can extend past
    // first and last ticks. Base height is irrelevant.
    qreal height = 0;

    switch (which)
    {
        case Qt::MinimumSize:
        {
            if (labelsVisible())
            {
                QRectF boundingRect =
                    presenter()->textBoundingRect(axis()->labelsFont(), QStringLiteral("..."), axis()->labelsAngle());
                width  = boundingRect.width() + labelPadding() + base.width() + 1.0;
                height = boundingRect.height() / 2.0;
            }
            else
            {
                width  = base.width() + 1.0;
                height = 0;
            }
            sh = QSizeF(width, height);
            break;
        }
        case Qt::PreferredSize:
        {
            if (labelsVisible())
            {
                qreal labelWidth  = 0.0;
                qreal firstHeight = -1.0;
                for (const QString& s : ticksList)
                {
                    QRectF rect = presenter()->textBoundingRect(axis()->labelsFont(), s, axis()->labelsAngle());
                    labelWidth  = qMax(rect.width(), labelWidth);
                    height      = rect.height();
                    if (firstHeight < 0.0)
                    {
                        firstHeight = height;
                    }
                }
                width  = labelWidth + labelPadding() + base.width() + 2.0; //two pixels of tolerance
                height = qMax(height, firstHeight) / 2.0;
            }
            else
            {
                width  = base.width() + 2.0; //two pixels of tolerance
                height = 0;
            }
            sh = QSizeF(width, height);
            break;
        }
        default:
            break;
    }
    return sh;
}

QList<qreal> ChartiumValueAxisY::calculateLayout() const
{
    if (mAxis->tickType() == IChartiumValueAxis::TicksFixed)
    {
        int tickCount = mAxis->tickCount();

        Q_ASSERT(tickCount >= 2);

        QList<qreal> points;
        points.resize(tickCount);

        const QRectF& gridRect = gridGeometry();
        const qreal   deltaY   = gridRect.height() / (qreal(tickCount) - 1.0);
        for (int i = 0; i < tickCount; ++i)
        {
            points[i] = qreal(i) * -deltaY + gridRect.bottom();
        }
        return points;
    }
    else
    {
        const qreal interval = mAxis->tickInterval();
        const qreal anchor   = mAxis->tickAnchor();
        const qreal maxValue = max();
        const qreal minValue = min();

        // Find the first major tick right after the min of the range
        const qreal ticksFromAnchor = (anchor - minValue) / interval;
        const qreal firstMajorTick  = anchor - std::floor(ticksFromAnchor) * interval;

        const QRectF& gridRect = gridGeometry();
        const qreal   deltaY   = gridRect.height() / (maxValue - minValue);

        QList<qreal> points;
        const qreal  bottomPos = gridRect.bottom();
        qreal        value     = firstMajorTick;
        while (value <= maxValue)
        {
            points << (value - minValue) * -deltaY + bottomPos;
            value += interval;
        }

        return points;
    }
}

void ChartiumValueAxisY::updateGeometry()
{
    const QList<qreal>& layout                 = IChartiumValueAxisY::layout();
    const QList<qreal>& dynamicMinorTicklayout = IChartiumValueAxisY::dynamicMinorTicklayout();

    if (layout.isEmpty() && dynamicMinorTicklayout.isEmpty())
    {
        return;
    }

    setLabels(createValueLabels(
        min(), max(), layout.size(), mAxis->tickInterval(), mAxis->tickAnchor(), mAxis->tickType(), mAxis->labelFormat()
    ));

    IChartiumValueAxisY::updateGeometry();
    updateLabelsValues(mAxis);
}

void ChartiumValueAxisY::handleTickCountChanged(int tick)
{
    Q_UNUSED(tick);
    QGraphicsLayoutItem::updateGeometry();

    if (presenter())
    {
        presenter()->layout()->invalidate();
    }
}

void ChartiumValueAxisY::handleMinorTickCountChanged(int tick)
{
    Q_UNUSED(tick);
    QGraphicsLayoutItem::updateGeometry();

    if (presenter())
    {
        presenter()->layout()->invalidate();
    }
}

void ChartiumValueAxisY::handleLabelFormatChanged(const QString& format)
{
    Q_UNUSED(format);
    QGraphicsLayoutItem::updateGeometry();

    if (presenter())
    {
        presenter()->layout()->invalidate();
    }
}

void ChartiumValueAxisY::handleTickIntervalChanged(qreal interval)
{
    Q_UNUSED(interval);
    QGraphicsLayoutItem::updateGeometry();

    if (presenter())
    {
        presenter()->layout()->invalidate();
    }
}

void ChartiumValueAxisY::handleTickAnchorChanged(qreal anchor)
{
    Q_UNUSED(anchor);
    QGraphicsLayoutItem::updateGeometry();

    if (presenter())
    {
        presenter()->layout()->invalidate();
    }
}

void ChartiumValueAxisY::handleTickTypeChanged(IChartiumValueAxis::TickType type)
{
    Q_UNUSED(type);
    QGraphicsLayoutItem::updateGeometry();

    if (presenter())
    {
        presenter()->layout()->invalidate();
    }
}
