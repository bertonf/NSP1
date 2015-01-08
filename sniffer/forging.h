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

private:
    Ui::Forging *ui;
};

#endif // FORGING_H
