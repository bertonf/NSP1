#include <QList>
#include <QTableWidgetItem>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

void MainWindow::AddRow(MyPacket const & packet)
{
    int j = ui->tableWidget->rowCount();

    ui->tableWidget->insertRow(j);
    ui->tableWidget->setItem(j,0,NewItem(QString::number(j)));

    /*
    ui->tableWidget->setItem(j,0,NewItem("Test1"));
    ui->tableWidget->setItem(j,1,NewItem("Test2"));
    ui->tableWidget->setItem(j,2,NewItem("Test3"));
    ui->tableWidget->setItem(j,3,NewItem("Test4"));
    ui->tableWidget->setItem(j,4,NewItem("Test5"));
    */

    ui->tableWidget->scrollToBottom();
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

