#pragma once



#include "src/qtchartium/axis/ichartiumeditableaxislabel.h"



class ChartiumEditableAxisLabel : public IChartiumEditableAxisLabel
{
    Q_OBJECT

public:
    explicit ChartiumEditableAxisLabel(QGraphicsItem* parent = nullptr);
    ~ChartiumEditableAxisLabel() override;

    ChartiumEditableAxisLabel(const ChartiumEditableAxisLabel& another)            = delete;
    ChartiumEditableAxisLabel& operator=(const ChartiumEditableAxisLabel& another) = delete;

    void setEditable(bool editable) override;
    void reloadBeforeEditContent() override;

    void setInitialEditValue() override;
    void finishEditing() override;
    void resetBeforeEditValue() override;

    bool isEditEndingKeyPress(QKeyEvent* event) override;

    void focusInEvent(QFocusEvent* event) override;
    void focusOutEvent(QFocusEvent* event) override;
    bool sceneEvent(QEvent* event) override;

    QRectF boundingRect() const override;

protected:
    QString mHtmlBeforeEdit;
    bool    mEditing;
    bool    mEditable;
};
