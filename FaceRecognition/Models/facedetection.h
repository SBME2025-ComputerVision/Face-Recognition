#ifndef FACEDETECTION_H
#define FACEDETECTION_H

#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

class FaceDetection
{
public:
    FaceDetection(Mat weights,Mat eigenFaces, Mat mean,std::vector <std::string> loadedWeights);
    Mat detectFaces(Mat faceImage);
    void recognize();
    void projectFace(Mat testVec);
    Mat prepareFace(Mat _testImg);

    string getFaceId();
    double getDistance();

private:

    Mat weights,eigenFaces,mean,projectedFace;
    string closetFaceID;
    double closetFaceDist;
    std::vector <std::string> loadedWeights;

};

#endif // FACEDETECTION_H
