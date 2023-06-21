#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <QTimer>
#include <QFileInfo>

bool fileExists(std::string path) {
    QFileInfo check_file(QString::fromStdString(path));
    // check if file exists and if yes: Is it really a file and no directory?
    if (check_file.exists() && check_file.isFile()) {
        return true;
    } else {
        return false;
    }
}

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    myTimer = new QTimer(this);
    myTimer->setInterval(2000);
    myTimer->setSingleShot(false);
    connect(myTimer, SIGNAL(timeout()), this, SLOT(on_rightArrow_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_rightArrow_clicked()
{
    currentImage++;
    std::string imagePath = "C:/Users/dasha/CLionProjects/Computer-graphics/Extra_Tests/PSE/test/" + std::to_string(currentImage) + ".bmp";
    if(!fileExists(imagePath)) {
        currentImage--;
        this->myTimer->stop();
        ui->pushButton->setText("Start");
        return;
    }
    QPixmap pixmap(imagePath.c_str());
    ui->label->setPixmap(pixmap);
    ui->label->setScaledContents( true );
    ui->label->show();
}


void MainWindow::on_leftArrow_clicked()
{
    if(currentImage <= 1) return;
    currentImage--;
    std::string imagePath = "C:/Users/dasha/CLionProjects/Computer-graphics/Extra_Tests/PSE/test/" + std::to_string(currentImage) + ".bmp";
    QPixmap pixmap(imagePath.c_str());
    ui->label->setPixmap(pixmap);
    ui->label->setScaledContents( true );
    ui->label->show();
}


void MainWindow::on_pushButton_clicked()
{
    if ( this->myTimer->isActive() == true ) {
        this->myTimer->stop();
        ui->pushButton->setText("Start");
    } else {
        this->myTimer->start(2000);
        ui->pushButton->setText("Stop");
    }
}