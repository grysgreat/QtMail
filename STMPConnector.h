#ifndef _STMPCONNTEROR_
#define _STMPCONNTEROR_

#include"TCPConnector.h"

class SMTPConnector : public TCPConnector {
	string emailAddress;
	string password;
	static const int port = 25;
	string SMTPClientDomain;

public:
SMTPConnector(string emailAddress, string password);
bool SendEmail(string destEmailAddress, const string & content) ;
void AuthLogin();

};
#endif