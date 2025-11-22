#pragma once



#include <QObject>

#include "src/qtchartium/axis/ichartiumaxis.h"
#include "src/qtchartium/domain/ichartiumdomain.h"
#include "src/qtchartium/ichartiumseries.h"



class IChartiumDataSet : public QObject
{
    Q_OBJECT

public:
    explicit IChartiumDataSet(QObject* parent = nullptr) :
        QObject(parent)
    {
    }
    ~IChartiumDataSet() override = default;

    IChartiumDataSet(const IChartiumDataSet& another)            = delete;
    IChartiumDataSet& operator=(const IChartiumDataSet& another) = delete;

    virtual void                    addSeries(IChartiumSeries* series)    = 0;
    virtual void                    removeSeries(IChartiumSeries* series) = 0;
    virtual QList<IChartiumSeries*> series() const                        = 0;

    virtual void                  addAxis(IChartiumAxis* axis, Qt::Alignment alignment) = 0;
    virtual void                  removeAxis(IChartiumAxis* axis)                       = 0;
    virtual QList<IChartiumAxis*> axes() const                                          = 0;

    virtual bool attachAxis(IChartiumSeries* series, IChartiumAxis* axis) = 0;
    virtual bool detachAxis(IChartiumSeries* series, IChartiumAxis* axis) = 0;

    virtual void createDefaultAxes() = 0;

    virtual void zoomInDomain(const QRectF& rect)  = 0;
    virtual void zoomOutDomain(const QRectF& rect) = 0;
    virtual void zoomResetDomain()                 = 0;
    virtual bool isZoomedDomain()                  = 0;
    virtual void scrollDomain(qreal dx, qreal dy)  = 0;

    virtual QPointF mapToValue(const QPointF& position, IChartiumSeries* series = 0) = 0;
    virtual QPointF mapToPosition(const QPointF& value, IChartiumSeries* series = 0) = 0;

    virtual IChartiumDomain* createDomain(IChartiumDomain::DomainType type) = 0;
    virtual IChartiumDomain* domainForSeries(IChartiumSeries* series) const = 0;

    virtual void                        createAxes(IChartiumAxis::AxisTypes type, Qt::Orientation orientation) = 0;
    virtual IChartiumDomain::DomainType selectDomain(const QList<IChartiumAxis*>& axes)                        = 0;
    virtual void                        deleteAllAxes()                                                        = 0;
    virtual void                        deleteAllSeries()                                                      = 0;
    virtual void
    findMinMaxForSeries(const QList<IChartiumSeries*>& series, Qt::Orientations orientation, qreal& min, qreal& max) = 0;

signals:
    void axisAdded(IChartiumAxis* axis);
    void axisRemoved(IChartiumAxis* axis);
    void seriesAdded(IChartiumSeries* series);
    void seriesRemoved(IChartiumSeries* series);
};
