#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <math.h>

#define RADIUS 100
#define SCENEX -200
#define SCENEY -200
#define SCENEWidth 400
#define SCENEHEIGHT 400

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //m_scene = new QGraphicsScene();
    //m_scene = new QGraphicsScene(-50, -50, 100, 100);
    m_scene = new QGraphicsScene(SCENEX, SCENEY, SCENEWidth, SCENEHEIGHT);

    //m_scene->addEllipse(-100, -100, 200, 200);

    m_steelNum = ui->spinBox->value();

    item[0] = NULL;
    lineItem[0] = NULL;
    on_spinBox_valueChanged(m_steelNum);

    QGraphicsView *view = new QGraphicsView(m_scene);

    view->show();

    ui->verticalLayout->addWidget(view);
    //resize(600,600);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::posChanged(int index)
{
    if(m_steelNum <1) return;
    if(index ==0)
    {
        m_scene->removeItem( lineItem[0] );
        lineItem[0] = new MyLineItem(item[0]->pos().x(), item[0]->pos().y(), item[1]->pos().x(), item[1]->pos().y(), 0);
                //m_scene->addLine(item[0]->pos().x(), item[0]->pos().y(), item[1]->pos().x(), item[1]->pos().y());
        m_scene->addItem(lineItem[0]);
        QObject::connect(lineItem[0], &MyLineItem::addNodeItem, this, &MainWindow::addNodeItem);
        return;
    }
    if(index == m_steelNum-1)
    {
        m_scene->removeItem( lineItem[m_steelNum-2] );
        lineItem[m_steelNum-2] = new MyLineItem(item[m_steelNum-2]->pos().x(), item[m_steelNum-2]->pos().y(), item[m_steelNum-1]->pos().x(), item[m_steelNum-1]->pos().y(), m_steelNum-2);
                //m_scene->addLine(item[m_steelNum-2]->pos().x(), item[m_steelNum-2]->pos().y(), item[m_steelNum-1]->pos().x(), item[m_steelNum-1]->pos().y());
        m_scene->addItem(lineItem[m_steelNum-2]);
        QObject::connect(lineItem[m_steelNum-2], &MyLineItem::addNodeItem, this, &MainWindow::addNodeItem);
        return;
    }
    m_scene->removeItem( lineItem[index-1] );
    m_scene->removeItem( lineItem[index] );
    lineItem[index-1] = new MyLineItem(item[index-1]->pos().x(), item[index-1]->pos().y(), item[index]->pos().x(), item[index]->pos().y(), index-1);
            //m_scene->addLine(item[index-1]->pos().x(), item[index-1]->pos().y(), item[index]->pos().x(), item[index]->pos().y());
    m_scene->addItem(lineItem[index-1]);
    QObject::connect(lineItem[index-1], &MyLineItem::addNodeItem, this, &MainWindow::addNodeItem);
    lineItem[index] = new MyLineItem(item[index]->pos().x(), item[index]->pos().y(), item[index+1]->pos().x(), item[index+1]->pos().y(), index);
            //m_scene->addLine(item[index]->pos().x(), item[index]->pos().y(), item[index+1]->pos().x(), item[index+1]->pos().y());
    m_scene->addItem(lineItem[index]);
    QObject::connect(lineItem[index], &MyLineItem::addNodeItem, this, &MainWindow::addNodeItem);
}

void MainWindow::addNodeItem(int index)
{
    m_steelNum = m_steelNum +1;
    //double angle = 1.0*3.14*2/m_steelNum;
    int radius;

    //set radius value
    if(m_steelNum<7)
        radius = 15;
    else if(m_steelNum<11)
        radius = 10;
    else
        radius = 15;
    for (int var = 0; var < m_steelNum-1; ++var) {
        item[var]->updateRadius(radius);
    }
    for (int i = m_steelNum-1; i > index+1; --i) {
        item[i] = item[i-1];
        item[i]->setIndex(i);
    }
    // add item
    item[index+1] = new MyItem(radius, RADIUS,index+1);
    double addNodeX = (item[index]->pos().x() + item[index+2]->pos().x())/2;
    double addNodeY = (item[index]->pos().y() + item[index+2]->pos().y())/2;
    item[index+1]->setPos( addNodeX, addNodeY);
    item[index+1]->setToolTip(QString::number(index+1));
    m_scene->addItem(item[index+1]);
    QObject::connect(item[index+1], &MyItem::posChanged, this, &MainWindow::posChanged);
    // add new line
    for (int i = m_steelNum-2; i > index; --i) {
        lineItem[i] = lineItem[i-1];
        lineItem[i]->setIndex(i);
    }
    m_scene->removeItem(lineItem[index]);
    //m_scene->removeItem(lineItem[index+1]);
    lineItem[index] = new MyLineItem(item[index]->pos().x(), item[index]->pos().y(), addNodeX, addNodeY, index);
    m_scene->addItem(lineItem[index]);
    QObject::connect(lineItem[index], &MyLineItem::addNodeItem, this, &MainWindow::addNodeItem);
    lineItem[index+1] = new MyLineItem(addNodeX, addNodeY, item[index+2]->pos().x(), item[index+2]->pos().y(), index+1);
    m_scene->addItem(lineItem[index+1]);
    QObject::connect(lineItem[index+1], &MyLineItem::addNodeItem, this, &MainWindow::addNodeItem);
}

void MainWindow::on_spinBox_valueChanged(int num)
{
    if(num == 0)
    {
        return;
    }
    for(int i=0; i<m_steelNum; i++)
    {
        //init channel state
        if(item[0] == NULL)
            break;
        m_scene->removeItem(item[i]);
        delete item[i];
    }
    for(int i=0; i<m_steelNum -1; i++)
    {
        //init channel state
        if(item[0] == NULL)
            break;
        m_scene->removeItem(lineItem[i]);
        //delete item[i];
    }

    m_steelNum = num;

    //double angle = 1.0*3.14*2/m_steelNum;
    int radius;

    //set radius value
    if(m_steelNum<7)
        radius = 15;
    else if(m_steelNum<11)
        radius = 10;
    else
        radius = 15;

    if(m_steelNum == 1)
    {
        item[0] = new MyItem(radius, RADIUS, 0);
        item[0]->setPos(0, 0);
        item[0]->setToolTip(QString::number(0));
        m_scene->addItem(item[0]);
        return;
    }

    qreal widthSpace = (SCENEWidth-radius*2)/(m_steelNum-1);
    qreal heightSpace = (SCENEHEIGHT-radius*2)/(m_steelNum-1);
    qreal startPointX = SCENEX+radius;
    qreal startPointY = SCENEY+radius;
    for(int i=0; i<m_steelNum; i++)
    {
        item[i] = new MyItem(radius, RADIUS,i);
        item[i]->setPos(startPointX+ widthSpace*i, -(startPointY+heightSpace*i));
        item[i]->setToolTip(QString::number(i));
        m_scene->addItem(item[i]);
        QObject::connect(item[i], &MyItem::posChanged, this, &MainWindow::posChanged);
    }
    for(int i=0; i<m_steelNum-1; i++)
    {
        lineItem[i] = new MyLineItem(item[i]->pos().x(), item[i]->pos().y(), item[i+1]->pos().x(), item[i+1]->pos().y(), i);
                //m_scene->addLine(item[i]->pos().x(), item[i]->pos().y(), item[i+1]->pos().x(), item[i+1]->pos().y());
        m_scene->addItem( lineItem[i] );
        QObject::connect(lineItem[i], &MyLineItem::addNodeItem, this, &MainWindow::addNodeItem);
    }

}
