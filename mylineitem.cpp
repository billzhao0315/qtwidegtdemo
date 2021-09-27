#include "mylineitem.h"

MyLineItem::MyLineItem(qreal x1, qreal y1, qreal x2, qreal y2,int index, QGraphicsItem *parent):QGraphicsLineItem(x1, y1, x2, y2, parent)
{
    m_colorFlag = true;
    m_index = index;
}
MyLineItem::MyLineItem(const QLineF &line,int index, QGraphicsItem *parent):QGraphicsLineItem(line, parent)
{
    m_colorFlag = true;
    m_index = index;
}
MyLineItem::MyLineItem(int index, QGraphicsItem *parent):QGraphicsLineItem(parent)
{
    m_colorFlag = true;
    m_index = index;
}

void MyLineItem::setIndex(int index)
{
    m_index = index;
}
void MyLineItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
//    qreal x = pos().x();
//    qreal y = pos().y();
//    double D = m_Radius - m_radius - 2;

//    // limit circle position
//    if(x*x + y*y >D*D)
//    {
//        double tmpX = x*D/sqrt(x*x + y*y);
//        double tmpY = y*D/sqrt(x*x + y*y);

//        setPos(tmpX, tmpY);
//    }
    //emit posChanged(m_index);
    QGraphicsLineItem::mouseReleaseEvent(event);
}
void MyLineItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //emit posChanged(m_index);
    QGraphicsLineItem::mouseMoveEvent(event);
}

void MyLineItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    m_colorFlag = !m_colorFlag;
    QGraphicsLineItem::mouseDoubleClickEvent(event);
    emit addNodeItem(m_index);
    update();
}

void MyLineItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    if(event->type() == QEvent::Enter)
    {
        m_colorFlag = !m_colorFlag;
    }
    QGraphicsLineItem::hoverEnterEvent(event);
    update();
}

void MyLineItem::focusInEvent(QFocusEvent *event)
{
    if(event->type() == QEvent::Enter)
    {
        m_colorFlag = !m_colorFlag;
    }
    QGraphicsLineItem::focusInEvent(event);
    update();
}

void MyLineItem::paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget)
{

    QPen pent = pen();
    if(m_colorFlag)
        pent.setColor(Qt::blue);
    else
        pent.setColor(Qt::red);
    pent.setWidth(2);
    painter->setPen(pent);
    painter->drawLine(line());
    //QGraphicsLineItem::paint(painter,option,widget);
}
