#include "imagefactory.h"

#include <QRunnable>
#include <QThreadPool>
#include "imagewrapper.h"

QList<ImageWrapper*> ImageFactory::list;

class Runnable : public QRunnable
{
public:
    Runnable(ImageWrapper* iw, const QString & filePath, bool preReading = true)
        : image(iw), path(filePath), ispreReading(preReading){}
    void run(){
        image->load(path, isPreReading);
    }

private:
    ImageWrapper * image;
    QString path;
    bool isPreReading;
};

