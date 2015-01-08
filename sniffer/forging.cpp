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
        forger->sendARPpacket(ui->SrcIpEdit->text(), ui->DestIpEdit->text(), ui->SrcPortEdit->text(), ui->DestPortEdit->text(), ui->OperationEdit->text(), ui->SrcAddrMacEdit->text(), ui->DestAddrMacEdit->text(), ui->IntComboBox->currentText());
    else if (ui->comboBox->currentText() == "TCP")
        forger->sendTCPpacket(ui->SrcIpEdit->text(), ui->DestIpEdit->text(), ui->SrcPortEdit->text(), ui->DestPortEdit->text(), ui->SrcAddrMacEdit->text(), ui->DestAddrMacEdit->text(), ui->IntComboBox->currentText());
}

void Forging::on_CancelButton_clicked()
{
    ~Forging();
}

void Forging::on_comboBox_currentTextChanged(const QString &arg1)
{
    if (arg1 == "ARP")
        ui->OperationEdit->show();
    else if (arg1 == "TCP")
        ui->OperationEdit->show();
}
