#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTableView>
#include <QStandardItemModel>
#include <QMainWindow>
#include <QTableWidgetItem>
#include <QThread>
#include "mypacket.h"
#include "internetprotocol.h"
#include "capture.h"
#include "interfaces.h"

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

    QTableWidgetItem* NewItem(QString);
    const Ui::MainWindow & getUI();
public slots:
    void AddRow(MyPacket*);
private:
    Ui::MainWindow *ui;
    QStandardItemModel tv;
    InternetProtocol _ipProto;
    std::vector<MyPacket> _packetTab;
    Capture _capture;
    Interfaces _interface;
};

#endif // MAINWINDOW_H
