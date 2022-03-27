#include "qmailbegin.h"
#include "ui_qmailbegin.h"
#include "QMovie"

QMailbegin::QMailbegin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QMailbegin)
{
    ///
    Qt::WindowFlags windowFlag  = Qt::Dialog;
    windowFlag                  |= Qt::WindowMinimizeButtonHint;
    windowFlag                  |= Qt::WindowMaximizeButtonHint;
    windowFlag                  |= Qt::WindowCloseButtonHint;
    setWindowFlags(windowFlag);

    ui->setupUi(this);

    ui->listWidget->setGridSize(QSize(335, 50));
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
    else {
        // 如果有用户  则将首个用户作为当前用户进行响应操作
        this->CurrentUser = alluser[0];
        // 从文件中读取信息
        inituserfromjson();

    }
    for(auto user:this->alluser){
        ui->comboBox->addItem(QString::fromStdString(user.email));
    }

    QMovie *movie = new QMovie(":/pics/loading.gif");
    ui->label->setMovie(movie);
    movie->start();




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

       // initonesinfo();
        refreshEmail();
        ui->label->setVisible(false);
        ui->pushButton_3->setEnabled(true);
        Emailstojson();
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

void QMailbegin::on_comboBox_currentIndexChanged(int index)
{
    /// 转换前先固化

    unsigned int usernumber = alluser.size();
    if(index >= 0 && index < usernumber){

        cout<< "change user "<< index<<endl;
        for(unsigned int i =0;i < usernumber;i++){
            if(this->alluser[i].email == CurrentUser.email){
                alluser[i] = CurrentUser;
                 Emailstojson();
                break;
        }

        }
        this->CurrentUser=this->alluser[index];
        ui->listWidget->clear();
        inituserfromjson();
    }

}

void QMailbegin::refreshuser(){
    ui->comboBox->clear();
    this->alluser = User::getallUserfromConf();
    for(auto user:this->alluser){
        ui->comboBox->addItem(QString::fromStdString(user.email));
    }
}
// 该函数执行前需要确保完全的刷新成功
// 目前还是仅支持单次仅删除一个吧
void QMailbegin::on_pushButton_5_clicked()
{
    cout<<"deleting..."<<endl;
  //删除选中checkbox
    for(int i = 0; i < ui->listWidget->count(); i++)
        {

            QListWidgetItem *item = ui->listWidget->item(i);
            //将QWidget 转化为QCheckBox  获取第i个item 的控件
            emailWgt *emailWgt = static_cast<class emailWgt *>(ui->listWidget->itemWidget(item));
            if(emailWgt->isCheck())
            {
                //TODO: 删除选中的邮件
                //ui->listWidget->takeItem(i);
                // 不能这么直接删  做了一次删除后会立刻生效 则顺序乱了了
                this->CurrentUser.DeleteEmail(this->CurrentUser.allUIDLs.size()-i);
                break;

            }
        }
refreshEmail();
    return ;

}

void QMailbegin::rsetText(QListWidgetItem *item){


}

void QMailbegin::initonesinfo(){

    if(this->CurrentUser.uidlEmial.size()<1){
     /// 通过已经存储的文件来初始化邮件
    nlohmann::json all_email_json ;
    string jsonpath = this->CurrentUser.email+"/allemail.json";
    this->CurrentUser.refreshUIDLs();
    ifstream inins(jsonpath,ios::in);
    if(!inins) return ;//如果打开失败则推出
    // TODO: 这里或许应该添加exception 
    inins>>all_email_json;
    int i=all_email_json.size();
    for (auto& element : all_email_json) {
       Email e(element);
            string s = to_string (i) +e.UIDL+"||" + "    from:" + e.from + "    date:" + e.date+ "    sub: " + e.subject  ;
       //       // cout<<s;
              cout<<s<<endl;
             ui->listWidget->addItem(QString::fromUtf8(&s[0]));
       this->CurrentUser.uidlEmial[e.UIDL] =e;
       i--;
    }
    inins.close();

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
    s =  qApp->applicationDirPath().toStdString() +"/"+ CurrentUser.email+"/"+this->CurrentUser.allUIDLs[sizeofemial-emailnumber-1]+".plain";
    QDesktopServices::openUrl(QUrl(QLatin1String(&s[0])));
}




/**
 * @brief QMailbegin::inituserfromjson
 * 从 json文件中读取emial信息
 */
void QMailbegin::inituserfromjson(){
    nlohmann::json all_email_json ;
    if(this->CurrentUser.email.size()<1) return ;/// 当用户不存在时不应该执行该函数

    string jsonpath = this->CurrentUser.email+"/allemail.json";
    this->CurrentUser.refreshUIDLs();
    ifstream inins(jsonpath,ios::in);
    if(inins){
        inins>>all_email_json;
        inins.close();
    }else {
        cout<<"there is no json of emails for currentuser"<<endl;
        return ;
    }

    int i=all_email_json.size();
    for (auto& element : all_email_json) {
       Email e(element);
             //string s = to_string (i)  + "    from:" + e.from + "    date:" + e.date+ "    sub: " + e.subject ;
             //ui->listWidget->addItem(QString::fromUtf8(&s[0]));
       this->CurrentUser.uidlEmial[e.UIDL] =e;
       i--;
    }
    refreshEmail();
}






/**
 * @brief QMailbegin::Emailstojson
 *  将已有邮箱信息固化为json文件
 */
void QMailbegin::Emailstojson(){
     if(this->CurrentUser.uidlEmial.size()<1) return ;/// 当用户不存在时不应该执行该函数


         nlohmann::json all_email_json = nlohmann::json::array();

         for(int i=this->CurrentUser.allUIDLs.size();i>=1;i--){
              string UIDL = this->CurrentUser.allUIDLs[this->CurrentUser.allUIDLs.size()-i];
              Email e = this->CurrentUser.uidlEmial[UIDL];
              all_email_json.push_back(e.returnjson());/// 将emial转化为json放入总json
         }

            string jsonpath = this->CurrentUser.email+"/allemail.json";
            ofstream emailjson(jsonpath);
            emailjson<<all_email_json;
            emailjson.close();

}


void QMailbegin::refreshEmail(){

        this->CurrentUser.refreshUIDLs();
        ui->listWidget->clear();
        for(auto i=this->CurrentUser.allUIDLs.size();i>=1;i--){
            string UIDL = this->CurrentUser.allUIDLs[i-1];
            if( this->CurrentUser.uidlEmial.find(UIDL)
                 ==this->CurrentUser.uidlEmial.end() ){ // 从没在map中存在过
                    this->CurrentUser.AddEmailById(i);
            }



            Email e = this->CurrentUser.uidlEmial[UIDL];
             QListWidgetItem * newItem =new QListWidgetItem();
             newItem->setSizeHint(QSize(210,220));
             this->ui->listWidget->addItem(newItem);
             emailWgt * emailwgt  = new emailWgt(this->CurrentUser.allUIDLs.size()-i,e);
            ui->listWidget->setItemWidget(newItem,emailwgt);

           connect(emailwgt,SIGNAL(chagestar(int )),this,SLOT(emailstarchange(int)));

            QApplication::processEvents();


        }


}





void QMailbegin::emailstarchange(int id){

this->CurrentUser.uidlEmial[ this->CurrentUser.allUIDLs[   this->CurrentUser.allUIDLs.size()-id-1]].star  =
  !this->CurrentUser.uidlEmial[ this->CurrentUser.allUIDLs[   this->CurrentUser.allUIDLs.size()-id-1]].star ;

return ;
}


void QMailbegin::on_QMailbegin_destroyed()
{
    Emailstojson();
}

void QMailbegin::on_pushButton_6_clicked()
{
    HELP help;
    help.exec();
}
