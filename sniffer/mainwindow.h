#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTableView>
#include <QStandardItemModel>
#include <QMainWindow>
#include <QTableWidgetItem>
#include "interfaces.h"
#include "capture.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void AddRow();
    QTableWidgetItem* NewItem(QString);
    void Loop();
private:
    Interfaces _interface;
    Capture _capture;
    Ui::MainWindow *ui;
    QStandardItemModel tv;
};

#endif // MAINWINDOW_H
