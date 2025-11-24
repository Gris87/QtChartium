#include "src/qtchartium/chartiumtitle.h"

#include <QTextDocument>

#include "src/qtchartium/ichartiumpresenter.h"



ChartiumTitle::ChartiumTitle(IChartiumPresenter* presenter, QGraphicsItem* parent) :
    IChartiumTitle(parent),
    mPresenter(presenter),
    mText()
{
    document()->setDocumentMargin(mPresenter->textMargin());
    setAcceptedMouseButtons({});
}

ChartiumTitle::~ChartiumTitle()
{
}

QSizeF ChartiumTitle::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
{
    QSizeF sh;

    switch (which)
    {
        case Qt::MinimumSize:
        {
            QRectF titleRect = mPresenter->textBoundingRect(font(), QStringLiteral("..."));
            sh               = QSizeF(titleRect.width(), titleRect.height());
        }
        break;

        case Qt::PreferredSize:
        case Qt::MaximumSize:
        {
            QRectF titleRect = mPresenter->textBoundingRect(font(), mText);
            sh               = QSizeF(titleRect.width(), titleRect.height());
        }
        break;

        case Qt::MinimumDescent:
        {
            QFontMetrics fn(font());
            sh = QSizeF(0, fn.descent());
        }
        break;
    }

    return sh;
}

void ChartiumTitle::setText(const QString& text)
{
    mText = text;
}

QString ChartiumTitle::text() const
{
    return mText;
}

void ChartiumTitle::setGeometry(const QRectF& rect)
{
    QRectF truncatedRect;

    if (mText == "")
    {
        setHtml(mText);
        setTextWidth(0.0);
    }
    else
    {
        setHtml(mPresenter->truncatedText(font(), mText, qreal(0.0), rect.width(), rect.height(), truncatedRect));
        setTextWidth(truncatedRect.width());
    }

    setPos(rect.topLeft());
}
