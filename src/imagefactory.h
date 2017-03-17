#ifndef IMAGEFACTORY_H
#define IMAGEFACTORY_H
#include <QList>
class ImageWrapper;
class ImageFactory
{
public:
    static ImageWrapper* getImageWrapper(const QString&filePath);
    static void freeAllCache();
    static ImageWrapper* findImageByHash(const uint hash);
    static ImageWrapper* newOrReuseImage();
    static void waitForImageReady(ImageWrapper*image);
private:
    static QList<ImageWrapper*> list;
    static void freeImage(ImageWrapper*image);
};

#endif // IMAGEFACTORY_H
