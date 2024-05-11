#ifndef FACEDETECTION_H
#define FACEDETECTION_H

#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;

class FaceDetection
{
public:
    FaceDetection();
    Mat detectFaces(Mat frame , std::string classifier, CascadeClassifier cascade);


};

#endif // FACEDETECTION_H
