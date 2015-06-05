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
    } else if(event->key() == Qt::Key_F){
        if(++currentFiler >= 3){
            currentFiler =0;
        }
        qDebug() << "Filter: " << currentFiler;
        ui->openGLWidget->setFilter(currentFiler);
    } else if(event->key() == Qt::Key_G){
        if(event->modifiers() == Qt::CTRL){
            ui->openGLWidget->changeFogMode();
            return;
        }
        ui->openGLWidget->setFog();
    }

    else if(event->key() == Qt::Key_W){
        if(cameraAuto) return;
        ui->openGLWidget->moveUp();
    } else if(event->key() == Qt::Key_S){
        if(cameraAuto) return;
        ui->openGLWidget->moveBack();
    }else if(event->key() == Qt::Key_A){
        if(cameraAuto) return;
        ui->openGLWidget->moveRight();
    } else if(event->key() == Qt::Key_D){
        if(cameraAuto) return;
        ui->openGLWidget->moveLeft();
    }

    else if(event->key() == Qt::Key_Space){
        cameraAuto = !cameraAuto;
        ui->openGLWidget->chnageCamera(cameraAuto);
    }

    else if(event->key() == Qt::Key_Plus){
        ui->openGLWidget->speedUp();
    }
    else if(event->key() == Qt::Key_Minus){
        ui->openGLWidget->speedDown();
    }
}

