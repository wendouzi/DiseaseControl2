#include "imagefactory.h"

#include <QRunnable>
#include <QThreadPool>
#include "imagewrapper.h"
#include "toolkit.h"
#include "config.h"

ImageFactory* ImageFactory::sInstance = NULL;

class Runnable : public QRunnable
{
public:
    Runnable(ImageWrapper* iw, const QString & filePath, bool preReading = true)
        : image(iw), path(filePath), isPreReading(preReading){}
    void run(){
        image->load(path, isPreReading);
    }

private:
    ImageWrapper * image;
    QString path;
    bool isPreReading;
};

ImageFactory::ImageFactory():QObject(),curIndex(-1){

}

ImageWrapper* ImageFactory::getImageWrapper(const QString&filePath){
    ImageWrapper *image;
    uint hash = filePath.isEmpty() ? ImageWrapper::HASH_INVALID : ToolKit::getFilesHash(filePath);
    if(image = findImageByHash(hash))
        return image;
    image = newOrReuseImage();
    image->setHashCode(hash);
    list.prepend(image);
    qDebug("list size:%d",list.size());
    emit filesChanged();
    if(hash == ImageWrapper::HASH_INVALID)
        image->setReady(true);
    else
        QThreadPool::globalInstance()->start(new Runnable(image,filePath));
    return image;
}

ImageWrapper* ImageFactory::newOrReuseImage(){
    ImageWrapper* image = new ImageWrapper;
    image->setHashCode(ImageWrapper::HASH_INVALID);
    image->setReady(false);
    return image;
}

ImageWrapper* ImageFactory::findImageByHash(const uint hash){
    foreach (ImageWrapper* image, list) {
        if(image->getHashCode() == hash)
            return image;
    }
    return NULL;
}

void ImageFactory::waitForImageReady(ImageWrapper*image){
    while(!image->getReady());
}

void ImageFactory::freeAllCache(){
    QThreadPool::globalInstance()->waitForDone();
    foreach(ImageWrapper*image, list)
        freeImage(image);
}
void ImageFactory::freeImage(ImageWrapper*image){
    waitForImageReady(image);
    SaftDelete(image);
}
