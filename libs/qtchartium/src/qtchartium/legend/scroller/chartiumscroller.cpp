#include "src/qtchartium/legend/scroller/chartiumscroller.h"

#include <QDebug>

#include "src/qtchartium/legend/scroller/chartiumscrollticker.h"



ChartiumScroller::ChartiumScroller() :
    IChartiumScroller(),
    m_ticker(new ChartiumScrollTicker(this)),
    m_timeStamp(),
    m_speed(),
    m_fraction(),
    m_timeTresholdMin(50),
    m_timeTresholdMax(300),
    m_state(IChartiumScroller::Idle),
    m_pressPos(),
    m_lastPos(),
    m_treshold(10)
{
}

ChartiumScroller::~ChartiumScroller()
{
    delete m_ticker;
}

void ChartiumScroller::setOffset(const QPointF& point)
{
}

QPointF ChartiumScroller::offset() const
{
    return QPointF();
}

void ChartiumScroller::move(const QPointF& delta)
{
    switch (m_state)
    {
        case IChartiumScroller::Pressed:
            m_timeStamp.start();
            break;
        case IChartiumScroller::Scroll:
            stopTicker();
            m_timeStamp.start();
            break;
        default:
            break;
    }

    setOffset(offset() - delta);
}

void ChartiumScroller::scrollTo(const QPointF& delta)
{
    // Starts scrolling, if at least m_timeTresholdMin msecs has gone since timestamp
    // current time is no more than m_timeTresholdMax from timestamp

    if ((m_timeStamp.elapsed() > m_timeTresholdMin) && (m_timeStamp.elapsed() < m_timeTresholdMax))
    {
        // Release was quick enough. Start scrolling.
        qreal interval = 25;
        qreal time     = m_timeStamp.elapsed();

        if (qFuzzyCompare(time, 0))
        {
            m_speed = delta / 5;
        }
        else
        {
            m_speed = delta * interval / time;
        }

        qreal fraction = qMax(qAbs(m_speed.x()), qAbs(m_speed.y()));

        if (!qFuzzyCompare(fraction, 0))
        {
            m_fraction.setX(qAbs(m_speed.x() / fraction));
            m_fraction.setY(qAbs(m_speed.y() / fraction));
        }
        else
        {
            m_fraction.setX(1);
            m_fraction.setY(1);
        }

        startTicker(interval);
    }
    else
    {
        stopTicker(); // Stop ticker, if one is running.
    }
}

void ChartiumScroller::handleMousePressEvent(QGraphicsSceneMouseEvent* event)
{
    stopTicker();

    m_pressPos = event->screenPos();
    m_lastPos  = m_pressPos;
    m_state    = Pressed;

    event->accept();
}

void ChartiumScroller::handleMouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    QPointF delta = event->screenPos() - m_lastPos;

    switch (m_state)
    {
        case IChartiumScroller::Pressed:
        {
            // calculate treshold. If enough, change to move state and send out move deltas.
            if (qAbs(delta.x()) > m_treshold || qAbs(delta.y()) > m_treshold)
            {
                m_lastPos = event->screenPos();
                move(delta);
                m_state = Move;
            }

            event->accept();

            break;
        }
        case IChartiumScroller::Move:
        {
            m_lastPos = event->screenPos();
            move(delta);

            event->accept();

            break;
        }
        case IChartiumScroller::Idle:
        default:
        {
            event->ignore();
            break;
        }
    }
}

void ChartiumScroller::handleMouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    switch (m_state)
    {
        case IChartiumScroller::Move:
        {
            scrollTo(m_lastPos - m_pressPos);
            event->accept();

            break;
        }
        default:
        {
            m_state = Idle;
            event->ignore();

            break;
        }
    }
}

void ChartiumScroller::scrollTick()
{
    switch (m_state)
    {
        case Scroll:
            lowerSpeed(m_speed);
            setOffset(offset() - m_speed);
            if (m_speed == QPointF(0, 0))
            {
                m_state = Idle;
                m_ticker->stop();
            }
            break;
        default:
            qWarning() << __FUNCTION__ << "Scroller unexpected state" << m_state;
            m_ticker->stop();
            m_state = Idle;
            break;
    }
}

void ChartiumScroller::startTicker(int interval)
{
    m_state = Scroll;
    m_ticker->start(interval);
}

void ChartiumScroller::stopTicker()
{
    m_state = Idle;
    m_ticker->stop();
}

void ChartiumScroller::calculateSpeed(const QPointF& position)
{
}

void ChartiumScroller::lowerSpeed(QPointF& speed, qreal maxSpeed)
{
    qreal x = qBound(-maxSpeed, speed.x(), maxSpeed);
    qreal y = qBound(-maxSpeed, speed.y(), maxSpeed);

    x = (x == 0) ? x : (x > 0) ? qMax(qreal(0), x - m_fraction.x()) : qMin(qreal(0), x + m_fraction.x());
    y = (y == 0) ? y : (y > 0) ? qMax(qreal(0), y - m_fraction.y()) : qMin(qreal(0), y + m_fraction.y());

    speed.setX(x);
    speed.setY(y);
}
