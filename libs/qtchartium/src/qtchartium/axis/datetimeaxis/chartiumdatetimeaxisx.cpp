#include "src/qtchartium/axis/datetimeaxis/chartiumdatetimeaxisx.h"

#include "src/qtchartium/ichartiumpresenter.h"



ChartiumDateTimeAxisX::ChartiumDateTimeAxisX(
    IChartiumDateTimeAxis* axis, IChartiumPresenter* presenter, QGraphicsItem* item, QGraphicsLayoutItem* parent
) :
    IChartiumDateTimeAxisX(axis, presenter, item, parent),
    mAxis(axis)
{
    // clang-format off
    connect(mAxis, SIGNAL(tickCountChanged(int)),  this, SLOT(handleTickCountChanged(int)));
    connect(mAxis, SIGNAL(formatChanged(QString)), this, SLOT(handleFormatChanged(QString)));
    // clang-format on
}

ChartiumDateTimeAxisX::~ChartiumDateTimeAxisX()
{
}

QSizeF ChartiumDateTimeAxisX::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
{
    Q_UNUSED(constraint);

    QSizeF sh;

    QSizeF            base      = IChartiumDateTimeAxisX::sizeHint(which, constraint);
    const QStringList ticksList = createDateTimeLabels(min(), max(), mAxis->tickCount(), mAxis->format());

    // Width of horizontal axis sizeHint indicates the maximum distance labels can extend past
    // first and last ticks. Base width is irrelevant.
    qreal width  = 0;
    qreal height = 0;

    if (ticksList.empty())
    {
        return sh;
    }

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

QList<qreal> ChartiumDateTimeAxisX::calculateLayout() const
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

void ChartiumDateTimeAxisX::updateGeometry()
{
    const QList<qreal>& layout = IChartiumDateTimeAxisX::layout();

    if (layout.isEmpty())
    {
        return;
    }

    setLabels(createDateTimeLabels(min(), max(), layout.size(), mAxis->format()));
    IChartiumDateTimeAxisX::updateGeometry();
    updateLabelsDateTimes();
}

void ChartiumDateTimeAxisX::handleTickCountChanged(int tick)
{
    QGraphicsLayoutItem::updateGeometry();

    if (presenter())
    {
        presenter()->layout()->invalidate();
    }
}

void ChartiumDateTimeAxisX::handleFormatChanged(const QString& format)
{
    QGraphicsLayoutItem::updateGeometry();

    if (presenter())
    {
        presenter()->layout()->invalidate();
    }
}
