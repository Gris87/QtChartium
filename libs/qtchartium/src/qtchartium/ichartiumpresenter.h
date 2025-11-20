#pragma once



#include <QObject>

#include "src/qtchartium/axis/ichartiumaxis.h"
#include "src/qtchartium/axis/ichartiumaxiselement.h"
#include "src/qtchartium/ichartiumbackground.h"
#include "src/qtchartium/ichartiumchart.h"
#include "src/qtchartium/ichartiumitem.h"
#include "src/qtchartium/ichartiumseries.h"
#include "src/qtchartium/ichartiumtitle.h"
#include "src/qtchartium/layout/ichartiumlayout.h"



class IChartiumPresenter : public QObject
{
    Q_OBJECT

public:
    enum ZValues : qint8
    {
        BackgroundZValue = -1,
        PlotAreaZValue,
        ShadesZValue,
        GridZValue,
        AxisZValue,
        SeriesZValue,
        LineChartZValue         = SeriesZValue,
        SplineChartZValue       = SeriesZValue,
        BarSeriesZValue         = SeriesZValue,
        ScatterSeriesZValue     = SeriesZValue,
        PieSeriesZValue         = SeriesZValue,
        BoxPlotSeriesZValue     = SeriesZValue,
        CandlestickSeriesZValue = SeriesZValue,
        LegendZValue,
        TopMostZValue
    };

    enum State : quint8
    {
        ShowState,
        ScrollUpState,
        ScrollDownState,
        ScrollLeftState,
        ScrollRightState,
        ZoomInState,
        ZoomOutState
    };

    explicit IChartiumPresenter(QObject* parent = nullptr) :
        QObject(parent)
    {
    }
    ~IChartiumPresenter() override = default;

    IChartiumPresenter(const IChartiumPresenter& another)            = delete;
    IChartiumPresenter& operator=(const IChartiumPresenter& another) = delete;

    virtual bool   isFixedGeometry() const              = 0;
    virtual void   setFixedGeometry(const QRectF& rect) = 0;
    virtual void   setGeometry(QRectF rect)             = 0;
    virtual QRectF geometry() const                     = 0;
    virtual void   updateGeometry(const QRectF& rect)   = 0;

    virtual QGraphicsItem*               rootItem()          = 0;
    virtual IChartiumBackground*         backgroundElement() = 0;
    virtual QAbstractGraphicsShapeItem*  plotAreaElement()   = 0;
    virtual IChartiumTitle*              titleElement()      = 0;
    virtual QList<IChartiumAxisElement*> axisItems() const   = 0;
    virtual QList<IChartiumItem*>        chartItems() const  = 0;

    virtual IChartiumLegend* legend() = 0;

    virtual void   setBackgroundBrush(const QBrush& brush) = 0;
    virtual QBrush backgroundBrush() const                 = 0;

    virtual void setBackgroundPen(const QPen& pen) = 0;
    virtual QPen backgroundPen() const             = 0;

    virtual void  setBackgroundRoundness(qreal diameter) = 0;
    virtual qreal backgroundRoundness() const            = 0;

    virtual void   setPlotAreaBackgroundBrush(const QBrush& brush) = 0;
    virtual QBrush plotAreaBackgroundBrush() const                 = 0;

    virtual void setPlotAreaBackgroundPen(const QPen& pen) = 0;
    virtual QPen plotAreaBackgroundPen() const             = 0;

    virtual void    setTitle(const QString& title) = 0;
    virtual QString title() const                  = 0;

    virtual void  setTitleFont(const QFont& font) = 0;
    virtual QFont titleFont() const               = 0;

    virtual void   setTitleBrush(const QBrush& brush) = 0;
    virtual QBrush titleBrush() const                 = 0;

    virtual void setBackgroundVisible(bool visible) = 0;
    virtual bool isBackgroundVisible() const        = 0;

    virtual void setPlotAreaBackgroundVisible(bool visible) = 0;
    virtual bool isPlotAreaBackgroundVisible() const        = 0;

    virtual void setBackgroundDropShadowEnabled(bool enabled) = 0;
    virtual bool isBackgroundDropShadowEnabled() const        = 0;

    virtual void           setLocalizeNumbers(bool localize) = 0;
    virtual bool           localizeNumbers() const           = 0;
    virtual void           setLocale(const QLocale& locale)  = 0;
    virtual const QLocale& locale() const                    = 0;

    virtual void setVisible(bool visible) = 0;

    virtual void             setState(State state, QPointF point) = 0;
    virtual State            state() const                        = 0;
    virtual QPointF          statePoint() const                   = 0;
    virtual IChartiumLayout* layout()                             = 0;

    virtual IChartiumChart::ChartType chartType() const = 0;
    virtual IChartiumChart*           chart()           = 0;

    virtual QRectF textBoundingRect(const QFont& font, const QString& text, qreal angle = 0.0) = 0;
    virtual QString
    truncatedText(const QFont& font, const QString& text, qreal angle, qreal maxWidth, qreal maxHeight, QRectF& boundingRect) = 0;
    virtual qreal textMargin()                                                                                                = 0;

    virtual QString numberToString(double value, char f = 'g', int prec = 6) = 0;
    virtual QString numberToString(int value)                                = 0;

    virtual void createBackgroundItem()         = 0;
    virtual void createPlotAreaBackgroundItem() = 0;
    virtual void createTitleItem()              = 0;

public slots:
    virtual void handleSeriesAdded(IChartiumSeries* series)   = 0;
    virtual void handleSeriesRemoved(IChartiumSeries* series) = 0;
    virtual void handleAxisAdded(IChartiumAxis* axis)         = 0;
    virtual void handleAxisRemoved(IChartiumAxis* axis)       = 0;

signals:
    void plotAreaChanged(const QRectF& plotArea);
};
