#pragma once



#include <QObject>



class IChartiumBackground : public QObject
{
    Q_OBJECT

public:
    explicit IChartiumBackground(QObject* parent = nullptr) :
        QObject(parent)
    {
    }
    ~IChartiumBackground() override = default;

    IChartiumBackground(const IChartiumBackground& another)            = delete;
    IChartiumBackground& operator=(const IChartiumBackground& another) = delete;
};
