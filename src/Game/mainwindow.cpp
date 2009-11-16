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
