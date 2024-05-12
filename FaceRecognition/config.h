#ifndef CONFIG_H
#define CONFIG_H

#include<QString>

#include "Models/pca.h"
#include "opencv2/objdetect.hpp"
extern QString inactiveBtnStyle;
extern QString activeBtnStyle;
extern int labelsSize;



extern _PCA pcaInstance;
extern CascadeClassifier cascade;

#endif // CONFIG_H
