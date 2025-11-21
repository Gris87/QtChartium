#pragma once



#include <QObject>



class IChartiumLegendMarker : public QObject
{
    Q_OBJECT

public:
    explicit IChartiumLegendMarker(QObject* parent = nullptr) :
        QObject(parent)
    {
    }
    ~IChartiumLegendMarker() override = default;

    IChartiumLegendMarker(const IChartiumLegendMarker& another)            = delete;
    IChartiumLegendMarker& operator=(const IChartiumLegendMarker& another) = delete;
};
