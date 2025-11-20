#pragma once



#include <QObject>



class IChartiumItem : public QObject
{
    Q_OBJECT

public:
    explicit IChartiumItem(QObject* parent = nullptr) :
        QObject(parent)
    {
    }
    ~IChartiumItem() override = default;

    IChartiumItem(const IChartiumItem& another)            = delete;
    IChartiumItem& operator=(const IChartiumItem& another) = delete;
};
