#include "infrom.h"
#include "ui_infrom.h"
#include <string>
#include <QString>

#include "QMessageBox"
#include "User.h"


using namespace std;

infrom::infrom(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::infrom)
{
    ui->setupUi(this);
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
       // printf("WSAStartup failed: %d\n", iResult);
    }

}

infrom::~infrom()
{
    delete ui;
    WSACleanup();
}

void infrom::on_wqeww_clicked()
{



    string s=ui->textEdit->toPlainText().toStdString();
    string s2=ui->textEdit_2->toPlainText().toStdString();
    //int flag = fx(argc,argv);
    if(1){
        User temp(s,s2,true);
        QMessageBox::information(this, tr("success"),  tr("生成个人信息成功"),QMessageBox::Save | QMessageBox::Discard,  QMessageBox::Discard);
    } else {
        QMessageBox::critical(this, tr("error"),  tr("生成个人信息失败"),QMessageBox::Save | QMessageBox::Discard,  QMessageBox::Discard);
    }
}

void infrom::on_infrom_destroyed()
{
    emit iscloseed();
}

void infrom::iscloseed(){

}
