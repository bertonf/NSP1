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
#include "readPcap.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


    QTableWidgetItem* NewItem(QString);
    const Ui::MainWindow & getUI();
public slots:
    void AddRow(MyPacket*);
    void AddRowFromFile(MyPacket*);
private slots:
    void on_tableWidget_currentCellChanged(int currentRow, int currentColumn,
                                           int previousRow, int previousColumn);
    void on_pushButtonStartStop_clicked();

    void on_actionSave_triggered();

    void on_actionOpen_file_triggered();

private:
    Ui::MainWindow *ui;
    QStandardItemModel tv;
    InternetProtocol _ipProto;
    EthernetProtocol _ethProto;
    std::vector<MyPacket*> _packetTab;
    Capture _capture;
    ReadPcap _readPcap;
    Interfaces _interface;
    void InitInterfaces(const std::vector<std::string>& );
    void RowIPv4(MyPacket * packet, int numRow);
    void RowIPv6(MyPacket * packet, int numRow);
    void RowArp(MyPacket * packet, int numRow);
    void RowOther(MyPacket * packet, int numRow);
};

#endif // MAINWINDOW_H
