#pragma once



#include <QObject>



class IChartiumAxis : public QObject
{
    Q_OBJECT

public:
    enum AxisType : quint8
    {
        AxisTypeNoAxis      = 0x0,
        AxisTypeValue       = 0x1,
        AxisTypeBarCategory = 0x2,
        AxisTypeCategory    = 0x4,
        AxisTypeDateTime    = 0x8,
        AxisTypeLogValue    = 0x10,
        AxisTypeColor       = 0x20
    };
    typedef quint8 AxisTypes;

    explicit IChartiumAxis(QObject* parent = nullptr) :
        QObject(parent)
    {
    }
    ~IChartiumAxis() override = default;

    IChartiumAxis(const IChartiumAxis& another)            = delete;
    IChartiumAxis& operator=(const IChartiumAxis& another) = delete;
};
