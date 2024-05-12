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

map<string,int> idToPerson;
int idx= 0 ;

std::vector<Mat> getFaces(std::string path){
    std::vector<Mat> faces;
    Size targetSize = cv::Size(64,64);
    // Iterate over files in the folder
    for (const auto& entry : fs::directory_iterator(path)) {
        if (entry.is_regular_file()) {
            std::string imagePath = entry.path().string();
            Mat image = cv::imread(imagePath, cv::IMREAD_GRAYSCALE);

            // Create a path object from the imagePath string
             fs::path filePath(imagePath);
             std::string filename = filePath.filename().string();
             size_t pos = filename.find('-');
             std::string extractedFilename = filename.substr(0, pos);

             std::cout << "Extracted Filename: " << extractedFilename << std::endl;
            if(!idToPerson[extractedFilename]){
                idToPerson[extractedFilename] = idx;
                idx++;
            }
        //    cout<<imagePath<<endl;
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

     for(auto it = idToPerson.begin(); it != idToPerson.end(); ++it){
        cout<<"key"<<it->first<<"  value "<<it->second<<endl;
     }

     _PCA pca = _PCA(faces);
     Mat eigenVector = pca.getEigenvectors();


    FilesHelper::writeToFile(eigenVector,"./dataset4files/eigen.txt");

    Mat eigens= FilesHelper::readMatrixFromFile("./dataset4files/eigen.txt");

//     cout<<eigens;

    Mat mean = pca.getAverage();

//     cout<<"Mean Sz"<<mean.size()<<endl;
    FilesHelper::writeMeanToFile(mean,"./dataset4files/mean.txt");


     Mat meanRead= FilesHelper::readMeanFromFile("./dataset4files/mean.txt");

//     cout<<"Mean"<<mean<<endl;
//     cout<<"Mean Read"<<meanRead<<endl;





     Mat weight = pca.getWeights();
//     FilesHelper::writeToFile(weight,"weights.txt");

//     vector<string>ids{"mariam","mariam","mariam","mariam","mariam","mariam","mariam","mariam","mariam","ashf","ashf","ashf","ashf","ashf","ashf","ashf","ashf","emad","emad","emad","emad","emad","emad","emad","emad","ziad","ziad","ziad","ziad","ziad","ziad","ziad","ziad","mourad","mourad","mourad","mourad","mourad","mourad","mourad"};
     vector<string>ids;
     for(auto it = idToPerson.begin(); it != idToPerson.end(); ++it){
           for(int j=0;j<7;j++){
               ids.push_back(it->first);
           }
     }
     for(int i=0;i<ids.size();i++){
         cout<<"id"<<ids[i]<<endl;
     }
     FilesHelper::writeWeights(ids,weight);
     vector<string>loadedWeights;
     Mat w= FilesHelper::readWeights(ids.size(),loadedWeights);



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
    Mat img=imread("./test/s2-7.pgm");
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
