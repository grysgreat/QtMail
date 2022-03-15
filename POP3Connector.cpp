#include "POP3Connector.h"
#include "util.h"




POP3Connector::	POP3Connector(string emailAddress, string password) :TCPConnector(GetEmailServerIP("pop", emailAddress), port) {
		this->emailAddress = emailAddress;
		this->password = password;
		string s = "user " + GetUserFromEmailAddress(emailAddress) + "\r\n";
		//string s = "user " + emailAddress + "\r\n";
		Receive(2000);   //
		if (Send(s)) {
			string ret = Receive(2000);
			if (ret.length() > 0 && ret[0] == '+') {
				s = "pass " + password + "\r\n";
				if (Send(s)) {
					ret = Receive(2000);
					if (ret.length() <= 0 || ret[0] != '+') throw Exception(ret);

				}
				else throw Exception("Send failed with CML " + s);
			}
			else throw Exception(ret);
		}
		else throw Exception("Send failed with CML " + s);
	}


//closetodo: 针对user中数据结构的更改需要进行更新  遍历top 并进行更新
vector<Email> POP3Connector::List(int count ) {
    vector<Email> allEmail;
  //  vector <string> emailuidl;
		int emailCount = 0;
		if (Send("stat\r\n")) {
			string ret;
			ret = Receive(100);
			if (ret.length() > 0 && ret[0] == '+') {
				vector<string> res;
				SplitString(res, ret, ' ');
				sscanf(res[1].c_str(), "%d\n", &emailCount);
				//printf("ID\tFrom\tTo\tDate\tSubject\tCount=%d\n", emailCount);
				if (count == -1) count = emailCount;
				if (count > emailCount) count = emailCount;
				for (int i = emailCount; i > emailCount - count; i--) {
					char buf[20];
					sprintf(buf, "%d", i);
					//printf("%d\t", i);
					if (Send("top " + string(buf) + " 1\r\n")) {
						string ret = Receive(-1);
						if (ret.length() > 0 && ret[0] == '+') {
							//Email().FillTopInfo(ret).PrintTopInfo();
							Email temp = Email().FillTopInfo(ret);

                           // if (Send("uidl " + string(buf) + "\r\n")) {

                            //    string ret = Receive(50);
                            //    SplitString(emailuidl,ret,' ');
                                //temp.SetUIDL(emailuidl[2]);
                            //}

                            allEmail.push_back(temp);

						}
						else throw Exception(ret);
					}
					else throw Exception("send top failed");

				}
			}
			else throw Exception(ret);
		}
		else throw Exception("send list failed");

		return allEmail;
	}
void POP3Connector::Retr(int id,string UIDL) {
		char buf[20];
		sprintf(buf, "%d", id);
		if (Send("retr " + string(buf) + "\r\n")) {
			printf("receiving...\n");
			string ret = Receive(-1);
			if (ret.length() > 0 && ret[0] == '+') {
				printf("receive success!\n");
				Email().FillAll(ret).PrintTopInfo().Save(this->emailAddress,UIDL);
			}
			else throw Exception(ret);
		}
		else throw Exception("send retr failed");
	}
POP3Connector::~POP3Connector() {

  // if(Send("quit \r\n")) {
       //cout<<"quit success!"<<endl;
  // }

}


/**
 * 删除i号邮件
 * @param id
 */
void POP3Connector::Delt(int id) {
    char buf[20];
    sprintf(buf, "%d", id);
    if (Send("dele " + string(buf) + "\r\n")) {
        printf("delt...\n");
        string ret = Receive(50);
    }else printf("delt error...\n");
     if(Send("quit \r\n")) {
        // cout<<"quit success!"<<endl;
     }
}


/**
 * 获取i号右键的uidl
 * @param id
 * @return
 */
string POP3Connector::getallUIDL(int id) {
    char buf[20];
    sprintf(buf, "%d", id);
    vector<string> emailuidl;
    if (Send("uidl " + string(buf) + "\r\n")) {
        string ret = Receive(50);
        SplitString(emailuidl,ret,' ');
        return emailuidl[2];
    }else return std::__cxx11::string();
}

vector<string> POP3Connector::getallUIDL() {
    vector <string> emailuidl;

    int emailCount = 0;
    if (Send("stat\r\n")) {
        string ret;
        ret = Receive(100);
        if (ret.length() > 0 && ret[0] == '+') {
            vector<string> res;
            SplitString(res, ret, ' ');
            sscanf(res[1].c_str(), "%d\n", &emailCount);
            for (int i = 1; i <= emailCount ; i++) {
                vector <string>temp;
                char buf[20];
                sprintf(buf, "%d", i);
                        if (Send("uidl " + string(buf) + "\r\n")) {

                            string ret = Receive(50);

                            SplitString(temp,ret,' ');
                            string UIDLtemp = temp[2];
                                UIDLtemp.erase(std::remove(UIDLtemp.begin(),UIDLtemp.end(),'\n'),UIDLtemp.end());
                                UIDLtemp.erase(std::remove(UIDLtemp.begin(),UIDLtemp.end(),'\r'),UIDLtemp.end());
                            emailuidl.push_back(UIDLtemp);
                        }else throw Exception(temp[0]);

                    }
                }
                else throw Exception("send top failed");

            }

    return emailuidl;
}

vector<string> POP3Connector::getallUIDL2(){
    vector <string> emailuidl;
    if (Send("stat\r\n")) {
        string ret;
        ret = Receive(100);
        if (ret.length() > 0 && ret[0] == '+') {
            if(Send("uidl \r\n")){
            ret = Receive(-1);
            vector<string> res;

            SplitString(res, ret, '\n');
            for(string eachuidl:res){
                if(eachuidl.size()<10) continue;
                vector <string>temp;
                SplitString(temp,eachuidl,' ');
                string UIDLtemp = temp[1];
                cout<<temp[1];
                UIDLtemp.erase(std::remove(UIDLtemp.begin(),UIDLtemp.end(),'\n'),UIDLtemp.end());
                UIDLtemp.erase(std::remove(UIDLtemp.begin(),UIDLtemp.end(),'\r'),UIDLtemp.end());
                emailuidl.push_back(UIDLtemp);
            }

            }
        }
    }else{
        throw Exception("connect fails.");
    }

    return emailuidl;
}

Email POP3Connector::getEmailByTop(int id) {

    int emailCount = 0;
    Email temp;
    char buf[20];
    sprintf(buf, "%d", id);
                //printf("%d\t", i);
                if (Send("top " + string(buf) + " 1\r\n")) {
                    string ret = Receive(-1);
                    if (ret.length() > 0 && ret[0] == '+') {
                        //Email().FillTopInfo(ret).PrintTopInfo();
                        temp = Email().FillTopInfo(ret);
                    }else throw Exception("send the commend top error!!");
                }else throw Exception("linkd error!");
    return temp;

}


