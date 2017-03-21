#ifndef IMAGEWRAPPER_H
#define IMAGEWRAPPER_H

#include <QImage>
#include "imageheader.h"

class Cache {
public:
    enum { HASH_INVALID = 0 };
    Cache() : hashCode(HASH_INVALID), isReady(false) {}
    bool isValid() const { return hashCode > HASH_INVALID && isReady;}
    uint getHashCode() const { return hashCode;}
    bool getReady() const { return isReady;}
    void setHashCode(uint hc) { hashCode = hc;}
    void setReady(bool ready) { isReady = ready;}
protected:
    uint hashCode;
    volatile bool isReady;
private:
    Cache(const Cache & r);
    Cache & operator = (const Cache &);
};

class ImageWrapper:public QObject, public Cache
{
public:
    ImageWrapper();
    virtual ~ImageWrapper();
    virtual void load(const QString& filePath, bool preReading);
    virtual QImage currentImage();
    virtual QString attibute();
    virtual QString getImagePath(){return imagePath;}
private:
    enum {
        REGULAR_FLAG = 0x0,
        GEOTIFF = 0x1,
    };
    QImage image;
    QString imagePath;
    QString imageFormat;
    QString attributes;
    int imageFrames;
    int currentFrame;
    uint formatFlag;
    ImageHeader * header;


};

#endif // IMAGEWRAPPER_H
