#ifndef FACEDETECTION2_H
#define FACEDETECTION2_H
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;
class FaceDetection2
{
public:
    FaceDetection2();
    void applyPCA(Mat data);
    void projectToPCA(Mat data);
    Mat eigenValues,eigenVectors,projectedData,dataNormailzed;
};

#endif // FACEDETECTION2_H
