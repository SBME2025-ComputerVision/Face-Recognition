#include "pca.h"

_PCA::_PCA() {}


/*
    @param data: The data to be standardized.
    @return: The standardized data.

    @brief: data is Mat where each row is a sample and each column is a feature.
            The data is standardized by subtracting the mean of each feature from each sample and dividing by the standard deviation of each feature.
            This is done to ensure that each feature contributes equally to the PCA.
*/
cv::Mat _PCA::normalizeData(cv::Mat data)
{
    cv::Mat normalizedData;
    cv::Mat mean, stdDev;
    cv::meanStdDev(data, mean, stdDev);
    cv::subtract(data, mean, normalizedData);
    cv::divide(normalizedData, stdDev, normalizedData);
    return normalizedData;
}

/*
    @param normalizedData: The data to calculate the covariance matrix of.
    @return: The covariance matrix of the data.

    @brief: The covariance matrix is calculated by multiplying the normalized data by its transpose.
*/

cv::Mat _PCA::calculateCovarianceMatrix(cv::Mat normalizedData)
{
    cv::Mat covarianceMatrix;
    cv::calcCovarMatrix(normalizedData, covarianceMatrix, cv::Mat(), cv::COVAR_NORMAL | cv::COVAR_ROWS);
    return covarianceMatrix;
}

/*
    @param normalizedData: The data to compute the PCA of.
    @param covarianceMatrix: The covariance matrix of the data.
    @return: The eigenvectors of the data.

    @brief: The eigenvectors are computed by performing an eigenvalue decomposition on the covariance matrix.
*/

cv::Mat _PCA::computePCA(cv::Mat normalizedData, cv::Mat covarianceMatrix)
{
    cv::Mat eigenValues, eigenVectors;
    cv::eigen(covarianceMatrix, eigenValues, eigenVectors);
    return eigenVectors;
    // TODO Pass by ref
}

/*
    @param normalizedData: The data to compute the weights of.
    @param eigenFaces: The eigenvectors of the data.
    @return: The weights of the data.

    @brief: The weights are computed by projecting the data onto the eigenvectors.
*/

cv::Mat _PCA::computeWeights(cv::Mat normalizedData, cv::Mat eigenFaces)
{
    cv::Mat weights;
    // Project the data onto the eigenfaces.
    cv::Mat eigenfacesTranspose = eigenFaces.t();
    cv::Mat normalizedTranspose = normalizedData.t();
    weights = normalizedTranspose * eigenfacesTranspose;
    return weights;
}
