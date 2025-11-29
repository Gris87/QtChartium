#include "src/qtchartium/axis/valueaxis/chartiumvalueaxislabel.h"

#include <QKeyEvent>
#include <QTextDocument>



ChartiumValueAxisLabel::ChartiumValueAxisLabel(QGraphicsItem* parent) :
    IChartiumValueAxisLabel(parent),
    mValue(),
    mValueBeforeEdit()
{
}

ChartiumValueAxisLabel::~ChartiumValueAxisLabel()
{
}

qreal ChartiumValueAxisLabel::value() const
{
    return mValue;
}

void ChartiumValueAxisLabel::setValue(const qreal& value)
{
    setTextInteractionFlags(Qt::NoTextInteraction);
    clearFocus();

    mValue = value;
}

void ChartiumValueAxisLabel::keyPressEvent(QKeyEvent* event)
{
    if (isEditEndingKeyPress(event))
    {
        // prevent further event processing with a return
        // because the focusOutEvent could have triggered
        // a range change which might have invalidated the current label
        return;
    }

    if (event->text().size() >= 1)
    {
        QLocale locale;
        if (!event->text().at(0).isDigit() && event->text().at(0) != locale.decimalPoint() &&
            event->text().at(0) != locale.negativeSign() && event->text().at(0) != locale.exponential() &&
            event->key() != Qt::Key_Backspace && event->key() != Qt::Key_Delete)
        {
            event->ignore();
            return;
        }
    }

    IChartiumValueAxisLabel::keyPressEvent(event);
}

void ChartiumValueAxisLabel::setInitialEditValue()
{
    mValueBeforeEdit = mValue;
    setHtml(QString::number(mValue));
}

void ChartiumValueAxisLabel::finishEditing()
{
    bool    ok = false;
    QLocale locale;
    qreal   oldValue = mValue;
    qreal   newValue = locale.toDouble(document()->toPlainText(), &ok);

    if (ok && newValue != mValue)
    {
        mValue = newValue;
        emit valueChanged(oldValue, newValue);
    }
    else
    {
        document()->setHtml(mHtmlBeforeEdit);
    }
}

void ChartiumValueAxisLabel::resetBeforeEditValue()
{
    mValue = mValueBeforeEdit;
}
