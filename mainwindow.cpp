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
#include<QDebug>

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

    m_axis = new QAxis(SCENEX, SCENEY, SCENEWidth, SCENEHEIGHT);
    {
        m_axis->setXValueRange(0, 255);
        m_axis->setYValueRange(0, 255);

        m_axis->setXLabels("0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10");
        m_axis->setYLabels("0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10");

        m_axis->setAutoScale("X", true);
        m_axis->setAutoScale("Y", true);

        m_axis->addCurve("testCurve", m_scene);
        m_axis->setGridShow(true);
        m_axis->addData("testCurve", 0, 0);
        m_axis->addData("testCurve", 30, 30);
        m_axis->addData("testCurve", 60, 60);
        m_axis->addData("testCurve", 90, 90);
        //m_axis->addData("testCurve", 120, 120);
    }
    m_scene->addItem(m_axis);
    on_spinBox_valueChanged(m_steelNum);
    QVector<MyItem*> posPointData = m_axis->getPosPointData("testCurve");
    for (int i = 0; i < posPointData.size(); ++i) {
        m_scene->addItem(posPointData[i]);
    }
    QVector<MyLineItem*> posSegmentData = m_axis->getPosSegmentData("testCurve");
    for (int i = 0; i < posSegmentData.size(); ++i) {
        m_scene->addItem(posSegmentData[i]);
    }
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
    //updateCurve();
    QMainWindow::resizeEvent(event);
}



void MainWindow::on_spinBox_valueChanged(int num)
{

//    if(num == 0)
//    {
//        return;
//    }
//    for(int i=0; i<m_steelNum; i++)
//    {
//        //init channel state
//        if(item[0] == NULL)
//            break;
//        m_scene->removeItem(item[i]);
//        delete item[i];
//    }
//    for(int i=0; i<m_steelNum -1; i++)
//    {
//        //init channel state
//        if(item[0] == NULL)
//            break;
//        m_scene->removeItem(lineItem[i]);
//        //delete item[i];
//    }

//    m_steelNum = num;

//    //double angle = 1.0*3.14*2/m_steelNum;
//    int radius= getRadius();

//    qreal widthSpace = (SCENEWidth-radius*2)/(m_steelNum-1);
//    qreal heightSpace = (SCENEHEIGHT-radius*2)/(m_steelNum-1);
//    qreal startPointX = SCENEX+radius;
//    qreal startPointY = SCENEY+radius;
//    for(int i=0; i<m_steelNum; i++)
//    {
//        item[i] = new MyItem(radius, RADIUS,i);
////        qreal itemX = startPointX+ widthSpace*i;
////        qreal itemY = (startPointY+heightSpace*i);
//        qreal itemX = i*30;
//        qreal itemY = i*30;
//        QPointF point = m_axis->mapToAxis(itemX, itemY);
//        qDebug()<<"item point"<<point;
//        item[i]->setPos(point);
//        item[i]->setToolTip(QString::number(i));
//        m_scene->addItem(item[i]);
//        QObject::connect(item[i], &MyItem::posChanged, this, &MainWindow::posChanged);
//    }
//    for(int i=0; i<m_steelNum-1; i++)
//    {
//        lineItem[i] = new MyLineItem(item[i]->pos().x(), item[i]->pos().y(), item[i+1]->pos().x(), item[i+1]->pos().y(), i);
//                //m_scene->addLine(item[i]->pos().x(), item[i]->pos().y(), item[i+1]->pos().x(), item[i+1]->pos().y());
//        m_scene->addItem( lineItem[i] );
//        QObject::connect(lineItem[i], &MyLineItem::addNodeItem, this, &MainWindow::addNodeItem);
//    }

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
void MainWindow::updateCurve()
{
//    for (int i = 0; i < m_steelNum; ++i) {
//        qreal itemX = i*30;
//        qreal itemY = i*30;
//        QPointF point = m_axis->mapToAxis(itemX, itemY);
//        item[i]->setPos(point);
//    }
//    for(int i=0; i<m_steelNum-1; i++)
//    {
//        m_scene->removeItem(lineItem[i]);
//        lineItem[i] = new MyLineItem(item[i]->pos().x(), item[i]->pos().y(), item[i+1]->pos().x(), item[i+1]->pos().y(), i);
//                //m_scene->addLine(item[i]->pos().x(), item[i]->pos().y(), item[i+1]->pos().x(), item[i+1]->pos().y());
//        m_scene->addItem( lineItem[i] );
//        QObject::connect(lineItem[i], &MyLineItem::addNodeItem, this, &MainWindow::addNodeItem);
//    }
    //m_scene->update();
}
