#include "mainwindow.h"
#include "config.h"
#include "QToolBar"
#include "QLabel"
#include "QStatusBar"
#include <QFileInfo>
#include <QtGui>
#include "global.h"
#include "toolkit.h"
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
#include <QtWidgets>
#endif // QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    viewer = new ImageManager(this);
    viewer->installEventFilter(this);
    centerLayout = new QVBoxLayout(viewer);
#ifndef Q_OS_MAC
    centerLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
    centerLayout->setContentsMargins(9, 9, 9, 9);
#endif
    centerLayout->setObjectName(QStringLiteral("centerLayout"));
    setCentralWidget(viewer);

    createActions();
    createMenus();

    filesviewer = new FilesViewer(this);
    filesviewer->setObjectName(QStringLiteral("Files View"));
    filesviewer->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
    if(!connect(filesviewer,SIGNAL(showImage(uint)),viewer,SLOT(showImage(uint))))
        qDebug("filesviewer and viewer connect error");
 //   filesviewer->setGeometry(Config::AutoFilesViewGeometry);
    this->addDockWidget(static_cast<Qt::DockWidgetArea>(1),filesviewer);

    //  filesviewer->setWidget(viewer);
    //  setCentralWidget(filesviewer);


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
    setAcceptDrops(true);
}

MainWindow::~MainWindow()
{
    disconnect(filesviewer,SIGNAL(showImage(uint)),viewer,SLOT(showImage(uint)));
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
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
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
    switch( QMessageBox::information( this, tr("DCD"),
                                      tr("Do you really want to log out DCD?"),
                                      tr("Yes"), tr("No"),
                                      0, 1 ) )
    {
    case 0:
        event->accept();
        break;
    case 1:
    default:
        event->ignore();
        break;
    }

}

void MainWindow::dragEnterEvent(QDragEnterEvent *event){
    const QMimeData *mimeData = event->mimeData();
    if (event->mimeData()->hasUrls()){
        QList<QUrl> urlList(mimeData->urls());
        QFileInfo fileInfo;
        for (int i = 0; i < urlList.size(); ++i) {
            fileInfo.setFile(urlList.at(i).toLocalFile());
            if(fileInfo.isFile()){
//                    && FORMAT_LIST.contains(fileInfo.suffix().toLower())){
                event->acceptProposedAction();
                break;
            }
        }
    }
}

void MainWindow::dropEvent(QDropEvent * event){
    const QMimeData *mimeData = event->mimeData();
    if (mimeData->hasUrls()) {
        QList<QUrl> urlList(mimeData->urls());
        QStringList fileList;
        for(int size = urlList.size(), i=0; i < size; ++i)
            fileList.append(urlList.at(i).toLocalFile());
        fileList = ToolKit::getFilesExist(fileList);   ///
        if(!fileList.empty())
            viewer->openFiles(fileList);
    }

    event->acceptProposedAction();
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

bool MainWindow::maybeSave(){
    if (true) {
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, tr("Application"),
                     tr("The document has been modified.\n"
                        "Do you want to save your changes?"),
                     QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        if (ret == QMessageBox::Save)
         //   return save();
            return true;
        else if (ret == QMessageBox::Cancel)
            return false;
    }
    return true;
}
