#pragma once



#include <QGraphicsView>



class IChartiumView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit IChartiumView(QWidget* parent = nullptr) :
        QGraphicsView(parent)
    {
    }
    ~IChartiumView() override = default;

    IChartiumView(const IChartiumView& another)            = delete;
    IChartiumView& operator=(const IChartiumView& another) = delete;
};
