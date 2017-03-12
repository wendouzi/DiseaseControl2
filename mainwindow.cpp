#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QToolBar"
#include "QLabel"
#include "QStatusBar"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

//    mdiArea = new QMdiArea;
//    setCentralWidget(mdiArea);

//    createActions();
//    createMenus();

//    createToolBars();
//    createContentMenu();
//    createStatusBar();

    setWindowTitle(tr("MDI Editor"));
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete fileToolBar;
    delete mdiArea;
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
  //  newAction->setIcon(QIcon(":/images/new.png"));
    newAction->setStatusTip(tr("Create a new file"));

    openAction = new QAction(tr("&Open..."), this);
    openAction->setShortcut(QKeySequence::Open);
 //   openAction->setIcon(QIcon(":/images/open.png"));
    openAction->setStatusTip(tr("Open an existing file"));

    saveAction = new QAction(tr("&Save"), this);
    saveAction->setShortcut(QKeySequence::Save);
 //   saveAction->setIcon(QIcon(":/images/save.png"));
    saveAction->setStatusTip(tr("Save the file to disk"));

    saveAsAction = new QAction(tr("Save &As..."), this);
    saveAsAction->setStatusTip(tr("Save the file under a new name"));

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("Exit the application"));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&FFile"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);
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
