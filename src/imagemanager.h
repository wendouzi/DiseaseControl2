#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H
#include "imageviewer.h"
#include "imagewrapper.h"
#include <QImage>
#include <QString>
#include <QFileSystemWatcher>
class ImageManager: public ImageViewer
{
    Q_OBJECT
public:
    ImageManager(QWidget *parent = 0);
    const QString & fileName() const { return curName;}
    const QString & filePath() const { return curPath;}
    bool hasPicture() const { return false;}
    void openFile(const QString & filePath);
    void openFiles(const QStringList & list);
    ~ImageManager();
public slots:
    void fileChanged(const QString&);
    void directoryChanged(const QString &);
signals:
    void imageChanged(const QString & fileName);
private:
    ImageWrapper *curImage;
    QString curName;
    QString curPath;
    QFileSystemWatcher fsWatcher;
};

#endif // IMAGEMANAGER_H
