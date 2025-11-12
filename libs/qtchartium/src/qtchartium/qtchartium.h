#pragma once



#include <QGraphicsView>



class ChartiumView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit ChartiumView(QWidget* parent = nullptr);
    ~ChartiumView() override;

    ChartiumView(const ChartiumView& another)            = delete;
    ChartiumView& operator=(const ChartiumView& another) = delete;
};
