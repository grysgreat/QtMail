#ifndef CHECKMAIL_H
#define CHECKMAIL_H

#include <QDialog>
#include "checkmail.h"
#include "ui_checkmail.h"
#include <string>
#include <QString>
#include "User.h"
#include "QMessageBox"
#include "QTextStream"
#include "QFile"
#include <stdio.h>
#include <stdlib.h>
#include<QDesktopServices>

#include<QUrl>
#include <QTextCodec>

#include <QVBoxLayout>
namespace Ui {
class checkMail;
}

class checkMail : public QDialog
{
    Q_OBJECT

public:
    explicit checkMail(QWidget *parent = nullptr);
    ~checkMail();
    string s;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::checkMail *ui;
};

#endif // CHECKMAIL_H
