#pragma once



#include "src/qtchartium/ichartiumchart.h"

#include "src/qtchartium/ichartiumdataset.h"
#include "src/qtchartium/ichartiumpresenter.h"



class ChartiumChart : public IChartiumChart
{
    Q_OBJECT

public:
    explicit ChartiumChart(QGraphicsItem* parent = nullptr, Qt::WindowFlags wFlags = Qt::WindowFlags());
    ~ChartiumChart() override;

    ChartiumChart(const ChartiumChart& another)            = delete;
    ChartiumChart& operator=(const ChartiumChart& another) = delete;

    void                    addSeries(IChartiumSeries* series) override;
    void                    removeSeries(IChartiumSeries* series) override;
    void                    removeAllSeries() override;
    QList<IChartiumSeries*> series() const override;

    void addAxis(IChartiumAxis* axis, Qt::Alignment alignment) override;
    void removeAxis(IChartiumAxis* axis) override;
    QList<IChartiumAxis*>
    axes(Qt::Orientations orientation = Qt::Horizontal | Qt::Vertical, IChartiumSeries* series = nullptr) const override;

    void createDefaultAxes() override;

    void    setTitle(const QString& title) override;
    QString title() const override;
    void    setTitleFont(const QFont& font) override;
    QFont   titleFont() const override;
    void    setTitleBrush(const QBrush& brush) override;
    QBrush  titleBrush() const override;

    void   setBackgroundBrush(const QBrush& brush) override;
    QBrush backgroundBrush() const override;
    void   setBackgroundPen(const QPen& pen) override;
    QPen   backgroundPen() const override;
    void   setBackgroundVisible(bool visible = true) override;
    bool   isBackgroundVisible() const override;

    void  setDropShadowEnabled(bool enabled = true) override;
    bool  isDropShadowEnabled() const override;
    void  setBackgroundRoundness(qreal diameter) override;
    qreal backgroundRoundness() const override;

    void zoomIn() override;
    void zoomOut() override;

    void zoomIn(qreal factor) override;
    void zoomOut(qreal factor) override;
    void zoomIn(const QRectF& rect) override;
    void zoom(qreal factor) override;
    void zoomReset() override;
    bool isZoomed() override;

    void scroll(qreal dx, qreal dy) override;

    IChartiumLegend* legend() const override;

    void     setMargins(const QMargins& margins) override;
    QMargins margins() const override;

    QRectF  plotArea() const override;
    void    setPlotArea(const QRectF& rect) override;
    void    setPlotAreaBackgroundBrush(const QBrush& brush) override;
    QBrush  plotAreaBackgroundBrush() const override;
    void    setPlotAreaBackgroundPen(const QPen& pen) override;
    QPen    plotAreaBackgroundPen() const override;
    void    setPlotAreaBackgroundVisible(bool visible = true) override;
    bool    isPlotAreaBackgroundVisible() const override;
    void    setLocalizeNumbers(bool localize) override;
    bool    localizeNumbers() const override;
    void    setLocale(const QLocale& locale) override;
    QLocale locale() const override;

    QPointF mapToValue(const QPointF& position, IChartiumSeries* series = nullptr) override;
    QPointF mapToPosition(const QPointF& value, IChartiumSeries* series = nullptr) override;

    ChartType chartType() const override;

    IChartiumDataSet* dataset() const override;

private:
    IChartiumLegend*    mLegend;
    IChartiumDataSet*   mDataset;
    IChartiumPresenter* mPresenter;
    ChartType           mChartType;
};
