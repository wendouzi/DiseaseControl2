#ifndef FILESVIEWER_H
#define FILESVIEWER_H

#include <QDockWidget>
#include <QTreeWidget>
#include <QVBoxLayout>
class FilesViewer : public QDockWidget
{
public:
    FilesViewer(QWidget *parent = 0,Qt::WindowFlags flags = 0);
    void initFeatures();
    QTreeWidget * Tree(){return filesTree;}
private:
    QTreeWidget *filesTree;
    QVBoxLayout *vboxLayout1;
    QWidget *dockWidgetContents;
};

#endif // FILESVIEWER_H
