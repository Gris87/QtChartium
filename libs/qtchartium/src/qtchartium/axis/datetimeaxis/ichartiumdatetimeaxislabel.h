#pragma once



#include "src/qtchartium/axis/chartiumeditableaxislabel.h"

#include <QDateTime>



class IChartiumDateTimeAxisLabel : public ChartiumEditableAxisLabel
{
    Q_OBJECT

public:
    explicit IChartiumDateTimeAxisLabel(QGraphicsItem* parent = nullptr) :
        ChartiumEditableAxisLabel(parent)
    {
    }
    ~IChartiumDateTimeAxisLabel() override = default;

    IChartiumDateTimeAxisLabel(const IChartiumDateTimeAxisLabel& another)            = delete;
    IChartiumDateTimeAxisLabel& operator=(const IChartiumDateTimeAxisLabel& another) = delete;

    virtual QDateTime value() const                    = 0;
    virtual void      setValue(const QDateTime& value) = 0;
    virtual void      setFormat(const QString& format) = 0;

signals:
    void dateTimeChanged(const QDateTime& oldDateTime, const QDateTime& newDateTime);
};
