#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H
#include "imageviewer.h"
#include "imagewrapper.h"
#include <QImage>

class ImageManager: public ImageViewer
{
public:
    ImageManager(QWidget *parent = 0);
    ~ImageManager();
    ImageWrapper *curImage;
};

#endif // IMAGEMANAGER_H
