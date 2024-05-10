#include "pca.h"
<<<<<<< Updated upstream
#include <QDebug>

std::pair<cv::Mat, cv::Mat> _PCA::applyPCA(cv::Mat data)
{
    cv::Mat normalizedData = normalize(data);
    cv::Mat cov = calcCov(normalizedData);
    cv::Mat eigenFaces = calcEigenFaces(cov,normalizedData,0.95);
    cv::Mat weights = calcWeights(normalizedData,eigenFaces);
    return std::make_pair(eigenFaces,weights);
}

cv::Mat _PCA::normalize(cv::Mat data)
{
    cv::Mat avg;
    cv::Mat normalizedData = data;
    cv::reduce(data,avg,1,cv::REDUCE_AVG);

    for(int i = 0; i < data.cols; i++)
    {
        cv::subtract(data.col(i),avg,normalizedData.col(i));
    }

    return normalizedData;
}

cv::Mat _PCA::calcCov(cv::Mat normalizedData)
{
    cv::Mat cov;
    cov = (normalizedData * normalizedData.t());
    return cov;

}

cv::Mat _PCA::calcEigenFaces(cv::Mat cov,cv::Mat normalizedData, float threshold)
{
    cv::Mat eigenValues;
    cv::Mat eigenVectors;
    cv::eigen(cov,eigenValues,eigenVectors);

    double sum = cv::sum(eigenValues)[0];
    double sumThreshold = sum * threshold;
    double currentSum = 0;
    int i;

    for (i = 0; i < eigenValues.rows ; i++)
    {
        currentSum += eigenValues.at<double>(i,0);
        if(currentSum >= sumThreshold)
        {
            std::cout<<"Threshold reached at: "<<i<<std::endl;
            eigenValues = eigenValues.rowRange(0,i);
            eigenVectors = eigenVectors.rowRange(0,i);
            break;
        }

    }
    cv::Mat eigenFaces = eigenVectors *  normalizedData.t();

    return eigenFaces;
}

cv::Mat _PCA::calcWeights(cv::Mat normalizedData, cv::Mat eigenFaces)
{
    cv::Mat weights =normalizedData.t() * eigenFaces.t();
    return weights;

=======
#include "QDebug"

#define SHOW_IMAGE 0

_PCA::_PCA(vector<string>& _facesPath){
    getImgSize(_facesPath);
    imgRows = imread(_facesPath[0],0).rows;
    mergeMatrix(_facesPath);
    getAverageVector();
    subtractMatrix();
    Mat _covarMatrix = (subFacesMatrix.t()) * subFacesMatrix;
    getBestEigenVectors(_covarMatrix);



}

void _PCA:: getImgSize(vector<string>& _facesPath)
{
    Mat sampleImg = imread(_facesPath[0], 0);
    if (sampleImg.empty()) {
        qDebug() << "Fail to Load Image in PCA \n";
    }
    //Dimession of Features
    imgSize = sampleImg.rows * sampleImg.cols;
    //cout << "Per Image Size is: " << size << endl;
}

void _PCA::mergeMatrix(vector<string>& _facesPath)
{
    int col = int(_facesPath.size());
    allFacesMatrix.create(imgSize, col, CV_32FC1);

    for (int i = 0; i < col; i++) {
        Mat tmpMatrix = allFacesMatrix.col(i);
        //Load grayscale image 0
        Mat tmpImg;
        imread(_facesPath[i], 0).convertTo(tmpImg, CV_32FC1);
        //convert to 1D matrix
        tmpImg.reshape(1, imgSize).copyTo(tmpMatrix);
    }
    //cout << "Merged Matix(Width, Height): " << mergedMatrix.size() << endl;
}

void _PCA::getAverageVector()
{
    //To calculate average face, 1 means that the matrix is reduced to a single column.
    //vector is 1D column vector, face is 2D Mat
    Mat face;
    reduce(allFacesMatrix, avgVector, 1, REDUCE_AVG);
>>>>>>> Stashed changes
}

void _PCA::subtractMatrix()
{
    allFacesMatrix.copyTo(subFacesMatrix);
    for (int i = 0; i < subFacesMatrix.cols; i++) {
        subtract(subFacesMatrix.col(i), avgVector, subFacesMatrix.col(i));
    }
}

void _PCA::getBestEigenVectors(Mat _covarMatrix)
{
    //Get all eigenvalues and eigenvectors from covariance matrix
    Mat allEigenValues, allEigenVectors;
    eigen(_covarMatrix, allEigenValues, allEigenVectors);

    eigenVector = allEigenVectors * (subFacesMatrix.t());
    //Normalize eigenvectors
    for(int i = 0; i < eigenVector.rows; i++ )
    {
        Mat tempVec = eigenVector.row(i);
        normalize(tempVec, tempVec);
    }
}

Mat _PCA::getFacesMatrix()
{
    return allFacesMatrix;
}

Mat _PCA::getAverage()
{
    return avgVector;
}

Mat _PCA::getEigenvectors()
{
    return eigenVector;
}

_PCA::~_PCA() {}
