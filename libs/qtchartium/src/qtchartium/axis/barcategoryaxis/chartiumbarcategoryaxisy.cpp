#include "src/qtchartium/axis/barcategoryaxis/chartiumbarcategoryaxisy.h"

#include "src/qtchartium/ichartiumpresenter.h"



ChartiumBarCategoryAxisY::ChartiumBarCategoryAxisY(
    IChartiumBarCategoryAxis* axis, IChartiumPresenter* presenter, QGraphicsItem* item, QGraphicsLayoutItem* parent
) :
    IChartiumBarCategoryAxisY(axis, presenter, item, parent),
    mAxis(axis)
{
    connect(mAxis, SIGNAL(categoriesChanged()), this, SLOT(handleCategoriesChanged()));

    handleCategoriesChanged();
}

ChartiumBarCategoryAxisY::~ChartiumBarCategoryAxisY()
{
}

QStringList ChartiumBarCategoryAxisY::createCategoryLabels(const QList<qreal>& layout) const
{
    QStringList   result;
    const QRectF& gridRect = gridGeometry();
    const qreal   d        = (max() - min()) / gridRect.height();

    for (int i = 0; i < layout.size() - 1; ++i)
    {
        int x = qFloor(((gridRect.height() - (layout[i + 1] + layout[i]) / 2 + gridRect.top()) * d + min() + 0.5));

        if ((x < mAxis->categories().size()) && (x >= 0))
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

QSizeF ChartiumBarCategoryAxisY::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
{
    QSizeF            sh;
    QSizeF            base      = IChartiumBarCategoryAxisY::sizeHint(which, constraint);
    const QStringList ticksList = mAxis->categories();
    qreal             width     = 0;
    qreal             height    = 0; // Height is irrelevant for Y axes with interval labels

    switch (which)
    {
        case Qt::MinimumSize:
        {
            if (labelsVisible())
            {
                QRectF boundingRect =
                    presenter()->textBoundingRect(axis()->labelsFont(), QStringLiteral("..."), axis()->labelsAngle());
                width = boundingRect.width() + labelPadding() + base.width() + 1.0;

                if (base.width() > 0.0)
                {
                    width += labelPadding();
                }
            }
            else
            {
                width = base.width() + 1.0;
            }

            sh = QSizeF(width, height);

            break;
        }
        case Qt::PreferredSize:
        {
            if (labelsVisible())
            {
                qreal labelWidth = 0.0;

                for (const QString& s : ticksList)
                {
                    QRectF rect = presenter()->textBoundingRect(axis()->labelsFont(), s, axis()->labelsAngle());
                    labelWidth  = qMax(rect.width(), labelWidth);
                }

                width = labelWidth + labelPadding() + base.width() + 1.0;

                if (base.width() > 0.0)
                {
                    width += labelPadding();
                }
            }
            else
            {
                width = base.width() + 1.0;
            }

            sh = QSizeF(width, height);

            break;
        }
        default:
            break;
    }

    return sh;
}

QList<qreal> ChartiumBarCategoryAxisY::calculateLayout() const
{
    QList<qreal>  points;
    const QRectF& gridRect = gridGeometry();
    const qreal   range    = max() - min();
    const qreal   delta    = gridRect.height() / range;

    if (delta < 2)
    {
        return points;
    }

    const qreal adjustedMin = min() + 0.5;
    const qreal offset      = (qRound(adjustedMin) - adjustedMin) * delta;

    int count = qFloor(range);
    if (count < 1)
    {
        return points;
    }

    points.resize(count + 2);

    for (int i = 0; i < count + 2; ++i)
    {
        points[i] = gridRect.bottom() - (qreal(i) * delta) - offset;
    }

    return points;
}

void ChartiumBarCategoryAxisY::updateGeometry()
{
    const QList<qreal>& layout = IChartiumBarCategoryAxisY::layout();

    if (layout.isEmpty())
    {
        return;
    }

    setLabels(createCategoryLabels(layout));
    IChartiumBarCategoryAxisY::updateGeometry();
}

void ChartiumBarCategoryAxisY::handleCategoriesChanged()
{
    QGraphicsLayoutItem::updateGeometry();

    if (presenter())
    {
        presenter()->layout()->invalidate();
    }
}
