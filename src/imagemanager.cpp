#include "imagemanager.h"
#include "imagefactory.h"
#include "imagewrapper.h"
#include <QFileInfo>
#include <QApplication>
#include "global.h"
ImageManager::ImageManager(QWidget *parent): ImageViewer(parent), curImage(NULL)
{

}

ImageManager::~ImageManager()
{
    ImageFactory::freeAllCache();
}

void ImageManager::openFile(const QString & filePath){
    QFileInfo fileInfo(filePath);
    if(fileInfo.absoluteFilePath() == curPath)
        return;
    curPath = fileInfo.absoluteFilePath();
    curName = fileInfo.fileName();
    curImage = ImageFactory::getImageWrapper(filePath);
    while(!curImage->getReady())
        qApp->processEvents(QEventLoop::AllEvents);
    QImage image = curImage->currentImage();
    QString errorMsg = image.isNull() ? Global::LoadFileErrorInfo().arg(curPath):QString::null;
    loadImage(image,errorMsg);
    emit imageChanged(curPath);
}
