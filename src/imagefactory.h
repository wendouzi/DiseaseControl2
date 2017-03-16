#ifndef IMAGEFACTORY_H
#define IMAGEFACTORY_H
#include <QList>
class ImageWrapper;
class ImageFactory
{
public:
    static ImageWrapper* getImageWrapper(const QString&filePath);
    static void freeAllCache();
private:
    static QList<ImageWrapper*> list;
};

#endif // IMAGEFACTORY_H
