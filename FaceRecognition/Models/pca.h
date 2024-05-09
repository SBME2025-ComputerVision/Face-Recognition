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
    static cv::Mat applyPCA(cv::Mat data, float accuracy = 0.9);
    static cv::Mat normalizeData(cv::Mat data);
    static cv::Mat calculateCovarianceMatrix(cv::Mat normalizedData);
    static cv::Mat computePCA(cv::Mat normalizedData, cv::Mat covarianceMatrix);
    static cv::Mat computeWeights(cv::Mat normalizedData, cv::Mat eigenFaces);
};

#endif // PCA_H
