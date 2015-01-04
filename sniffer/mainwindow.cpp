#include <iostream>
#include <iomanip>
#include <sstream>
#include <sys/socket.h>
#include <stdio.h>
#include <stdarg.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <QList>
#include <QTableWidgetItem>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mypacket.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->resizeColumnsToContents();
    ui->pushButtonStartStop->setText("Start Capture");
    InitInterfaces(_interface.GetInterfaces());

    connect(&_capture, SIGNAL(AddPacketToList(MyPacket*)),
            this, SLOT(AddRow(MyPacket*)));
   /* connect(ui->tableWidget, SIGNAL(currentCellChanged(int,int,int,int)),
            this, SLOT(on_tableWidget_currentCellChanged(int, int, int, int)));*/
   /* connect(ui->pushButtonStartStop, SIGNAL(clicked()),
            this, SLOT(on_pushButtonStartStop_clicked()));*/

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitInterfaces(const std::vector<std::string>& list)
{
    for (std::vector<std::string>::const_iterator it = list.begin();
         it != list.end(); ++it)
        ui->comboBoxInterfaces->addItem(QString::fromStdString(*it));
}

void MainWindow::RowIPv4(MyPacket * packet, int numRow)
{
    std::cout << "IPV4" << std::endl;
    struct in_addr sin_addr;

    sin_addr.s_addr = packet->getIpHeader()->saddr;
    std::string tmp = inet_ntoa(sin_addr);
    ui->tableWidget->setItem(numRow,1,NewItem(QString::fromStdString(tmp))); /*SOURCE*/
    sin_addr.s_addr = packet->getIpHeader()->daddr;
    tmp = inet_ntoa(sin_addr);
    ui->tableWidget->setItem(numRow,2,NewItem(QString::fromStdString(tmp))); /*DESTINATION0*/
    ui->tableWidget->setItem(numRow,3,NewItem(QString::fromStdString(
                                _ipProto.getProtocolName(
                                    packet->getIpHeader()->protocol)))); /*PROTOCOL*/

}

void MainWindow::RowIPv6(MyPacket * packet, int numRow)
{
    std::cout << "IPV6" << std::endl;
    char tmp2[INET6_ADDRSTRLEN];
    inet_ntop(AF_INET6, &(packet->getIpHeader6()->ip6_src), tmp2, INET6_ADDRSTRLEN);
    std::string tmp = tmp2;
    ui->tableWidget->setItem(numRow,1,NewItem(QString::fromStdString(tmp))); /*SOURCE*/
    inet_ntop(AF_INET6, &(packet->getIpHeader6()->ip6_dst), tmp2, INET6_ADDRSTRLEN);
    tmp = tmp2;
    ui->tableWidget->setItem(numRow,2,NewItem(QString::fromStdString(tmp))); /*DESTINATION0*/
    ui->tableWidget->setItem(numRow,3,NewItem(QString::fromStdString(
                                 _ipProto.getProtocolName(
                                     packet->getIpHeader6()->ip6_nxt)))); /*PROTOCOL*/
}

void MainWindow::RowArp(MyPacket * packet, int numRow)
{
    std::cout << "ARP" << std::endl;
    char macaddrsrc[6];
    char macaddrdest[6];
    char result[50];
    memcpy(macaddrsrc, packet->getEthHeader()->h_source, 6);
    memcpy(macaddrdest, packet->getEthHeader()->h_dest, 6);

    sprintf(result, "%X-%X-%X-%X-%X-%X",
            macaddrsrc[5], macaddrsrc[4], macaddrsrc[3],
            macaddrsrc[2], macaddrsrc[1], macaddrsrc[0]);
    std::string strsrc = result;
    ui->tableWidget->setItem(numRow,1,NewItem(QString::fromStdString(strsrc))); /*SOURCE*/
    sprintf(result, "%X-%X-%X-%X-%X-%X",
            macaddrdest[5], macaddrdest[4], macaddrdest[3],
            macaddrdest[2], macaddrdest[1], macaddrdest[0]);
    std::string strdest = result;
    ui->tableWidget->setItem(numRow,2,NewItem(QString::fromStdString(strdest))); /*DESTINATION0*/

    ui->tableWidget->setItem(numRow,3,NewItem(QString::fromStdString(
                             _ethProto.getProtocolName(
                                 static_cast<unsigned int>(htobe32(packet->getEthHeader()->h_proto)))))); /*PROTOCOL*/
}

void MainWindow::RowOther(MyPacket * packet, int numRow)
{
    std::cout << "OTHER" << std::endl;
    char macaddrsrc[6];
    char macaddrdest[6];
    char result[50];
    memcpy(macaddrsrc, packet->getEthHeader()->h_source, 6);
    memcpy(macaddrdest, packet->getEthHeader()->h_dest, 6);

    sprintf(result, "%X-%X-%X-%X-%X-%X",
            macaddrsrc[5], macaddrsrc[4], macaddrsrc[3],
            macaddrsrc[2], macaddrsrc[1], macaddrsrc[0]);
    std::string strsrc = result;
    ui->tableWidget->setItem(numRow,1,NewItem(QString::fromStdString(strsrc))); /*SOURCE*/
    sprintf(result, "%X-%X-%X-%X-%X-%X",
            macaddrdest[5], macaddrdest[4], macaddrdest[3],
            macaddrdest[2], macaddrdest[1], macaddrdest[0]);
    std::string strdest = result;
    ui->tableWidget->setItem(numRow,2,NewItem(QString::fromStdString(strdest))); /*DESTINATION0*/

    ui->tableWidget->setItem(numRow,3,NewItem(QString::fromStdString(
                             _ethProto.getProtocolName(
                                 static_cast<unsigned int>(htobe32(packet->getEthHeader()->h_proto)))))); /*PROTOCOL*/
}


void MainWindow::AddRow(MyPacket * packet)
{
    try
    {
        if (packet == NULL)
            return;
        std::cout << "DEBUT FONCTION AddRow()" << std::endl;
        int numRow = ui->tableWidget->rowCount();
        _packetTab.push_back(packet);
        ui->tableWidget->insertRow(numRow);
        ui->tableWidget->setItem(numRow,0,NewItem(QString::number(numRow)));
        if (packet->getIpHeader() != NULL)
        {
            RowIPv4(packet, numRow);
        }
        else if (packet->getIpHeader6() != NULL)
        {
            RowIPv6(packet, numRow);
        }
        else if (packet->getArpHeader() != NULL)
        {
            RowArp(packet, numRow);
        }
        else
        {
            RowOther(packet, numRow);
        }
        ui->tableWidget->scrollToBottom();
        ui->tableWidget->resizeColumnsToContents();
        ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
        std::cout << "END FONCTION AddRow()" << std::endl;
    }
    catch(std::exception ex)
    {
       std::cerr << "ERROR : " << ex.what() << std::endl;
    }
}

QTableWidgetItem* MainWindow::NewItem(const QString str)
{
   QTableWidgetItem *newItem = new QTableWidgetItem(str);
   return (newItem);
}

const Ui::MainWindow &MainWindow::getUI()
{
    return (*ui);
}

void MainWindow::on_tableWidget_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    (void)previousColumn;
    (void)currentColumn;
    if (currentRow == previousRow)
        return;
    std::string buffer;
    std::ostringstream oss;
    ui->textEditHexa->clear();
    ui->textEditChar->clear();

    buffer = reinterpret_cast<char*>(_packetTab[currentRow]->getBuffer());
    //oss = std::hex << buffer;

    for (size_t i = 0; i < buffer.length();i++)
    {
        oss << std::setw(2) << std::hex << std::setw(2) << std::setfill('0') << std::setw(2) << static_cast<int>(buffer[i]);
        oss << " ";
        if ((i + 1) % 8 == 0)
            oss << std::endl;
    }

    /*sprintf(result, "%X-%X-%X-%X-%X-%X",
            macaddrsrc[5], macaddrsrc[4], macaddrsrc[3],
            macaddrsrc[2], macaddrsrc[1], macaddrsrc[0]);
*/

    ui->textEditHexa->setText(QString::fromStdString(oss.str()));
    ui->textEditChar->setText(QString::fromStdString(buffer));
}

void MainWindow::on_pushButtonStartStop_clicked()
{
    std::string interface;

    ui->pushButtonStartStop->setEnabled(false);
    if (_capture.getCaptureOn())
    {
        std::cout << "Click On to Off" << std::endl;
        ui->pushButtonStartStop->setText("Start Capture");
        _capture.setCaptureOn(false);
        _capture.wait();
        ui->pushButtonStartStop->setText("Start Capture");
    }
    else
    {
        std::cout << "Click Off to On" << std::endl;
        ui->pushButtonStartStop->setText("Stop Capture");
        interface = _interface.GetInterfaces()[ui->comboBoxInterfaces->currentIndex()];
        _capture.SetNetworkInterface(interface);
        _capture.start();
    }
    ui->pushButtonStartStop->setEnabled(true);
}
