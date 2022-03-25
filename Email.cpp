#include "util.h"
#include "Email.h"

#include <utility>


using namespace std;

Email& Email::FillTopInfo(const string & s) {
    this->star = false;
		this->topStr = s;
		this->from = ParseString(GetValueByKey(s, "\nFrom"));
		this->to = ParseString(GetValueByKey(s, "\nTo"));
		this->date = GetValueByKey(s, "\nDate");
		string subjecttemp = GetValueByKey(s, "\nSubject");
		this->subject = ParseString(subjecttemp);
		string t = "\\/*:?\"<>|";
		for (int i = 0; i < subject.length(); i++) {
			if (t.find(subject[i]) != string::npos) subject[i] = '_';
		}
		return *this;
	}
Email& Email::FillTopInfoRude(const string &s){
    this->topStr = s;
    this->from = ParseString(GetValueByKey(s, "\nFrom"));
    this->to = ParseString(GetValueByKey(s, "\nTo"));
    this->date = GetValueByKey(s, "\nDate");
    string subjecttemp = GetValueByKey(s, "\nSubject");
    this->subject = ParseString(subjecttemp);

    return *this;
}
Email& Email::PrintTopInfo() {
		//printf("ID\tFrom\tTo\tDate\tSubject\tCount=%d\n",emailCount);
		printf("%s\t%s\t%s\t%s\n", from.c_str(), to.c_str(), date.c_str(), subject.c_str());
		return *this;
	}

Email& Email::FillAll(const string & s) {
		this->allStr = s;
		FillTopInfo(s);
		return *this;
	}

Email& Email::Save(string email,string UIDL) {
    this->UIDL = UIDL;
		content = new MIMEContent(allStr.substr(allStr.find("\nContent-Type:")));
		content->SaveToFileByUIDL(this->UIDL,std::move(email));
		return *this;
	}
Email& Email::SetFrom(string srcEmailAddress) {
		this->from = srcEmailAddress;
		return *this;

	}
Email& Email::SetTo(string destEmailAddress) {
		this->to = destEmailAddress;
		return *this;
	}
Email& Email::SetSubject(string s) {
		//=?gb18030?B?zrTD/MP7My5jcHA=?=
		FILE* fp = fopen("temp", "w");
		fprintf(fp, "%s", s.c_str());
		fclose(fp);
		string res;
		EnCode(res, "temp", "base64");
		this->subject = "=?gb18030?B?" + res + "?=";
		return *this;
	}
Email& Email::SetMIMEContent(MIMEContent* cont) {
		this->content = cont;
		return *this;
	}
string Email::BuidEmailString() {
		string s = "";
		s = "MIME-Version: 1.0\r\nFrom: " + from + "\r\nTo: " + to + "\r\nSubject: " + subject + "\r\nDate: " + GetLocalCST() + "\r\n"
			+ content->ToString() + "\r\n.\r\n";
		return s;
	}

Email &Email::SetUIDL(string uidl) {
    this->UIDL = uidl;
}

json Email::returnjson(){
    json rejson ;
    rejson["uidl"] = string_To_UTF8(this->UIDL);
    rejson["subject"] = string_To_UTF8(this->subject);
    rejson["from"] = string_To_UTF8(this->from);
    rejson["date"] =string_To_UTF8(this->date);
    rejson["star"] = this->star;
    return rejson;

}
Email::Email(json rejson){
    this->UIDL = UTF8_To_string( rejson["uidl"]);
    this->subject = UTF8_To_string( rejson["subject"]);
    this->from=UTF8_To_string(  rejson["from"] );
    this->date= UTF8_To_string(  rejson["date"]);
    this->star = rejson["star"];
}
