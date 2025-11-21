#pragma once



#include <QObject>

#include <QFont>
#include <QGraphicsItem>
#include <QPen>

#include "src/qtchartium/axis/ichartiumaxiselement.h"
#include "src/qtchartium/domain/ichartiumdomain.h"



class IChartiumChart;
class IChartiumSeries;



class IChartiumAxis : public QObject
{
    Q_OBJECT

public:
    enum AxisType : quint8
    {
        AxisTypeNoAxis      = 0x0,
        AxisTypeValue       = 0x1,
        AxisTypeBarCategory = 0x2,
        AxisTypeCategory    = 0x4,
        AxisTypeDateTime    = 0x8,
        AxisTypeLogValue    = 0x10,
        AxisTypeColor       = 0x20
    };
    typedef quint8 AxisTypes;

    explicit IChartiumAxis(QObject* parent = nullptr) :
        QObject(parent)
    {
    }
    ~IChartiumAxis() override = default;

    IChartiumAxis(const IChartiumAxis& another)            = delete;
    IChartiumAxis& operator=(const IChartiumAxis& another) = delete;

    virtual AxisType type() const = 0;

    virtual bool isVisible() const               = 0;
    virtual void setVisible(bool visible = true) = 0;
    virtual void show()                          = 0;
    virtual void hide()                          = 0;

    virtual IChartiumChart* chart() const                   = 0;
    virtual void            setChart(IChartiumChart* chart) = 0;

    virtual bool   isLineVisible() const               = 0;
    virtual void   setLineVisible(bool visible = true) = 0;
    virtual void   setLinePen(const QPen& pen)         = 0;
    virtual QPen   linePen() const                     = 0;
    virtual void   setLinePenColor(QColor color)       = 0;
    virtual QColor linePenColor() const                = 0;

    virtual bool   isGridLineVisible() const                    = 0;
    virtual void   setGridLineVisible(bool visible = true)      = 0;
    virtual void   setGridLinePen(const QPen& pen)              = 0;
    virtual QPen   gridLinePen() const                          = 0;
    virtual bool   isMinorGridLineVisible() const               = 0;
    virtual void   setMinorGridLineVisible(bool visible = true) = 0;
    virtual void   setMinorGridLinePen(const QPen& pen)         = 0;
    virtual QPen   minorGridLinePen() const                     = 0;
    virtual void   setGridLineColor(const QColor& color)        = 0;
    virtual QColor gridLineColor()                              = 0;
    virtual void   setMinorGridLineColor(const QColor& color)   = 0;
    virtual QColor minorGridLineColor()                         = 0;

    virtual bool   labelsVisible() const                 = 0;
    virtual void   setLabelsVisible(bool visible = true) = 0;
    virtual void   setLabelsBrush(const QBrush& brush)   = 0;
    virtual QBrush labelsBrush() const                   = 0;
    virtual void   setLabelsFont(const QFont& font)      = 0;
    virtual QFont  labelsFont() const                    = 0;
    virtual void   setLabelsAngle(int angle)             = 0;
    virtual int    labelsAngle() const                   = 0;
    virtual void   setLabelsColor(QColor color)          = 0;
    virtual QColor labelsColor() const                   = 0;

    virtual bool    isTitleVisible() const               = 0;
    virtual void    setTitleVisible(bool visible = true) = 0;
    virtual void    setTitleBrush(const QBrush& brush)   = 0;
    virtual QBrush  titleBrush() const                   = 0;
    virtual void    setTitleFont(const QFont& font)      = 0;
    virtual QFont   titleFont() const                    = 0;
    virtual void    setTitleText(const QString& title)   = 0;
    virtual QString titleText() const                    = 0;

    virtual bool   shadesVisible() const                 = 0;
    virtual void   setShadesVisible(bool visible = true) = 0;
    virtual void   setShadesPen(const QPen& pen)         = 0;
    virtual QPen   shadesPen() const                     = 0;
    virtual void   setShadesBrush(const QBrush& brush)   = 0;
    virtual QBrush shadesBrush() const                   = 0;
    virtual void   setShadesColor(QColor color)          = 0;
    virtual QColor shadesColor() const                   = 0;
    virtual void   setShadesBorderColor(QColor color)    = 0;
    virtual QColor shadesBorderColor() const             = 0;

    virtual Qt::Orientation orientation() const = 0;
    virtual Qt::Alignment   alignment() const                     = 0;
    virtual void            setAlignment(Qt::Alignment alignment) = 0;

    virtual void setMin(const QVariant& min)                        = 0;
    virtual void setMax(const QVariant& max)                        = 0;
    virtual void setRange(const QVariant& min, const QVariant& max) = 0;

    virtual void  setRange(qreal min, qreal max) = 0;
    virtual qreal min()                          = 0;
    virtual qreal max()                          = 0;

    virtual void setReverse(bool reverse = true) = 0;
    virtual bool isReverse() const               = 0;

    virtual void setLabelsEditable(bool editable = true) = 0;
    virtual bool labelsEditable() const                  = 0;

    virtual bool labelsTruncated() const = 0;

    virtual void setTruncateLabels(bool truncateLabels = true) = 0;
    virtual bool truncateLabels() const                        = 0;

    virtual void initializeDomain(IChartiumDomain* domain) = 0;
    virtual void initializeGraphics(QGraphicsItem* parent) = 0;

    virtual IChartiumAxisElement* axisItem() = 0;

    virtual QList<IChartiumSeries*> getSeries() const                     = 0;
    virtual void                    appendSeries(IChartiumSeries* series) = 0;
    virtual void                    removeSeries(IChartiumSeries* series) = 0;

public slots:
    virtual void handleRangeChanged(qreal min, qreal max) = 0;

signals:
    void visibleChanged(bool visible);
    void linePenChanged(const QPen& pen);
    void lineVisibleChanged(bool visible);
    void labelsVisibleChanged(bool visible);
    void labelsBrushChanged(const QBrush& brush);
    void labelsFontChanged(const QFont& pen);
    void labelsAngleChanged(int angle);
    void gridLinePenChanged(const QPen& pen);
    void gridVisibleChanged(bool visible);
    void minorGridVisibleChanged(bool visible);
    void minorGridLinePenChanged(const QPen& pen);
    void gridLineColorChanged(const QColor& color);
    void minorGridLineColorChanged(const QColor& color);
    void colorChanged(QColor color);
    void labelsColorChanged(QColor color);
    void titleTextChanged(const QString& title);
    void titleBrushChanged(const QBrush& brush);
    void titleVisibleChanged(bool visible);
    void titleFontChanged(const QFont& font);
    void shadesVisibleChanged(bool visible);
    void shadesColorChanged(QColor color);
    void shadesBorderColorChanged(QColor color);
    void shadesPenChanged(const QPen& pen);
    void shadesBrushChanged(const QBrush& brush);
    void reverseChanged(bool reverse);
    void labelsEditableChanged(bool editable);
    void labelsTruncatedChanged(bool labelsTruncated);
    void truncateLabelsChanged(bool truncateLabels);
    void rangeChanged(qreal min, qreal max);
};
