#include "MainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "Key pressed: " + event->text();
    if(event->key() == Qt::Key_B){
        ui->openGLWidget->blender();
    } else if(event->key() == Qt::Key_L){
        ui->openGLWidget->turnOnOffLight();
    }

    else if(event->key() == Qt::Key_W){
            ui->openGLWidget->moveUp();
    } else if(event->key() == Qt::Key_S){
        ui->openGLWidget->moveBack();
    }else if(event->key() == Qt::Key_A){
        ui->openGLWidget->moveRight();
    } else if(event->key() == Qt::Key_D){
        ui->openGLWidget->moveLeft();
    }

}

