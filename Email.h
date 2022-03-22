#ifndef MAIL_H
#define MAIL_H
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>

#include <string>
#include<Windows.h>
#include "MIMEContent.h"
#include <regex>
#include "json.hpp"
using json = nlohmann::json;

using namespace std;


class Email {
public:
    string UIDL;
	string topStr;
	string allStr;
	string from;
	string to;
	string date;
	string subject;
	MIMEContent* content;

	Email(){
	    content = NULL;
	}
    Email(json e);
	/**
	 * 在Email类中填充
	 * @param s
	 * @return
	 */
    Email& FillTopInfo(const string & s);
	Email& PrintTopInfo() ;
    Email& FillAll(const string & s);
    Email& Save(string email,string UIDL) ;
    Email& SetUIDL(string uidl);
    Email& SetFrom(string srcEmailAddress);
	Email& SetTo(string destEmailAddress);
    Email& SetSubject(string s) ;
    Email& SetMIMEContent(MIMEContent* cont) ;
    string BuidEmailString() ;
    Email& FillTopInfoRude(const string &s);
    json returnjson();


};

#endif // MAIL_H
