#pragma once



#include "src/qtchartium/axis/ichartiumaxiselement.h"



class ChartiumAxisElement : public IChartiumAxisElement
{
    Q_OBJECT

public:
    explicit ChartiumAxisElement(
        IChartiumAxis*       axis,
        IChartiumPresenter*  presenter,
        bool                 intervalAxis = false,
        QGraphicsItem*       item         = nullptr,
        QGraphicsLayoutItem* parent       = nullptr
    );
    ~ChartiumAxisElement() override;

    ChartiumAxisElement(const ChartiumAxisElement& another)            = delete;
    ChartiumAxisElement& operator=(const ChartiumAxisElement& another) = delete;

    QRectF gridGeometry() const override;

    void setGeometry(const QRectF& axis, const QRectF& grid) override;
    bool emptyAxis() const override;

    IChartiumAxis* axis() const override;

    void          setLayout(const QList<qreal>& layout) override;
    QList<qreal>& layout() override;

    void          setDynamicMinorTickLayout(const QList<qreal>& layout) override;
    QList<qreal>& dynamicMinorTicklayout() override;

    qreal labelPadding() const override;
    qreal titlePadding() const override;
    qreal colorScalePadding() const override;

    void        setLabels(const QStringList& labels) override;
    QStringList labels() const override;
    qreal       min() const override;
    qreal       max() const override;

    qreal tickInterval() const override;
    qreal tickAnchor() const override;

    QRectF axisGeometry() const override;
    void   setAxisGeometry(const QRectF& axisGeometry) override;

    void axisSelected() override;

    bool intervalAxis() const override;

    QStringList createValueLabels(
        qreal                        max,
        qreal                        min,
        int                          ticks,
        qreal                        tickInterval,
        qreal                        tickAnchor,
        IChartiumValueAxis::TickType tickType,
        const QString&               format
    ) const override;
    QStringList createLogValueLabels(qreal min, qreal max, qreal base, int ticks, const QString& format) const override;
    QStringList createDateTimeLabels(qreal max, qreal min, int ticks, const QString& format) const override;
    QStringList createColorLabels(qreal min, qreal max, int ticks) const override;

    bool labelsEditable() const override;
    void setLabelsEditable(bool labelsEditable) override;
    bool labelsVisible() const override;

    QList<qreal> calculateLayout() const override;
    void         updateLayout(const QList<qreal>& layout) override;

    QList<QGraphicsItem*> gridItems() override;
    QList<QGraphicsItem*> minorGridItems() override;
    QList<QGraphicsItem*> labelItems() override;
    QList<QGraphicsItem*> shadeItems() override;
    QList<QGraphicsItem*> arrowItems() override;
    QList<QGraphicsItem*> minorArrowItems() override;
    QGraphicsTextItem*    titleItem() const override;
    QGraphicsPixmapItem*  colorScaleItem() const override;
    QGraphicsItemGroup*   gridGroup() override;
    QGraphicsItemGroup*   minorGridGroup() override;
    QGraphicsItemGroup*   labelGroup() override;
    QGraphicsItemGroup*   shadeGroup() override;
    QGraphicsItemGroup*   arrowGroup() override;
    QGraphicsItemGroup*   minorArrowGroup() override;

    void prepareColorScale(const qreal width, const qreal height) override;

    void    connectSlots() override;
    QString formatLabel(
        const QString&    formatSpec,
        const QByteArray& array,
        qreal             value,
        int               precision,
        const QString&    preStr,
        const QString&    postStr
    ) const override;

public slots:
    void handleVisibleChanged(bool visible) override;
    void handleArrowVisibleChanged(bool visible) override;
    void handleGridVisibleChanged(bool visible) override;
    void handleLabelsVisibleChanged(bool visible) override;
    void handleShadesVisibleChanged(bool visible) override;
    void handleLabelsAngleChanged(int angle) override;
    void handleShadesBrushChanged(const QBrush& brush) override;
    void handleShadesPenChanged(const QPen& pen) override;
    void handleArrowPenChanged(const QPen& pen) override;
    void handleGridPenChanged(const QPen& pen) override;
    void handleMinorArrowPenChanged(const QPen& pen) override;
    void handleMinorGridPenChanged(const QPen& pen) override;
    void handleMinorGridLineColorChanged(const QColor& color) override;
    void handleGridLineColorChanged(const QColor& color) override;
    void handleLabelsBrushChanged(const QBrush& brush) override;
    void handleLabelsFontChanged(const QFont& font) override;
    void handleTitleBrushChanged(const QBrush& brush) override;
    void handleTitleFontChanged(const QFont& font) override;
    void handleTitleTextChanged(const QString& title) override;
    void handleTitleVisibleChanged(bool visible) override;
    void handleRangeChanged(qreal min, qreal max) override;
    void handleReverseChanged(bool reverse) override;
    void handleMinorArrowVisibleChanged(bool visible) override;
    void handleMinorGridVisibleChanged(bool visible) override;
    void handleLabelsPositionChanged() override;
    void handleTruncateLabelsChanged() override;
    void handleColorScaleSizeChanged() override;
    void handleColorScaleGradientChanged() override;
    void valueLabelEdited(qreal oldValue, qreal newValue) override;
    void dateTimeLabelEdited(const QDateTime& oldTime, const QDateTime& newTime) override;

protected:
    IChartiumAxis*                       mAxis;
    QList<qreal>                         mLayout;
    QList<qreal>                         mDynamicMinorTickLayout;
    QStringList                          mLabelsList;
    QRectF                               mAxisRect;
    QScopedPointer<QGraphicsItemGroup>   mGrid;
    QScopedPointer<QGraphicsItemGroup>   mArrow;
    QScopedPointer<QGraphicsItemGroup>   mMinorGrid;
    QScopedPointer<QGraphicsItemGroup>   mMinorArrow;
    QScopedPointer<QGraphicsItemGroup>   mShades;
    QScopedPointer<QGraphicsItemGroup>   mLabels;
    QScopedPointer<QGraphicsTextItem>    mTitle;
    std::unique_ptr<QGraphicsPixmapItem> mColorScale;
    bool                                 mIntervalAxis;
    bool                                 mLabelsEditable;
};
