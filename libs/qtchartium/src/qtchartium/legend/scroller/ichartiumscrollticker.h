#pragma once



#include <QObject>



class IChartiumScrollTicker : public QObject
{
    Q_OBJECT

public:
    explicit IChartiumScrollTicker(QObject* parent = nullptr) :
        QObject(parent)
    {
    }
    ~IChartiumScrollTicker() override = default;

    IChartiumScrollTicker(const IChartiumScrollTicker& another)            = delete;
    IChartiumScrollTicker& operator=(const IChartiumScrollTicker& another) = delete;

    virtual void start(int interval) = 0;
    virtual void stop()              = 0;
};
