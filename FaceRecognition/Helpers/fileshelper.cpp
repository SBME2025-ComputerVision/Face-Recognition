#include "fileshelper.h"


FilesHelper::FilesHelper()
{

}
void FilesHelper:: writeToFile(const Mat& inputMat, const std::string& filename) {
    std::ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        std::cerr << "Failed to open output file!" << std::endl;
        return;
    }

    // Write eigenVector matrix to file
    for (int i = 0; i < inputMat.rows; ++i) {
        for (int j = 0; j < inputMat.cols; ++j) {
            outputFile << inputMat.at<double>(i, j) << " ";
        }
        outputFile << std::endl;
    }

    outputFile.close();
    std::cout << "EigenVector matrix written to " << filename << std::endl;
}


Mat FilesHelper:: readMatrixFromFile(const std::string& filename) {
    // Open the file for reading
      std::ifstream inputFile(filename);
      if (!inputFile.is_open()) {
          std::cerr << "Failed to open input file!" << std::endl;
          return Mat();
      }

      // Read the contents of the file into a vector of vectors
      std::vector<std::vector<double>> data;
      std::string line;
      while (std::getline(inputFile, line)) {
          std::istringstream iss(line);
          std::vector<double> row;
          double value;
          while (iss >> value) {
              row.push_back(value);
          }
          data.push_back(row);
      }

      // Close the file
      inputFile.close();

      // Check if the data is valid
      if (data.empty()) {
          std::cerr << "No data found in file!" << std::endl;
          return Mat();
      }

      // Determine the number of columns
      size_t cols = data[0].size();

      // Create a matrix to store the data
      Mat matrix(data.size(), cols, CV_64F);

      // Copy the data from the vector of vectors to the matrix
      for (size_t i = 0; i < data.size(); ++i) {
          for (size_t j = 0; j < cols; ++j) {
              matrix.at<double>(i, j) = data[i][j];
          }
      }

      return matrix;
  }


void FilesHelper::writeWeights(vector<string>& _trainFacesID,Mat weights)
{
    string facesDataPath = "./data/weights.txt";
    ofstream writeFaceFile(facesDataPath.c_str(), ofstream::out | ofstream::trunc);
    if (!writeFaceFile) {
        cout << "Fail to open file: " << facesDataPath << endl;
    }

    for (int i = 0; i < _trainFacesID.size(); i++) {
        writeFaceFile << _trainFacesID[i] << ":";
        for (int j = 0; j < weights.rows; j++) {
            writeFaceFile << weights.col(i).at<float>(j);
            writeFaceFile << " ";
        }
        writeFaceFile << "\n";
    }

    writeFaceFile.close();
}


Mat FilesHelper::readWeights(int noOfFaces,vector<string>& loadedFaceID)
{
    Mat faces = Mat::zeros(noOfFaces, noOfFaces, CV_32FC1);
    string facesDataPath = "./data/weights.txt";
    ifstream readFaces(facesDataPath.c_str(), ifstream::in);

    if (!readFaces) {
        cout << "Fail to open file: " << facesDataPath << endl;
    }

    string line, id;
    loadedFaceID.clear();
    for (int i = 0; i < noOfFaces; i++) {
        getline(readFaces, line);
        stringstream lines(line);
        getline(lines, id, ':');
        loadedFaceID.push_back(id);
        for (int j = 0; j < noOfFaces; j++) {
            string data;
            getline(lines, data, ' ');
            faces.col(i).at<float>(j) = atof(data.c_str());
        }
    }

    readFaces.close();
    //cout << faces.row(14).at<float>(14) << endl;
    return faces;
}
