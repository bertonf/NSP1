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
#include <QFileDialog>
#include <pcap.h>
#include <pcap/pcap.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mypacket.h"
#include "readPcap.h"
#include "forging.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->resizeColumnsToContents();
    ui->pushButtonStartStop->setText("Start Capture");
    InitInterfaces(_interface.GetInterfaces());

    connect(&_readPcap, SIGNAL(AddPacketFromFileToList(MyPacket*)),
            this, SLOT(AddRow(MyPacket*)));
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
    std::string ipsrc = inet_ntoa(sin_addr);
    ui->tableWidget->setItem(numRow,1,NewItem(QString::fromStdString(ipsrc))); /*SOURCE*/
    sin_addr.s_addr = packet->getIpHeader()->daddr;
    std::string ipdest = inet_ntoa(sin_addr);
    ui->tableWidget->setItem(numRow,2,NewItem(QString::fromStdString(ipdest))); /*DESTINATION0*/
    ui->tableWidget->setItem(numRow,3,NewItem(QString::fromStdString(
                                _ipProto.getProtocolName(
                                    packet->getIpHeader()->protocol)))); /*PROTOCOL*/

    if (packet->getIpHeader()->protocol == 6) /*TCP*/
    {
        struct tcphdr *tcphdr;
        int portsrc;
        int portdest;
        tcphdr = reinterpret_cast<struct tcphdr *>(packet->getIpHeader()) + sizeof(struct iphdr);
        portsrc = htobe16(tcphdr->source);
        portdest = htobe16(tcphdr->dest);
        std::cout << "SRC = " << tcphdr->source << " - DEST = " << tcphdr->dest << std::endl;
        QString info = "Port Source = " + QString::number(portsrc) +
                        " / Port Destination = " + QString::number(portdest);
        ui->tableWidget->setItem(numRow,4,NewItem(info)); /*INFO*/
    }
    else if (packet->getIpHeader()->protocol == 17) /*UDP*/
    {
        if (ipdest == "239.255.255.250") /*protocol SSDP*/
        {
            ui->tableWidget->setItem(numRow,3,NewItem("SSDP"));
            ui->tableWidget->setItem(numRow,4,NewItem("NOTIFY HTTP")); /*INFO*/
        }
        else
        {
            struct udphdr *udphdr;
            int portsrc;
            int portdest;

            udphdr = reinterpret_cast<struct udphdr *>(packet->getIpHeader()) + sizeof(struct iphdr);
            portsrc = htobe16(udphdr->source);
            portdest = htobe16(udphdr->dest);
            QString info = "Port Source = " + QString::number(portsrc) +
                            " / Port Destination = " + QString::number(portdest);
            ui->tableWidget->setItem(numRow,4,NewItem(info)); /*INFO*/
        }

    }
}

void MainWindow::RowIPv6(MyPacket * packet, int numRow)
{
    std::cout << "IPV6" << std::endl;
    char tmp2[INET6_ADDRSTRLEN];
    inet_ntop(AF_INET6, &(packet->getIpHeader6()->ip6_src), tmp2, INET6_ADDRSTRLEN);
    std::string ipsrc = tmp2;
    ui->tableWidget->setItem(numRow,1,NewItem(QString::fromStdString(ipsrc))); /*SOURCE*/
    inet_ntop(AF_INET6, &(packet->getIpHeader6()->ip6_dst), tmp2, INET6_ADDRSTRLEN);
    std::string ipdest = tmp2;
    ui->tableWidget->setItem(numRow,2,NewItem(QString::fromStdString(ipdest))); /*DESTINATION0*/
    ui->tableWidget->setItem(numRow,3,NewItem(QString::fromStdString(
                                 _ipProto.getProtocolName(
                                     packet->getIpHeader6()->ip6_nxt)))); /*PROTOCOL*/
    if (packet->getIpHeader6()->ip6_nxt == 6) /*TCP*/
    {
        struct tcphdr *tcphdr;
        int portsrc;
        int portdest;
        tcphdr = reinterpret_cast<struct tcphdr *>(packet->getIpHeader6()) + sizeof(struct ip6_hdr);
        portsrc = htobe16(tcphdr->source);
        portdest = htobe16(tcphdr->dest);
std::cout << "SRC = " << tcphdr->source << " - DEST = " << tcphdr->dest << std::endl;
        QString info = "Port Source = " + QString::number(portsrc) +
                        " / Port Destination = " + QString::number(portdest);
        ui->tableWidget->setItem(numRow,4,NewItem(info)); /*INFO*/
    }
    else if (packet->getIpHeader6()->ip6_nxt == 17) /*UDP*/
    {
        if (ipdest == "ff01::c" ||
            ipdest == "ff02::c" ||
            ipdest == "ff05::c" ||
            ipdest == "ff08::c" ||
            ipdest == "ff0e::c") /*protocol SSDP*/
        {
            ui->tableWidget->setItem(numRow,3,NewItem("SSDP"));
            ui->tableWidget->setItem(numRow,4,NewItem("NOTIFY HTTP")); /*INFO*/
        }
        else
        {
            struct udphdr *udphdr;
            int portsrc;
            int portdest;

            udphdr = reinterpret_cast<struct udphdr *>(packet->getIpHeader6()) + sizeof(struct ip6_hdr);
            portsrc = htobe16(udphdr->source);
            portdest = htobe16(udphdr->dest);
            QString info = "Port Source = " + QString::number(portsrc) +
                            " / Port Destination = " + QString::number(portdest);
            ui->tableWidget->setItem(numRow,4,NewItem(info)); /*INFO*/
        }
    }

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

void MainWindow::AddRowFromFile(MyPacket * packet)
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

        if (packet->getBuffer()[i] >= 33 && packet->getBuffer()[i] <= 126)
        {
            tmp2 = static_cast<char>(packet->getBuffer()[i]);
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

void MainWindow::on_actionSave_triggered()
{
    pcap_t *p;
    pcap_dumper_t *pdumper;
    struct pcap_pkthdr pcaphdr;

    if (_capture.getCaptureOn())
    {
        on_pushButtonStartStop_clicked();
    }
    QString file = QFileDialog::getSaveFileName(this, "Save", "/home", "pcap file (*.pcap)");

    p = pcap_open_dead(DLT_EN10MB, 65535);
    pdumper = pcap_dump_open(p, file.toStdString().c_str());

    for (std::vector<MyPacket*>::const_iterator it = _packetTab.begin();
         it != _packetTab.end(); ++it)
    {
        pcaphdr.caplen = (*it)->getLength();
        pcaphdr.len = (*it)->getLength();
        pcap_dump(reinterpret_cast<uchar*>(pdumper), &pcaphdr, (*it)->getBuffer());
    }
    pcap_dump_close(pdumper);
}

void MainWindow::on_actionOpen_file_triggered()
{
    if (_capture.getCaptureOn())
    {
        on_pushButtonStartStop_clicked();
    }
    //ui->tableWidget->clearContents(); /*BUG*/
    QString file = QFileDialog::getOpenFileName(this, "Open", "/home", "pcap file (*.pcap)");
    _readPcap.run(file.toStdString());
}

void MainWindow::on_forgingButton_clicked()
{
    Forging *forging = new Forging();
    forging->show();
}
