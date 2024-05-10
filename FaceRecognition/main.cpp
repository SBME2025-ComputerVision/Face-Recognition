#include "Views/mainwindow.h"
#include "Models/facedetection.h"
#include "Models/fetcher.h"
#include "Models/pca.h"
#include <filesystem>

#include <QApplication>
#include <iostream>

namespace fs = std::filesystem;
CascadeClassifier cascade;

int main(int argc, char *argv[])
{


    Mat data = Fetcher::fetch("./dataset/training/");
    std::cout<<data.size();


    data = _PCA::normalizeData(data);
    std::cout<<"Norm data sz "<<data.size();
    Mat cov;
    cov = _PCA::calculateCovarianceMatrix(data);
    Mat pcas;
    std::cout<<pcas.size();
    pcas = _PCA::computePCA(data,cov);

    for (int i = 0; i < pcas.rows; ++i) {
        cv::Mat tmp = pcas.row(i).reshape(1, 64); // Reshape each row of data
        std::string filename ="face_" + std::to_string(i) + ".jpg"; // Construct filename

        // Save the flattened face as an image
        cv::imwrite(filename, tmp);
    }





    return 0;



    // std::string faceClassifier = "./Assets/haarcascade_frontalface_alt.xml";
    // std::string faceClassifier2 = "./Assets/haarcascade_frontalface_alt2.xml";
    // std::string faceClassifier3 = "./Assets/haarcascade_frontalcatface.xml";
    // std::string faceClassifier4 = "./Assets/haarcascade_frontalface_default.xml";
    // std::string faceClassifier5 = "./Assets/haarcascade_frontalface_alt_tree.xml";
    // std::string faceClassifier6 = "./Assets/haarcascade_frontalcatface_extended.xml";

//     Mat img;
//     std::vector<Mat> faces;

//     img = imread("./Gallery/originalBoys.jpg");
//     img = FaceDetection::detectFaces(img,faceClassifier,cascade);

//     //for each file in ./Gallery/Faces/ folder add to faces vector
//     for (const auto & entry : fs::directory_iterator("./Gallery/Faces/")) {
//         Mat face = imread(entry.path().string(),CV_8UC1);
//         faces.push_back(face);
//     }
//     Mat data = FaceDetection::flattenFaces(faces);






//     Mat tmp = pcas.row(0).reshape(1,100);




//     return 0;






    // QApplication a(argc, argv);
    // MainWindow w;
    // w.show();
    // return a.exec();
}
