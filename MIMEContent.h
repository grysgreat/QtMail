#ifndef _MIMECONTENT_
#define _MIMECONTENT_


#include<string>
#include<vector>
#include<time.h>
#include<windows.h>
#include<regex>

using namespace std;

class MIMEContent {
	vector<MIMEContent*> items;
	bool isMultipart;
	string boundary;  //not NULL represents multipart  
	string contentType;
	string contentTransferEnCodeing;
	string contentDisposition;
	string contentString;
public:
	MIMEContent(string contentType, string contentTransferEnCodeing,string contentFileName ="", string contentDisposition ="" );
    MIMEContent(const string & MIMEString);
    void SaveToFile(string subject,string email ="");
    void AddMIMEContent(MIMEContent* c);
    string ToString() ;
    void SaveToFileByUIDL(string subject,string email);
    
};
#endif
