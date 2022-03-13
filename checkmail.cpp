#include "checkmail.h"

#define m_pWebWidget  ui->axWidget
#pragma execution_character_set("utf-8")
using namespace std;
checkMail::checkMail(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::checkMail)
{
    ui->setupUi(this);
    qApp->applicationDirPath();
    m_pWebWidget->setControl(QString::fromUtf8("{8856F961-340A-11D0-A96B-00C04FD705A2}"));
    m_pWebWidget->setObjectName(QString::fromUtf8("WEB BROWSER"));//设置控件的名称
    m_pWebWidget->setFocusPolicy(Qt::StrongFocus);//设置控件接收键盘焦点的方式：鼠标单击、Tab键
    m_pWebWidget->setProperty("DisplayAlerts",false); //不显示任何警告信息。
    m_pWebWidget->setProperty("DisplayScrollBars",true); // 显示滚动条
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
       // printf("WSAStartup failed: %d\n", iResult);
    }


}

checkMail::~checkMail()
{
    delete ui;
}

void checkMail::on_pushButton_clicked()
{

    QTextCodec *codec = QTextCodec::codecForName("GBK");//或者"GBK",不分大小写
    QTextCodec::setCodecForLocale(codec);

    QString s = ui->textEdit->toPlainText();
    int t = s.toInt();
    string num=to_string (t);

    QFile *file=new QFile(qApp->applicationDirPath());
    file->open(QIODevice::ReadOnly);
    QTextStream in(file);



    file->close();

    vector<User> all  = User::getallUserfromConf();
    if(!all.empty()){
        User myuser = all[0];
        cout<<myuser.email<<endl;
        myuser.getallEmailinfo();
        cout<<"get fui"<<endl;
        myuser.RetrEmail(1);
        //myuser.emailist[1];
        Email tmp = myuser.uidlEmial[myuser.allUIDLs[1]];

        this->s =  qApp->applicationDirPath().toStdString() +"/"+ myuser.email+"/"+tmp.UIDL+".html";

        m_pWebWidget->dynamicCall("Navigate(const QString&)",QString::fromStdString(this->s).trimmed());// 此处需要在Debug目录下一级html目录下存在00.html文件。 也可以自己路径



        string thispath = myuser.email+"\\"+myuser.allUIDLs[0]+".html";


    }


    //QVBoxLayout * vblayMain = new QVBoxLayout;
    //vblayMain ->addWidget(m_pWebWidget);
   // setLayout(vblayMain);
   // setWindowState(Qt::WindowMaximized);//最大化

}

string& replace_all(string& src, const string& old_value, const string& new_value) {
    // 每次重新定位起始位置，防止上轮替换后的字符串形成新的old_value
    for (string::size_type pos(0); pos != string::npos; pos += new_value.length()) {
        if ((pos = src.find(old_value, pos)) != string::npos) {
            src.replace(pos, old_value.length(), new_value);
        }
        else break;
    }
    return src;
}


void checkMail::on_pushButton_2_clicked()
{

    QDesktopServices::openUrl(QUrl(QLatin1String(&this->s[0])));
}
