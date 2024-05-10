#include "facedetection2.h"

FaceDetection2::FaceDetection2()
{

}

void FaceDetection2::applyPCA(Mat data)
{
    Mat mean;
    reduce(data,mean,0,REDUCE_AVG);
    for(int i =0;i<data.rows;i++){
       data.row(i) = data.row(i) - mean;
    }

    this->dataNormailzed = data;
    Mat cov;
    calcCovarMatrix(data,cov,mean,COVAR_NORMAL|COVAR_ROWS|COVAR_SCALE);
    eigen(cov,this->eigenValues,this->eigenVectors);
}

void FaceDetection2::projectToPCA(Mat data)
{
   Mat selectTopK = this->eigenVectors.rowRange(0,0.1*4096);
   selectTopK = selectTopK.t();
   this->projectedData = data * selectTopK;
}
