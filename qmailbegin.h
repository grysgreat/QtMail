#ifndef QMAILBEGIN_H
#define QMAILBEGIN_H

#include <QDialog>

#include "mainwindow.h"
#include "infrom.h"
#include <string>
#include <QString>

#include "QMessageBox"
#include "QTextStream"
#include "QFile"
#include "checkmail.h"
#include "sendmail.h"
# include<vector>
#include "User.h"
#include <QFuture>
#include <QtConcurrent/QtConcurrent>
#include<QMovie>
#include "toast.h"
#include <QListWidgetItem>
#include <QListWidget>
#include <QLabel>
#include"json.hpp"

#include <fstream>


namespace Ui {
class QMailbegin;
}

class QMailbegin : public QDialog
{
    Q_OBJECT

public:
    explicit QMailbegin(QWidget *parent = nullptr);
    ~QMailbegin();
    //获取的全部user列表
    vector<User> alluser;
    //当前用户
    User CurrentUser;
    void rsetText(QListWidgetItem *item);
    infrom BindNewuser;



private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_comboBox_activated(const QString &arg1);
    void on_comboBox_currentIndexChanged(int index);

    void refreshuser();
    void on_pushButton_5_clicked();
   void initonesinfo();
   void on_listWidget_clicked(const QModelIndex &index);
   void inituserfromjson();
  void Emailstojson();
   void refreshEmail();
   void on_QMailbegin_destroyed();

private:
    Ui::QMailbegin *ui;
};

#endif // QMAILBEGIN_H
