#include "mainwindow.h"
#include <QApplication>
#include "middleware.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow _mainWindow;
    _mainWindow.show();
    /*Middleware middleware;
    middleware.ShowWindow();
    middleware.start();*/

    return a.exec();
}
