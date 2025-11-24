#pragma once



#include <QGraphicsTextItem>



class IChartiumTitle : public QGraphicsTextItem
{
public:
    explicit IChartiumTitle(QGraphicsItem* parent = nullptr) :
        QGraphicsTextItem(parent)
    {
    }
    ~IChartiumTitle() override = default;

    IChartiumTitle(const IChartiumTitle& another)            = delete;
    IChartiumTitle& operator=(const IChartiumTitle& another) = delete;

    virtual QSizeF  sizeHint(Qt::SizeHint which, const QSizeF& constraint = QSizeF()) const = 0;
    virtual void    setText(const QString& text)                                            = 0;
    virtual QString text() const                                                            = 0;
    virtual void    setGeometry(const QRectF& rect)                                         = 0;
};
