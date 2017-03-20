#include "filesviewer.h"
#include <QTreeWidgetItem>
#include <QFontDatabase>
FilesViewer::FilesViewer(QWidget *parent, Qt::WindowFlags flags):
    QDockWidget(parent,flags)
{
    dockWidgetContents = new QWidget();
    dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
    vboxLayout1 = new QVBoxLayout(dockWidgetContents);
#ifndef Q_OS_MAC
    vboxLayout1->setSpacing(6);
#endif
#ifndef Q_OS_MAC
    vboxLayout1->setContentsMargins(9, 9, 9, 9);
#endif
    vboxLayout1->setObjectName(QStringLiteral("vboxLayout1"));
    filesTree = new QTreeWidget(dockWidgetContents);
    QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
    __qtreewidgetitem->setText(0, QStringLiteral("1"));
    filesTree->setHeaderItem(__qtreewidgetitem);
    filesTree->setObjectName(QStringLiteral("fontTree"));
    filesTree->setSelectionMode(QAbstractItemView::ExtendedSelection);

    vboxLayout1->addWidget(filesTree);

    setWidget(dockWidgetContents);

   // initFeatures();
}

void FilesViewer::initFeatures(){
    QFontDatabase database;
    filesTree->setColumnCount(1);
    filesTree->setHeaderLabels(QStringList() << tr("Font"));

    foreach (QString family, database.families()) {
        const QStringList styles = database.styles(family);
        if (styles.isEmpty())
            continue;

        QTreeWidgetItem *familyItem = new QTreeWidgetItem(filesTree);
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
