#include "facepredictioncontroller.h"
#include "Helpers/basichelpers.h"
FacePredictionController::FacePredictionController() {
    img = new Image();
}

QPixmap FacePredictionController::uploadImg() {

    QString path = BasicHelpers::openFile(); // Opens a file dialog to select an image file
    if(!path.isEmpty()){
        //        delete img; // Deletes any previous image
        img = new Image(path.toStdString()); // Loads the image from the selected path
        if(!img->isEmpty()){ // Checks if the image is successfully loaded
            return BasicHelpers::convertMatToPixmap(img->getOriginalImg()); // Converts the image to QPixmap
        }
    }
    return BasicHelpers::convertMatToPixmap(Mat::zeros(1,1,CV_8UC1)); // Returns a blank QPixmap if image loading fails
}
