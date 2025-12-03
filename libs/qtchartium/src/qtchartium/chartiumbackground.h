#pragma once



#include "src/qtchartium/ichartiumbackground.h"

#include <QGraphicsDropShadowEffect>
#include <QPainter>



class ChartiumBackground : public IChartiumBackground
{
public:
    explicit ChartiumBackground(QGraphicsItem* parent = nullptr);
    ~ChartiumBackground() override;

    ChartiumBackground(const ChartiumBackground& another)            = delete;
    ChartiumBackground& operator=(const ChartiumBackground& another) = delete;

    void  setDiameter(qreal diameter) override;
    qreal diameter() const override;

    void setDropShadowEnabled(bool enabled) override;
    bool isDropShadowEnabled() const override;

protected:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    qreal                      mDiameter;
    QGraphicsDropShadowEffect* mDropShadow;
};
