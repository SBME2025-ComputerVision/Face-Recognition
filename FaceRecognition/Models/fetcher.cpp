#include "fetcher.h"
#include <filesystem>

namespace fs = std::filesystem;

Fetcher::Fetcher() {}

cv::Mat Fetcher::fetch(std::string datasetPath)
{
    std::vector<cv::Mat> allFaces;

    // Iterate over folders in the dataset path
    for (const auto& entry : fs::directory_iterator(datasetPath)) {
        if (entry.is_directory()) {
            std::string folderPath = entry.path().string();
            std::vector<cv::Mat> faces = readImagesFromFolder(folderPath);
            allFaces.insert(allFaces.end(), faces.begin(), faces.end());
        }
    }
    cv::Mat data = flattenFaces(allFaces);
    return data;
}

std::vector<cv::Mat> Fetcher::readImagesFromFolder(const std::string& folderPath) {
    std::vector<cv::Mat> faces;

    // Iterate over files in the folder
    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (entry.is_regular_file()) {
            std::string imagePath = entry.path().string();
            cv::Mat image = cv::imread(imagePath, cv::IMREAD_GRAYSCALE);
            if (!image.empty()) {
                faces.push_back(image);
            }
        }
    }

    return faces;
}

cv::Mat Fetcher::flattenFaces(std::vector<cv::Mat> faces)
{
    cv::Size targetSize = cv::Size(100,100);

    // Resizing faces
    for(int i = 0; i < faces.size(); i++) {
        resize(faces[i], faces[i], targetSize);
    }

    // Debugging output
    // std::cout << "Number of faces: " << faces.size() << std::endl;

    // Creating the matrix to hold all flattened faces
    cv::Mat all_data = cv::Mat::zeros(static_cast<int>(faces.size()), targetSize.width * targetSize.height, CV_8UC1);

    // Debugging output
    // std::cout << "all_data size: " << all_data.size() << std::endl;

    // Copying each flattened image data to a row in all_data
    for(int i = 0; i < faces.size(); i++) {
        cv::Mat currentFace = faces[i];
        // Reshape currentFace to be a row vector
        cv::Mat row = currentFace.reshape(1, 1);
        // Debugging output
        // std::cout << "Row size: " << row.size() << std::endl;
        // Copy the data of the row vector to the corresponding row in all_data
        row.copyTo(all_data.row(i));
    }
    return all_data;
}
