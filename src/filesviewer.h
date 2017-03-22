#ifndef FILESVIEWER_H
#define FILESVIEWER_H

#include <QDockWidget>
#include <QTreeWidget>
#include <QVBoxLayout>
#include <QObject>
#include "toolkit.h"
#include "imagewrapper.h"

class FilesViewerItem {
    friend class FilesViewerList;
    FilesViewerItem(uint hash, QString path): Hash(hash), Path(path),Name(ToolKit::fileName(Path)){}
public:
    uint getHash(){ return Hash;}
    QString getPath(){ return Path;}
    QString getName(){ return Name;}
    void changeName() { Name = Path;}
private:
    uint Hash;
    QString Path;
    QString Name;
};
// manage files viewer item
class FilesViewerList {
    friend class FilesViewer;
public:
    FilesViewerList(const FilesViewerList&);
    FilesViewerList & operator = (const FilesViewerList &);
    FilesViewerList(){}
    FilesViewerList(QList<ImageWrapper*> li){
        if(!li.isEmpty())
            return;
        addItems(li);
    }

    void setImageList(QList<ImageWrapper*> li){
        list.clear();
        addItems(li);
    }

    uint getHashByName(const QString& name){
        if(name.isEmpty()) return ImageWrapper::HASH_INVALID;
        for(int s = list.size(), idx = 0; idx < s; ++idx){
            if(name == list[idx].getName())
                return list[idx].getHash();
        }
        return ImageWrapper::HASH_INVALID;
    }

private:
    void addItems(QList<ImageWrapper*> li){
        for(int s = li.size(), idx = 0; idx < s; ++idx){
            list.append(FilesViewerItem(li[idx]->getHashCode(),li[idx]->getImagePath()));
        }
        for(int s = list.size(), idx = 0; idx< s; ++idx){
            QString cur = list[idx].getName();
            for(int jdx = idx+1; jdx < s; ++jdx){
                if(cur == list[jdx].getName()){
                    list[idx].changeName();
                    list[jdx].changeName();
                }
            }
        }
    }
    QList<FilesViewerItem> list;
};

class FilesViewer :public QDockWidget
{
    Q_OBJECT
public:
    FilesViewer(QWidget *parent = 0,Qt::WindowFlags flags = 0);
    ~FilesViewer();
    void initFeatures();
    void update();
    QTreeWidget * Tree(){return tree;}
signals:
    void showImage(uint);
public slots:
    void filesChanged();
    void selectionChanged();
private slots:
    void doubleClicked(QTreeWidgetItem *item, int column);

private:
    QTreeWidget *tree;
    QVBoxLayout *vboxLayout;
    QWidget * Content;
    FilesViewerList fvlist;
};

#endif // FILESVIEWER_H
