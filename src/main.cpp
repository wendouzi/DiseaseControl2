#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow m;
    m.show();

    return app.exec();
}
