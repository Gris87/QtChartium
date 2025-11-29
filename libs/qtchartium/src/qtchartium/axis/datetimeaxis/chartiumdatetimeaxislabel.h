#pragma once



#include "src/qtchartium/axis/datetimeaxis/ichartiumdatetimeaxislabel.h"



class ChartiumDateTimeAxisLabel : public IChartiumDateTimeAxisLabel
{
    Q_OBJECT

public:
    explicit ChartiumDateTimeAxisLabel(QGraphicsItem* parent = nullptr);
    ~ChartiumDateTimeAxisLabel() override;

    ChartiumDateTimeAxisLabel(const ChartiumDateTimeAxisLabel& another)            = delete;
    ChartiumDateTimeAxisLabel& operator=(const ChartiumDateTimeAxisLabel& another) = delete;

    QDateTime value() const override;
    void      setValue(const QDateTime& value) override;
    void      setFormat(const QString& format) override;

    void keyPressEvent(QKeyEvent* event) override;

    void setInitialEditValue() override;
    void finishEditing() override;
    void resetBeforeEditValue() override;

protected:
    QDateTime mDateTime;
    QDateTime mDateTimeBeforeEdit;
    QString   mFormat;
};
