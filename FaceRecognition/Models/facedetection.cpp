#include "facedetection.h"
#include "qdebug.h"

FaceDetection::FaceDetection() {}

Mat FaceDetection::detectFaces(Mat frame, std::string classifier , CascadeClassifier cascade)
{

    if(!cascade.load(classifier)){
        qDebug()<< "Error";
        return Mat::zeros(frame.size(),frame.type());
    }

    qDebug()<< "Classifier loaded";

    Mat grey;
    cvtColor(frame,grey,COLOR_BGR2GRAY);

    /*
     * Detect faces with the classifier
    */
    std::vector<Rect> faces;
    cascade.detectMultiScale(grey,faces);

    for (int i = 0; i < faces.size(); ++i) {

        Mat faceROI = grey(faces[i]);
        std::string faceName = "./Gallery/face" + std::to_string(i) + ".jpg";
        imwrite(faceName,faceROI);


        double cX,cY;
        cX = (faces[i].x + faces[i].width)/2;
        cY = (faces[i].y + faces[i].height)/2;
        Point center(cX,cY);
        rectangle(frame,faces[i],Scalar(255,0,0),2);
    }

    return frame;
}


