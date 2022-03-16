#include "qmailbegin.h"
#include "ui_qmailbegin.h"
#include "QMovie"
QMailbegin::QMailbegin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QMailbegin)
{
    ui->setupUi(this);
    ui->label->setVisible(false);
    QMovie * move = new QMovie(":/loading.gif");
        ui->label->setMovie(move);
        ui->label->setFixedSize(100,100);
        ui->label->setScaledContents(true);

        //ui->label_gif->adjustSize();//在这里没有效果
        move->start(); //没有这一行，就不会显示任何内容
    //初始化Socket
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
       // printf("WSAStartup failed: %d\n", iResult);
    }

    // 获取到所有存在的用户 并将其赋值给currentuser
    this->alluser  = User::getallUserfromConf(); 
    if(alluser.empty()){
        //cout<<"there is no user ";
        Toast::instance().show(1,"there is no user,please input first");
    }//如果不存在已经注册过的用户  则想办法进行响应提示
    else {// 如果有用户  则将首个用户作为当前用户进行响应操作
        this->CurrentUser = alluser[0];
        //this->currentuser = &alluser[0];
    }
    for(auto user:this->alluser){
        ui->comboBox->addItem(QString::fromStdString(user.email));
    }

    QMovie *movie = new QMovie(":/pics/loading.gif");
    ui->label->setMovie(movie);
    movie->start();

  //connect(&BindNewuser,&infrom::destroyed,this,SLOT(refreshuser()));

}

QMailbegin::~QMailbegin()
{
    delete ui;
}

void QMailbegin::on_pushButton_2_clicked()
{
    SendMail s(this->CurrentUser);
    s.exec();
}

void QMailbegin::on_pushButton_4_clicked()
{
    checkMail m;
    m.exec();
}


void QMailbegin::on_pushButton_3_clicked()
{
ui->label->setVisible(true);
ui->pushButton_3->setDisabled(true);




//    QFuture<void> future = QtConcurrent::run(this,&QMailbegin::initonesinfo);
//    while(!future.isFinished())
//           {
//               QApplication::processEvents(QEventLoop::AllEvents, 100);
//               //QMessageBox::information(this, tr("success"),  tr("发送成功"),QMessageBox::Save | QMessageBox::Discard,  QMessageBox::Discard);

//           }
//    if(future.isFinished()){
//       // QMessageBox::information(this, tr("success"),  tr("发送成功"),QMessageBox::Save | QMessageBox::Discard,  QMessageBox::Discard);
//        ui->label->setVisible(false);
//        ui->pushButton_3->setEnabled(true);
//        Toast::instance().show(1, "load the top of all eamils finished!");
//    }

        initonesinfo();

        ui->label->setVisible(false);
        ui->pushButton_3->setEnabled(true);
        Toast::instance().show(1, "load the top of all eamils finished!");



}

void QMailbegin::on_pushButton_clicked()
{

  //  connect(m,&infrom::destroyed,this,&QMailbegin::on_comboBox_activated);
    BindNewuser.exec();
    refreshuser();
}

void QMailbegin::on_comboBox_activated(const QString &arg1)
{

}

void QMailbegin::on_comboBox_currentIndexChanged(const QString &arg1){

}

void QMailbegin::on_comboBox_currentIndexChanged(int index)
{
if(index >= 0 && index < alluser.size()){

    for(int i =0;i< this->alluser.size();i++){
        if(this->alluser[i].email == CurrentUser.email);
        alluser[i] = CurrentUser;
        break;
    }
     this->CurrentUser=this->alluser[index];
       ui->listWidget->clear();
    //initonesinfo();
       if( this->CurrentUser.uidlEmial.size()>1){
           for(int i=this->CurrentUser.allUIDLs.size();i>=1;i--){
               Email e = this->CurrentUser.uidlEmial[this->CurrentUser.allUIDLs[this->CurrentUser.allUIDLs.size()-i]];
               string s = to_string (i)  + "    from:" + e.from + "    date:" + e.date+ "    sub: " + e.subject ;
              // cout<<s;
               ui->listWidget->addItem(QString::fromStdString(s));
               //ui->listWidget->update();
               QApplication::processEvents();
           }
       }
}

}


void QMailbegin::refreshuser(){
    ui->comboBox->clear();
//    vector<User> tempall = User::getallUserfromConf();


//     for(int i =0;i<(int)tempall.size();i++){
//         bool isnew = true;
//            for ( int j =0;j<(int)this->alluser.size();j++){
//                if(tempall[i].email == this->alluser[j].email)
//                    isnew = false;
//            }
//         if(isnew) this->alluser.push_back(tempall[i]);
//     }

    this->alluser = User::getallUserfromConf();
    for(auto user:this->alluser){
        ui->comboBox->addItem(QString::fromStdString(user.email));
    }
   // cout<<"endd!!!!!";
}

void QMailbegin::on_pushButton_5_clicked()
{
    refreshuser();
}
void QMailbegin::rsetText(QListWidgetItem *item){


}
void QMailbegin::initonesinfo(){
//    //this->CurrentUser.getallEmailinfo();//初始化用户邮件信息 即维护 邮件的vector与map
//    int i=1;
//    //该过程需要耗时较长 想办法进行多线程的转换
//    ui->listWidget->setGridSize(QSize(335, 30));
//    for(auto a: this->CurrentUser.allUIDLs){
//      //  cout<<a<<endl;
//        //cout<<this->CurrentUser.uidlEmial.size();
//        cout<<"----------";
//        Email e =this->CurrentUser.uidlEmial[a];
//        cout<<e.UIDL<<endl;
//        string s = to_string (i)  + "    from:" + e.from + "    date:" + e.date+ "    sub: " + e.subject ;

//        ui->listWidget->addItem(QString::fromStdString(s));
//        i++;
//    }
if(this->CurrentUser.uidlEmial.size()<1){

    this->CurrentUser.refreshUIDLs();
    for(int i=this->CurrentUser.allUIDLs.size();i>=1;i--){
        this->CurrentUser.AddEmailById(i);
        Email e = this->CurrentUser.uidlEmial[this->CurrentUser.allUIDLs[this->CurrentUser.allUIDLs.size()-i]];

        string s = to_string (i)  + "    from:" + e.from + "    date:" + e.date+ "    sub: " + e.subject ;
       // cout<<s;
        ui->listWidget->addItem(QString::fromStdString(s));
        //ui->listWidget->update();
        QApplication::processEvents();
    }
}
else{

}

}

void QMailbegin::on_listWidget_clicked(const QModelIndex &index)
{
    int sizeofemial = this->CurrentUser.allUIDLs.size();
    int emailnumber =index.row();
    this->CurrentUser.RetrEmail(sizeofemial-emailnumber-1);
    string s =  qApp->applicationDirPath().toStdString() +"/"+ CurrentUser.email+"/"+this->CurrentUser.allUIDLs[sizeofemial-emailnumber-1]+".html";

    QDesktopServices::openUrl(QUrl(QLatin1String(&s[0])));
}
