#pragma once



#include <QGraphicsRectItem>



class IChartiumBackground : public QGraphicsRectItem
{
public:
    explicit IChartiumBackground(QGraphicsItem* parent = nullptr) :
        QGraphicsRectItem(parent)
    {
    }
    ~IChartiumBackground() override = default;

    IChartiumBackground(const IChartiumBackground& another)            = delete;
    IChartiumBackground& operator=(const IChartiumBackground& another) = delete;

    virtual void  setDiameter(qreal diameter) = 0;
    virtual qreal diameter() const            = 0;

    virtual void setDropShadowEnabled(bool enabled) = 0;
    virtual bool isDropShadowEnabled() const        = 0;
};
