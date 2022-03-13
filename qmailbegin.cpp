#include "qmailbegin.h"
#include "ui_qmailbegin.h"

QMailbegin::QMailbegin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QMailbegin)
{
    ui->setupUi(this);
    //初始化Socket
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
       // printf("WSAStartup failed: %d\n", iResult);
    }


    // 获取到所有存在的用户 并将其赋值给currentuser
    this->alluser  = User::getallUserfromConf(); 
    if(alluser.empty()){
        cout<<"there is no user ";
    }//如果不存在已经注册过的用户  则想办法进行响应提示
    else {// 如果有用户  则将首个用户作为当前用户进行响应操作
        this->CurrentUser = alluser[0];
    }
    for(auto user:this->alluser){
        ui->comboBox->addItem(QString::fromStdString(user.email));
    }


}

QMailbegin::~QMailbegin()
{
    delete ui;
}

void QMailbegin::on_pushButton_2_clicked()
{
    SendMail s;
    s.exec();
}

void QMailbegin::on_pushButton_4_clicked()
{
    checkMail m;
    m.exec();
}



void QMailbegin::on_pushButton_3_clicked()
{
    cout<<"11";
    this->CurrentUser.getallEmailinfo();//初始化用户邮件信息 即维护 邮件的vector与map
    cout<<"22";
    int i=1;
    //该过程需要耗时较长 想办法进行多线程的转换
    for(auto a: this->CurrentUser.allUIDLs){
      //  cout<<a<<endl;
        //cout<<this->CurrentUser.uidlEmial.size();
        cout<<"----------";
        Email e =this->CurrentUser.uidlEmial[a];
        cout<<e.UIDL<<endl;
        string s = to_string (i)  + "    from:" + e.from + "    date:" + e.date+ "    sub: " + e.subject ;

        ui->listWidget->addItem(QString::fromStdString(s));
        i++;
    }



}

void QMailbegin::on_pushButton_clicked()
{
    infrom m;
    m.exec();
    ui->comboBox->clear();
    this->alluser  = User::getallUserfromConf();
    for(auto user:this->alluser){
        ui->comboBox->addItem(QString::fromStdString(user.email));
    }
    cout<<"endd!!!!!";
}

void QMailbegin::on_comboBox_activated(const QString &arg1)
{

}

void QMailbegin::on_comboBox_currentIndexChanged(const QString &arg1){}

void QMailbegin::on_comboBox_currentIndexChanged(int index)
{

    this->CurrentUser=this->alluser[index];
}
