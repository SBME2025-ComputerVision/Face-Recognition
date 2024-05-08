#include "Views/mainwindow.h"
#include "Models/facedetection.h"

#include <QApplication>
#include <iostream>

CascadeClassifier cascade;

int main(int argc, char *argv[])
{

    std::string faceClassifier = "./Assets/haarcascade_frontalface_alt.xml";
    std::string faceClassifier2 = "./Assets/haarcascade_frontalface_alt2.xml";
    std::string faceClassifier3 = "./Assets/haarcascade_frontalcatface.xml";
    std::string faceClassifier4 = "./Assets/haarcascade_frontalface_default.xml";
    std::string faceClassifier5 = "./Assets/haarcascade_frontalface_alt_tree.xml";
    std::string faceClassifier6 = "./Assets/haarcascade_frontalcatface_extended.xml";





    Mat img;

    img = imread("./Gallery/family.jpg");

    imwrite("./Gallery/read.png",img);

    img = FaceDetection::detectFaces(img,faceClassifier,cascade);

    imwrite("./Gallery/faces.png",img);


    return 0;






    // QApplication a(argc, argv);
    // MainWindow w;
    // w.show();
    // return a.exec();
}
