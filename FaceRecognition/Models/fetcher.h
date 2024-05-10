#ifndef FETCHER_H
#define FETCHER_H

#include<opencv2/opencv.hpp>
#include<iostream>



class Fetcher
{
public:
    Fetcher();
    static cv::Mat fetch(std::string datasetPath);
    static cv::Mat flattenFaces(std::vector<cv::Mat> faces);
private:
    static std::vector<cv::Mat> readImagesFromFolder(const std::string &folderPath);
};

#endif // FETCHER_H
