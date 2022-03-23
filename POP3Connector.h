

#ifndef _POP3CONNTEROR_
#define _POP3CONNTEROR_

#include "TCPConnector.h"
#include "Email.h"
#include <algorithm>
class POP3Connector : public TCPConnector {
	string emailAddress;
	string password;
	static const int port = 110;

public:


	POP3Connector(string emailAddress, string password);
	vector<Email> List(int count=-1);
	void Retr(int id,string UIDL);
    //closeTODO:更新一个函数，专门用来遍历全部的uidl
	string getallUIDL(int id);
	vector<string> getallUIDL();
	Email getEmailByTop(int id);
    void Delt(int id);
	~POP3Connector();
    void Quit();
    vector<string> getallUIDL2();
};
#endif
