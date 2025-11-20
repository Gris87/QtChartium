#pragma once



#include <QObject>



class IChartiumLegend : public QObject
{
    Q_OBJECT

public:
    explicit IChartiumLegend(QObject* parent = nullptr) :
        QObject(parent)
    {
    }
    ~IChartiumLegend() override = default;

    IChartiumLegend(const IChartiumLegend& another)            = delete;
    IChartiumLegend& operator=(const IChartiumLegend& another) = delete;

    virtual void hide() = 0;
};
