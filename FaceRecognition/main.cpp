#include "Views/mainwindow.h"
#include "Models/facedetection.h"
#include "Models/fetcher.h"
#include "Models/pca.h"
#include <filesystem>

#include <QApplication>
#include"Models/readfile.h"

#include <iostream>

namespace fs = std::filesystem;
CascadeClassifier cascade;

std::vector<Mat> getFaces(std::string path){
    std::vector<Mat> faces;
    Size targetSize = cv::Size(64,64);
    // Iterate over files in the folder
    for (const auto& entry : fs::directory_iterator(path)) {
        if (entry.is_regular_file()) {
            std::string imagePath = entry.path().string();
            Mat image = cv::imread(imagePath, cv::IMREAD_GRAYSCALE);

            if (!image.empty()) {
                faces.push_back(image);
            }
        }
    }
    for(int i = 0; i < faces.size(); i++) {
        resize(faces[i], faces[i], targetSize);
    }
    for (int i = 0; i < faces.size(); i++) {
        faces[i].convertTo(faces[i],CV_32FC1);
    }
    return faces;
}

void writeToFile(const Mat& eigenVector, const std::string& filename) {
    std::ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        std::cerr << "Failed to open output file!" << std::endl;
        return;
    }

    // Write eigenVector matrix to file
    for (int i = 0; i < eigenVector.rows; ++i) {
        for (int j = 0; j < eigenVector.cols; ++j) {
            outputFile << eigenVector.at<double>(i, j) << " ";
        }
        outputFile << std::endl;
    }

    outputFile.close();
    std::cout << "EigenVector matrix written to " << filename << std::endl;
}

int main(int argc, char *argv[])
{


     std::vector<Mat> faces;
     faces = getFaces("./Gallery/Faces/");

     _PCA pca = _PCA(faces);

     Mat eigenVector = pca.getEigenvectors();

//     std::ofstream outputFile("eigenVector.txt");
//       if (!outputFile.is_open()) {
//           std::cerr << "Failed to open output file!" << std::endl;
//           return 1;
//       }

//       // Write eigenVector matrix to file
//       for (int i = 0; i < eigenVector.rows; ++i) {
//           for (int j = 0; j < eigenVector.cols; ++j) {
//               outputFile << eigenVector.at<double>(i, j) << " ";
//           }
//           outputFile << std::endl;
//       }

//       outputFile.close();
//       std::cout << "EigenVector matrix written to eigenVector.txt" << std::endl;




     Mat weight = pca.getWeights();
     writeToFile(weight,"weights.txt");



     qDebug()<<"Size of weightst: " << weight.rows<<"*"<< weight.cols <<"\n";

     std::cout<<weight;

     //reconstruct the faces
     Mat recon;
     recon = weight.t() * eigenVector;


     // write eigenVectors to images
     for (int i = 0; i < eigenVector.rows; i++) {
         Mat eigenFace = eigenVector.row(i).clone();

         eigenFace *= 10000;        // add mean face
         // Mat avg = pca.getAverage().t();
         // eigenFace = eigenFace + avg;
         eigenFace = eigenFace.reshape(1, 64);

         // std::cout<<eigenFace<<"\n";
         eigenFace.convertTo(eigenFace, CV_8UC1);
         imwrite("./Gallery/" + std::to_string(i) + ".jpg", eigenFace);
     }

     return 0;
}







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


//int main() {
//    string trainListFilePath = "C:/Users/user/Documents/GitHub/Face-Recognition/FaceRecognition/train_list.txt";
//     vector<string> trainFacesPath;
//     vector<string> trainFacesID;
//     vector<string> loadedFacesID;
//     //read training list and ID from txt file
//     readList(trainListFilePath, trainFacesPath, trainFacesID);
//     for(int i=0;i<trainFacesPath.size();i++){
//         cout<<trainFacesPath[i]<<endl;;

//     }
     //read training data(faces, eigenvector, average face) from txt file
//     Mat avgVec, eigenVec, facesInEigen;
//     facesInEigen =  readFaces(int(trainFacesID.size()), loadedFacesID);
//     avgVec = readMean();
//     eigenVec = readEigen(int(trainFacesID.size()));
//    return 0;





//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();
//}
