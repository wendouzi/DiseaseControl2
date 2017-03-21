#include "filesviewer.h"
#include <QTreeWidgetItem>
#include <QFontDatabase>
#include "langconfig.h"
#include "imagefactory.h"
#include "toolkit.h"
FilesViewer::FilesViewer(QWidget *parent, Qt::WindowFlags flags):
    QDockWidget(parent,flags)
{
    Content = new QWidget();
    Content->setObjectName(QStringLiteral("FilesViewerContent"));
    vboxLayout = new QVBoxLayout(Content);
#ifndef Q_OS_MAC
    vboxLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
    vboxLayout->setContentsMargins(9, 9, 9, 9);
#endif
    vboxLayout->setObjectName(QStringLiteral("FilesViewervboxLayout"));
    tree = new QTreeWidget(Content);
    QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
    __qtreewidgetitem->setText(0, LangConfig::FilesViewerTitle);
    tree->setHeaderItem(__qtreewidgetitem);
    tree->setObjectName(QStringLiteral("FilesViewervTree"));
    tree->setSelectionMode(QAbstractItemView::ExtendedSelection);

    vboxLayout->addWidget(tree);

    setWidget(Content);
    if(connect(IMAGEFACTORY,SIGNAL(filesChanged()),SLOT(filesChanged())))
        qDebug("FilesViewer connect error");
    //  initFeatures();
}

FilesViewer::~FilesViewer(){
    disconnect(IMAGEFACTORY,SIGNAL(filesChanged()),this,SLOT(filesChanged()));
}

void FilesViewer::update(){
    tree->clear();
    QList<ImageWrapper*> list = IMAGEFACTORY->files();
    qDebug("list size:%d",list.size());
    foreach(ImageWrapper* image, list){
        if(!image)
            continue;
        QTreeWidgetItem *familyItem = new QTreeWidgetItem(tree);
        QString name = ToolKit::fileName(image->getImagePath());
        familyItem->setText(0, name);
        qDebug("imagepath:%s",qPrintable(name));
        familyItem->setCheckState(0, Qt::Unchecked);
    }
}

void FilesViewer::filesChanged(){
    update();
}


void FilesViewer::initFeatures(){
    QFontDatabase database;
    tree->setColumnCount(1);
    tree->setHeaderLabels(QStringList() << tr("Font"));

    foreach (QString family, database.families()) {
        const QStringList styles = database.styles(family);
        if (styles.isEmpty())
            continue;

        QTreeWidgetItem *familyItem = new QTreeWidgetItem(tree);
        familyItem->setText(0, family);
        familyItem->setCheckState(0, Qt::Unchecked);

        foreach (QString style, styles) {
            QTreeWidgetItem *styleItem = new QTreeWidgetItem(familyItem);
            styleItem->setText(0, style);
            styleItem->setCheckState(0, Qt::Unchecked);
            styleItem->setData(0, Qt::UserRole, QVariant(database.weight(family, style)));
            styleItem->setData(0, Qt::UserRole + 1, QVariant(database.italic(family, style)));
        }
    }
}
