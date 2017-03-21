#ifndef FILESVIEWER_H
#define FILESVIEWER_H

#include <QDockWidget>
#include <QTreeWidget>
#include <QVBoxLayout>
#include <QObject>
class FilesViewer :public QDockWidget
{
    Q_OBJECT
public:
    FilesViewer(QWidget *parent = 0,Qt::WindowFlags flags = 0);
    ~FilesViewer();
    void initFeatures();
    void update();
    QTreeWidget * Tree(){return tree;}
public slots:
    void filesChanged();
private:
    QTreeWidget *tree;
    QVBoxLayout *vboxLayout;
    QWidget * Content;
};

#endif // FILESVIEWER_H
