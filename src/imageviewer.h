#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QWidget>
#include <QString>
class ImageViewer : public QWidget
{
    Q_OBJECT
public:
    explicit ImageViewer(QWidget *parent = 0);
    ~ImageViewer();
    void loadImage(const QImage &im,
                   const QString &msg_if_no_image = QString::null);
    void updatePixmap(const QImage &image);
    bool hasPicture() const { return !image.isNull();}
    bool noPicture() const { return image.isNull();}

protected slots:
    // override
    void paintEvent(QPaintEvent *);

private:
    QImage image;
    QString errStr; // msg to show if image is null.
    QColor bgColor;
};

#endif // IMAGEVIEWER_H
