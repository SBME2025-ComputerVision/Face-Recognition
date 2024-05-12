#include "facedetection.h"
#include "qdebug.h"

FaceDetection::FaceDetection(Mat weights,Mat eigenFaces, Mat mean,std::vector <std::string> loadedWeights) {
    this->eigenFaces= eigenFaces;
    this->weights = weights;
    this->mean = mean;
    this->loadedWeights = loadedWeights;
}

void FaceDetection::liveDetection(Mat &frame)
{
    Mat grey;
    cvtColor(frame,grey,COLOR_BGR2GRAY);

    /*
    * Detect faces with the classifier
   */
    detectFaces(frame);
    string face = closetFaceID;
    std::vector<Rect> faces;
    cascade.detectMultiScale(grey,faces);
    // Draw rectangles around the faces
    for (int i = 0; i < faces.size(); ++i) {
        rectangle(frame, faces[i], Scalar(255, 0, 0), 2);
        putText(frame, face, Point(faces[i].x, faces[i].y), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 2);
    }
}



void FaceDetection::detectFaces(Mat faceImage)
{
    Mat grey;
    cvtColor(faceImage, grey, COLOR_BGR2GRAY);

    // Assuming 'cascade' and other necessary variables are already initialized

    // Preprocess the face image if needed
    Mat processedFace = prepareFace(grey);

    // Project the face for recognition
    projectFace(processedFace);

    // Recognize the face
    recognize();

    // Return the grey image (original image) or you can return any other result as needed
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
    this->closetFaceID = loadedWeights[min_index];
//    cout<<loadedWeights[min_index]<<endl;
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

string FaceDetection::getFaceId()
{
    return closetFaceID;
}

