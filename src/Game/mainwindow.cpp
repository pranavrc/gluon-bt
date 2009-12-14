#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "game.h"
#include "scenarioset.h"
#include "scenario.h"
#include <QGLWidget>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   // ui->graphicsView->setViewport(new QGLWidget());
    ui->graphicsView->setScene(new Game(this));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    Game *scene =  static_cast<Game*>(ui->graphicsView->scene());
    scene->marker->goRight();
}

void MainWindow::on_pushButton_2_clicked()
{
    Game *scene =  static_cast<Game*>(ui->graphicsView->scene());
    scene->marker->goDown();
}

void MainWindow::on_pushButton_4_clicked()
{
    Game *scene =  static_cast<Game*>(ui->graphicsView->scene());
    scene->marker->goLeft();
}

void MainWindow::on_pushButton_3_clicked()
{
    Game *scene =  static_cast<Game*>(ui->graphicsView->scene());
    scene->marker->goUp();
}

void MainWindow::on_pushButton_5_clicked()
{
    Game *scene =  static_cast<Game*>(ui->graphicsView->scene());
    scene->reset();
}


void MainWindow::on_pushButton_7_clicked()
{
    Game *scene =  static_cast<Game*>(ui->graphicsView->scene());
#warning skal laves om så værdierne gemmes
    ui->interest->setText( QString("%1").arg(scene->ss->calculateInterest()) );
    ui->interest_2->setText(QString("%1").arg(scene->ss->calculateChallengeLevel()));
    ui->interest_3->setText(QString("%1").arg(scene->ss->calculateBehavioralDiversity()));
    ui->interest_4->setText(QString("%1").arg(scene->ss->calculateSpatialDiversity()));
}

void MainWindow::takeScreenshot(int counter)
{
    QPixmap::grabWindow(ui->graphicsView->winId()).save(QString("game%1.png").arg(QString("%1").arg(counter),5,'0'));
}

#include "mainwindow.moc"
