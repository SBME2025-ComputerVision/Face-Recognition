#include "facedetection.h"
#include "qdebug.h"

FaceDetection::FaceDetection(Mat weights,Mat eigenFaces, Mat mean,std::vector <std::string> loadedWeights) {
    this->eigenFaces= eigenFaces;
    this->weights = weights;
    this->mean = mean;
    this->loadedWeights = loadedWeights;
}

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
          imwrite("yah"+to_string(i)+".png",faceROI);
          faceROI = prepareFace(faceROI);
          projectFace(faceROI);
          recognize();
    }

 return grey;

}

void FaceDetection::recognize()
{

    int minDist = INT_MAX;
    int min_index = -1;
    for (int i =0; i < loadedWeights.size(); i++) {
        Mat src1 = weights.col(i);
        Mat src2 = projectedFace;

        double dist = norm(src1, src2, NORM_L2);
        cout << dist << endl ;
        if (dist < minDist) {
            minDist = dist;
            min_index = i;
        }
    }
    cout<<loadedWeights[min_index]<<endl;
}

void FaceDetection::projectFace(Mat testVec)
{
    Mat tmpData;
    cout << testVec.type()<<endl;
    cout << mean.type() << endl;
    cout << testVec.rows << "X" << testVec.cols <<endl;
    cout << eigenFaces.rows << "X" << eigenFaces.cols <<endl;
    mean.convertTo(mean,CV_32FC1);
    testVec.convertTo(testVec,CV_32FC1);
    subtract(testVec, mean, tmpData);
    projectedFace = eigenFaces * tmpData;
}

Mat FaceDetection::prepareFace(Mat faceROI)
{
    Size newSize(64, 64);
    resize(faceROI, faceROI, newSize);
    faceROI = faceROI.reshape(1, (faceROI.rows * faceROI.cols));
   faceROI.convertTo(faceROI,CV_32FC1);
return faceROI;
}

