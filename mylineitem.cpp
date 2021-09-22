#include "mylineitem.h"

MyLineItem::MyLineItem(qreal x1, qreal y1, qreal x2, qreal y2, QGraphicsItem *parent):QGraphicsLineItem(x1, y1, x2, y2, parent)
{
    m_colorFlag = false;
}
MyLineItem::MyLineItem(const QLineF &line, QGraphicsItem *parent):QGraphicsLineItem(line, parent)
{
    m_colorFlag = false;
}
MyLineItem::MyLineItem(QGraphicsItem *parent):QGraphicsLineItem(parent)
{
    m_colorFlag = false;
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
    QGraphicsItem::mouseReleaseEvent(event);
}
void MyLineItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //emit posChanged(m_index);
    QGraphicsItem::mouseMoveEvent(event);
}

void MyLineItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    m_colorFlag = !m_colorFlag;
    QGraphicsItem::mouseDoubleClickEvent(event);
    update();
}

void MyLineItem::paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget)
{

    QPen pent = pen();
    if(m_colorFlag)
        pent.setColor(Qt::blue);
    else
        pent.setColor(Qt::red);
    pent.setWidth(3);
    painter->setPen(pent);
    painter->drawLine(line());
    //QGraphicsLineItem::paint(painter,option,widget);
}
