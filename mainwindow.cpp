#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <opencv2/opencv.hpp>
#include <QFileDialog>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <string.h>
#include <opencv2/core/types_c.h>
using namespace cv ;
using namespace std;

void detectAndDraw( Mat& img, CascadeClassifier& cascade,
                    CascadeClassifier& nestedCascade,
                    double scale)
{
    vector<Rect> faces, faces2;
    Mat gray, smallImg;

    cv::cvtColor( img, gray, COLOR_BGR2GRAY ); // Convert to Gray Scale
    double fx = 1 / scale;

    // Resize the Grayscale Image
    resize( gray, smallImg, Size(), fx, fx, INTER_LINEAR );
    equalizeHist( smallImg, smallImg );

    // Detect faces of different sizes using cascade classifier
    cascade.detectMultiScale( smallImg, faces, 1.1,
                            2, 0|CASCADE_SCALE_IMAGE, Size(30, 30) );

    // Draw circles around the faces
    for ( size_t i = 0; i < faces.size(); i++ )
    {
        Rect r = faces[i];
        Mat smallImgROI;
        vector<Rect> nestedObjects;
        Point center;
        Scalar color = Scalar(255, 0, 0); // Color for Drawing tool
        int radius;

        double aspect_ratio = (double)r.width/r.height;
        if( 0.75 < aspect_ratio && aspect_ratio < 1.3 )
        {
            center.x = cvRound((r.x + r.width*0.5)*scale);
            center.y = cvRound((r.y + r.height*0.5)*scale);
            radius = cvRound((r.width + r.height)*0.25*scale);
            circle( img, center, radius, color, 3, 8, 0 );
        }
        else
            rectangle( img, cvPoint(cvRound(r.x*scale), cvRound(r.y*scale)),
                    cvPoint(cvRound((r.x + r.width-1)*scale),
                    cvRound((r.y + r.height-1)*scale)), color, 3, 8, 0);
        if( nestedCascade.empty() )
            continue;
        smallImgROI = smallImg( r );

        // Detection of eyes int the input image
        nestedCascade.detectMultiScale( smallImgROI, nestedObjects, 1.1, 2,
                                        0|CASCADE_SCALE_IMAGE, Size(30, 30) );

        // Draw circles around eyes
        for ( size_t j = 0; j < nestedObjects.size(); j++ )
        {
            Rect nr = nestedObjects[j];
            center.x = cvRound((r.x + nr.x + nr.width*0.5)*scale);
            center.y = cvRound((r.y + nr.y + nr.height*0.5)*scale);
            radius = cvRound((nr.width + nr.height)*0.25*scale);
            circle( img, center, radius, color, 3, 8, 0 );
        }
    }

    // Show Processed Image with detected faces
    imshow( "Face Detection", img );
}
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->horizontalSlider->setRange(1,50);
    historyNum=0;
    filterNum1=1;
    filterNum2=1;
    filterNum3=1;
    filterNum4=1;
    filterNum5=1;
    ui->action_3->setDisabled(1);
    ui->pushButton->setDisabled(true);
    ui->pushButton_2->setDisabled(true);
    ui->pushButton_3->setDisabled(true);
    ui->pushButton_4->setDisabled(true);
    ui->pushButton_5->setDisabled(true);
    ui->pushButton_6->setDisabled(true);
    ui->pushButton_7->setDisabled(true);
    ui->pushButton_8->setDisabled(true);
    ui->pushButton_9->setDisabled(true);
    ui->pushButton_10->setDisabled(true);
    ui->pushButton_11->setDisabled(true);
    ui->pushButton_12->setDisabled(true);
    ui->pushButton_13->setDisabled(true);
    ui->pushButton_14->setDisabled(true);
    ui->pushButton_15->setDisabled(true);
    f1 = false;
    f2 = false;
    f3 = false;
    f4 = false;
    f5 = false;
    f6 = false;
    f7 = false;
    f8 = false;
    f9 = false;
    f10 = false;
    f11 = false;
    edit=false;
    gs=false;
    ui->horizontalSlider->setEnabled(edit);
    ui->confirm->setEnabled(false);
    ui->action_2->setEnabled(false);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_triggered()
{



        w = ui->label->width();
        h = ui->label->height();
        filePath = QFileDialog::getOpenFileName(this, tr("Open Data"), "C:/Users/ted01/Desktop/PASSPORT.jpg", tr("(*.jpg)"));
        filep = filePath.toLocal8Bit().constData();

        QFile file(filePath);
        if(file.open(QIODevice::ReadOnly)){
            img= cv::imread(filep);
            history.push_back(img.clone());
            img2=img.clone();
            ui->pushButton->setDisabled(false);
            ui->pushButton_2->setDisabled(false);
            ui->pushButton_3->setDisabled(false);
            ui->pushButton_4->setDisabled(false);
            ui->pushButton_5->setDisabled(false);
            ui->pushButton_6->setDisabled(false);
            ui->pushButton_7->setDisabled(false);
            ui->pushButton_8->setDisabled(false);
            ui->pushButton_9->setDisabled(false);
            ui->pushButton_10->setDisabled(false);
            ui->pushButton_11->setDisabled(false);
            ui->pushButton_12->setDisabled(false);
            ui->pushButton_13->setDisabled(false);
            ui->pushButton_14->setDisabled(false);
            ui->pushButton_15->setDisabled(false);
            ui->action->setDisabled(1);
            ui->action_3->setDisabled(0);
            ui->label->setPixmap(QPixmap::fromImage(QImage(history[historyNum].data,
                                                           history[historyNum].cols,
                                                           history[historyNum].rows,
                                                           history[historyNum].step,
                                                           QImage::Format_RGB888)));
        }
        else {
            QMessageBox::warning(this, "WARNING","READ FAILED");
        }

}



void MainWindow::on_pushButton_clicked()
{
    f1=true;
    f2=0;
    f3=0;
    f4=0;
    f5=0;
    f6 = false;
    f7 = false;
    f8 = false;
    f9=0;
    f10=0;
    f11=0;
    edit=true;
    ui->horizontalSlider->setEnabled(edit);
    ui->pushButton->setDisabled(true);
    ui->pushButton_2->setDisabled(true);
    ui->pushButton_3->setDisabled(true);
    ui->pushButton_4->setDisabled(true);
    ui->pushButton_5->setDisabled(true);
    ui->pushButton_6->setDisabled(true);
    ui->pushButton_7->setDisabled(true);
    ui->pushButton_8->setDisabled(true);
    ui->pushButton_9->setDisabled(true);
    ui->pushButton_10->setDisabled(true);
    ui->pushButton_11->setDisabled(true);
    ui->pushButton_12->setDisabled(true);
    ui->pushButton_13->setDisabled(true);
    ui->pushButton_14->setDisabled(true);
    ui->pushButton_15->setDisabled(true);

}

void MainWindow::on_pushButton_2_clicked()
{
    f2=true;
    f3=0;
    f4=0;
    f5=0;
    f1=0;
    f6 = false;
    f7 = false;
    f8 = false;
    f9=0;
    f10=0;
    f11=0;
    edit=true;
    ui->horizontalSlider->setEnabled(edit);
    ui->pushButton->setDisabled(true);
    ui->pushButton_2->setDisabled(true);
    ui->pushButton_3->setDisabled(true);
    ui->pushButton_4->setDisabled(true);
    ui->pushButton_5->setDisabled(true);
    ui->pushButton_6->setDisabled(true);
    ui->pushButton_7->setDisabled(true);
    ui->pushButton_8->setDisabled(true);
    ui->pushButton_9->setDisabled(true);
    ui->pushButton_10->setDisabled(true);
    ui->pushButton_11->setDisabled(true);
    ui->pushButton_12->setDisabled(true);
    ui->pushButton_13->setDisabled(true);
    ui->pushButton_14->setDisabled(true);
    ui->pushButton_15->setDisabled(true);
}

void MainWindow::on_pushButton_3_clicked()
{
    f3=true;
    f1=0;
    f2=0;
    f4=0;
    f5=0;
    f6 = false;
    f7 = false;
    f8 = false;
    f9=0;
    f10=0;
    f11=0;
    edit=true;
    ui->horizontalSlider->setEnabled(edit);
    ui->pushButton->setDisabled(true);
    ui->pushButton_2->setDisabled(true);
    ui->pushButton_3->setDisabled(true);
    ui->pushButton_4->setDisabled(true);
    ui->pushButton_5->setDisabled(true);
    ui->pushButton_6->setDisabled(true);
    ui->pushButton_7->setDisabled(true);
    ui->pushButton_8->setDisabled(true);
    ui->pushButton_9->setDisabled(true);
    ui->pushButton_10->setDisabled(true);
    ui->pushButton_11->setDisabled(true);
    ui->pushButton_12->setDisabled(true);
    ui->pushButton_13->setDisabled(true);
    ui->pushButton_14->setDisabled(true);
    ui->pushButton_15->setDisabled(true);
}

void MainWindow::on_pushButton_4_clicked()
{
    f4=true;
    f3=0;
    f1=0;
    f2=0;
    f5=0;
    f6 = false;
    f7 = false;
    f8 = false;
    f9=0;
    f10=0;
    f11=0;
    edit=true;
    ui->horizontalSlider->setEnabled(edit);
    ui->pushButton->setDisabled(true);
    ui->pushButton_2->setDisabled(true);
    ui->pushButton_3->setDisabled(true);
    ui->pushButton_4->setDisabled(true);
    ui->pushButton_5->setDisabled(true);
    ui->pushButton_6->setDisabled(true);
    ui->pushButton_7->setDisabled(true);
    ui->pushButton_8->setDisabled(true);
    ui->pushButton_9->setDisabled(true);
    ui->pushButton_10->setDisabled(true);
    ui->pushButton_11->setDisabled(true);
    ui->pushButton_12->setDisabled(true);
    ui->pushButton_13->setDisabled(true);
    ui->pushButton_14->setDisabled(true);
    ui->pushButton_15->setDisabled(true);
}

void MainWindow::on_pushButton_5_clicked()
{
    f5=true;
    f3=0;
    f4=0;
    f1=0;
    f2=0;
    f6 = false;
    f7 = false;
    f8 = false;
    f9=0;
    f10=0;
    f11=0;
    edit=true;
    ui->horizontalSlider->setEnabled(edit);
    ui->pushButton->setDisabled(true);
    ui->pushButton_2->setDisabled(true);
    ui->pushButton_3->setDisabled(true);
    ui->pushButton_4->setDisabled(true);
    ui->pushButton_5->setDisabled(true);
    ui->pushButton_6->setDisabled(true);
    ui->pushButton_7->setDisabled(true);
    ui->pushButton_8->setDisabled(true);
    ui->pushButton_9->setDisabled(true);
    ui->pushButton_10->setDisabled(true);
    ui->pushButton_11->setDisabled(true);
    ui->pushButton_12->setDisabled(true);
    ui->pushButton_13->setDisabled(true);
    ui->pushButton_14->setDisabled(true);
    ui->pushButton_15->setDisabled(true);
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    ui->confirm->setEnabled(true);
    img2=img.clone();

    if(f1){
        ui->lcdNumber->display(position*2+1);
        filterNum1=position*2+1;


        cv::blur( img, img2,cv::Size(filterNum1,filterNum1));

        ui->label->setPixmap(QPixmap::fromImage(cvMat2QImage(img2)).scaled(w,h,Qt::KeepAspectRatio));
    }
    else if (f2) {
        ui->lcdNumber->display(position*2+1);
        filterNum2=position*2+1;
        cv::GaussianBlur( img, img2,cv::Size(filterNum2,filterNum2),0);
        ui->label->setPixmap(QPixmap::fromImage(cvMat2QImage(img2)).scaled(w,h,Qt::KeepAspectRatio));
    }
    else if (f3) {
        ui->lcdNumber->display(position*2+1);
        filterNum3=position*2+1;
        cv::medianBlur( img, img2,filterNum3);
        ui->label->setPixmap(QPixmap::fromImage(cvMat2QImage(img2)).scaled(w,h,Qt::KeepAspectRatio));
    }
    else if (f4) {
        ui->lcdNumber->display(position*2+1);
        filterNum4=position*2+1;

        cv::bilateralFilter ( img, img2, filterNum4, filterNum4*2, filterNum4/2 );
        ui->label->setPixmap(QPixmap::fromImage(cvMat2QImage(img2)).scaled(w,h,Qt::KeepAspectRatio));
    }
    else if (f5){
        ui->lcdNumber->display(position);
        filterNum5=position;
        cv::Mat sharpeningKernel = (cv::Mat_<double>(filterNum5,filterNum5) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
        filter2D(img, img2, -1, sharpeningKernel);

        ui->label->setPixmap(QPixmap::fromImage(cvMat2QImage(img2)).scaled(w,h,Qt::KeepAspectRatio));
    }
    else if(filep==""){
        QMessageBox::warning(this, "WARNING","NO FILE IS EDITING");

    }
    else if (f6) {

        for(int i=0;i<img.rows;i++){
            for (int j=0;j<img.cols;j++) {
                int pix = img.at<Vec3b>(i,j)[2];
                if( pix + position >255){
                    img2.at<Vec3b>(i,j)[2]=255;
                }
                else if (pix + position < 0) {
                    img2.at<Vec3b>(i,j)[2]=0;
                }
                else {
                    img2.at<Vec3b>(i,j)[2]=pix + position;
                }
            }
        }
        ui->label->setPixmap(QPixmap::fromImage(cvMat2QImage(img2)).scaled(w,h,Qt::KeepAspectRatio));
    }
    else if (f7) {

        for(int i=0;i<img.rows;i++){
            for (int j=0;j<img.cols;j++) {
                int pix = img.at<cv::Vec3b>(i,j)[1];
                if( pix + position >255){
                    img2.at<cv::Vec3b>(i,j)[1]=255;
                }
                else if (pix + position < 0) {
                    img2.at<cv::Vec3b>(i,j)[1]=0;
                }
                else {
                    img2.at<cv::Vec3b>(i,j)[1]=pix + position;
                }
            }
        }
        ui->label->setPixmap(QPixmap::fromImage(cvMat2QImage(img2)).scaled(w,h,Qt::KeepAspectRatio));
    }
    else if (f8) {

        for(int i=0;i<img.rows;i++){
            for (int j=0;j<img.cols;j++) {
                int pix = img.at<cv::Vec3b>(i,j)[0];
                if( pix + position >255){
                    img2.at<cv::Vec3b>(i,j)[0]=255;
                }
                else if (pix + position < 0) {
                    img2.at<cv::Vec3b>(i,j)[0]=0;
                }
                else {
                    img2.at<cv::Vec3b>(i,j)[0]=pix + position;
                }
            }
        }
        ui->label->setPixmap(QPixmap::fromImage(cvMat2QImage(img2)).scaled(w,h,Qt::KeepAspectRatio));
    }
    else if (f9) {
        cvtColor(img,img,COLOR_BGR2HSV);
        cvtColor(img2,img2,COLOR_BGR2HSV);
        for (int i=0;i<img.cols;i++) {
            for (int j=0;j<img.rows;j++) {
                int pix = img.at<Vec3b>(j,i).val[0];
                if( pix + position >180){
                    img2.at<Vec3b>(j,i).val[0]=180;
                }
                else if (pix + position < 0) {
                    img2.at<Vec3b>(j,i).val[0]=0;
                }
                else {
                    img2.at<Vec3b>(j,i).val[0]=pix + position;
                }
            }
        }
        cvtColor(img,img,COLOR_HSV2BGR);
        cvtColor(img2,img2,COLOR_HSV2BGR);
        ui->label->setPixmap(QPixmap::fromImage(cvMat2QImage(img2)).scaled(w,h,Qt::KeepAspectRatio));
    }
    else if (f10) {
        cvtColor(img,img,COLOR_BGR2HSV);
        cvtColor(img2,img2,COLOR_BGR2HSV);
        for (int i=0;i<img.cols;i++) {
            for (int j=0;j<img.rows;j++) {
                int pix = img.at<Vec3b>(j,i).val[1];
                if( pix + position >255){
                    img2.at<Vec3b>(j,i).val[1]=255;
                }
                else if (pix + position < 1) {
                    img2.at<Vec3b>(j,i).val[1]=1;
                }
                else {
                    img2.at<Vec3b>(j,i).val[1]=pix + position;
                }
            }
        }
        cvtColor(img,img,COLOR_HSV2BGR);
        cvtColor(img2,img2,COLOR_HSV2BGR);
        ui->label->setPixmap(QPixmap::fromImage(cvMat2QImage(img2)).scaled(w,h,Qt::KeepAspectRatio));
    }
    else if (f11) {
        cvtColor(img,img,COLOR_BGR2HSV);
        cvtColor(img2,img2,COLOR_BGR2HSV);
        for (int i=0;i<img.cols;i++) {
            for (int j=0;j<img.rows;j++) {
                int pix = img.at<Vec3b>(j,i).val[2];
                if( pix + position >255){
                    img2.at<Vec3b>(j,i).val[2]=255;
                }
                else if (pix + position < 1) {
                    img2.at<Vec3b>(j,i).val[2]=1;
                }
                else {
                    img2.at<Vec3b>(j,i).val[2]=pix + position;
                }
            }
        }
        cvtColor(img,img,COLOR_HSV2BGR);
        cvtColor(img2,img2,COLOR_HSV2BGR);
        ui->label->setPixmap(QPixmap::fromImage(cvMat2QImage(img2)).scaled(w,h,Qt::KeepAspectRatio));
    }


}

void MainWindow::on_confirm_clicked()
{
    ui->confirm->setDisabled(true);
    edit=false;
    ui->horizontalSlider->setEnabled(edit);
    history.push_back(img2.clone());
    historyNum++;
    img=history[historyNum];
    ui->label->setPixmap(QPixmap::fromImage(cvMat2QImage(history[historyNum])).scaled(w,h,Qt::KeepAspectRatio));
    if(historyNum>=1){
        ui->action_2->setEnabled(true);
    }
    ui->horizontalSlider->setValue(0);
    ui->lcdNumber->display(0);
    ui->pushButton->setDisabled(false);
    ui->pushButton_2->setDisabled(false);
    ui->pushButton_3->setDisabled(false);
    ui->pushButton_4->setDisabled(false);
    ui->pushButton_5->setDisabled(false);
    ui->pushButton_6->setDisabled(false);
    ui->pushButton_7->setDisabled(false);
    ui->pushButton_8->setDisabled(false);
    ui->pushButton_9->setDisabled(0);
    ui->pushButton_10->setDisabled(0);
    ui->pushButton_11->setDisabled(0);
    ui->pushButton_12->setDisabled(0);
    ui->pushButton_13->setDisabled(0);
    ui->pushButton_14->setDisabled(0);
    ui->pushButton_15->setDisabled(0);
}

void MainWindow::on_action_2_triggered()
{
    if(historyNum<2){
        ui->action_2->setEnabled(false);
    }
    if(gs){
        gs=false;
    }
    historyNum--;
    img=history[historyNum];
    history.erase(history.end()-1);
    ui->label->setPixmap(QPixmap::fromImage(cvMat2QImage(history[historyNum])).scaled(w,h,Qt::KeepAspectRatio));
}


void MainWindow::on_action_3_triggered()
{
    filePath = QFileDialog::getSaveFileName(this, tr("Save Data"), "",tr("(*.jpg)"));
    filep = filePath.toLocal8Bit().constData();
    QFile file(filePath);
    if(file.open(QFile::WriteOnly)){
        imwrite(filep,img);
        QMessageBox::information(this, "INFO","SAVE SUCCEED");
    }
    else {
        QMessageBox::warning(this, "WANRING","SAVE FAILED");
    }
}

void MainWindow::on_pushButton_6_clicked()
{

    f6=true;
    f3=0;
    f1=0;
    f2=0;
    f4=0;
    f5=0;
    f7=0;
    f8=0;
    f9=0;
    f10=0;
    f11=0;
    edit=true;
    ui->horizontalSlider->setEnabled(edit);
    ui->pushButton->setDisabled(true);
    ui->pushButton_2->setDisabled(true);
    ui->pushButton_3->setDisabled(true);
    ui->pushButton_4->setDisabled(true);
    ui->pushButton_5->setDisabled(true);
    ui->pushButton_6->setDisabled(true);
    ui->pushButton_7->setDisabled(true);
    ui->pushButton_8->setDisabled(true);
    ui->pushButton_9->setDisabled(true);
    ui->pushButton_10->setDisabled(true);
    ui->pushButton_11->setDisabled(true);
    ui->pushButton_12->setDisabled(true);
    ui->pushButton_13->setDisabled(true);
    ui->pushButton_14->setDisabled(true);
    ui->pushButton_15->setDisabled(true);
}

void MainWindow::on_pushButton_7_clicked()
{
    f7=true;
    f3=0;
    f1=0;
    f2=0;
    f4=0;
    f5=0;
    f8=0;
    f6=0;
    f9=0;
    f10=0;
    f11=0;
    edit=true;
    ui->horizontalSlider->setEnabled(edit);
    ui->pushButton->setDisabled(true);
    ui->pushButton_2->setDisabled(true);
    ui->pushButton_3->setDisabled(true);
    ui->pushButton_4->setDisabled(true);
    ui->pushButton_5->setDisabled(true);
    ui->pushButton_6->setDisabled(true);
    ui->pushButton_7->setDisabled(true);
    ui->pushButton_8->setDisabled(true);
    ui->pushButton_9->setDisabled(true);
    ui->pushButton_10->setDisabled(true);
    ui->pushButton_11->setDisabled(true);
    ui->pushButton_12->setDisabled(true);
    ui->pushButton_13->setDisabled(true);
    ui->pushButton_14->setDisabled(true);
    ui->pushButton_15->setDisabled(true);
}

void MainWindow::on_pushButton_8_clicked()
{
    f8=true;
    f3=0;
    f1=0;
    f2=0;
    f4=0;
    f5=0;
    f7=0;
    f6=0;
    f9=0;
    f10=0;
    f11=0;
    edit=true;
    ui->horizontalSlider->setEnabled(edit);
    ui->pushButton->setDisabled(true);
    ui->pushButton_2->setDisabled(true);
    ui->pushButton_3->setDisabled(true);
    ui->pushButton_4->setDisabled(true);
    ui->pushButton_5->setDisabled(true);
    ui->pushButton_6->setDisabled(true);
    ui->pushButton_7->setDisabled(true);
    ui->pushButton_8->setDisabled(true);
    ui->pushButton_9->setDisabled(true);
    ui->pushButton_10->setDisabled(true);
    ui->pushButton_11->setDisabled(true);
    ui->pushButton_12->setDisabled(true);
    ui->pushButton_13->setDisabled(true);
    ui->pushButton_14->setDisabled(true);
    ui->pushButton_15->setDisabled(true);
}



void MainWindow::on_pushButton_9_clicked()
{
    cv::Rect rectangle(50,50,img.cols-70,img.rows-70);
    cv::Mat bgModel,fgModel;
    cv::Mat result;
    cv::grabCut(img,result,rectangle,bgModel,fgModel,1,cv::GC_INIT_WITH_RECT);
    cv::compare(result,cv::GC_PR_FGD,result,cv::CMP_EQ);
    cv::Mat foreground(img.size(),CV_8UC3,cv::Scalar(255,255,255));
    img.copyTo(foreground,result);
    cv::rectangle(img, rectangle, cv::Scalar(255,255,255),1);
    img2=foreground.clone();
    //
    ui->label->setPixmap(QPixmap::fromImage(cvMat2QImage(img2)).scaled(w,h,Qt::KeepAspectRatio));
    historyNum++;
    history.push_back(img2.clone());
    img=history[historyNum];
    if(historyNum>=1){
        ui->action_2->setEnabled(true);
    }

}

void MainWindow::on_pushButton_10_clicked()
{
    Rect2d r = selectROI(img);
    img2=img(r);
    //
    ui->label->setPixmap(QPixmap::fromImage(cvMat2QImage(img2)).scaled(w,h,Qt::KeepAspectRatio));
    historyNum++;
    history.push_back(img2.clone());
    img=history[historyNum];
    if(historyNum>=1){
        ui->action_2->setEnabled(true);
    }
}

void MainWindow::on_pushButton_11_clicked()
{
    cv::transpose(img,img2);
    cv::flip(img2,img2,1);
    //
    ui->label->setPixmap(QPixmap::fromImage(cvMat2QImage(img2)).scaled(w,h,Qt::KeepAspectRatio));
    historyNum++;
    history.push_back(img2.clone());
    img=history[historyNum];
    if(historyNum>=1){
        ui->action_2->setEnabled(true);
    }


}

void MainWindow::on_pushButton_12_clicked()
{
    if(!gs){
        cv::cvtColor(img, img2, COLOR_BGR2GRAY);
        //
        ui->label->setPixmap(QPixmap::fromImage(cvMat2QImage(img2)).scaled(w,h,Qt::KeepAspectRatio));
        historyNum++;
        history.push_back(img2.clone());
        img=history[historyNum];
        if(historyNum>=1){
            ui->action_2->setEnabled(true);
        }
        gs=true;
    }

}

void MainWindow::on_pushButton_13_clicked()
{
    f9=1;
    f8=0;
    f3=0;
    f1=0;
    f2=0;
    f4=0;
    f5=0;
    f7=0;
    f6=0;
    f10=0;
    f11=0;
    edit=true;
    ui->horizontalSlider->setEnabled(edit);
    ui->pushButton->setDisabled(true);
    ui->pushButton_2->setDisabled(true);
    ui->pushButton_3->setDisabled(true);
    ui->pushButton_4->setDisabled(true);
    ui->pushButton_5->setDisabled(true);
    ui->pushButton_6->setDisabled(true);
    ui->pushButton_7->setDisabled(true);
    ui->pushButton_8->setDisabled(true);
    ui->pushButton_9->setDisabled(true);
    ui->pushButton_10->setDisabled(true);
    ui->pushButton_11->setDisabled(true);
    ui->pushButton_12->setDisabled(true);
    ui->pushButton_13->setDisabled(true);
    ui->pushButton_14->setDisabled(true);
    ui->pushButton_15->setDisabled(true);
}

void MainWindow::on_pushButton_14_clicked()
{
    f10=1;
    f9=0;
    f8=0;
    f3=0;
    f1=0;
    f2=0;
    f4=0;
    f5=0;
    f7=0;
    f6=0;
    f11=0;
    edit=true;
    ui->horizontalSlider->setEnabled(edit);
    ui->pushButton->setDisabled(true);
    ui->pushButton_2->setDisabled(true);
    ui->pushButton_3->setDisabled(true);
    ui->pushButton_4->setDisabled(true);
    ui->pushButton_5->setDisabled(true);
    ui->pushButton_6->setDisabled(true);
    ui->pushButton_7->setDisabled(true);
    ui->pushButton_8->setDisabled(true);
    ui->pushButton_9->setDisabled(true);
    ui->pushButton_10->setDisabled(true);
    ui->pushButton_11->setDisabled(true);
    ui->pushButton_12->setDisabled(true);
    ui->pushButton_13->setDisabled(true);
    ui->pushButton_14->setDisabled(true);
    ui->pushButton_15->setDisabled(true);
}

void MainWindow::on_pushButton_15_clicked()
{
    f11=1;
    f9=0;
    f8=0;
    f3=0;
    f1=0;
    f2=0;
    f4=0;
    f5=0;
    f7=0;
    f6=0;
    f10=0;
    edit=true;
    ui->horizontalSlider->setEnabled(edit);
    ui->pushButton->setDisabled(true);
    ui->pushButton_2->setDisabled(true);
    ui->pushButton_3->setDisabled(true);
    ui->pushButton_4->setDisabled(true);
    ui->pushButton_5->setDisabled(true);
    ui->pushButton_6->setDisabled(true);
    ui->pushButton_7->setDisabled(true);
    ui->pushButton_8->setDisabled(true);
    ui->pushButton_9->setDisabled(true);
    ui->pushButton_10->setDisabled(true);
    ui->pushButton_11->setDisabled(true);
    ui->pushButton_12->setDisabled(true);
    ui->pushButton_13->setDisabled(true);
    ui->pushButton_14->setDisabled(true);
    ui->pushButton_15->setDisabled(true);
}
