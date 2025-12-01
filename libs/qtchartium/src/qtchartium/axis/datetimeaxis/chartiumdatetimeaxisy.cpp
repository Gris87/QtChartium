#include "src/qtchartium/axis/datetimeaxis/chartiumdatetimeaxisy.h"

#include "src/qtchartium/ichartiumpresenter.h"



ChartiumDateTimeAxisY::ChartiumDateTimeAxisY(
    IChartiumDateTimeAxis* axis, IChartiumPresenter* presenter, QGraphicsItem* item, QGraphicsLayoutItem* parent
) :
    IChartiumDateTimeAxisY(axis, presenter, item, parent),
    mAxis(axis)
{
    // clang-format off
    connect(mAxis, SIGNAL(tickCountChanged(int)),  this, SLOT(handleTickCountChanged(int)));
    connect(mAxis, SIGNAL(formatChanged(QString)), this, SLOT(handleFormatChanged(QString)));
    // clang-format on
}

ChartiumDateTimeAxisY::~ChartiumDateTimeAxisY()
{
}

QSizeF ChartiumDateTimeAxisY::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
{
    Q_UNUSED(constraint);

    QSizeF sh;

    QSizeF            base      = IChartiumDateTimeAxisY::sizeHint(which, constraint);
    const QStringList ticksList = createDateTimeLabels(min(), max(), mAxis->tickCount(), mAxis->format());
    qreal             width     = 0;

    // Height of vertical axis sizeHint indicates the maximum distance labels can extend past
    // first and last ticks. Base height is irrelevant.
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
                width  = base.width() + 2.0;
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

QList<qreal> ChartiumDateTimeAxisY::calculateLayout() const
{
    const int tickCount = mAxis->tickCount();

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

void ChartiumDateTimeAxisY::updateGeometry()
{
    const QList<qreal>& layout = IChartiumDateTimeAxisY::layout();

    if (layout.isEmpty())
    {
        return;
    }

    setLabels(createDateTimeLabels(min(), max(), layout.size(), mAxis->format()));
    IChartiumDateTimeAxisY::updateGeometry();
    updateLabelsDateTimes();
}

void ChartiumDateTimeAxisY::handleTickCountChanged(int tick)
{
    QGraphicsLayoutItem::updateGeometry();

    if (presenter())
    {
        presenter()->layout()->invalidate();
    }
}

void ChartiumDateTimeAxisY::handleFormatChanged(const QString& format)
{
    QGraphicsLayoutItem::updateGeometry();

    if (presenter())
    {
        presenter()->layout()->invalidate();
    }
}
