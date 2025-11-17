#pragma once



#include "src/qtchartium/ichartiumseries.h"



class ChartiumSeries : public IChartiumSeries
{
public:
    explicit ChartiumSeries();
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
    void initializeGraphics(QGraphicsItem* parent) override;

    IChartiumAxis::AxisType defaultAxisType(Qt::Orientation) const override;
    IChartiumAxis*          createDefaultAxis(Qt::Orientation) const override;

    void             setDomain(IChartiumDomain* domain) override;
    IChartiumDomain* domain() override;

private:
    QString mName;
    bool    mVisible;
    qreal   mOpacity;
};
