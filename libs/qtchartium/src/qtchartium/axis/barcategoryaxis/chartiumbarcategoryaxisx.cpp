#include "src/qtchartium/axis/barcategoryaxis/chartiumbarcategoryaxisx.h"

#include "src/qtchartium/ichartiumpresenter.h"



ChartiumBarCategoryAxisX::ChartiumBarCategoryAxisX(
    IChartiumBarCategoryAxis* axis, IChartiumPresenter* presenter, QGraphicsItem* item, QGraphicsLayoutItem* parent
) :
    IChartiumBarCategoryAxisX(axis, presenter, item, parent),
    mAxis(axis)
{
    connect(mAxis, SIGNAL(categoriesChanged()), this, SLOT(handleCategoriesChanged()));

    handleCategoriesChanged();
}

ChartiumBarCategoryAxisX::~ChartiumBarCategoryAxisX()
{
}

QStringList ChartiumBarCategoryAxisX::createCategoryLabels(const QList<qreal>& layout) const
{
    QStringList   result;
    const QRectF& gridRect = gridGeometry();
    const qreal   d        = (max() - min()) / gridRect.width();

    for (int i = 0; i < layout.size() - 1; ++i)
    {
        int x = qFloor((((layout[i] + layout[i + 1]) / 2 - gridRect.left()) * d + min() + 0.5));

        if (x < max() && (x >= 0) && x < mAxis->categories().size())
        {
            result.append(mAxis->categories().at(x));
        }
        else
        {
            // No label for x coordinate
            result.append("");
        }
    }

    result.append("");

    return result;
}

QSizeF ChartiumBarCategoryAxisX::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
{
    QSizeF            sh;
    QSizeF            base      = IChartiumBarCategoryAxisX::sizeHint(which, constraint);
    const QStringList ticksList = mAxis->categories();

    qreal width  = 0; // Width is irrelevant for X axes with interval labels
    qreal height = 0;

    switch (which)
    {
        case Qt::MinimumSize:
        {
            if (labelsVisible())
            {
                QRectF boundingRect =
                    presenter()->textBoundingRect(axis()->labelsFont(), QStringLiteral("..."), axis()->labelsAngle());
                height = boundingRect.height() + labelPadding() + base.height() + 1.0;
            }
            else
            {
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

                for (const QString& s : ticksList)
                {
                    QRectF rect = presenter()->textBoundingRect(axis()->labelsFont(), s, axis()->labelsAngle());
                    labelHeight = qMax(rect.height(), labelHeight);
                }

                height = labelHeight + labelPadding() + base.height() + 1.0;
            }
            else
            {
                height = base.height() + 1.0;
            }

            sh = QSizeF(width, height);

            break;
        }
        default:
            break;
    }
    return sh;
}

QList<qreal> ChartiumBarCategoryAxisX::calculateLayout() const
{
    QList<qreal>  points;
    const QRectF& gridRect = gridGeometry();
    qreal         range    = max() - min();
    const qreal   delta    = gridRect.width() / range;

    if (delta < 2)
    {
        return points;
    }

    qreal adjustedMin = min() + 0.5;
    qreal offset      = (qRound(adjustedMin) - adjustedMin) * delta;

    int count = qFloor(range);

    if (count < 1)
    {
        return points;
    }

    points.resize(count + 2);

    for (int i = 0; i < count + 2; ++i)
    {
        points[i] = offset + (qreal(i) * delta) + gridRect.left();
    }

    return points;
}

void ChartiumBarCategoryAxisX::updateGeometry()
{
    const QList<qreal>& layout = IChartiumBarCategoryAxisX::layout();

    if (layout.isEmpty())
    {
        return;
    }

    setLabels(createCategoryLabels(layout));
    IChartiumBarCategoryAxisX::updateGeometry();
}

void ChartiumBarCategoryAxisX::handleCategoriesChanged()
{
    QGraphicsLayoutItem::updateGeometry();

    if (presenter())
    {
        presenter()->layout()->invalidate();
    }
}
