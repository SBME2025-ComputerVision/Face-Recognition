#include "livecameracontroller.h"

LiveCameraController::LiveCameraController() {


}

void LiveCameraController::predictPerson(Mat& frame)
{
    Mat eigens = pcaInstance.getEigenvectors();
    Mat mean = pcaInstance.getAverage();
    vector<string>loadedWeights;
    Mat _= FilesHelper::readWeights(labelsSize,loadedWeights);
    Mat w = pcaInstance.getWeights();
    FaceDetection detector(w,eigens,mean,loadedWeights);
    detector.liveDetection(frame);
}

void LiveCameraController::predictPerson2(Mat& frame)
{
    Mat eigens = pcaInstance.getEigenvectors();
    Mat mean = pcaInstance.getAverage();
    vector<string>loadedWeights;
    Mat _= FilesHelper::readWeights(labelsSize,loadedWeights);
    Mat w = pcaInstance.getWeights();
    FaceDetection detector(w,eigens,mean,loadedWeights);
    detector.liveDetection2(frame);
}
