#pragma once



#include "src/qtchartium/axis/ichartiumaxis.h"



class ChartiumAxis : public IChartiumAxis
{
    Q_OBJECT

public:
    explicit ChartiumAxis(QObject* parent = nullptr);
    ~ChartiumAxis() override;

    ChartiumAxis(const ChartiumAxis& another)            = delete;
    ChartiumAxis& operator=(const ChartiumAxis& another) = delete;

    AxisType type() const override;

    bool isVisible() const override;
    void setVisible(bool visible = true) override;
    void show() override;
    void hide() override;

    IChartiumChart* chart() const override;
    void            setChart(IChartiumChart* chart) override;

    bool   isLineVisible() const override;
    void   setLineVisible(bool visible = true) override;
    void   setLinePen(const QPen& pen) override;
    QPen   linePen() const override;
    void   setLinePenColor(QColor color) override;
    QColor linePenColor() const override;

    bool   isGridLineVisible() const override;
    void   setGridLineVisible(bool visible = true) override;
    void   setGridLinePen(const QPen& pen) override;
    QPen   gridLinePen() const override;
    bool   isMinorGridLineVisible() const override;
    void   setMinorGridLineVisible(bool visible = true) override;
    void   setMinorGridLinePen(const QPen& pen) override;
    QPen   minorGridLinePen() const override;
    void   setGridLineColor(const QColor& color) override;
    QColor gridLineColor() override;
    void   setMinorGridLineColor(const QColor& color) override;
    QColor minorGridLineColor() override;

    bool   labelsVisible() const override;
    void   setLabelsVisible(bool visible = true) override;
    void   setLabelsBrush(const QBrush& brush) override;
    QBrush labelsBrush() const override;
    void   setLabelsFont(const QFont& font) override;
    QFont  labelsFont() const override;
    void   setLabelsAngle(int angle) override;
    int    labelsAngle() const override;
    void   setLabelsColor(QColor color) override;
    QColor labelsColor() const override;

    bool    isTitleVisible() const override;
    void    setTitleVisible(bool visible = true) override;
    void    setTitleBrush(const QBrush& brush) override;
    QBrush  titleBrush() const override;
    void    setTitleFont(const QFont& font) override;
    QFont   titleFont() const override;
    void    setTitleText(const QString& title) override;
    QString titleText() const override;

    bool   shadesVisible() const override;
    void   setShadesVisible(bool visible = true) override;
    void   setShadesPen(const QPen& pen) override;
    QPen   shadesPen() const override;
    void   setShadesBrush(const QBrush& brush) override;
    QBrush shadesBrush() const override;
    void   setShadesColor(QColor color) override;
    QColor shadesColor() const override;
    void   setShadesBorderColor(QColor color) override;
    QColor shadesBorderColor() const override;

    Qt::Orientation orientation() const override;
    Qt::Alignment   alignment() const override;
    void            setAlignment(Qt::Alignment alignment) override;

    void setMin(const QVariant& min) override;
    void setMax(const QVariant& max) override;
    void setRange(const QVariant& min, const QVariant& max) override;

    void  setRange(qreal min, qreal max) override;
    qreal minReal() override;
    qreal maxReal() override;

    void setReverse(bool reverse = true) override;
    bool isReverse() const override;

    void setLabelsEditable(bool editable = true) override;
    bool labelsEditable() const override;

    void setLabelsTruncated(bool labelsTruncated) override;
    bool labelsTruncated() const override;

    void setTruncateLabels(bool truncateLabels = true) override;
    bool truncateLabels() const override;

    void initializeDomain(IChartiumDomain* domain) override;
    void initializeGraphics(QGraphicsItem* parent) override;
    void initializeTheme(IChartiumTheme* theme) override;

    IChartiumAxisElement* axisItem() override;

    QList<IChartiumSeries*> getSeries() const override;
    void                    appendSeries(IChartiumSeries* series) override;
    void                    removeSeries(IChartiumSeries* series) override;

public slots:
    void handleRangeRealChanged(qreal min, qreal max) override;

protected:
    IChartiumChart*         mChart;
    IChartiumAxisElement*   mItem;
    QList<IChartiumSeries*> mSeries;
    Qt::Alignment           mAlignment;
    Qt::Orientation         mOrientation;
    bool                    mVisible;
    bool                    mArrowVisible;
    QPen                    mAxisPen;
    QBrush                  mAxisBrush;
    bool                    mGridLineVisible;
    QPen                    mGridLinePen;
    bool                    mMinorGridLineVisible;
    QPen                    mMinorGridLinePen;
    bool                    mLabelsVisible;
    bool                    mLabelsEditable;
    QBrush                  mLabelsBrush;
    QFont                   mLabelsFont;
    int                     mLabelsAngle;
    bool                    mLabelsTruncated;
    bool                    mTruncateLabels;
    bool                    mTitleVisible;
    QBrush                  mTitleBrush;
    QFont                   mTitleFont;
    QString                 mTitle;
    bool                    mShadesVisible;
    QPen                    mShadesPen;
    QBrush                  mShadesBrush;
    qreal                   mShadesOpacity;
    bool                    mDirty;
    bool                    mReverse;
};
