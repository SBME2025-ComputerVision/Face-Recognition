#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QApplication>
#include<iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void plot_roc(std::vector<double> tpr, std::vector<double> fpr)
{
    // Create a new window to display the ROC curve
    namedWindow("ROC Curve", WINDOW_NORMAL);
    resizeWindow("ROC Curve", 650, 650);

    // Draw the ROC curve on a white background
    Mat rocCurve(650, 650, CV_8UC3, Scalar(255, 255, 255));

    // Draw the ROC curve
    int x, y;
    for (size_t i = 0; i < tpr.size(); i++) {
        if (tpr[i] <= 0.5) {
            x = static_cast<int>(tpr[i] * 550 + 10);
            y = static_cast<int>((1 - fpr[i]) * 500 + 50);  // Scale the y-coordinate between 0 and 1
            circle(rocCurve, Point(x, y), 5, Scalar(0, 0, 255), FILLED);
        }
        else {
            x = static_cast<int>(tpr[i] * 550 + 10);
            y = static_cast<int>((1 - fpr[i]) * 500 + 50);  // Scale the y-coordinate between 0 and 1
            circle(rocCurve, Point(x, y), 5, Scalar(0, 0, 255), FILLED);
        }

        // Connect consecutive points with lines
        if (i > 0) {
            int prevX = static_cast<int>(tpr[i - 1] * 550 + 10);
            int prevY = static_cast<int>((1 - fpr[i - 1]) * 500 + 50);  // Scale the y-coordinate between 0 and 1
            line(rocCurve, Point(prevX, prevY), Point(x, y), Scalar(255, 0, 0), 2, LINE_AA);
        }
    }

    // Draw the axes
    line(rocCurve, Point(10, 550), Point(600, 550), Scalar(0, 0, 0), 3, LINE_AA);
    line(rocCurve, Point(10, 550), Point(10, 50), Scalar(0, 0, 0), 3, LINE_AA);

    // Add labels to the axes
    putText(rocCurve, "False Positive Rate", Point(215, 600), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0), 1, LINE_AA);
    putText(rocCurve, "True Positive Rate", Point(10, 20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0), 1, LINE_AA);

    // Draw the number "0" at position (5, 580)
    putText(rocCurve, "0", Point(.5, 550), FONT_HERSHEY_SIMPLEX, 0.4, Scalar(0, 0, 0), 2, LINE_AA);
    putText(rocCurve, "1", Point(.5, 60), FONT_HERSHEY_SIMPLEX, 0.4, Scalar(0, 0, 0), 2, LINE_AA);

    // Display the ROC curve
    imshow("ROC Curve", rocCurve);
    waitKey(0);
}


void MainWindow::on_pushButton_clicked()
{
    std::vector<double> tpr = { 0.0, 0.2, 0.4, 0.8, 1.0 };
    std::vector<double> fpr = { 0.0, 0.6, 0.8, 0.95, 1.0 };
    plot_roc(tpr,fpr);
}

