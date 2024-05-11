#include "faceprediction.h"
#include "ui_faceprediction.h"

FacePrediction::FacePrediction(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FacePrediction)
{
    ui->setupUi(this);
}

FacePrediction::~FacePrediction()
{
    delete ui;
}

void FacePrediction::on_uploadBtn_clicked()
{

}


void FacePrediction::on_detectBtn_clicked()
{

}

