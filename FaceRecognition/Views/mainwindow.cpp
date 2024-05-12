#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    liveCameraWidget = new LiveCameraWidget();
    facePredictionWidget = new FacePrediction();
    faceDetectionWidget = new FaceDetection2();

    ui->stackedWidget->addWidget(facePredictionWidget);
    ui->stackedWidget->addWidget(liveCameraWidget);
    ui->stackedWidget->addWidget(faceDetectionWidget);

    menuBtns.append(ui->liveCameraBtn);
    menuBtns.append(ui->faceRecognitionBtn);
    menuBtns.append(ui->dataAndModelBtn);
    menuBtns.append(ui->faceDetectionBtn);
    ui->stackedWidget->setCurrentWidget(liveCameraWidget);
    GUI_HELPER::changeBtnStyle(ui->liveCameraBtn,activeBtnStyle);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_liveCameraBtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(liveCameraWidget);
    GUI_HELPER::changeBtnsStyle(menuBtns,inactiveBtnStyle);
    GUI_HELPER::changeBtnStyle(ui->liveCameraBtn,activeBtnStyle);
}


void MainWindow::on_faceRecognitionBtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(facePredictionWidget);
    GUI_HELPER::changeBtnsStyle(menuBtns,inactiveBtnStyle);
    GUI_HELPER::changeBtnStyle(ui->faceRecognitionBtn,activeBtnStyle);
}


void MainWindow::on_dataAndModelBtn_clicked()
{
    GUI_HELPER::changeBtnsStyle(menuBtns,inactiveBtnStyle);
    GUI_HELPER::changeBtnStyle(ui->dataAndModelBtn,activeBtnStyle);
}




void MainWindow::on_faceDetectionBtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(faceDetectionWidget);
    GUI_HELPER::changeBtnsStyle(menuBtns,inactiveBtnStyle);
    GUI_HELPER::changeBtnStyle(ui->faceDetectionBtn,activeBtnStyle);
}

