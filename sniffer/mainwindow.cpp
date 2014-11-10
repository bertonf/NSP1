#include <QList>
#include <QTableWidgetItem>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for (std::list<std::string>::const_iterator it = _interface.GetInterfaces().begin();
         it != _interface.GetInterfaces().end(); ++it)
        ui->comboBoxInterfaces->addItem(QString::fromStdString(*it));

    this->AddRow();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::AddRow()
{
    int j = ui->tableWidget->rowCount();

    ui->tableWidget->insertRow(j);
    ui->tableWidget->setItem(j,0,NewItem("Test1"));
    ui->tableWidget->setItem(j,1,NewItem("Test2"));
    ui->tableWidget->setItem(j,2,NewItem("Test3"));
    ui->tableWidget->setItem(j,3,NewItem("Test4"));
    ui->tableWidget->setItem(j,4,NewItem("Test5"));
}

QTableWidgetItem* MainWindow::NewItem(const QString str)
{
   QTableWidgetItem *newItem = new QTableWidgetItem(str);
   return (newItem);
}

void MainWindow::Loop()
{


}
