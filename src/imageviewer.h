#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QWidget>
#include <QString>
#include "tooltip.h"
class VelocityTracker;
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
    qreal currentScale() const              { return scale; }
public slots:
    void changeScaleMode(int mode);
    void changeAlignMode(int mode);
    void changeAntialiasMode(int mode);
    // if color is invalid, means disabled custom background color.
    void changeBgColor(const QColor &color);

    void scrollContent(int deltaX, int deltaY);
    void scrollContent(const QPoint &delta) { scrollContent(delta.x(), delta.y()); }
    void zoomIn(double factor); // pivot is the center of this widget.
    void zoomIn(double factor, const QPoint &pivot);
protected slots:
    // override
    void paintEvent(QPaintEvent *);
    void resizeEvent ( QResizeEvent * event );

    void mouseMoveEvent ( QMouseEvent * event );
    void mousePressEvent ( QMouseEvent * event );
    void mouseReleaseEvent ( QMouseEvent * event );
private:
    bool scaleLargeThanWidget();

    void updateImageArea()
    { update(QRect((topLeft + shift).toPoint(), image.size()*scale)); }

    /*! init the value of topLeft and scale, according to the size of image
     * no use update(), no impact the value of rotate or mirrorH/mirrorV.
     */
    void layoutImage(); // determine the visible rect of the image.

    void calcScaleRatio();
    /*! updateShift() needs the value of topLeft,
     * so the order of these two functions below is important.
     */
    void calcTopLeft();    // no use update()
    void calcShift();      // no use update()

    void changeCursor(Qt::CursorShape shape); // for updateCursor()
    void updateCursor();
    void updateShift();    // use update()

    void rotatePixmap(int degree); // use update()
    QImage image;
    QString errStr; // msg to show if image is null.
    QColor bgColor;
    int scaleMode;
    int alignMode;
    int antialiasMode;

    QPointF topLeft;   //
    qreal scale;
    qreal scaleMin; //
    int rotate;
    QPointF shift;    //
    bool hasUserZoom;

    bool leftMousePressed;  // for updateCursor()
    VelocityTracker *velocityTracker;
};
inline void ImageViewer::calcTopLeft()
{
    topLeft.setX((rect().width() - image.width() * scale) / qreal(2));
    topLeft.setY((rect().height() - image.height() * scale ) / qreal(2));
}

inline void ImageViewer::changeCursor(Qt::CursorShape shape)
{
    if (cursor().shape() != shape)
        setCursor(shape);
}
#endif // IMAGEVIEWER_H
