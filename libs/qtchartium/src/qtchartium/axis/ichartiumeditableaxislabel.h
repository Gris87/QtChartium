#pragma once



#include <QGraphicsTextItem>



class IChartiumEditableAxisLabel : public QGraphicsTextItem
{
    Q_OBJECT

public:
    explicit IChartiumEditableAxisLabel(QGraphicsItem* parent = nullptr) :
        QGraphicsTextItem(parent)
    {
    }
    ~IChartiumEditableAxisLabel() override = default;

    IChartiumEditableAxisLabel(const IChartiumEditableAxisLabel& another)            = delete;
    IChartiumEditableAxisLabel& operator=(const IChartiumEditableAxisLabel& another) = delete;

    virtual void setEditable(bool editable) = 0;
    virtual void reloadBeforeEditContent()  = 0;

    virtual void setInitialEditValue()  = 0;
    virtual void finishEditing()        = 0;
    virtual void resetBeforeEditValue() = 0;

    virtual bool isEditEndingKeyPress(QKeyEvent* event) = 0;
};
