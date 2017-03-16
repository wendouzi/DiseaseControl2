#ifndef IMAGEWRAPPER_H
#define IMAGEWRAPPER_H

#include <QImage>
#include "imageheader.h"
class ImageWrapper:public QObject
{
public:
    ImageWrapper();
    virtual void load(const QString& filePath, bool preReading);
private:
    enum {
        REGULAR_FLAG = 0x0,
    };
    QImage image;
    QString imagePath;
    QString imageFormat;
    QString imageName;
    QString attributes;
    uint formatFlag;
    ImageHeader * header;


};

#endif // IMAGEWRAPPER_H
