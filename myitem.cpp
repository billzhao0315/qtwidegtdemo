#include "myitem.h"
#include <QMimeData>
#include <QDrag>
#include <QDebug>
#include <QGraphicsView>
#include <QVarLengthArray>
#include <QPointF>
#include "math.h"

MyItem::MyItem(double radius, double Radius, int index)
{
    m_colorFlag = true;
    m_radius = radius;
    m_Radius = Radius;
    m_index  = index;
    setFlags(ItemIsSelectable | ItemIsMovable | ItemSendsGeometryChanges);
}

MyItem::~MyItem()
{

}

QRectF MyItem::boundingRect() const
{
    return QRectF(-m_radius, -m_radius,
                  2*m_radius, 2*m_radius);
}

void MyItem::setIndex(int index)
{
    m_index = index;
}

void MyItem::updateRadius(double radius)
{
    if(m_radius != radius)
    {
        m_radius = radius;
        update();
    }
    //m_radius = radius;
}

void MyItem::paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget)
{
    if(m_colorFlag)
        painter->setBrush(Qt::blue);
    else
        painter->setBrush(Qt::red);

    painter->drawEllipse(QPointF(0, 0), m_radius, m_radius);
    //painter->save();
    //painter->setPen(Qt::green);
    //painter->drawText(QPointF(0,0), QString::number(m_index)+ ":(" + QString::number(pos().x()) + "," + QString::number(-pos().y()) + ")");
    this->setToolTip(QString::number(m_index)+ ":(" + QString::number(pos().x()) + "," + QString::number(pos().y()) + ")");
    //painter->restore();
    //QGraphicsItem::paint(painter,option,widget);
}

void MyItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
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

QVariant MyItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange) {
        emit posChanged(m_index);
//        // value is the new position.
//        QPointF newPos = value.toPointF();
//        QRectF rect = scene()->sceneRect();
//        if (!rect.contains(newPos)) {
//            // Keep the item inside the scene rect.
//            newPos.setX(qMin(rect.right(), qMax(newPos.x(), rect.left())));
//            newPos.setY(qMin(rect.bottom(), qMax(newPos.y(), rect.top())));
//            return newPos;
//        }
    }
    return QGraphicsItem::itemChange(change, value);
}

void MyItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //emit posChanged(m_index);
    QGraphicsItem::mouseMoveEvent(event);
}

void MyItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    m_colorFlag = !m_colorFlag;
    QGraphicsItem::mouseDoubleClickEvent(event);
    update();
}
