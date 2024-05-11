#ifndef FILESHELPER_H
#define FILESHELPER_H

#include <opencv2/core.hpp>
#include <filesystem>
#include<iostream>
#include <fstream>
#include<string>
#include<vector>
using namespace std;
using namespace cv;
class FilesHelper
{
public:
    FilesHelper();
    static void writeToFile(const Mat& inputMat, const std::string& filename);
    static Mat readMatrixFromFile(const std::string& filename);
    static void writeWeights(vector<string>& _trainFacesID,Mat weights);
    static Mat readWeights(int noOfFaces,vector<string>& loadedFaceID);

};

#endif // FILESHELPER_H
