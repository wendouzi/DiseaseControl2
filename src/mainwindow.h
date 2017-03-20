#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "imagemanager.h"
#include "QWidget"
#include "filesviewer.h"
#include <QtGui>
#include <QVBoxLayout>
class QLabel;
class QMenu;
class QAction;
class QPushButton;
class QMdiArea;
class ImageManager;
class QToolBar;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected slots:
    void closeEvent(QCloseEvent *event);
    void dragEnterEvent(QDragEnterEvent * event);
    void dropEvent(QDropEvent * event);
//    void keyPressEvent(QKeyEvent *event);
//    void resizeEvent(QResizeEvent *event);

    bool eventFilter(QObject *obj, QEvent *event);
    void applyConfig();
    void imageChanged(const QString &fileName = QString::null);
//    void showContextMenu(const QPoint &pos);

    void openFile();
    void changeFullScreen();
    void showAttribute();
    void switchSlideShow();
    void setting();
    void about();
private:
    void readSettings();
    void writeSettings();
    bool maybeSave();
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void createContentMenu();
    void registerAllFunction();

    ImageManager *viewer;
    FilesViewer * filesviewer;
    QVBoxLayout * centerLayout;
    QVBoxLayout * filesviewLayout;
    QRect attributeRect;
    QMenu *fileMenu;
    QMenu * aboutMenu;
    QToolBar *fileToolBar;
    QMdiArea *mdiArea;
    QLabel *readyLabel;

    QAction *openAction;
    QAction *saveAction;
    QAction *saveAsAction;
    QAction *exitAction;
    QAction *newAction;
    QAction *aboutAction;
};

#endif // MAINWINDOW_H
