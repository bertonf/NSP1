#ifndef MIDDLEWARE_H
#define MIDDLEWARE_H

#include <QThread>

#include "interfaces.h"
#include "capture.h"
#include "mainwindow.h"

class Middleware : public QThread
{
    MainWindow _mainWindow;
    Interfaces _interface;
    Capture _capture;
public:
    Middleware();
    void run();
    void ShowWindow();

};

#endif // MIDDLEWARE_H
