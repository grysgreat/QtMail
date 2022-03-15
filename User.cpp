//
// Created by HAN on 2022/3/10.
//
#include "User.h"
bool isinit = false;

User::User(){
    this->email ="emails";
    this->password ="passwords";
}

User::User(string emails, string passwords,bool init) {
    try {
        POP3Connector(emails, passwords);
       // SMTPConnector(emails,passwords);
        SaveInfoToFile(emails, passwords);
        printf("binding success!\n");
    }
    catch (Exception e) {
        e.Print();
    }
    this->email = emails;
    this->password =passwords;
    string md = "md ";
    string  ttt =(md + this->email).c_str();
    char*p=(char*)ttt.data();
    system(p);

}

User::User(string emails, string passwords){
    this->email = emails;
    this->password =passwords;
}

/**
 * 获取所有已经验证的用户 vector
 *
 * @return
 */
vector<User> User::getallUserfromConf() {
    vector<User> uu;
    string addr;
    string pass;
    char buf[100];
    GetModuleFileNameA(NULL, buf, 100);
    string t = string(buf);
    string PATH = t.substr(0, t.rfind('\\'));
    vector <string> alle;
    getFiles(PATH,alle);

    for (int i = 0; i <alle.size(); ++i) {
        cout<<alle[i]<<endl;
        addr = alle[i];
        GetInfoFromFile(addr, pass);
        uu.push_back(User(addr,pass));
    }
    if(alle.empty())printf("you did not bind before\n");
    //else
    return uu;
}


User::~User() {
  //  delete this->pop3;
   // delete this->smtp;
  // WSACleanup();
}

void User::getallEmailinfo() {
    POP3Connector pop3(this->email, this->password);
    this->emailist =  pop3.List(-1);
    this->allUIDLs = pop3.getallUIDL();
    int email_number  = emailist.size();
    for (int i = 0; i <email_number; ++i) {
        //this->Emailid[emailist[i].UIDL] = (email_number-i);
        emailist[i].SetUIDL(allUIDLs[i]);
        this->uidlEmial[allUIDLs[i]] = emailist[i];

    }
}


bool User::refreshemail() {
    bool is_new = false;
    POP3Connector pop3(this->email, this->password);
    this->allUIDLs = pop3.getallUIDL();
    Email temp;
    int allemailnumber =  this->allUIDLs.size() ;
    for (int i = 0; i < allemailnumber; ++i) {
        if(this->uidlEmial.find(allUIDLs[i]) == this->uidlEmial.end()){//说明收到了新邮件 更新 ;
            is_new = true;
            temp  = pop3.getEmailByTop(allemailnumber-i);
            this->uidlEmial[allUIDLs[i]] = temp;
        }
        else {
            break;
        }
    }
    return is_new;
}

void User::RetrEmail(int id) {

        try{

            POP3Connector pop3(this->email, this->password);
            Email retremail = this->uidlEmial[this->allUIDLs[id]];
            cout<<this->allUIDLs[id];
            pop3.Retr(id+1,this->allUIDLs[id]);
            }

    catch (Exception e) {
        e.Print();
    }
}

void User::SendEmail(string subject,const string& emialName,string contextpath,string attachname,bool isutf8) {
   // if ((argc == 4 || argc == 5 || argc == 6) )
   //myemail send username@xxxx.xx contentfilename [utf-8] [attachmentfilename]


   string charset = "gb18030";
   MIMEContent cont("multipart/alternative;", "8Bit");
   if (!isutf8) {
       cont.AddMIMEContent(new MIMEContent("text/plain; charset=\"" + charset + "\";", "base64", contextpath));
   }
   else{
       charset = "utf-8";
       cont.AddMIMEContent(new MIMEContent("text/plain; charset=\"" + charset + "\";", "base64",contextpath));
   }

   if (!attachname.empty()) {
       cont.AddMIMEContent(new MIMEContent("application/octet-stream;",
                                                            "base64", attachname, "attachment;"));
   }


   string content = Email().SetFrom(this->email).SetTo(emialName).SetSubject(subject)
           .SetMIMEContent(&cont)
           .BuidEmailString();

   SMTPConnector smtp(this->email, this->password);
   if (!smtp.SendEmail(emialName, content)) {
       throw Exception("---------send email failed-------");
   }
   else printf("send success!\n");

}

void User::DeleteEmail(int id) {
    try {
        POP3Connector pop3(this->email, this->password);
        pop3.Delt(id);
    }catch (Exception e){
        cout<<"Delete fails"<<endl;
    }
}

