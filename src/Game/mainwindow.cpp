#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "game.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->graphicsView->setScene(new Game());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    Game *scene =  static_cast<Game*>(ui->graphicsView->scene());
    QPointF pos = scene->marker->pos();
    if(pos.x() < 280){
        pos += QPointF(20.0,0.0);
        scene->marker->setPos(pos);
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    Game *scene =  static_cast<Game*>(ui->graphicsView->scene());
    QPointF pos = scene->marker->pos();
    if(pos.y() < 280){
        pos += QPointF(0.0,20.0);
        scene->marker->setPos(pos);
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    Game *scene =  static_cast<Game*>(ui->graphicsView->scene());
    QPointF pos = scene->marker->pos();
     if(pos.x() > 20){
        pos += QPointF(-20.0,0.0);
        scene->marker->setPos(pos);
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    Game *scene =  static_cast<Game*>(ui->graphicsView->scene());
    QPointF pos = scene->marker->pos();

    if(pos.y() > 20){
        pos += QPointF(0.0,-20.0);
        scene->marker->setPos(pos);
    }
}
