#include "mainwindow.h"
#include <QApplication>
#include "middleware.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Middleware middleware;
    middleware.ShowWindow();
    middleware.start();
    return a.exec();
}
