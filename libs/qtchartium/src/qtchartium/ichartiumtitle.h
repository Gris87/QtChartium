#pragma once



#include <QObject>



class IChartiumTitle : public QObject
{
    Q_OBJECT

public:
    explicit IChartiumTitle(QObject* parent = nullptr) :
        QObject(parent)
    {
    }
    ~IChartiumTitle() override = default;

    IChartiumTitle(const IChartiumTitle& another)            = delete;
    IChartiumTitle& operator=(const IChartiumTitle& another) = delete;
};
