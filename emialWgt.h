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
    int id;
public:
    explicit emailWgt(QWidget *parent = nullptr);
    emailWgt(int ids,Email e,QWidget *parent = nullptr);
    ~emailWgt();
    bool isCheck();
signals:
    void chagestar(int);

private slots:
    void on_pushButton_star_clicked();

private:
    Ui::emailWgt *ui;
};

#endif // EMIALWGT_H
