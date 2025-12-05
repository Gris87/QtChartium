#pragma once



#include <QObject>

#include "src/qtchartium/legend/ichartiumlegend.h"



class IChartiumSeries;
class IChartiumLegendMarkerItem;



class IChartiumLegendMarker : public QObject
{
    Q_OBJECT

public:
    enum LegendMarkerType
    {
        LegendMarkerTypeArea,
        LegendMarkerTypeBar,
        LegendMarkerTypePie,
        LegendMarkerTypeXY,
        LegendMarkerTypeBoxPlot,
        LegendMarkerTypeCandlestick
    };

    explicit IChartiumLegendMarker(QObject* parent = nullptr) :
        QObject(parent)
    {
    }
    ~IChartiumLegendMarker() override = default;

    IChartiumLegendMarker(const IChartiumLegendMarker& another)            = delete;
    IChartiumLegendMarker& operator=(const IChartiumLegendMarker& another) = delete;

    virtual LegendMarkerType type() = 0;

    virtual QString label() const                  = 0;
    virtual void    setLabel(const QString& label) = 0;

    virtual QBrush labelBrush() const                 = 0;
    virtual void   setLabelBrush(const QBrush& brush) = 0;

    virtual QFont font() const               = 0;
    virtual void  setFont(const QFont& font) = 0;

    virtual QPen pen() const             = 0;
    virtual void setPen(const QPen& pen) = 0;

    virtual QBrush brush() const                 = 0;
    virtual void   setBrush(const QBrush& brush) = 0;

    virtual bool isVisible() const        = 0;
    virtual void setVisible(bool visible) = 0;

    virtual IChartiumLegend::MarkerShape shape() const                                = 0;
    virtual void                         setShape(IChartiumLegend::MarkerShape shape) = 0;

    virtual IChartiumSeries* series() = 0;

    virtual IChartiumLegendMarkerItem* item() const = 0;

    virtual QObject* relatedObject() = 0;

    virtual void invalidateLegend()   = 0;
    virtual void invalidateAllItems() = 0;

public slots:
    virtual void updated()           = 0;
    virtual void handleShapeChange() = 0;

signals:
    void clicked();
    void hovered(bool status);
    void labelChanged();
    void labelBrushChanged();
    void fontChanged();
    void penChanged();
    void brushChanged();
    void visibleChanged();
    void shapeChanged();
};
