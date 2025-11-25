#pragma once



#include "src/qtchartium/chartiumelement.h"
#include <QGraphicsLayoutItem>

#include "src/qtchartium/axis/valueaxis/ichartiumvalueaxis.h"



class IChartiumAxisElement : public ChartiumElement,
                             public QGraphicsLayoutItem
{
    Q_OBJECT

public:
    explicit IChartiumAxisElement(QGraphicsItem* item = nullptr, QGraphicsLayoutItem* parent = nullptr) :
        ChartiumElement(item),
        QGraphicsLayoutItem(parent)
    {
    }
    ~IChartiumAxisElement() override = default;

    IChartiumAxisElement(const IChartiumAxisElement& another)            = delete;
    IChartiumAxisElement& operator=(const IChartiumAxisElement& another) = delete;

    virtual QRectF gridGeometry() const = 0;

    virtual void setGeometry(const QRectF& axis, const QRectF& grid) = 0;
    virtual bool emptyAxis() const                                   = 0;

    virtual IChartiumAxis* axis() const = 0;

    virtual void          setLayout(const QList<qreal>& layout) = 0;
    virtual QList<qreal>& layout()                              = 0;

    virtual void          setDynamicMinorTickLayout(const QList<qreal>& layout) = 0;
    virtual QList<qreal>& dynamicMinorTicklayout()                              = 0;

    virtual qreal labelPadding() const      = 0;
    virtual qreal titlePadding() const      = 0;
    virtual qreal colorScalePadding() const = 0;

    virtual void        setLabels(const QStringList& labels) = 0;
    virtual QStringList labels() const                       = 0;
    virtual qreal       min() const                          = 0;
    virtual qreal       max() const                          = 0;

    virtual qreal tickInterval() const = 0;
    virtual qreal tickAnchor() const   = 0;

    virtual QRectF axisGeometry() const                        = 0;
    virtual void   setAxisGeometry(const QRectF& axisGeometry) = 0;

    virtual void axisSelected() = 0;

    virtual bool intervalAxis() const = 0;

    virtual QStringList createValueLabels(
        qreal                        max,
        qreal                        min,
        int                          ticks,
        qreal                        tickInterval,
        qreal                        tickAnchor,
        IChartiumValueAxis::TickType tickType,
        const QString&               format
    ) const                                                                                                            = 0;
    virtual QStringList createLogValueLabels(qreal min, qreal max, qreal base, int ticks, const QString& format) const = 0;
    virtual QStringList createDateTimeLabels(qreal max, qreal min, int ticks, const QString& format) const             = 0;
    virtual QStringList createColorLabels(qreal min, qreal max, int ticks) const                                       = 0;

    virtual bool labelsEditable() const                 = 0;
    virtual void setLabelsEditable(bool labelsEditable) = 0;
    virtual bool labelsVisible() const                  = 0;

    virtual QList<qreal> calculateLayout() const                  = 0;
    virtual void         updateLayout(const QList<qreal>& layout) = 0;

    virtual QList<QGraphicsItem*> gridItems()            = 0;
    virtual QList<QGraphicsItem*> minorGridItems()       = 0;
    virtual QList<QGraphicsItem*> labelItems()           = 0;
    virtual QList<QGraphicsItem*> shadeItems()           = 0;
    virtual QList<QGraphicsItem*> arrowItems()           = 0;
    virtual QList<QGraphicsItem*> minorArrowItems()      = 0;
    virtual QGraphicsTextItem*    titleItem() const      = 0;
    virtual QGraphicsPixmapItem*  colorScaleItem() const = 0;
    virtual QGraphicsItemGroup*   gridGroup()            = 0;
    virtual QGraphicsItemGroup*   minorGridGroup()       = 0;
    virtual QGraphicsItemGroup*   labelGroup()           = 0;
    virtual QGraphicsItemGroup*   shadeGroup()           = 0;
    virtual QGraphicsItemGroup*   arrowGroup()           = 0;
    virtual QGraphicsItemGroup*   minorArrowGroup()      = 0;

    virtual void prepareColorScale(const qreal width, const qreal height) = 0;

    virtual void    connectSlots() = 0;
    virtual QString formatLabel(
        const QString&    formatSpec,
        const QByteArray& array,
        qreal             value,
        int               precision,
        const QString&    preStr,
        const QString&    postStr
    ) const = 0;

public slots:
    virtual void handleVisibleChanged(bool visible)                                      = 0;
    virtual void handleArrowVisibleChanged(bool visible)                                 = 0;
    virtual void handleGridVisibleChanged(bool visible)                                  = 0;
    virtual void handleLabelsVisibleChanged(bool visible)                                = 0;
    virtual void handleShadesVisibleChanged(bool visible)                                = 0;
    virtual void handleLabelsAngleChanged(int angle)                                     = 0;
    virtual void handleShadesBrushChanged(const QBrush& brush)                           = 0;
    virtual void handleShadesPenChanged(const QPen& pen)                                 = 0;
    virtual void handleArrowPenChanged(const QPen& pen)                                  = 0;
    virtual void handleGridPenChanged(const QPen& pen)                                   = 0;
    virtual void handleMinorArrowPenChanged(const QPen& pen)                             = 0;
    virtual void handleMinorGridPenChanged(const QPen& pen)                              = 0;
    virtual void handleMinorGridLineColorChanged(const QColor& color)                    = 0;
    virtual void handleGridLineColorChanged(const QColor& color)                         = 0;
    virtual void handleLabelsBrushChanged(const QBrush& brush)                           = 0;
    virtual void handleLabelsFontChanged(const QFont& font)                              = 0;
    virtual void handleTitleBrushChanged(const QBrush& brush)                            = 0;
    virtual void handleTitleFontChanged(const QFont& font)                               = 0;
    virtual void handleTitleTextChanged(const QString& title)                            = 0;
    virtual void handleTitleVisibleChanged(bool visible)                                 = 0;
    virtual void handleRangeChanged(qreal min, qreal max)                                = 0;
    virtual void handleReverseChanged(bool reverse)                                      = 0;
    virtual void handleMinorArrowVisibleChanged(bool visible)                            = 0;
    virtual void handleMinorGridVisibleChanged(bool visible)                             = 0;
    virtual void handleLabelsPositionChanged()                                           = 0;
    virtual void handleTruncateLabelsChanged()                                           = 0;
    virtual void handleColorScaleSizeChanged()                                           = 0;
    virtual void handleColorScaleGradientChanged()                                       = 0;
    virtual void valueLabelEdited(qreal oldValue, qreal newValue)                        = 0;
    virtual void dateTimeLabelEdited(const QDateTime& oldTime, const QDateTime& newTime) = 0;

signals:
    void clicked();
};
