#pragma once



#include <QObject>



class IChartiumLayout : public QObject
{
    Q_OBJECT

public:
    explicit IChartiumLayout(QObject* parent = nullptr) :
        QObject(parent)
    {
    }
    ~IChartiumLayout() override = default;

    IChartiumLayout(const IChartiumLayout& another)            = delete;
    IChartiumLayout& operator=(const IChartiumLayout& another) = delete;
};
