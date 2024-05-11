#include "pca.h"
#include "QDebug"

#define SHOW_IMAGE 0

_PCA::_PCA(vector<Mat> faces){
    getImgSize(faces);
    imgRows = faces[0].rows;
    mergeMatrix(faces);
    getAverageVector();
    subtractMatrix();
    Mat _covarMatrix = (subFacesMatrix.t()) * subFacesMatrix;
    getBestEigenVectors(_covarMatrix,1.0);
    calcWeights();
}

void _PCA:: getImgSize(vector<Mat> faces)
{
    //Dimession of Features
    imgSize = faces[0].rows * faces[0].cols;
    //cout << "Per Image Size is: " << size << endl;
}

void _PCA::mergeMatrix(vector<Mat> faces)
{
    int col = faces.size();
    allFacesMatrix.create(imgSize, col, CV_32FC1);

    for (int i = 0; i < col; i++) {
        Mat tmpMatrix = allFacesMatrix.col(i);
        //Load grayscale image 0
        Mat tmpImg;
        faces[i].convertTo(tmpImg, CV_32FC1);
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
    cv::reduce(allFacesMatrix, avgVector, 1, REDUCE_AVG);
}

void _PCA::subtractMatrix()
{
    allFacesMatrix.copyTo(subFacesMatrix);
    for (int i = 0; i < subFacesMatrix.cols; i++) {
        subtract(subFacesMatrix.col(i), avgVector, subFacesMatrix.col(i));
    }
}

void _PCA::getBestEigenVectors(Mat _covarMatrix,float threshold)
{
    //Get all eigenvalues and eigenvectors from covariance matrix
    Mat allEigenValues, allEigenVectors;
    eigen(_covarMatrix, allEigenValues, allEigenVectors);

    // reduce till the threshold
    float sum = 0;
    float totalSum = 0;
    for (int i = 0; i < allEigenValues.rows; i++) {
        totalSum += allEigenValues.at<float>(i, 0);
    }
    for (int i = 0; i < allEigenValues.rows; i++) {
        sum += allEigenValues.at<float>(i, 0);
        if (sum / totalSum >= threshold) {
            qDebug() << "Reached threshold at: " << i<<"\n";
            eigenVector = allEigenVectors.rowRange(0, i + 1);
            break;
        }
    }


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

Mat _PCA::getWeights()
{
    return weights;
}

void _PCA::calcWeights()
{

    Mat facesMatrix = getFacesMatrix();
    Mat avg = getAverage();
    Mat eigenVec = getEigenvectors();

    weights.create(facesMatrix.cols, facesMatrix.cols, CV_32FC1);

    for (int i = 0; i < facesMatrix.cols; i++) {
        Mat temp;
        Mat projectFace = weights.col(i);
        subtract(facesMatrix.col(i), avg, temp);
        projectFace = eigenVec * temp;
    }
}

_PCA::~_PCA() {}
