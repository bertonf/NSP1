#ifndef FORGING_H
#define FORGING_H

#include <QWidget>

namespace Ui {
class Forging;
}

class Forging : public QWidget
{
    Q_OBJECT

public:
    explicit Forging(QWidget *parent = 0);
    ~Forging();
    void on_comboBox_currentTextChanged(const QString &arg1);
    void on_CancelButton_clicked();
    void on_SendButton_clicked();

private:
    Ui::Forging *ui;
};

#endif // FORGING_H
