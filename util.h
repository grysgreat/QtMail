//
// Created by HAN on 2022/3/8.
//

#ifndef UNTITLED1_UTIL_H
#define UNTITLED1_UTIL_H
#include <io.h>
#include<string>
#include<regex>
#include<winsock2.h>
#include<vector>
#include "Exception.h"
#pragma comment(lib,"ws2_32.lib")
using namespace std;

string GetEmailServerIP(string protoName, string emailAddress) ;
string GetUserFromEmailAddress(string emailAddress) ;
//+OK 20 72782
void SplitString(vector<string>& res, string s, char c);
//输出的字符如果超过76个字符就会自动换行
bool EnCode(string& res, string filename, string rule) ;
bool DeCode(string filename, const string& src, string rule) ;
void MyBoundaryFind(string src, string boundary, vector<int>& index);
string GetEnCodeContent(const string& s, string encoding = "base64") ;
bool DeQuoPri(const string& _src, string filename) ;
string GetStringFromFile(string charset) ;
string ParseString(string s);
string GetValueByKey(string s, string key);
string GetFieldInValue(string value, string f);
string GetLocalCST();
void SaveInfoToFile(string emailAddress, string password) ;
bool GetInfoFromFile(string& emailAddress, string& password);
void getFiles( string path, vector<string>& files );
//222114
bool isNumber(string s) ;


#endif //UNTITLED1_UTIL_H


