#pragma once



#include <QGraphicsLayout>

#include "src/qtchartium/axis/ichartiumaxiselement.h"
#include "src/qtchartium/chartiumbackground.h"
#include "src/qtchartium/chartiumtitle.h"
#include "src/qtchartium/legend/ichartiumlegend.h"



class IChartiumLayout : public QGraphicsLayout
{
public:
    explicit IChartiumLayout(QGraphicsLayoutItem* parent = nullptr) :
        QGraphicsLayout(parent)
    {
    }
    ~IChartiumLayout() override = default;

    IChartiumLayout(const IChartiumLayout& another)            = delete;
    IChartiumLayout& operator=(const IChartiumLayout& another) = delete;

    virtual void     setMargins(const QMargins& margins) = 0;
    virtual QMargins margins() const                     = 0;

    virtual QRectF
    calculateBackgroundGeometry(const QRectF& geometry, IChartiumBackground* background, bool update = true) const    = 0;
    virtual QRectF calculateBackgroundMinimum(const QRectF& minimum) const                                            = 0;
    virtual QRectF calculateContentGeometry(const QRectF& geometry) const                                             = 0;
    virtual QRectF calculateContentMinimum(const QRectF& minimum) const                                               = 0;
    virtual QRectF calculateTitleGeometry(const QRectF& geometry, IChartiumTitle* title, bool update = true) const    = 0;
    virtual QRectF calculateTitleMinimum(const QRectF& minimum, IChartiumTitle* title) const                          = 0;
    virtual QRectF calculateLegendGeometry(const QRectF& geometry, IChartiumLegend* legend, bool update = true) const = 0;
    virtual QRectF calculateLegendMinimum(const QRectF& minimum, IChartiumLegend* legend) const                       = 0;

    virtual QRectF
    calculateAxisGeometry(const QRectF& geometry, const QList<IChartiumAxisElement*>& axes, bool update = true) const = 0;
    virtual QRectF calculateAxisMinimum(const QRectF& minimum, const QList<IChartiumAxisElement*>& axes) const        = 0;
};
