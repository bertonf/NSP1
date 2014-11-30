#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTableView>
#include <QStandardItemModel>
#include <QMainWindow>
#include <QTableWidgetItem>
#include <QThread>
#include "mypacket.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void InitInterfaces(const std::list<std::string>& );
    void AddRow(MyPacket const & packet);
    QTableWidgetItem* NewItem(QString);
    const Ui::MainWindow & getUI();
private:
    Ui::MainWindow *ui;
    QStandardItemModel tv;
    //Middleware *_mw;

};

#endif // MAINWINDOW_H
