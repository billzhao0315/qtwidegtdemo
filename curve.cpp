#include "curve.h"
#include <QDebug>
#include <QGraphicsScene>
#define RADIUS 100

Curve::Curve(QString title, QGraphicsScene *scene)
{
    m_title = title;
    m_linePen.setColor(Qt::black);
    m_linePen.setWidthF(1);
    m_pointPen.setColor(Qt::black);
    m_pointPen.setWidthF(3);
    m_titleShow = true;
    m_scene = scene;

    m_dataSize = 0;
    m_xOrigin = 0;
    m_yOrigin = 0;
}

void Curve::setTitle(QString title)
{
    m_title = title;
}

void Curve::setTitleShow(bool flag)
{
    m_titleShow = flag;
}

void Curve::setLinePen(QPen pen)
{
    m_linePen = pen;
}

void Curve::setPointSize(double size)
{
    m_pointPen.setWidthF(size);
}

void Curve::setPointPen(QPen pen)
{
    m_pointPen = pen;
}

void Curve::setPointColor(const QColor color)
{
    m_pointPen.setColor(color);
}

void Curve::setCurveColor(const QColor color)
{
    m_linePen.setColor(color);
}

void Curve::setCurveStyle(Qt::PenStyle style)
{
    m_linePen.setStyle(style);
}

void Curve::addData(QPointF d)
{

    m_data << d;
    m_dataSize = m_data.size();
}

void Curve::addPosData(QPointF p)
{
    qDebug()<<"addPosData:"<<p;
    MyItem* pointItem = new MyItem(getRadius(), RADIUS, m_posPointData.size());
    pointItem->setPos(p);
    pointItem->setToolTip("("+QString::number(p.x())+QString::number(p.y())+")");
    //m_scene->addItem(pointItem);
    QObject::connect(pointItem, &MyItem::posChanged, this, &Curve::posChanged);
    m_posPointData<< pointItem;
    if(m_posPointData.size() < 2) return;
    MyItem* startPoint = m_posPointData[m_posPointData.size()-2];
    MyItem* endPoint = m_posPointData[m_posPointData.size()-1];
    MyLineItem* lineItem = new MyLineItem(startPoint->pos().x(), startPoint->pos().y(), endPoint->pos().x(), endPoint->pos().y(), m_posPointData.size()-2);
    m_posSegmentData<<lineItem;
    //m_scene->addItem( lineItem );
    QObject::connect(lineItem, &MyLineItem::addNodeItem, this, &Curve::addNodeItem);

}

void Curve::setRawData(const QVector<QPointF> &data, int size)
{
    m_data = data;
    m_dataSize = size;
}

void Curve::resetPosData(int index, QPointF p)
{
    qDebug()<<"curv:"<<"index:"<< index <<",point:"<<p;
    m_posPointData[index]->setPos(p);
}

void Curve::setOriginPoint(double x, double y)
{
    m_xOrigin = x;
    m_yOrigin = y;
    for (int i = 0; i < m_posPointData.size(); ++i) {
        m_posPointData[i]->setOriginPoint(m_xOrigin, m_yOrigin);
    }
    for (int i = 0; i < m_posSegmentData.size(); ++i) {
        m_posSegmentData[i]->setOriginPoint(m_xOrigin,m_yOrigin);
    }
}

void Curve::clearData()
{
    m_data.clear();
    m_posPointData.clear();
    m_posSegmentData.clear();
    m_dataSize = 0;
}

QString Curve::getTitle()
{
    return m_title;
}

bool Curve::getTitleShow()
{
    return m_titleShow;
}

QPointF Curve::getData(int index)
{
    return m_data.at(index);
}

QPointF Curve::getPosData(int index)
{
    return m_posPointData[index]->pos();
}

int Curve::getDataSize()
{
    //return m_data.size();
    return m_dataSize;
}

QPen Curve::getLinePen()
{
    return m_linePen;
}

QPen Curve::getPointPen()
{
    return m_pointPen;
}

int Curve::getRadius()
{
    int radius;

    //set radius value
    if(m_posPointData.size()<7)
        radius = 15;
    else if(m_posPointData.size()<11)
        radius = 10;
    else
        radius = 15;
    return radius;
}

QVector<MyItem*> Curve::getPosPointData()
{
    return m_posPointData;
}
QVector<MyLineItem*> Curve::getPosSegmentData()
{
    return m_posSegmentData;
}

void Curve::posChanged(int index)
{
    if(m_posPointData.size() <1) return;
    if(index ==0)
    {
        m_scene->removeItem( m_posSegmentData[0] );
        m_posSegmentData[0] = new MyLineItem(m_posPointData[0]->pos().x(), m_posPointData[0]->pos().y(), m_posPointData[1]->pos().x(), m_posPointData[1]->pos().y(), 0);
                //m_scene->addLine(item[0]->pos().x(), item[0]->pos().y(), item[1]->pos().x(), item[1]->pos().y());
        m_scene->addItem(m_posSegmentData[0]);
        QObject::connect(m_posSegmentData[0], &MyLineItem::addNodeItem, this, &Curve::addNodeItem);
        return;
    }
    int m_steelNum = m_posPointData.size();
    if(index == m_posPointData.size()-1)
    {
        m_scene->removeItem( m_posSegmentData[m_steelNum-2] );
        m_posSegmentData[m_steelNum-2] = new MyLineItem(m_posPointData[m_steelNum-2]->pos().x(), m_posPointData[m_steelNum-2]->pos().y(), m_posPointData[m_steelNum-1]->pos().x(), m_posPointData[m_steelNum-1]->pos().y(), m_steelNum-2);
                //m_scene->addLine(item[m_steelNum-2]->pos().x(), item[m_steelNum-2]->pos().y(), item[m_steelNum-1]->pos().x(), item[m_steelNum-1]->pos().y());
        m_scene->addItem(m_posSegmentData[m_steelNum-2]);
        QObject::connect(m_posSegmentData[m_steelNum-2], &MyLineItem::addNodeItem, this, &Curve::addNodeItem);
        return;
    }
    m_scene->removeItem( m_posSegmentData[index-1] );
    m_scene->removeItem( m_posSegmentData[index] );
    m_posSegmentData[index-1] = new MyLineItem(m_posPointData[index-1]->pos().x(), m_posPointData[index-1]->pos().y(), m_posPointData[index]->pos().x(), m_posPointData[index]->pos().y(), index-1);
            //m_scene->addLine(item[index-1]->pos().x(), item[index-1]->pos().y(), item[index]->pos().x(), item[index]->pos().y());
    m_scene->addItem(m_posSegmentData[index-1]);
    QObject::connect(m_posSegmentData[index-1], &MyLineItem::addNodeItem, this, &Curve::addNodeItem);
    m_posSegmentData[index] = new MyLineItem(m_posPointData[index]->pos().x(), m_posPointData[index]->pos().y(), m_posPointData[index+1]->pos().x(), m_posPointData[index+1]->pos().y(), index);
            //m_scene->addLine(item[index]->pos().x(), item[index]->pos().y(), item[index+1]->pos().x(), item[index+1]->pos().y());
    m_scene->addItem(m_posSegmentData[index]);
    QObject::connect(m_posSegmentData[index], &MyLineItem::addNodeItem, this, &Curve::addNodeItem);
    m_scene->update();

}

void Curve::addNodeItem(int index)
{
    int m_steelNum = m_posPointData.size();
    m_steelNum = m_steelNum +1;
    //double angle = 1.0*3.14*2/m_steelNum;
    int radius= getRadius();
    for (int var = 0; var < m_steelNum-1; ++var) {
        m_posPointData[var]->updateRadius(radius);
    }
    for (int i = m_steelNum-1; i > index+1; --i) {
        m_posPointData[i] = m_posPointData[i-1];
        m_posPointData[i]->setIndex(i);
    }
    // add item
    m_posPointData[index+1] = new MyItem(radius, RADIUS,index+1);
    double addNodeX = (m_posPointData[index]->pos().x() + m_posPointData[index+2]->pos().x())/2;
    double addNodeY = (m_posPointData[index]->pos().y() + m_posPointData[index+2]->pos().y())/2;
    m_posPointData[index+1]->setPos( addNodeX, addNodeY);
    m_posPointData[index+1]->setToolTip(QString::number(index+1));
    m_scene->addItem(m_posPointData[index+1]);
    QObject::connect(m_posPointData[index+1], &MyItem::posChanged, this, &Curve::posChanged);
    // add new line
    for (int i = m_steelNum-2; i > index; --i) {
        m_posSegmentData[i] = m_posSegmentData[i-1];
        m_posSegmentData[i]->setIndex(i);
    }
    m_scene->removeItem(m_posSegmentData[index]);
    //m_scene->removeItem(lineItem[index+1]);
    m_posSegmentData[index] = new MyLineItem(m_posPointData[index]->pos().x(), m_posPointData[index]->pos().y(), addNodeX, addNodeY, index);
    m_scene->addItem(m_posSegmentData[index]);
    QObject::connect(m_posSegmentData[index], &MyLineItem::addNodeItem, this, &Curve::addNodeItem);
    m_posSegmentData[index+1] = new MyLineItem(addNodeX, addNodeY, m_posPointData[index+2]->pos().x(), m_posPointData[index+2]->pos().y(), index+1);
    m_scene->addItem(m_posSegmentData[index+1]);
    QObject::connect(m_posSegmentData[index+1], &MyLineItem::addNodeItem, this, &Curve::addNodeItem);
    m_scene->update();//otherwise, some item will be erased
}
