#pragma once



#include <QGraphicsObject>



class IChartiumDataSet;
class IChartiumPresenter;



class IChartiumElement : public QGraphicsObject
{
public:
    explicit IChartiumElement(QGraphicsItem* item = nullptr) :
        QGraphicsObject(item)
    {
    }
    ~IChartiumElement() override = default;

    IChartiumElement(const IChartiumElement& another)            = delete;
    IChartiumElement& operator=(const IChartiumElement& another) = delete;

    virtual void                setPresenter(IChartiumPresenter* presenter) = 0;
    virtual IChartiumPresenter* presenter() const                           = 0;

    virtual void              setDataSet(IChartiumDataSet* dataSet) = 0;
    virtual IChartiumDataSet* dataSet() const                       = 0;
};
