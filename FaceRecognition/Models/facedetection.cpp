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
    imwrite("./Gallery/faces.jpg",frame);
    return frame;
}


Mat FaceDetection::flattenFaces(std::vector<Mat> faces)
{
    Size targetSize = Size(100,100);

    // Resizing faces
    for(int i = 0; i < faces.size(); i++) {
        resize(faces[i], faces[i], targetSize);
    }

    // Debugging output
    std::cout << "Number of faces: " << faces.size() << std::endl;

    // Creating the matrix to hold all flattened faces
    Mat all_data = Mat::zeros(static_cast<int>(faces.size()), targetSize.width * targetSize.height, CV_8UC1);

    // Debugging output
    std::cout << "all_data size: " << all_data.size() << std::endl;

    // Copying each flattened image data to a row in all_data
    for(int i = 0; i < faces.size(); i++) {
        Mat currentFace = faces[i];
        // Reshape currentFace to be a row vector
        Mat row = currentFace.reshape(1, 1);
        // Debugging output
        std::cout << "Row size: " << row.size() << std::endl;
        // Copy the data of the row vector to the corresponding row in all_data
        row.copyTo(all_data.row(i));
    }

    return all_data;
}


