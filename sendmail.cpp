#include "sendmail.h"
#include "ui_sendmail.h"
#include "QFileDialog"
#include "iostream"
#include <string>
#include <QString>
#include "QMessageBox"

using namespace std;

SendMail::SendMail(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SendMail)
{
    ui->setupUi(this);
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
       // printf("WSAStartup failed: %d\n", iResult);
    }
}

SendMail::~SendMail()
{
    delete ui;
}

void SendMail::on_pushButton_clicked()
{
    QString filepath = QFileDialog::getOpenFileName(this,"选择单个文件","./");
    ui->textBrowser->setText(filepath);


}

void SendMail::on_pushButton_2_clicked()
{
    QString to=ui->textEdit_2->toPlainText();
    string messagetext=ui->textEdit->toPlainText().toStdString();
    char buf1[100];
    string t = string(buf1);
    string PATH = qApp->applicationDirPath().toStdString()+"/"+"message";
    remove(&PATH[0]);


    cout<<PATH<<endl;
    FILE* fp = fopen(PATH.c_str(), "wb");

    User myuser = User::getallUserfromConf()[0];



    fwrite(&messagetext[0], messagetext.size() , 1, fp );
    fclose(fp);

    if(ui->textBrowser->toPlainText().size()==0){
        int argc = 5;
        char* argv[10];
        argv[0]="myemail ";
        argv[1]="send";
        //argv[2]="771582678@qq.com";
        argv[2]=&to.toStdString()[0];
        argv[3]="message";
        argv[4]="utf-8";

        myuser.SendEmail("Gmail",argv[2],argv[3],"",true);
        QMessageBox::information(this, tr("success"),  tr("发送成功"),QMessageBox::Save | QMessageBox::Discard,  QMessageBox::Discard);
    } else {
        int argc = 6;
        char* argv[10];
        argv[0]="myemail ";
        argv[1]="send";
        //argv[2]="771582678@qq.com";
        argv[2]=&to.toStdString()[0];
        argv[3]="message";
        argv[4]="utf-8";
        argv[5]=&ui->textBrowser->toPlainText().toStdString()[0];


        myuser.SendEmail("Gmail",argv[2],argv[3],argv[5],true);
        QMessageBox::information(this, tr("success"),  tr("发送成功"),QMessageBox::Save | QMessageBox::Discard,  QMessageBox::Discard);
    }
}


