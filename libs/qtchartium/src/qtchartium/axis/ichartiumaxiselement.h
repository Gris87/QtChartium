#pragma once



#include <QObject>



class IChartiumAxisElement : public QObject
{
    Q_OBJECT

public:
    explicit IChartiumAxisElement(QObject* parent = nullptr) :
        QObject(parent)
    {
    }
    ~IChartiumAxisElement() override = default;

    IChartiumAxisElement(const IChartiumAxisElement& another)            = delete;
    IChartiumAxisElement& operator=(const IChartiumAxisElement& another) = delete;
};
