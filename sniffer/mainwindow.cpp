#include <iostream>
#include <iomanip>
#include <sstream>
#include <sys/socket.h>
#include <stdio.h>
#include <stdarg.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <linux/tcp.h>
#include <linux/udp.h>
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

    if (packet->getIpHeader()->protocol == 6) /*TCP*/
    {
        struct tcphdr *tcphdr;
        int portsrc;
        int portdest;
        tcphdr = reinterpret_cast<struct tcphdr *>(packet->getIpHeader()) + sizeof(struct iphdr);
        portsrc = tcphdr->source;
        portdest = tcphdr->dest;

        QString info = "Port Source = " + QString::number(portsrc) +
                        " / Port Destination = " + QString::number(portdest);
        ui->tableWidget->setItem(numRow,4,NewItem(info)); /*INFO*/
    }
    else if (packet->getIpHeader()->protocol == 17) /*UDP*/
    {
        struct tcphdr *udphdr;
        int portsrc;
        int portdest;
        udphdr = reinterpret_cast<struct tcphdr *>(packet->getIpHeader()) + sizeof(struct iphdr);
        portsrc = udphdr->source;
        portdest = udphdr->dest;

        QString info = "Port Source = " + QString::number(portsrc) +
                        " / Port Destination = " + QString::number(portdest);
        ui->tableWidget->setItem(numRow,4,NewItem(info)); /*INFO*/
    }
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

    sprintf(result, "%02X-%02X-%02X-%02X-%02X-%02X",
            macaddrsrc[0], macaddrsrc[1], macaddrsrc[2],
            macaddrsrc[3], macaddrsrc[4], macaddrsrc[5]);
    std::string strsrc = result;
    ui->tableWidget->setItem(numRow,1,NewItem(QString::fromStdString(strsrc))); /*SOURCE*/
    sprintf(result, "%02X-%02X-%02X-%02X-%02X-%02X",
            macaddrdest[0], macaddrdest[1], macaddrdest[2],
            macaddrdest[3], macaddrdest[4], macaddrdest[5]);
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

    sprintf(result, "%02X-%02X-%02X-%02X-%02X-%02X",
            macaddrsrc[0], macaddrsrc[1], macaddrsrc[2],
            macaddrsrc[3], macaddrsrc[4], macaddrsrc[5]);
    std::string strsrc = result;
    ui->tableWidget->setItem(numRow,1,NewItem(QString::fromStdString(strsrc))); /*SOURCE*/
    sprintf(result, "%02X-%02X-%02X-%02X-%02X-%02X",
            macaddrdest[0], macaddrdest[1], macaddrdest[2],
            macaddrdest[3], macaddrdest[4], macaddrdest[5]);
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
    char hex[20];
    std::string bufferHex;
    char str[20];
    std::string bufferStr;
    std::string tmp;
    std::string tmp2;
    ui->textEditHexa->clear();
    ui->textEditChar->clear();

    MyPacket *packet = _packetTab[currentRow];

    char result[20];
    memset(result, 0, 20);
    for (int i = 0; i < packet->getLength(); i++)
    {
        sprintf(hex, "%02X",
                packet->getBuffer()[i]);
        tmp = hex;
        bufferHex += " " + tmp;

        if (packet->getBuffer()[i] >= 33 && packet->getBuffer()[i] >= 126)
        {
            //tmp2 = reinterpret_cast<char*>(packet->getBuffer()[i]);
            sprintf(str, "%c",
                packet->getBuffer()[i]);
            tmp2 = str;
        }
        else
            tmp2 = ".";
        bufferStr += " " + tmp2;
    }
    ui->textEditHexa->setText(QString::fromStdString(bufferHex));
    ui->textEditChar->setText(QString::fromStdString(bufferStr));
}

void MainWindow::on_pushButtonStartStop_clicked()
{
    std::string interface;

    ui->pushButtonStartStop->setEnabled(false);
    if (_capture.getCaptureOn())
    {
        _capture.setCaptureOn(false);
        _capture.wait();
        ui->pushButtonStartStop->setText("Start Capture");
    }
    else
    {
        ui->pushButtonStartStop->setText("Stop Capture");
        interface = _interface.GetInterfaces()[ui->comboBoxInterfaces->currentIndex()];
        _capture.SetNetworkInterface(interface);
        _capture.start();
    }
    ui->pushButtonStartStop->setEnabled(true);
}
