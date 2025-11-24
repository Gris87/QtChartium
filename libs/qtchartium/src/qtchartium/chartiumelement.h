#pragma once



#include "src/qtchartium/ichartiumelement.h"



class ChartiumElement : public IChartiumElement
{
    Q_OBJECT

public:
    explicit ChartiumElement(QGraphicsItem* item = nullptr);
    ~ChartiumElement() override;

    ChartiumElement(const ChartiumElement& another)            = delete;
    ChartiumElement& operator=(const ChartiumElement& another) = delete;

    void                setPresenter(IChartiumPresenter* presenter) override;
    IChartiumPresenter* presenter() const override;

    void              setDataSet(IChartiumDataSet* dataSet) override;
    IChartiumDataSet* dataSet() const override;

protected:
    IChartiumPresenter* mPresenter;
    IChartiumDataSet*   mDataSet;
};
