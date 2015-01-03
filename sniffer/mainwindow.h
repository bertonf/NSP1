#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTableView>
#include <QStandardItemModel>
#include <QMainWindow>
#include <QTableWidgetItem>
#include <QThread>
#include "mypacket.h"
#include "ethernetprotocol.h"
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
    void InitInterfaces(const std::vector<std::string>& );

    QTableWidgetItem* NewItem(QString);
    const Ui::MainWindow & getUI();
public slots:
    void AddRow(MyPacket*);
private slots:
    void on_tableWidget_currentCellChanged(int currentRow, int currentColumn,
                                           int previousRow, int previousColumn);
    void on_pushButtonStartStop_clicked();

private:
    Ui::MainWindow *ui;
    QStandardItemModel tv;
    InternetProtocol _ipProto;
    EthernetProtocol _ethProto;
    std::vector<MyPacket> _packetTab;
    Capture _capture;
    Interfaces _interface;
};

#endif // MAINWINDOW_H
