#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H
#include "imageviewer.h"
#include "imagewrapper.h"
#include <QImage>

class ImageManager: public ImageViewer
{
public:
    ImageManager(QWidget *parent = 0);
    const QString & fileName() const { return curName;}
    const QString & filePath() const { return curPath;}
    bool hasPicture() const { return ;}
    ~ImageManager();
private:
    ImageWrapper *curImage;
    QString curName;
    QString curPath;
};

#endif // IMAGEMANAGER_H
