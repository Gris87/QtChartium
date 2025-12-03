#pragma once



#include "src/qtchartium/ichartiumpresenter.h"



class ChartiumPresenter : public IChartiumPresenter
{
public:
    explicit ChartiumPresenter(IChartiumChart* chart);
    ~ChartiumPresenter() override;

    ChartiumPresenter(const ChartiumPresenter& another)            = delete;
    ChartiumPresenter& operator=(const ChartiumPresenter& another) = delete;

    bool   isFixedGeometry() const override;
    void   setFixedGeometry(const QRectF& rect) override;
    void   setGeometry(QRectF rect) override;
    QRectF geometry() const override;
    void   updateGeometry(const QRectF& rect) override;

    QGraphicsItem*               rootItem() override;
    IChartiumBackground*         backgroundElement() override;
    QAbstractGraphicsShapeItem*  plotAreaElement() override;
    IChartiumTitle*              titleElement() override;
    QList<IChartiumAxisElement*> axisItems() const override;
    QList<IChartiumItem*>        chartItems() const override;

    IChartiumLegend* legend() override;

    void   setBackgroundBrush(const QBrush& brush) override;
    QBrush backgroundBrush() const override;

    void setBackgroundPen(const QPen& pen) override;
    QPen backgroundPen() const override;

    void  setBackgroundRoundness(qreal diameter) override;
    qreal backgroundRoundness() const override;

    void   setPlotAreaBackgroundBrush(const QBrush& brush) override;
    QBrush plotAreaBackgroundBrush() const override;

    void setPlotAreaBackgroundPen(const QPen& pen) override;
    QPen plotAreaBackgroundPen() const override;

    void    setTitle(const QString& title) override;
    QString title() const override;

    void  setTitleFont(const QFont& font) override;
    QFont titleFont() const override;

    void   setTitleBrush(const QBrush& brush) override;
    QBrush titleBrush() const override;

    void setBackgroundVisible(bool visible) override;
    bool isBackgroundVisible() const override;

    void setPlotAreaBackgroundVisible(bool visible) override;
    bool isPlotAreaBackgroundVisible() const override;

    void setBackgroundDropShadowEnabled(bool enabled) override;
    bool isBackgroundDropShadowEnabled() const override;

    void           setLocalizeNumbers(bool localize) override;
    bool           localizeNumbers() const override;
    void           setLocale(const QLocale& locale) override;
    const QLocale& locale() const override;

    void setVisible(bool visible) override;

    void             setState(State state, QPointF point) override;
    State            state() const override;
    QPointF          statePoint() const override;
    IChartiumLayout* layout() override;

    IChartiumChart::ChartType chartType() const override;
    IChartiumChart*           chart() override;

    QRectF  textBoundingRect(const QFont& font, const QString& text, qreal angle = 0.0) override;
    QString truncatedText(
        const QFont& font, const QString& text, qreal angle, qreal maxWidth, qreal maxHeight, QRectF& boundingRect
    ) override;
    qreal textMargin() override;

    QString numberToString(double value, char f = 'g', int prec = 6) override;
    QString numberToString(int value) override;

    void createBackgroundItem() override;
    void createPlotAreaBackgroundItem() override;
    void createTitleItem() override;

public slots:
    void handleSeriesAdded(IChartiumSeries* series) override;
    void handleSeriesRemoved(IChartiumSeries* series) override;
    void handleAxisAdded(IChartiumAxis* axis) override;
    void handleAxisRemoved(IChartiumAxis* axis) override;

protected:
    IChartiumChart*              mChart;
    QList<IChartiumItem*>        mChartItems;
    QList<IChartiumAxisElement*> mAxisItems;
    QList<IChartiumSeries*>      mSeries;
    QList<IChartiumAxis*>        mAxes;
    State                        mState;
    QPointF                      mStatePoint;
    IChartiumLayout*             mLayout;
    IChartiumBackground*         mBackground;
    QAbstractGraphicsShapeItem*  mPlotAreaBackground;
    IChartiumTitle*              mTitle;
    QRectF                       mRect;
    bool                         mLocalizeNumbers;
    QLocale                      mLocale;
    QRectF                       mFixedRect;
};
