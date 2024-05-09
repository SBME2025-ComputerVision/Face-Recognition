#include "pca.h"
#include <QDebug>
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
  //  cv::divide(normalizedData, stdDev, normalizedData);
    return normalizedData;
}

/*
    @param normalizedData: The data to calculate the covariance matrix of.
    @return: The covariance matrix of the data.

    @brief: The covariance matrix is calculated by multiplying the normalized data by its transpose.
*/

cv::Mat _PCA::calculateCovarianceMatrix(cv::Mat normalizedData)
{
    // initialize the covariance matrix
     // get the transpose of the normalized images matrix
     cv::Mat normalizedImagesT;

     transpose(normalizedData, normalizedImagesT);
       qDebug() << normalizedData.rows << normalizedData.cols;
       qDebug() << normalizedImagesT.rows << normalizedImagesT.cols;
     cv::Mat covarianceMatrix, mu;

     // calculate the covariance matrix
     calcCovarMatrix(normalizedData, covarianceMatrix, mu, cv::COVAR_NORMAL | cv::COVAR_ROWS);
     covarianceMatrix /= static_cast<double>(normalizedData.cols - 1);

       qDebug() << "Covariance Matrix Shape: " << covarianceMatrix.rows <<  covarianceMatrix.cols;
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
    // Compute the eigenvectors of the covariance matrix
    cv::Mat eigenvalues, eigenvectors;
   eigen(covarianceMatrix, eigenvalues, eigenvectors);

    cv::Mat eigenfaces_mat;
    cv::Mat eigenvectors_transpose = eigenvectors;
    cv::Mat normalized_data_transpose = normalizedData;

    // Convert the matrix types if necessary
    eigenvectors_transpose.convertTo(eigenvectors_transpose, CV_64FC1);
    normalized_data_transpose.convertTo(normalized_data_transpose, CV_64FC1);
    eigenfaces_mat =  normalized_data_transpose * eigenvectors_transpose;


    // Normalize the eigenfaces
    for (int i = 0; i < eigenfaces_mat.rows; i++)
      {
        normalize(eigenfaces_mat.row(i), eigenfaces_mat.row(i), 0, 255,cv:: NORM_MINMAX);
      }

    return eigenfaces_mat;
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
