#include "pca.h"
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

}
