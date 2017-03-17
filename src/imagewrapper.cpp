#include "imagewrapper.h"
#include <QImage>
#include <QImageReader>
#include <QDebug>
#include "toolkit.h"
ImageWrapper::ImageWrapper(): Cache(), imageFrames(0), formatFlag(REGULAR_FLAG)
, header(NULL){

}

ImageWrapper::~ImageWrapper(){

}

void ImageWrapper::load(const QString& filePath, bool preReading){
    if(filePath.isEmpty())
        return;
    imagePath = filePath;
    attributes = QString::null;
    formatFlag = REGULAR_FLAG;
    QImageReader reader(imagePath);
    reader.setDecideFormatFromContent(true);
    imageFormat = reader.format();
    imageFrames = reader.imageCount();
    qDebug("format is %s, filename is %s", qPrintable(imageFormat),
           qPrintable(ToolKit::fileName(filePath)));
    if(formatFlag == REGULAR_FLAG){
        if(imageFormat == "ico"){
            reader.read(&image);
            int maxIndex = 0;
            int maxWidth = image.width();
            for(int i=1; i < imageFrames; ++i){
                if(!reader.jumpToNextImage())
                    break;
                reader.read(&image);
                if(maxWidth < image.width())
                    maxWidth = image.width();
                    maxIndex = i;
            }
            reader.jumpToImage(maxIndex);
        }
    }
    if(!reader.read(&image)){
        image = QImage();
    }
    if(image.isNull()){
        imageFormat = "";
        imageFrames = 0;
    }
    isReady = true;
}


QString ImageWrapper::attibute(){
    return attributes;
}

QImage ImageWrapper::currentImage(){
    return image;
}
