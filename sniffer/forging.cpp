#include "forger.h"
#include "forging.h"
#include "ui_forging.h"

Forging::Forging(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Forging)
{
    ui->setupUi(this);
}

Forging::~Forging()
{
    delete ui;
}

void Forging::on_SendButton_clicked()
{
    Forger *forger = new Forger();

    if (ui->comboBox->currentText() == "ARP")
    {}    //forger->sendARPpacket(ui->srcAddrMacEdit->text().toStdString().c_str(), ui->destAddrMacEdit->text().toStdString().c_str(), ui->srcIpEdit->text().toStdString().c_str(), ui->destIpEdit->text().toStdString().c_str(), ui->operationEdit->text().toStdString().c_str(), ui->intComboBox->currentText().toStdString().c_str());
    else if (ui->comboBox->currentText() == "TCP")
        forger->sendTCPpacket(ui->srcIpEdit->text().toStdString().c_str(), ui->destIpEdit->text().toStdString().c_str(), atoi(ui->srcPortEdit->text().toStdString().c_str()),
                              atoi(ui->destPortEdit->text().toStdString().c_str()), ui->srcAddrMacEdit->text().toStdString().c_str(), ui->destAddrMacEdit->text().toStdString().c_str(),
                              ui->intComboBox->currentText().toStdString().c_str(), (char *)ui->dataTextEdit->toPlainText().toStdString().c_str());
}

void Forging::on_CancelButton_clicked()
{
    delete ui;
}

void Forging::on_comboBox_currentTextChanged(const QString &arg1)
{
    if (arg1 == "ARP")
        ui->operationEdit->show();
    else if (arg1 == "TCP")
        ui->operationEdit->hide();
}
