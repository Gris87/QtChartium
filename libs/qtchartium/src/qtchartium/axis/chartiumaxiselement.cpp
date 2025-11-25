#include "src/qtchartium/axis/chartiumaxiselement.h"



ChartiumAxisElement::ChartiumAxisElement(
    IChartiumAxis* axis, bool intervalAxis, QGraphicsItem* item, QGraphicsLayoutItem* parent
) :
    IChartiumAxisElement(item, parent)
{
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
    return false;
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
    return 0;
}

qreal ChartiumAxisElement::max() const
{
    return 0;
}

qreal ChartiumAxisElement::tickInterval() const
{
    return 0;
}

qreal ChartiumAxisElement::tickAnchor() const
{
    return 0;
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
}

bool ChartiumAxisElement::intervalAxis() const
{
    return false;
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
    QStringList res;

    return res;
}

QStringList ChartiumAxisElement::createLogValueLabels(qreal min, qreal max, qreal base, int ticks, const QString& format) const
{
    QStringList res;

    return res;
}

QStringList ChartiumAxisElement::createDateTimeLabels(qreal max, qreal min, int ticks, const QString& format) const
{
    QStringList res;

    return res;
}

QStringList ChartiumAxisElement::createColorLabels(qreal min, qreal max, int ticks) const
{
    QStringList res;

    return res;
}

bool ChartiumAxisElement::labelsEditable() const
{
    return false;
}

void ChartiumAxisElement::setLabelsEditable(bool labelsEditable)
{
}

bool ChartiumAxisElement::labelsVisible() const
{
    return false;
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
}

void ChartiumAxisElement::connectSlots()
{
}

QString ChartiumAxisElement::formatLabel(
    const QString& formatSpec, const QByteArray& array, qreal value, int precision, const QString& preStr, const QString& postStr
) const
{
    return "";
}

void ChartiumAxisElement::handleVisibleChanged(bool visible)
{
}

void ChartiumAxisElement::handleArrowVisibleChanged(bool visible)
{
}

void ChartiumAxisElement::handleGridVisibleChanged(bool visible)
{
}

void ChartiumAxisElement::handleLabelsVisibleChanged(bool visible)
{
}

void ChartiumAxisElement::handleShadesVisibleChanged(bool visible)
{
}

void ChartiumAxisElement::handleLabelsAngleChanged(int angle)
{
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
}

void ChartiumAxisElement::handleTitleBrushChanged(const QBrush& brush)
{
}

void ChartiumAxisElement::handleTitleFontChanged(const QFont& font)
{
}

void ChartiumAxisElement::handleTitleTextChanged(const QString& title)
{
}

void ChartiumAxisElement::handleTitleVisibleChanged(bool visible)
{
}

void ChartiumAxisElement::handleRangeChanged(qreal min, qreal max)
{
}

void ChartiumAxisElement::handleReverseChanged(bool reverse)
{
}

void ChartiumAxisElement::handleMinorArrowVisibleChanged(bool visible)
{
}

void ChartiumAxisElement::handleMinorGridVisibleChanged(bool visible)
{
}

void ChartiumAxisElement::handleLabelsPositionChanged()
{
}

void ChartiumAxisElement::handleTruncateLabelsChanged()
{
}

void ChartiumAxisElement::handleColorScaleSizeChanged()
{
}

void ChartiumAxisElement::handleColorScaleGradientChanged()
{
}

void ChartiumAxisElement::valueLabelEdited(qreal oldValue, qreal newValue)
{
}

void ChartiumAxisElement::dateTimeLabelEdited(const QDateTime& oldTime, const QDateTime& newTime)
{
}
