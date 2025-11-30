#include "src/qtchartium/axis/datetimeaxis/chartiumdatetimeaxislabel.h"

#include <QTextDocument>



ChartiumDateTimeAxisLabel::ChartiumDateTimeAxisLabel(QGraphicsItem* parent) :
    IChartiumDateTimeAxisLabel(parent),
    mDateTime(),
    mDateTimeBeforeEdit(),
    mFormat()
{
}

ChartiumDateTimeAxisLabel::~ChartiumDateTimeAxisLabel()
{
}

QDateTime ChartiumDateTimeAxisLabel::value() const
{
    return mDateTime;
}

void ChartiumDateTimeAxisLabel::setValue(const QDateTime& value)
{
    setTextInteractionFlags(Qt::NoTextInteraction);
    clearFocus();
    mDateTime = value;
}

void ChartiumDateTimeAxisLabel::setFormat(const QString& format)
{
    mFormat = format;
    // Labels should be edited as a single line regardless to their
    // format because enter triggers applying the current text.
    mFormat.replace(QChar::fromLatin1('\n'), QChar::fromLatin1(' '));
}

void ChartiumDateTimeAxisLabel::keyPressEvent(QKeyEvent* event)
{
    if (isEditEndingKeyPress(event))
    {
        // prevent further event processing with a return
        // because the focusOutEvent could have triggered
        // a range change which might have invalidated the current label
        return;
    }

    QGraphicsTextItem::keyPressEvent(event);
}

void ChartiumDateTimeAxisLabel::setInitialEditValue()
{
    mDateTimeBeforeEdit = mDateTime;
    setHtml(mDateTime.toString(mFormat));
}

void ChartiumDateTimeAxisLabel::finishEditing()
{
    QDateTime oldDateTime = mDateTime;
    QDateTime newDateTime = QDateTime::fromString(document()->toPlainText(), mFormat);
    if (newDateTime.isValid() && newDateTime != mDateTime)
    {
        mDateTime = newDateTime;
        emit dateTimeChanged(oldDateTime, newDateTime);
    }
    else
    {
        document()->setHtml(mHtmlBeforeEdit);
    }
}

void ChartiumDateTimeAxisLabel::resetBeforeEditValue()
{
    mDateTime = mDateTimeBeforeEdit;
}
