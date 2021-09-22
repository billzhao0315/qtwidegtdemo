#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "myitem.h"
#include "mylineitem.h"
#include "qaxis.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void on_spinBox_valueChanged(int num);
    void posChanged(int index);
    void addNodeItem(int index);

private:
    Ui::MainWindow *ui;
    MyItem *item[50];
    MyLineItem *lineItem[49];
    QAxis* m_axis;
    int m_steelNum;
    QGraphicsScene *m_scene;

};

#endif // MAINWINDOW_H
