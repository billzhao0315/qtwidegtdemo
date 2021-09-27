#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <math.h>

#include<QLabel>
#include<QVBoxLayout>
#include<QLineEdit>
#include<QTreeWidget>

#define RADIUS 100
#define SCENEX 0
#define SCENEY 0
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
    m_axis = new QAxis(SCENEX, SCENEY, SCENEWidth, SCENEHEIGHT);
    {
        m_axis->setXValueRange(0, 10);
        m_axis->setYValueRange(0, 10);

        m_axis->setXLabels("0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10");
        m_axis->setYLabels("0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10");

        m_axis->setAutoScale("X", true);
        m_axis->setAutoScale("Y", true);

        m_axis->addCurve("testCurve");
        m_axis->setGridShow(true);
        m_axis->addData("testCurve", 0, 0);
        m_axis->addData("testCurve", 2, 2);
        m_axis->addData("testCurve", 5, 3);
    }
    m_scene->addItem(m_axis);
    m_view = new MyQGraphicsView(m_scene);
    m_view->show();
    m_view->setToolTip("view test");
    qDebug()<<"view size"<<m_view->geometry();
    //ui->verticalLayout->addWidget(m_view);

    //
    mainWindowWidget=new QWidget(this);
    mainRightWidget = new QWidget(this);
    vlayout_right = new QVBoxLayout(this);
    hlayout_all = new QHBoxLayout(this);
    vlayout_right->addWidget(m_view);
    vlayout_right->setStretchFactor(m_view, 1);
    mainRightWidget->setLayout(vlayout_right);
    hlayout_all->addWidget(mainRightWidget);
    hlayout_all->setStretchFactor(mainRightWidget,1);

    mainWindowWidget->setLayout(hlayout_all);

    setCentralWidget(mainWindowWidget);//将mainWindowWidget设置为主窗口的中心窗口
    //m_scene->setSceneRect(0,0,m_view->size().width(), m_view->size().height());
    //m_axis->setAxisSize(m_view->size().width(), m_view->size().height());
    //resize(600,600);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
//    qDebug()<<"windows size"<<size();
//    qDebug()<<"view geometry size"<<m_view->geometry();
      //qDebug()<<"view size"<<m_view->size();
      //qDebug()<<"scene size"<<m_scene->sceneRect();
//    //m_view->resize(size().width()-50, size().height()-50);
//    m_scene->setSceneRect(0,0, m_view->size().width(), m_view->size().height());
    //ui->verticalLayout->setGeometry(QRect(0,0, m_view->size().width(), m_view->size().height()));
    //qDebug()<<"ver"<<ui->verticalLayout->geometry();
    m_scene->setSceneRect(-30,-10,m_view->size().width()-30, m_view->size().height()-20);
    m_axis->setAxisSize(m_view->size().width()-30, m_view->size().height()-20);
    //item[m_steelNum-1]->setPos(m_view->size().width()-60, m_view->size().height()-50);
    QMainWindow::resizeEvent(event);
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
    m_scene->update();
}

void MainWindow::addNodeItem(int index)
{
    m_steelNum = m_steelNum +1;
    //double angle = 1.0*3.14*2/m_steelNum;
    int radius= getRadius();
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
    m_scene->update();//otherwise, some item will be erased
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
    int radius= getRadius();

    qreal widthSpace = (SCENEWidth-radius*2)/(m_steelNum-1);
    qreal heightSpace = (SCENEHEIGHT-radius*2)/(m_steelNum-1);
    qreal startPointX = SCENEX+radius;
    qreal startPointY = SCENEY+radius;
    for(int i=0; i<m_steelNum; i++)
    {
        item[i] = new MyItem(radius, RADIUS,i);
        item[i]->setPos(startPointX+ widthSpace*i, (startPointY+heightSpace*i));
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

int MainWindow::getRadius()
{
    int radius;

    //set radius value
    if(m_steelNum<7)
        radius = 15;
    else if(m_steelNum<11)
        radius = 10;
    else
        radius = 15;
    return radius;
}
