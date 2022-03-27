#ifndef _TCPCONNECTOR_
#define _TCPCONNECTOR_


#include<winsock2.h>
#include<string>
#include "Exception.h"

//#pragma comment(lib,"ws2_32.lib")
using namespace std;
class TCPConnector {
	SOCKET sock;
public:
	TCPConnector(std::string destIP, int port) ;
	bool Send(const string & s) ;
	string Receive(int charLength , string delimit="\r\n.\r\n" );
	~TCPConnector() ;
};
#endif
