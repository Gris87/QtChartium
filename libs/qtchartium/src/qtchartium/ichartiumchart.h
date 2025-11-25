#pragma once



#include <QGraphicsWidget>

#include <QBrush>
#include <QPen>

#include "src/qtchartium/axis/ichartiumaxis.h"
#include "src/qtchartium/ichartiumseries.h"
#include "src/qtchartium/legend/ichartiumlegend.h"



class IChartiumChart : public QGraphicsWidget
{
    Q_OBJECT

public:
    enum ChartType : quint8
    {
        ChartTypeUndefined,
        ChartTypeCartesian,
        ChartTypePolar
    };

    explicit IChartiumChart(QGraphicsItem* parent = nullptr, Qt::WindowFlags wFlags = Qt::WindowFlags()) :
        QGraphicsWidget(parent, wFlags)
    {
    }
    ~IChartiumChart() override = default;

    IChartiumChart(const IChartiumChart& another)            = delete;
    IChartiumChart& operator=(const IChartiumChart& another) = delete;

    virtual void                    addSeries(IChartiumSeries* series)    = 0;
    virtual void                    removeSeries(IChartiumSeries* series) = 0;
    virtual void                    removeAllSeries()                     = 0;
    virtual QList<IChartiumSeries*> series() const                        = 0;

    virtual void addAxis(IChartiumAxis* axis, Qt::Alignment alignment) = 0;
    virtual void removeAxis(IChartiumAxis* axis)                       = 0;
    virtual QList<IChartiumAxis*>
    axes(Qt::Orientations orientation = Qt::Horizontal | Qt::Vertical, IChartiumSeries* series = nullptr) const = 0;

    virtual void createDefaultAxes() = 0;

    virtual void    setTitle(const QString& title)     = 0;
    virtual QString title() const                      = 0;
    virtual void    setTitleFont(const QFont& font)    = 0;
    virtual QFont   titleFont() const                  = 0;
    virtual void    setTitleBrush(const QBrush& brush) = 0;
    virtual QBrush  titleBrush() const                 = 0;

    virtual void   setBackgroundBrush(const QBrush& brush)   = 0;
    virtual QBrush backgroundBrush() const                   = 0;
    virtual void   setBackgroundPen(const QPen& pen)         = 0;
    virtual QPen   backgroundPen() const                     = 0;
    virtual void   setBackgroundVisible(bool visible = true) = 0;
    virtual bool   isBackgroundVisible() const               = 0;

    virtual void  setDropShadowEnabled(bool enabled = true) = 0;
    virtual bool  isDropShadowEnabled() const               = 0;
    virtual void  setBackgroundRoundness(qreal diameter)    = 0;
    virtual qreal backgroundRoundness() const               = 0;

    virtual void zoomIn()  = 0;
    virtual void zoomOut() = 0;

    virtual void zoomIn(qreal factor)       = 0;
    virtual void zoomOut(qreal factor)      = 0;
    virtual void zoomIn(const QRectF& rect) = 0;
    virtual void zoom(qreal factor)         = 0;
    virtual void zoomReset()                = 0;
    virtual bool isZoomed()                 = 0;

    virtual void scroll(qreal dx, qreal dy) = 0;

    virtual IChartiumLegend* legend() const = 0;

    virtual void     setMargins(const QMargins& margins) = 0;
    virtual QMargins margins() const                     = 0;

    virtual QRectF  plotArea() const                                  = 0;
    virtual void    setPlotArea(const QRectF& rect)                   = 0;
    virtual void    setPlotAreaBackgroundBrush(const QBrush& brush)   = 0;
    virtual QBrush  plotAreaBackgroundBrush() const                   = 0;
    virtual void    setPlotAreaBackgroundPen(const QPen& pen)         = 0;
    virtual QPen    plotAreaBackgroundPen() const                     = 0;
    virtual void    setPlotAreaBackgroundVisible(bool visible = true) = 0;
    virtual bool    isPlotAreaBackgroundVisible() const               = 0;
    virtual void    setLocalizeNumbers(bool localize)                 = 0;
    virtual bool    localizeNumbers() const                           = 0;
    virtual void    setLocale(const QLocale& locale)                  = 0;
    virtual QLocale locale() const                                    = 0;

    virtual QPointF mapToValue(const QPointF& position, IChartiumSeries* series = nullptr) = 0;
    virtual QPointF mapToPosition(const QPointF& value, IChartiumSeries* series = nullptr) = 0;

    virtual ChartType chartType() const = 0;

    virtual IChartiumDataSet* dataset() const = 0;

signals:
    void plotAreaChanged(const QRectF& plotArea);
};
