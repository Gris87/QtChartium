#pragma once



#include "src/qtchartium/charts/ichartiumseries.h"

#include "src/qtchartium/ichartiumchart.h"
#include "src/qtchartium/ichartiumpresenter.h"



class ChartiumSeries : public IChartiumSeries
{
    Q_OBJECT

public:
    explicit ChartiumSeries(QObject* parent = nullptr);
    ~ChartiumSeries() override;

    ChartiumSeries(const ChartiumSeries& another)            = delete;
    ChartiumSeries& operator=(const ChartiumSeries& another) = delete;

    SeriesType type() const override;

    void    setName(const QString& name) override;
    QString name() const override;

    void setVisible(bool visible = true) override;
    bool isVisible() const override;

    qreal opacity() const override;
    void  setOpacity(qreal opacity) override;

    IChartiumChart* chart() const override;
    void            setChart(IChartiumChart* chart) override;

    bool                  attachAxis(IChartiumAxis* axis) override;
    bool                  detachAxis(IChartiumAxis* axis) override;
    QList<IChartiumAxis*> attachedAxes() override;

    void show() override;
    void hide() override;

    void initializeDomain() override;
    void initializeAxes() override;
    void initializeTheme(int index, IChartiumTheme* theme) override;
    void initializeGraphics(QGraphicsItem* parent) override;

    QList<IChartiumLegendMarker*> createLegendMarkers(IChartiumLegend* legend) override;

    IChartiumAxis::AxisType defaultAxisType(Qt::Orientation) const override;
    IChartiumAxis*          createDefaultAxis(Qt::Orientation) const override;

    IChartiumItem* chartItem() override;

    void             setDomain(IChartiumDomain* domain) override;
    IChartiumDomain* domain() override;

    void                setPresenter(IChartiumPresenter* presenter) override;
    IChartiumPresenter* presenter() const override;

    void appendAxis(IChartiumAxis* axis) override;
    void removeAxis(IChartiumAxis* axis) override;

protected:
    IChartiumChart*       mChart;
    IChartiumItem*        mItem;
    QList<IChartiumAxis*> mAxes;
    IChartiumDomain*      mDomain;
    IChartiumPresenter*   mPresenter;
    QString               mName;
    bool                  mVisible;
    qreal                 mOpacity;
};
