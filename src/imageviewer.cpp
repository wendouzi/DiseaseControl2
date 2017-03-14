#include "imageviewer.h"
#include <QPainter>
#include "config.h"
#include <QPaintEvent>
#include <QDebug>
#include <iostream>
ImageViewer::ImageViewer(QWidget *parent) : QWidget(parent)
,bgColor(Config::DefaultBgColor)
{

}

ImageViewer::~ImageViewer(){

}

void ImageViewer::paintEvent(QPaintEvent *e){
    QPainter painter(this);
    if(bgColor.isValid())
        painter.fillRect(e->rect(),bgColor);
    if(noPicture() && !errStr.isEmpty()) {
        painter.drawText(rect(), Qt::AlignCenter, errStr);
        return;
    }
    painter.drawImage(Config::OriginPoint, image);
}

void ImageViewer::loadImage(const QImage &im,
               const QString &msg_if_no_image){
    image = im;
    errStr = msg_if_no_image;
    repaint();
}

void ImageViewer::updatePixmap(const QImage &im){
    image = im;
    update();
}
