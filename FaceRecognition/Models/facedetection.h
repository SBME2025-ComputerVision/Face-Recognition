#ifndef FACEDETECTION_H
#define FACEDETECTION_H

#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;

class FaceDetection
{
public:
    FaceDetection();
    static Mat detectFaces(Mat frame , std::string classifier, CascadeClassifier cascade);
    static Mat flattenFaces(std::vector<Mat> faces);

};

#endif // FACEDETECTION_H
