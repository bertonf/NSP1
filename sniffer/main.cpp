#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    int ret = 0;
    try
    {
        QApplication a(argc, argv);
        MainWindow _mainWindow;
        _mainWindow.showMaximized();
        ret = a.exec();
    }
    catch (std::exception ex)
    {
        std::cerr << "ERROR INCONNU : " << ex.what() << std::endl;
    }

    return (ret);
}
