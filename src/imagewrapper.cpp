#include "imagewrapper.h"
#include <QImage>

ImageWrapper::ImageWrapper(){

}

void ImageWrapper::load(const QString& filePath, bool preReading){
    if(filePath.isEmpty())
        return;
    imagePath = filePath;

}
