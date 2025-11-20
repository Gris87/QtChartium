#pragma once



#include <QObject>



class IChartiumDomain : public QObject
{
    Q_OBJECT

public:
    enum DomainType : quint8
    {
        UndefinedDomain,
        XYDomain,
        XLogYDomain,
        LogXYDomain,
        LogXLogYDomain,
        XYPolarDomain,
        XLogYPolarDomain,
        LogXYPolarDomain,
        LogXLogYPolarDomain
    };

    explicit IChartiumDomain(QObject* parent = nullptr) :
        QObject(parent)
    {
    }
    ~IChartiumDomain() override = default;

    IChartiumDomain(const IChartiumDomain& another)            = delete;
    IChartiumDomain& operator=(const IChartiumDomain& another) = delete;
};
