#ifndef EMIALWGT_H
#define EMIALWGT_H

#include <QWidget>
#include <QStyleOption>
#include <QString>
#include "ui_emailWgt.h"
#include "Email.h"
#include <string>

namespace Ui {
class emailWgt;
}

class emailWgt : public QWidget
{
    Q_OBJECT

public:
    explicit emailWgt(QWidget *parent = 0);
    emailWgt(Email e,QWidget *parent = 0);
    ~emailWgt();

private:
    Ui::emailWgt *ui;
};

#endif // EMIALWGT_H
