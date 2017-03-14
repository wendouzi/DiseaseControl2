#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "imagemanager.h"
#include "QWidget"
class QLabel;
class QMenu;
class QAction;
class QPushButton;
class QMdiArea;
class ImageManager;
class QToolBar;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected slots:
    void closeEvent(QCloseEvent *event);
//    void dragEnterEvent(QDragEnterEvent * event);
//    void dropEvent(QDropEvent * event);
//    void keyPressEvent(QKeyEvent *event);
//    void resizeEvent(QResizeEvent *event);

    bool eventFilter(QObject *obj, QEvent *event);
//    void applyConfig();
//    void imageChanged(const QString &fileName = QString::null);
//    void showContextMenu(const QPoint &pos);

    void openFile();
    void changeFullScreen();
    void showAttribute();
    void switchSlideShow();
    void setting();
    void about();
private:
//    void readSettings();
//    void writeSettings();

    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void createContentMenu();

    void registerAllFunction();

    ImageManager *viewer;
    QRect attributeRect;
    QMenu *fileMenu;
    QToolBar *fileToolBar;
    QMdiArea *mdiArea;
    QLabel *readyLabel;

    QAction *openAction;
    QAction *saveAction;
    QAction *saveAsAction;
    QAction *exitAction;
    QAction *newAction;
};

#endif // MAINWINDOW_H
