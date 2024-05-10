#ifndef PCA_H
#define PCA_H

#include <opencv2/opencv.hpp>



/*
    To Apply PCA There are 3 steps:
    1. Standardize the data.
    2. Obtain the Eigenvectors and Eigenvalues from the covariance matrix or correlation matrix, or perform Singular Vector Decomposition.
    3. Sort eigenvalues in descending order and choose the k eigenvectors that correspond to the k largest eigenvalues where k is the number of dimensions of the new feature subspace (k<=d).
*/

class _PCA
{
public:
    _PCA();
    static std::pair<cv::Mat,cv::Mat> applyPCA(cv::Mat data);
    static cv::Mat normalize(cv::Mat data);
    static cv::Mat calcCov(cv::Mat normalizedData);
    static cv::Mat calcEigenFaces(cv::Mat cov,cv::Mat normalizedData, float threshold);
    static cv::Mat calcWeights(cv::Mat normalizedData ,cv::Mat eigenFaces);
};

#endif // PCA_H
