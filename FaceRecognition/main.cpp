#include "Views/mainwindow.h"
#include "Models/facedetection.h"
#include "Models/fetcher.h"
#include "Models/pca.h"
#include <filesystem>

#include <QApplication>
#include"Models/readfile.h"

#include <iostream>
#include"Helpers/fileshelper.h"

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




int main(int argc, char *argv[])
{


     std::vector<Mat> faces;
     faces = getFaces("./dataset4");
     _PCA pca = _PCA(faces);
     Mat eigenVector = pca.getEigenvectors();


    FilesHelper::writeToFile(eigenVector,"./dataset4files/eigen.txt");

    Mat eigens= FilesHelper::readMatrixFromFile("./dataset4files/eigen.txt");

//     cout<<eigens;

    Mat mean = pca.getAverage();

     cout<<"Mean Sz"<<mean.size()<<endl;
    FilesHelper::writeMeanToFile(mean,"./dataset4files/mean.txt");


     Mat meanRead= FilesHelper::readMeanFromFile("./dataset4files/mean.txt");

//     cout<<"Mean"<<mean<<endl;
//     cout<<"Mean Read"<<meanRead<<endl;





     Mat weight = pca.getWeights();
//     FilesHelper::writeToFile(weight,"weights.txt");

     vector<string>ids{"mariam","mariam","mariam","mariam","mariam","mariam","mariam","mariam","mariam","mariam","ashf","ashf","ashf","ashf","ashf","ashf","ashf","ashf","ashf","emad","emad","emad","emad","emad","emad","emad","emad","emad","ziad","ziad","ziad","ziad","ziad","ziad","ziad","ziad","mourad","mourad","mourad","mourad","mourad","mourad","mourad","mourad"};

     FilesHelper::writeWeights(ids,weight);
     vector<string>loadedWeights;
     Mat w= FilesHelper::readWeights(44,loadedWeights);



     qDebug()<<"Size of weightst: " << weight.rows<<"*"<< weight.cols <<"\n";

//     std::cout<<weight;

     //reconstruct the faces
    Mat recon;
    eigens.convertTo(eigens,CV_32FC1);
    recon = weight.t() * eigenVector;


//     // write eigenVectors to images
    for (int i = 0; i < recon.rows; i++) {
        Mat eigenFace = recon.row(i).clone();

        // eigenFace *= 10000;        // add mean face
         Mat avg = pca.getAverage().t();
         eigenFace = eigenFace + avg;
        eigenFace = eigenFace.reshape(1, 64);

        // std::cout<<eigenFace<<"\n";
        eigenFace.convertTo(eigenFace, CV_8UC1);
        imwrite("./Gallery/" + std::to_string(i) + ".jpg", eigenFace);
    }
    Mat img=imread("./test/5-9.bmp");
    FaceDetection hello(weight,eigenVector,mean,loadedWeights);
    hello.detectFaces(img);

         // Mat recon;
         // eigens.convertTo(eigens,CV_32FC1);

         // recon = weight.t() * eigens;


         // write eigenVectors to images
//          for (int i = 0; i < recon.rows; i++) {
//              Mat eigenFace = recon.row(i).clone();

//              // eigenFace *= 10000;        // add mean face
// //             Mat avg = pca.getAverage().t();
// //             eigenFace = eigenFace + avg;
//              eigenFace = eigenFace + meanRead.t();
//              eigenFace = eigenFace.reshape(1, 64);

//              // std::cout<<eigenFace<<"\n";
//              eigenFace.convertTo(eigenFace, CV_8UC1);
//              imwrite("./Gallery/" + std::to_string(i) + ".jpg", eigenFace);
//          }





     return 0;
}


