#include "src/qtchartium/axis/chartiumcartesianaxis.h"

#include <QTextDocument>

#include "src/qtchartium/axis/chartiumlinearrowitem.h"
#include "src/qtchartium/axis/datetimeaxis/chartiumdatetimeaxislabel.h"
#include "src/qtchartium/axis/datetimeaxis/ichartiumdatetimeaxis.h"
#include "src/qtchartium/axis/valueaxis/chartiumvalueaxislabel.h"
#include "src/qtchartium/ichartiumpresenter.h"



ChartiumCartesianAxis::ChartiumCartesianAxis(
    IChartiumAxis* axis, IChartiumPresenter* presenter, bool intervalAxis, QGraphicsItem* item, QGraphicsLayoutItem* parent
) :
    IChartiumCartesianAxis(axis, presenter, intervalAxis, item, parent),
    mPresenter(presenter),
    mGridRect()
{
}

ChartiumCartesianAxis::~ChartiumCartesianAxis()
{
}

void ChartiumCartesianAxis::setDateTimeLabelsFormat(const QString& format)
{
    if (max() <= min() || layout().size() < 1 || axis()->type() != IChartiumAxis::AxisTypeDateTime)
    {
        return;
    }

    for (int i = 0; i < layout().size(); i++)
    {
        static_cast<IChartiumDateTimeAxisLabel*>(labelItems().at(i))->setFormat(format);
    }
}

void ChartiumCartesianAxis::updateLabelsValues(IChartiumValueAxis* axis)
{
    const QList<qreal>& layout = IChartiumCartesianAxis::layout();
    if (layout.isEmpty())
    {
        return;
    }

    if (axis->tickType() == IChartiumValueAxis::TicksFixed)
    {
        for (int i = 0; i < layout.size(); ++i)
        {
            qreal value = axis->isReverse() ? min() + ((layout.size() - 1 - i) * (max() - min()) / (layout.size() - 1))
                                            : min() + (i * (max() - min()) / (layout.size() - 1));
            static_cast<IChartiumValueAxisLabel*>(labelItems().at(i))->setValue(value);
        }
    }
    else
    {
        const qreal anchor          = axis->tickAnchor();
        const qreal interval        = axis->tickInterval();
        const qreal ticksFromAnchor = (anchor - min()) / interval;
        const qreal firstMajorTick  = anchor - std::floor(ticksFromAnchor) * interval;

        int   i     = axis->isReverse() ? labelItems().size() - 1 : 0;
        qreal value = firstMajorTick;
        while (value <= max())
        {
            static_cast<IChartiumValueAxisLabel*>(labelItems().at(i))->setValue(value);
            value += interval;
            i     += axis->isReverse() ? -1 : 1;
        }
    }
}

void ChartiumCartesianAxis::updateLabelsDateTimes()
{
    if (max() <= min() || layout().size() < 1)
    {
        return;
    }

    for (int i = 0; i < layout().size(); i++)
    {
        qreal value = min() + (i * (max() - min()) / (layout().size() - 1));
        static_cast<IChartiumDateTimeAxisLabel*>(labelItems().at(i))->setValue(QDateTime::fromMSecsSinceEpoch(value));
    }
}

void ChartiumCartesianAxis::createItems(int count)
{
    if (arrowItems().size() == 0)
    {
        QGraphicsLineItem* arrow = new ChartiumLineArrowItem(this, this);
        arrow->setAcceptedMouseButtons({});
        arrow->setPen(axis()->linePen());
        arrowGroup()->addToGroup(arrow);
    }

    if (intervalAxis() && gridItems().size() == 0)
    {
        for (int i = 0; i < 2; i++)
        {
            QGraphicsLineItem* item = new QGraphicsLineItem(this);
            item->setAcceptedMouseButtons({});
            item->setPen(axis()->gridLinePen());
            gridGroup()->addToGroup(item);

            QGraphicsRectItem* shades = new QGraphicsRectItem(this);
            shades->setAcceptedMouseButtons({});
            shades->setPen(axis()->shadesPen());
            shades->setBrush(axis()->shadesBrush());
            shadeGroup()->addToGroup(shades);
        }
    }

    QGraphicsTextItem* title = titleItem();
    title->setFont(axis()->titleFont());
    title->setDefaultTextColor(axis()->titleBrush().color());
    title->setHtml(axis()->titleText());

    for (int i = 0; i < count; ++i)
    {
        QGraphicsLineItem* arrow = new QGraphicsLineItem(this);
        arrow->setAcceptedMouseButtons({});
        QGraphicsLineItem* grid = new QGraphicsLineItem(this);
        grid->setAcceptedMouseButtons({});
        QGraphicsTextItem* label;

        if (axis()->type() == IChartiumAxis::AxisTypeValue)
        {
            label = new ChartiumValueAxisLabel(this);
            connect(
                static_cast<IChartiumValueAxisLabel*>(label),
                &IChartiumValueAxisLabel::valueChanged,
                this,
                &IChartiumAxisElement::valueLabelEdited
            );
            if (labelsEditable())
            {
                static_cast<IChartiumValueAxisLabel*>(label)->setEditable(true);
            }
        }
        else if (axis()->type() == IChartiumAxis::AxisTypeDateTime)
        {
            IChartiumDateTimeAxisLabel* dateTimeLabel = new ChartiumDateTimeAxisLabel(this);
            label                            = dateTimeLabel;
            connect(
                dateTimeLabel, &IChartiumDateTimeAxisLabel::dateTimeChanged, this, &IChartiumAxisElement::dateTimeLabelEdited
            );
            if (labelsEditable())
            {
                dateTimeLabel->setEditable(true);
            }
            dateTimeLabel->setFormat(static_cast<IChartiumDateTimeAxis*>(axis())->format());
        }
        else
        {
            label = new QGraphicsTextItem(this);
        }

        label->setAcceptedMouseButtons({});
        label->document()->setDocumentMargin(mPresenter->textMargin());
        arrow->setPen(axis()->linePen());
        grid->setPen(axis()->gridLinePen());
        label->setFont(axis()->labelsFont());
        label->setDefaultTextColor(axis()->labelsBrush().color());
        label->setRotation(axis()->labelsAngle());
        arrowGroup()->addToGroup(arrow);
        gridGroup()->addToGroup(grid);
        labelGroup()->addToGroup(label);

        if (gridItems().size() == 1 || (((gridItems().size() + 1) % 2) && gridItems().size() > 0))
        {
            QGraphicsRectItem* shades = new QGraphicsRectItem(this);

            shades->setPen(axis()->shadesPen());
            shades->setBrush(axis()->shadesBrush());
            shadeGroup()->addToGroup(shades);
        }
    }
}

void ChartiumCartesianAxis::deleteItems(int count)
{
    QList<QGraphicsItem*> lines  = gridItems();
    QList<QGraphicsItem*> labels = labelItems();
    QList<QGraphicsItem*> shades = shadeItems();
    QList<QGraphicsItem*> axis   = arrowItems();

    for (int i = 0; i < count; ++i)
    {
        if (lines.size() == 1 || (((lines.size() + 1) % 2) && lines.size() > 0))
        {
            delete(shades.takeLast());
        }
        delete(lines.takeLast());
        delete(labels.takeLast());
        delete(axis.takeLast());
    }
}

void ChartiumCartesianAxis::updateMinorTickItems()
{
    int currentCount  = minorArrowItems().size();
    int expectedCount = 0;

    if (axis()->type() == IChartiumAxis::AxisTypeValue)
    {
        IChartiumValueAxis* valueAxis = qobject_cast<IChartiumValueAxis*>(axis());

        if (valueAxis->tickType() == IChartiumValueAxis::TicksFixed)
        {
            expectedCount = valueAxis->minorTickCount() * (valueAxis->tickCount() - 1);
            expectedCount = qMax(expectedCount, 0);
        }
        else
        {
            const qreal interval        = valueAxis->tickInterval();
            const qreal anchor          = valueAxis->tickAnchor();
            const qreal max             = valueAxis->max();
            const qreal min             = valueAxis->min();
            const int   _minorTickCount = valueAxis->minorTickCount();

            // Find the closest major tick <= the min of the range, even if it's not drawn!
            // This is where we'll start counting minor ticks from, because minor ticks
            // might need to be drawn even before the first major tick.
            const qreal ticksFromAnchor = (anchor - min) / interval;
            const qreal firstMajorTick  = anchor - std::ceil(ticksFromAnchor) * interval;

            const qreal deltaMinor   = interval / qreal(_minorTickCount + 1);
            qreal       minorTick    = firstMajorTick + deltaMinor;
            int         minorCounter = 0;

            while (minorTick < min)
            {
                minorTick += deltaMinor;
                minorCounter++;
            }

            QList<qreal> points;

            // Calculate the points on axis value space. Conversion to graphical points
            // will be done on axis specific geometry update function
            while (minorTick <= max)
            {
                if (minorCounter < _minorTickCount)
                {
                    expectedCount++;
                    minorCounter++;
                    points << (minorTick - min);
                }
                else
                {
                    minorCounter = 0;
                }
                minorTick += deltaMinor;
            }

            setDynamicMinorTickLayout(points);
        }
    }
    else
    {
        // minor ticks are not supported
        return;
    }

    int diff = expectedCount - currentCount;
    if (diff > 0)
    {
        for (int i = 0; i < diff; ++i)
        {
            QGraphicsLineItem* minorGridLineItem = new QGraphicsLineItem(this);
            minorGridLineItem->setPen(axis()->minorGridLinePen());
            minorGridGroup()->addToGroup(minorGridLineItem);

            QGraphicsLineItem* minorArrowLineItem = new QGraphicsLineItem(this);
            minorArrowLineItem->setPen(axis()->linePen());
            minorArrowGroup()->addToGroup(minorArrowLineItem);
        }
    }
    else
    {
        QList<QGraphicsItem*> minorGridItemsList  = minorGridItems();
        QList<QGraphicsItem*> minorArrowItemsList = minorArrowItems();
        for (int i = 0; i > diff; --i)
        {
            if (!minorGridItemsList.isEmpty())
            {
                delete minorGridItemsList.takeLast();
            }

            if (!minorArrowItemsList.isEmpty())
            {
                delete minorArrowItemsList.takeLast();
            }
        }
    }
}

void ChartiumCartesianAxis::setGeometry(const QRectF& axis, const QRectF& grid)
{
    mGridRect = grid;
    setAxisGeometry(axis);

    if (emptyAxis())
    {
        prepareGeometryChange();
        return;
    }

    const QList<qreal> layout = calculateLayout();
    updateLayout(layout);
}

QRectF ChartiumCartesianAxis::gridGeometry() const
{
    return QRectF();
}

bool ChartiumCartesianAxis::emptyAxis() const
{
    return axisGeometry().isEmpty() || gridGeometry().isEmpty() || qFuzzyIsNull(max() - min());
}

QSizeF ChartiumCartesianAxis::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
{
    return QSizeF();
}

void ChartiumCartesianAxis::setGeometry(const QRectF& size)
{
}

void ChartiumCartesianAxis::updateGeometry()
{
}

void ChartiumCartesianAxis::updateLayout(const QList<qreal>& layout)
{
    int diff = IChartiumCartesianAxis::layout().size() - layout.size();

    if (diff > 0)
    {
        deleteItems(diff);
    }
    else if (diff <= 0)
    {
        createItems(-diff);
    }

    updateMinorTickItems();
    setLayout(layout);
    updateGeometry();
}

void ChartiumCartesianAxis::handleArrowPenChanged(const QPen& pen)
{
    const auto arrows = arrowItems();
    for (QGraphicsItem* item : arrows)
    {
        static_cast<QGraphicsLineItem*>(item)->setPen(pen);
    }
}

void ChartiumCartesianAxis::handleGridPenChanged(const QPen& pen)
{
    const auto items = gridItems();
    for (QGraphicsItem* item : items)
    {
        static_cast<QGraphicsLineItem*>(item)->setPen(pen);
    }
}

void ChartiumCartesianAxis::handleShadesBrushChanged(const QBrush& brush)
{
    const auto items = shadeItems();
    for (QGraphicsItem* item : items)
    {
        static_cast<QGraphicsRectItem*>(item)->setBrush(brush);
    }
}

void ChartiumCartesianAxis::handleShadesPenChanged(const QPen& pen)
{
    const auto items = shadeItems();
    for (QGraphicsItem* item : items)
    {
        static_cast<QGraphicsRectItem*>(item)->setPen(pen);
    }
}

void ChartiumCartesianAxis::handleMinorArrowPenChanged(const QPen& pen)
{
    const auto items = minorArrowItems();
    for (QGraphicsItem* item : items)
    {
        static_cast<QGraphicsLineItem*>(item)->setPen(pen);
    }
}

void ChartiumCartesianAxis::handleMinorGridPenChanged(const QPen& pen)
{
    const auto items = minorGridItems();
    for (QGraphicsItem* item : items)
    {
        static_cast<QGraphicsLineItem*>(item)->setPen(pen);
    }
}

void ChartiumCartesianAxis::handleGridLineColorChanged(const QColor& color)
{
    const auto items = gridItems();
    for (QGraphicsItem* item : items)
    {
        QGraphicsLineItem* lineItem = static_cast<QGraphicsLineItem*>(item);
        QPen               pen      = lineItem->pen();
        pen.setColor(color);
        lineItem->setPen(pen);
    }
}

void ChartiumCartesianAxis::handleMinorGridLineColorChanged(const QColor& color)
{
    const auto items = minorGridItems();
    for (QGraphicsItem* item : items)
    {
        QGraphicsLineItem* lineItem = static_cast<QGraphicsLineItem*>(item);
        QPen               pen      = lineItem->pen();
        pen.setColor(color);
        lineItem->setPen(pen);
    }
}
