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
    InitInterfaces(_interface.GetInterfaces());
    _capture.SetNetworkInterface("wlan0");
    _capture.start();
    connect(&_capture, SIGNAL(AddPacketToList(MyPacket*)),
            this, SLOT(AddRow(MyPacket*)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitInterfaces(const std::list<std::string>& list)
{
    for (std::list<std::string>::const_iterator it = list.begin();
         it != list.end(); ++it)
        ui->comboBoxInterfaces->addItem(QString::fromStdString(*it));
}

void MainWindow::AddRow(MyPacket * packet)
{
    try
    {
        int j = ui->tableWidget->rowCount();
        int i = 0;
        _packetTab.push_back(*packet);
        ui->tableWidget->insertRow(j);
        ui->tableWidget->setItem(j,i++,NewItem(QString::number(j)));

        if (packet->getIpHeader()->version != 6){
        struct in_addr sin_addr;

        sin_addr.s_addr = packet->getIpHeader()->saddr;
        std::string tmp = inet_ntoa(sin_addr);
        ui->tableWidget->setItem(j,i++,NewItem(QString::fromStdString(tmp))); /*SOURCE*/
        sin_addr.s_addr = packet->getIpHeader()->daddr;
        tmp = inet_ntoa(sin_addr);
        ui->tableWidget->setItem(j,i++,NewItem(QString::fromStdString(tmp))); /*DESTINATION0*/
        }
        else
        {
            char tmp2[INET6_ADDRSTRLEN];
            inet_ntop(AF_INET6, &(packet->getIpHeader6()->ip6_src), tmp2, INET6_ADDRSTRLEN);
            std::string tmp = tmp2;
            ui->tableWidget->setItem(j,i++,NewItem(QString::fromStdString(tmp))); /*SOURCE*/
            inet_ntop(AF_INET6, &(packet->getIpHeader6()->ip6_dst), tmp2, INET6_ADDRSTRLEN);
            tmp = tmp2;
            ui->tableWidget->setItem(j,i++,NewItem(QString::fromStdString(tmp))); /*DESTINATION0*/
        }

        //if (packet->getIpHeader()->version != 6)
        if (1)
        {
            ui->tableWidget->setItem(j,i,NewItem(QString::fromStdString(
                                         _ipProto.getProtocolName(
                                             packet->getIpHeader()->protocol)))); /*PROTOCOL*/
        }
        else
        {
            ui->tableWidget->setItem(j,i,NewItem(QString::fromStdString(
                                         _ipProto.getProtocolName(
                                             packet->getIpHeader6()->ip6_nxt)))); /*PROTOCOL*/
        }
        ui->tableWidget->setItem(j,++i,NewItem("Test5")); /*Info*/
        ui->tableWidget->scrollToBottom();
    }
    catch(std::exception ex)
    {
       std::cerr << "ERROR" << std::endl;
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

