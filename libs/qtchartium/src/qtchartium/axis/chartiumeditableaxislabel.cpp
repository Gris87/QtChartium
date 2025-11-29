#include "src/qtchartium/axis/chartiumeditableaxislabel.h"

#include <QKeyEvent>
#include <QTextCursor>
#include <QTextDocument>



ChartiumEditableAxisLabel::ChartiumEditableAxisLabel(QGraphicsItem* parent) :
    IChartiumEditableAxisLabel(parent)
{
}

ChartiumEditableAxisLabel::~ChartiumEditableAxisLabel()
{
}

void ChartiumEditableAxisLabel::setEditable(bool editable)
{
    mEditable = editable;
}

void ChartiumEditableAxisLabel::reloadBeforeEditContent()
{
    resetBeforeEditValue();
    setHtml(mHtmlBeforeEdit);
}

void ChartiumEditableAxisLabel::setInitialEditValue()
{
}

void ChartiumEditableAxisLabel::finishEditing()
{
}

void ChartiumEditableAxisLabel::resetBeforeEditValue()
{
}

bool ChartiumEditableAxisLabel::isEditEndingKeyPress(QKeyEvent* event)
{
    if (event->text().size() >= 1)
    {
        // finish editing with enter or ESC
        if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
        {
            clearFocus();
            return true;
        }
        else if (event->key() == Qt::Key_Escape)
        {
            document()->setHtml(mHtmlBeforeEdit);
            clearFocus();
            return true;
        }
    }

    return false;
}

void ChartiumEditableAxisLabel::focusInEvent(QFocusEvent* event)
{
    mHtmlBeforeEdit = toHtml();
    setTextWidth(-1);
    setInitialEditValue();
    mEditing = true;

    IChartiumEditableAxisLabel::focusInEvent(event);
}

void ChartiumEditableAxisLabel::focusOutEvent(QFocusEvent* event)
{
    IChartiumEditableAxisLabel::focusOutEvent(event);
    setTextInteractionFlags(Qt::NoTextInteraction);

    mEditing = false;

    finishEditing();
}

bool ChartiumEditableAxisLabel::sceneEvent(QEvent* event)
{
    if (mEditable && event->type() == QEvent::GraphicsSceneMouseDoubleClick)
    {
        setTextInteractionFlags(Qt::TextEditorInteraction);

        bool ret = IChartiumEditableAxisLabel::sceneEvent(event);

        setFocus(Qt::MouseFocusReason);
        QTextCursor cursor = textCursor();
        cursor.select(QTextCursor::Document);
        setTextCursor(cursor);

        return ret;
    }

    return IChartiumEditableAxisLabel::sceneEvent(event);
}

QRectF ChartiumEditableAxisLabel::boundingRect() const
{
    QRectF ret = QGraphicsTextItem::boundingRect();

    // add 2px margin to allow the cursor to
    // show up properly when editing
    if (mEditing)
    {
        ret.setWidth(ret.width() + 2);
    }

    return ret;
}
