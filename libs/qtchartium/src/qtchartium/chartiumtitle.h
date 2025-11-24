#pragma once



#include "src/qtchartium/ichartiumtitle.h"



class IChartiumPresenter;



class ChartiumTitle : public IChartiumTitle
{
public:
    explicit ChartiumTitle(IChartiumPresenter* presenter, QGraphicsItem* parent = nullptr);
    ~ChartiumTitle() override;

    ChartiumTitle(const ChartiumTitle& another)            = delete;
    ChartiumTitle& operator=(const ChartiumTitle& another) = delete;

    QSizeF  sizeHint(Qt::SizeHint which, const QSizeF& constraint = QSizeF()) const override;
    void    setText(const QString& text) override;
    QString text() const override;
    void    setGeometry(const QRectF& rect) override;

protected:
    IChartiumPresenter* mPresenter;
    QString             mText;
};
