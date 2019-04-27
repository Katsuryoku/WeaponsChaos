#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QPixmap>
#include <QDebug>
#include <QKeyEvent>


using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    webCam_=new VideoCapture(0);
    double width=webCam_->get(CV_CAP_PROP_FRAME_WIDTH);
    double height=webCam_->get(CV_CAP_PROP_FRAME_HEIGHT);
    webCam_->set(CV_CAP_PROP_FRAME_WIDTH,width);
    webCam_->set(CV_CAP_PROP_FRAME_HEIGHT,height);

    if(!webCam_->isOpened())  // check if we succeeded
    {
        ui->infoLabel->setText("Error openning the default camera !");
    }





    QTimer* q  = new QTimer(this);
    connect(q, SIGNAL(timeout()), this, SLOT(capture()));
    connect(q, SIGNAL(timeout()), this, SLOT(process()));
    connect(q, SIGNAL(timeout()), this, SLOT(affiche()));
    connect(this,SIGNAL(rotation()),this,SLOT(latence()));
    connect(this,SIGNAL(right()),this,SLOT(latence()));
    connect(this,SIGNAL(left()),this,SLOT(latence()));


    q->start(100);



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::capture(){
    Mat frame,frame_gray;
    // Get frame
    *webCam_ >> frame;
    // Mirror effect
    cv::flip(frame,frame,1);
    // Convert to gray
    cv::cvtColor(frame,frame_gray,COLOR_BGR2GRAY);
    // Equalize graylevels
//        equalizeHist( frame_gray, frame_gray );

    fileFrame.push(frame);
}

void MainWindow::affiche(){
    if(!fileQPix.empty()){
        QPixmap pix = fileQPix.front();
        fileQPix.pop();
        ui->webcamWindow->setPixmap(pix);
    }
}

void MainWindow::process(){
    if(!fileFrame.empty()){
        Mat f = fileFrame.front();
        fileFrame.pop();
        cvtColor(f,f,CV_BGR2RGB);
        QPixmap pix = QPixmap::fromImage(QImage((unsigned char*) f.data, f.cols, f.rows, QImage::Format_RGB888));
        fileQPix.push(pix);
    }

}

void MainWindow::report(QString s){
    ui->infoLabel->setText(s);
}

void MainWindow::latence(){
    lat=true;
    fistsDetected=false;
    QTimer::singleShot(500, this, SLOT(reprise()));
}



void MainWindow::reprise(){
    lat=false;
}



void MainWindow::keyPressEvent(QKeyEvent* event){

    switch(event->key()){

        case Qt::Key_Left :
            emit left();
        break;
        case Qt::Key_Right :
            emit right();
        break;
        case Qt::Key_Up :
            emit rotation();
        break;

    }
}



void MainWindow::quit(){

    close();


}

