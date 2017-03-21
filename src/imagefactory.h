#ifndef IMAGEFACTORY_H
#define IMAGEFACTORY_H
#include <QList>
#include <QString>
#include "imagewrapper.h"
#include <QMutex>
#include <QObject>
#define IMAGEFACTORY ImageFactory::instance()

class ImageFactory: public QObject
{
    Q_OBJECT
public:
    ImageWrapper* getImageWrapper(const QString&filePath);
    void freeAllCache();
    ImageWrapper* findImageByHash(const uint hash);
    ImageWrapper* newOrReuseImage();
    void waitForImageReady(ImageWrapper*image);
    QList<ImageWrapper*> files(){return list;}
    static ImageFactory* instance(){
        QMutex mutex;
        if(!sInstance){
            mutex.lock();
            if(!sInstance){
                sInstance = new ImageFactory;
            }
            mutex.unlock();
        }
        return sInstance;
    }

signals:
    void filesChanged();
private:
    ImageFactory();
    int curIndex;
    QList<ImageWrapper*> list;
    void freeImage(ImageWrapper*image);
    static ImageFactory * sInstance;
};

#endif // IMAGEFACTORY_H
