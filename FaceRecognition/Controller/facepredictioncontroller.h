#ifndef FACEPREDICTIONCONTROLLER_H
#define FACEPREDICTIONCONTROLLER_H
#include "Models/image.h"
#include <opencv2/opencv.hpp>
class FacePredictionController
{
public:
    FacePredictionController();
    Image* img;
    QPixmap uploadImg();
};

#endif // FACEPREDICTIONCONTROLLER_H
