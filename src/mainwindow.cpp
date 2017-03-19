#include "mainwindow.h"
#include "config.h"
#include "QToolBar"
#include "QLabel"
#include "QStatusBar"
#include <QFileInfo>
#include <QtGui>
#include "global.h"
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
#include <QtWidgets>
#endif // QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    viewer = new ImageManager(this);
    setCentralWidget(viewer);
    viewer->installEventFilter(this);
    createActions();
    createMenus();

//    createToolBars();
//    createContentMenu();
//    createStatusBar();
    resize(Config::WindowFitSize);
    QRect rect = QApplication::desktop()->availableGeometry();
    QPoint pos = QPoint((rect.width() - Config::WindowFitSize.width())/2 + rect.left(),
                        (rect.height() - Config::WindowFitSize.height())/2 + rect.top());
    move(pos);
    readSettings();
    Config::insertConfigWatcher(this,SLOT(applyConfig()));
    setWindowTitle(tr("CDC"));
    setWindowIcon(QIcon(":/appIcon"));
}

MainWindow::~MainWindow()
{
    delete fileToolBar;
//    delete mdiArea;
    delete readyLabel;
    delete openAction;
    delete newAction;
    delete saveAction;
    delete saveAsAction;
    delete exitAction;
}

void MainWindow::createActions()
{
    newAction = new QAction(tr("&New"), this);
    newAction->setShortcut(QKeySequence::New);
    newAction->setIcon(QIcon(":/images/New.png"));
    newAction->setStatusTip(tr("Create a new file"));

    openAction = new QAction(tr("&Open..."), this);
    openAction->setShortcut(QKeySequence::Open);
    openAction->setIcon(QIcon(":/images/Open.png"));
    openAction->setStatusTip(tr("Open an existing file"));

    saveAction = new QAction(tr("&Save"), this);
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setIcon(QIcon(":/images/Save.png"));
    saveAction->setStatusTip(tr("Save the file to disk"));

    saveAsAction = new QAction(tr("Save &As..."), this);
    saveAsAction->setStatusTip(tr("Save the file under a new name"));

    aboutAction = new QAction(tr("&About"),this);

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("Exit the application"));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    connect(openAction, SIGNAL(triggered()), SLOT(openFile()));
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    aboutMenu = menuBar()->addMenu(tr("&About"));
    aboutMenu->addAction(aboutAction);
    connect(aboutAction, SIGNAL(triggered()), SLOT(about()));
}

void MainWindow::createToolBars()
{
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(newAction);
    fileToolBar->addAction(openAction);
    fileToolBar->addAction(saveAction);
    fileToolBar->addAction(saveAsAction);
}

void MainWindow::createStatusBar()
{
    readyLabel = new QLabel(tr(" Ready"));
    statusBar()->addWidget(readyLabel, 1);
}

void MainWindow::createContentMenu() {
    this->addAction(newAction);
    this->addAction(openAction);
    addAction(saveAction);
    addAction(saveAsAction);
    //设置如何显示上下文菜单
    this->setContextMenuPolicy(Qt::ActionsContextMenu);
}

void MainWindow::closeEvent(QCloseEvent *event){
    Config::cancelConfigWatcher(this,SLOT(applyConfig()));
    if(!isFullScreen()) {
        qDebug("MainWindow::closeEvent(): !isFullScreenn");
        writeSettings();
    }
    event->accept();
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event){
    switch(event->type()){
    case QEvent::ToolTip:{
    }
    case QEvent::MouseButtonDblClick:{
    }
    case QEvent::ContextMenu:{

    }
    case QEvent::Wheel:{
        QWheelEvent* e = static_cast<QWheelEvent *>(event);
        qreal factor = 0.1;
        switch(e->modifiers()){
        case Qt::ShiftModifier:
            factor = e->delta()/qreal(2400);
            break;
        case Qt::ControlModifier:
            factor = e->delta() / qreal(600);
            break;
        default:
            factor = e->delta() / qreal(1200);
            break;
        }
        viewer->zoomIn(factor, viewer->mapFromGlobal(e->globalPos()));
        break;
    }
    default:
        break;
    }
    return false;
}

void MainWindow::imageChanged(const QString &fileName){
    bool hasFile = !fileName.isEmpty();
    bool hasPicture = viewer->hasPicture();

    setWindowTitle(hasFile
                   ? QString("%1 - %2").arg(fileName).arg(Global::ProjectName())
                   : Global::ProjectName());
}

void MainWindow::openFile(){
    QString currentFile(viewer->filePath());
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
    const QString systemPicturesPath = QDesktopServices::storageLocation(QDesktopServices::PicturesLocation);
#else
    const QStringList systemPaths = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
    const QString systemPicturesPath = systemPaths.empty() ? QString::null : systemPaths.first();
#endif // QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
    QString defaultDir = (currentFile.isEmpty() ? systemPicturesPath
                                                : QFileInfo(currentFile).absoluteFilePath());
    QString fileName =
            QFileDialog::getOpenFileName(
                this, tr("Open File"), defaultDir,
                tr("Images (%1);;All Files (*)").arg(Config::supportFormats()));
    if(!fileName.isEmpty())
        viewer->openFile(fileName);
}

void MainWindow::applyConfig() {

}


void MainWindow::readSettings() {
    applyConfig();
    if(!Config::lastGeometry().isEmpty()){
        restoreGeometry(Config::lastGeometry());
        qDebug("MainWindow::readSettings()");
    }
}

void MainWindow::writeSettings() {
    Config::setLastGeometry(saveGeometry());
}

void MainWindow::changeFullScreen(){

}

void MainWindow::showAttribute(){

}

void MainWindow::switchSlideShow(){

}

void MainWindow::setting(){

}

void MainWindow::about(){
    QMessageBox::about(this,tr("About %1").arg(Global::ProjectName()),
                       Global::AboutInfo());
}
