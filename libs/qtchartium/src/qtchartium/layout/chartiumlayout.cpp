#include "src/qtchartium/layout/chartiumlayout.h"

#include "src/qtchartium/ichartiumpresenter.h"



constexpr qreal GOLDEN_RATIO = 0.04;



ChartiumLayout::ChartiumLayout(IChartiumPresenter* presenter, QGraphicsLayoutItem* parent) :
    IChartiumLayout(parent),
    mPresenter(presenter),
    mMargins(20, 20, 20, 20),
    mMinAxisRect()
{
}

ChartiumLayout::~ChartiumLayout()
{
}

void ChartiumLayout::setMargins(const QMargins& margins)
{
    if (mMargins != margins)
    {
        mMargins = margins;

        updateGeometry();
    }
}

QMargins ChartiumLayout::margins() const
{
    return mMargins;
}

void ChartiumLayout::setGeometry(const QRectF& rect)
{
    if (!rect.isValid())
    {
        return;
    }

    // If the chart has a fixed geometry then don't update visually, unless plotbackground is
    // visible.
    const bool updateLayout =
        (!mPresenter->isFixedGeometry() || mPresenter->isPlotAreaBackgroundVisible() || mPresenter->geometry() == rect);
    if (mPresenter->chart()->isVisible())
    {
        QList<IChartiumAxisElement*> axes       = mPresenter->axisItems();
        IChartiumTitle*              title      = mPresenter->titleElement();
        IChartiumLegend*             legend     = mPresenter->legend();
        IChartiumBackground*         background = mPresenter->backgroundElement();

        QRectF contentGeometry = calculateBackgroundGeometry(rect, background, updateLayout);

        contentGeometry = calculateContentGeometry(contentGeometry);

        if (title && title->isVisible())
        {
            contentGeometry = calculateTitleGeometry(contentGeometry, title, updateLayout);
        }

        if (legend->isAttachedToChart() && legend->isVisible())
        {
            contentGeometry = calculateLegendGeometry(contentGeometry, legend, updateLayout);
        }

        contentGeometry = calculateAxisGeometry(contentGeometry, axes, updateLayout);

        if (contentGeometry.isValid())
        {
            mPresenter->setGeometry(contentGeometry);
            if (updateLayout)
            {
                if (mPresenter->chart()->chartType() == IChartiumChart::ChartTypeCartesian)
                {
                    static_cast<QGraphicsRectItem*>(mPresenter->plotAreaElement())->setRect(contentGeometry);
                }
                else
                {
                    static_cast<QGraphicsEllipseItem*>(mPresenter->plotAreaElement())->setRect(contentGeometry);
                }
            }
        }
    }

    QGraphicsLayout::setGeometry(rect);
}

QRectF ChartiumLayout::calculateBackgroundGeometry(const QRectF& geometry, IChartiumBackground* background, bool update) const
{
    qreal left;
    qreal top;
    qreal right;
    qreal bottom;

    getContentsMargins(&left, &top, &right, &bottom);

    QRectF backgroundGeometry = geometry.adjusted(left, top, -right, -bottom);

    if (background && update)
    {
        background->setRect(backgroundGeometry);
    }

    return backgroundGeometry;
}

QRectF ChartiumLayout::calculateBackgroundMinimum(const QRectF& minimum) const
{
    qreal left;
    qreal top;
    qreal right;
    qreal bottom;
    getContentsMargins(&left, &top, &right, &bottom);

    return minimum.adjusted(0, 0, left + right, top + bottom);
    ;
}

QRectF ChartiumLayout::calculateContentGeometry(const QRectF& geometry) const
{
    return geometry.adjusted(mMargins.left(), mMargins.top(), -mMargins.right(), -mMargins.bottom());
}

QRectF ChartiumLayout::calculateContentMinimum(const QRectF& minimum) const
{
    return minimum.adjusted(0, 0, mMargins.left() + mMargins.right(), mMargins.top() + mMargins.bottom());
}

QRectF ChartiumLayout::calculateTitleGeometry(const QRectF& geometry, IChartiumTitle* title, bool update) const
{
    if (update)
    {
        title->setGeometry(geometry);
    }
    if (title->text().isEmpty())
    {
        return geometry;
    }
    else
    {
        // Round to full pixel via QPoint to avoid one pixel clipping on the edge in some cases
        QPointF center((geometry.center() - title->boundingRect().center()).toPoint());
        if (update)
        {
            title->setPos(center.x(), title->pos().y());
        }
        return geometry.adjusted(0, title->boundingRect().height() + 1, 0, 0);
    }
}

QRectF ChartiumLayout::calculateTitleMinimum(const QRectF& minimum, IChartiumTitle* title) const
{
    if (!title->isVisible() || title->text().isEmpty())
    {
        return minimum;
    }
    else
    {
        QSizeF min = title->sizeHint(Qt::MinimumSize);
        return minimum.adjusted(0, 0, min.width(), min.height());
    }
}

QRectF ChartiumLayout::calculateLegendGeometry(const QRectF& geometry, IChartiumLegend* legend, bool update) const
{
    QSizeF size = legend->effectiveSizeHint(Qt::PreferredSize, QSizeF(-1, -1));
    QRectF legendRect;
    QRectF result;

    switch (legend->alignment())
    {
        case Qt::AlignTop:
        {
            legendRect = QRectF(geometry.topLeft(), QSizeF(geometry.width(), size.height()));
            result     = geometry.adjusted(0, legendRect.height(), 0, 0);
            break;
        }
        case Qt::AlignBottom:
        {
            legendRect =
                QRectF(QPointF(geometry.left(), geometry.bottom() - size.height()), QSizeF(geometry.width(), size.height()));
            result = geometry.adjusted(0, 0, 0, -legendRect.height());
            break;
        }
        case Qt::AlignLeft:
        {
            qreal width = qMin(size.width(), geometry.width() * GOLDEN_RATIO);
            legendRect  = QRectF(geometry.topLeft(), QSizeF(width, geometry.height()));
            result      = geometry.adjusted(width, 0, 0, 0);
            break;
        }
        case Qt::AlignRight:
        {
            qreal width = qMin(size.width(), geometry.width() * GOLDEN_RATIO);
            legendRect  = QRectF(QPointF(geometry.right() - width, geometry.top()), QSizeF(width, geometry.height()));
            result      = geometry.adjusted(0, 0, -width, 0);
            break;
        }
        default:
        {
            legendRect = QRectF(0, 0, 0, 0);
            result     = geometry;
            break;
        }
    }
    if (update)
    {
        legend->setGeometry(legendRect);
    }

    return result;
}

QRectF ChartiumLayout::calculateLegendMinimum(const QRectF& minimum, IChartiumLegend* legend) const
{
    if (!legend->isAttachedToChart() || !legend->isVisible())
    {
        return minimum;
    }
    else
    {
        QSizeF minSize = legend->effectiveSizeHint(Qt::MinimumSize, QSizeF(-1, -1));
        return minimum.adjusted(0, 0, minSize.width(), minSize.height());
    }
}

QRectF ChartiumLayout::calculateAxisGeometry(const QRectF& geometry, const QList<IChartiumAxisElement*>& axes, bool update) const
{
    return QRectF();
}

QRectF ChartiumLayout::calculateAxisMinimum(const QRectF& minimum, const QList<IChartiumAxisElement*>& axes) const
{
    return QRectF();
}

QSizeF ChartiumLayout::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
{
    if (which == Qt::MinimumSize)
    {
        QList<IChartiumAxisElement*> axes   = mPresenter->axisItems();
        IChartiumTitle*              title  = mPresenter->titleElement();
        IChartiumLegend*             legend = mPresenter->legend();
        QRectF                       minimumRect(0, 0, 0, 0);

        minimumRect = calculateBackgroundMinimum(minimumRect);
        minimumRect = calculateContentMinimum(minimumRect);
        minimumRect = calculateTitleMinimum(minimumRect, title);
        minimumRect = calculateLegendMinimum(minimumRect, legend);
        minimumRect = calculateAxisMinimum(minimumRect, axes);

        return minimumRect.size().toSize();
    }

    return QSize(-1, -1);
}

int ChartiumLayout::count() const
{
    return 0;
}

QGraphicsLayoutItem* ChartiumLayout::itemAt(int i) const
{
    return nullptr;
}

void ChartiumLayout::removeAt(int)
{
}
