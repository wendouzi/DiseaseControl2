#include "imagemanager.h"
#include "imagefactory.h"
#include "imagewrapper.h"
#include <QFileInfo>
#include <QApplication>
#include "global.h"
ImageManager::ImageManager(QWidget *parent): ImageViewer(parent), curImage(NULL)
  , fsWatcher(this)
{
    connect(&fsWatcher,SIGNAL(fileChanged(QString)),this,SLOT(fileChanged(QString)));
    connect(&fsWatcher,SIGNAL(directoryChanged(QString)),this,SLOT(directoryChanged(QString)));
}

ImageManager::~ImageManager()
{
    ImageFactory::freeAllCache();
    disconnect(&fsWatcher,SIGNAL(fileChanged(QString)),this,SLOT(fileChanged(QString)));
    disconnect(&fsWatcher,SIGNAL(directoryChanged(QString)),this,SLOT(directoryChanged(QString)));
}

void ImageManager::fileChanged(const QString&){

}

void ImageManager::directoryChanged(const QString &){

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

void ImageManager::openFiles(const QStringList & fileList){
    if(fileList.empty()) return;
    if(fileList.size() == 1){
        openFile(fileList.first());
        return;
    }
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    openFile(fileList.at(0));
    QApplication::restoreOverrideCursor();
}
