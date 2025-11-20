#pragma once



#include "src/qtchartium/ichartiumdataset.h"

#include "src/qtchartium/ichartiumchart.h"



class ChartiumDataSet : public IChartiumDataSet
{
    Q_OBJECT

public:
    explicit ChartiumDataSet(IChartiumChart* chart);
    ~ChartiumDataSet() override;

    ChartiumDataSet(const ChartiumDataSet& another)            = delete;
    ChartiumDataSet& operator=(const ChartiumDataSet& another) = delete;

    void                    addSeries(IChartiumSeries* series) override;
    void                    removeSeries(IChartiumSeries* series) override;
    QList<IChartiumSeries*> series() const override;

    void                  addAxis(IChartiumAxis* axis, Qt::Alignment alignment) override;
    void                  removeAxis(IChartiumAxis* axis) override;
    QList<IChartiumAxis*> axes() const override;

    bool attachAxis(IChartiumSeries* series, IChartiumAxis* axis) override;
    bool detachAxis(IChartiumSeries* series, IChartiumAxis* axis) override;

    void createDefaultAxes() override;

    void zoomInDomain(const QRectF& rect) override;
    void zoomOutDomain(const QRectF& rect) override;
    void zoomResetDomain() override;
    bool isZoomedDomain() override;
    void scrollDomain(qreal dx, qreal dy) override;

    QPointF mapToValue(const QPointF& position, IChartiumSeries* series) override;
    QPointF mapToPosition(const QPointF& value, IChartiumSeries* series) override;

    IChartiumDomain* createDomain(IChartiumDomain::DomainType type) override;
    IChartiumDomain* domainForSeries(IChartiumSeries* series) const override;

    void                        createAxes(IChartiumAxis::AxisTypes type, Qt::Orientation orientation) override;
    IChartiumAxis*              createAxis(IChartiumAxis::AxisType type, Qt::Orientation orientation) override;
    IChartiumDomain::DomainType selectDomain(const QList<IChartiumAxis*>& axes) override;
    void                        deleteAllAxes() override;
    void                        deleteAllSeries() override;
    void
    findMinMaxForSeries(const QList<IChartiumSeries*>& series, Qt::Orientations orientation, qreal& min, qreal& max) override;

public slots:
    void handleReverseChanged() override;

private:
    QList<IChartiumSeries*> mSeriesList;
    QList<IChartiumAxis*>   mAxisList;
    IChartiumChart*         mChart;
};
