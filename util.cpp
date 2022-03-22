//
// Created by HAN on 2022/3/8.
//

#include "util.h"

/**
 *
 * @param protoName
 * @param emailAddress
 * @return 通过邮箱获取服务器的ip地址
 */
string GetEmailServerIP(string protoName, string emailAddress) {
    string serverName = protoName + "." + emailAddress.substr(emailAddress.find("@") + 1);
    HOSTENT* hostent = gethostbyname(serverName.c_str());
    if (hostent == NULL) throw Exception("gethostbyname failed with " + serverName);
    if (hostent->h_addrtype != AF_INET) throw Exception("hostent addrtype is not AF_INET");
    in_addr addr;
    if (hostent->h_addr_list[0] == 0) throw Exception("hostent addr_list[0] equals zero");
    addr.S_un.S_addr = *(u_long*)hostent->h_addr_list[0];
    return inet_ntoa(addr);
}

/**
 *
 * @param emailAddress
 * @return 获取用户名
 */
string GetUserFromEmailAddress(string emailAddress) {
    return emailAddress.substr(0, emailAddress.find("@"));
}
//+OK 20 72782
/**
 *
 * @param res
 * @param s
 * @param c  字符串拆分
 */
void SplitString(vector<string>& res, string s, char c) {
    if (s.length() > 0) {
        int start = 0;
        if (s[0] == c) start = 1;
        for (int i = start + 1; i < s.length(); i++) {
            if (s[i] == c) {
                res.push_back(s.substr(start, i - start));
                start = i + 1;
            }
        }
        if (start != s.length()) res.push_back(s.substr(start));
    }
}
//输出的字符如果超过76个字符就会自动换行
/**
 * base64 编码
 * @param res
 * @param filename
 * @param rule
 * @return
 */
bool EnCode(string& res, string filename, string rule) {
    cout<<"---------"<<filename;
    FILE* fp = fopen(filename.c_str(), "rb");
    if (fp == NULL) return false;
    fseek(fp, 0, SEEK_END);
    int len = ftell(fp);
    char* out = new char[(int)(1.5 * len)];
    memset(out, 0, len);
    fseek(fp, 0, SEEK_SET);
    unsigned char in[3];
    memset(in, 0, 3);
    int i = 0;
    string a = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    int j = 0;
    int c = 0;
    while ((j = fread(in, 1, 3, fp)) == 3) {
        out[i] = a[(char)(in[0] >> 2)];
        out[i + 1] = a[(char)((in[0] & 0x03) << 4 | in[1] >> 4)];
        out[i + 2] = a[(char)((in[1] & 0x0f) << 2 | in[2] >> 6)];
        out[i + 3] = a[(char)(in[2] & 0x3f)];
        i += 4;
        memset(in, 0, 3);

        c += 4;
        if (c == 76) {
            out[i] = '\r';
            out[i + 1] = '\n';
            i += 2;
            c = 0;
        }

    }
    if (j != 0) {
        out[i] = a[(char)(in[0] >> 2)];
        out[i + 1] = a[(char)((in[0] & 0x03) << 4 | in[1] >> 4)];
        out[i + 2] = a[(char)((in[1] & 0x0f) << 2 | in[2] >> 6)];
        out[i + 3] = a[(char)(in[2] & 0x3f)];
        if (j == 2) out[i + 3] = '=';
        if (j == 1) {
            out[i + 3] = '=';
            out[i + 2] = '=';
        }
        out[i + 4] = '\0';
    }
    else out[i] = '\0';
    res = out;
    fclose(fp);
    return true;
}

/**
 * base64 解码
 * @param filename
 * @param src
 * @param rule
 * @return
 */ //closetodo: 要解决路径保存问题
bool DeCode(string filename, const string& src, string rule) {
    FILE* fp = fopen(filename.c_str(), "wb");
    if (fp == NULL) {
        printf("can't open %s\n", filename.c_str());
        return false;
    }
    char a[127];
    for (int i = 'a', j = 'A', k = 0; i <= 'z'; i++, j++, k++) {
        a[i] = k + 26;
        a[j] = k;
    }
    for (int i = '0', j = 52; i <= '9'; i++, j++) a[i] = j;
    a['+'] = 62;
    a['/'] = 63;
    a['='] = 0;
    int len = src.length();
    int i = 3;
    unsigned char b[4];
    char buf[3];
    for (; i < len; i += 4) {
        b[0] = a[src[i - 3]];
        b[1] = a[src[i - 2]];
        b[2] = a[src[i - 1]];
        b[3] = a[src[i]];

        buf[0] = (b[0] << 2) | (b[1] >> 4);
        buf[1] = (b[1] << 4) | (b[2] >> 2);
        buf[2] = (b[2] << 6) | b[3];
        if (src[i] != '=') fwrite(buf, 1, 3, fp);
        else {
            if (src[i] == '=' && src[i - 1] == '=') fwrite(buf, 1, 1, fp);
            else if (src[i] == '=') fwrite(buf, 1, 2, fp);
        }
    }
    fclose(fp);
    return true;
}

/**
 *
 * @param src
 * @param boundary
 * @param index
 */
void MyBoundaryFind(string src, string boundary, vector<int>& index) {
    int len = boundary.length();
    int pre = src.find(boundary);
    src = src.substr(pre + len);
    index.push_back(pre);
    int i;
    while ((i = src.find(boundary)) != string::npos) {
        pre = pre + len + i;
        index.push_back(pre);
        src = src.substr(i + len);
    }
}
/**
 * 获取内容
 */
string GetEnCodeContent(const string& s, string encoding) {
    smatch sm;
    regex_search(s,sm,regex("(\\r?\\n)\\1"));
    int i = sm.position();
    if (s[i] == '\r') i = i + 4;
    else i = i + 3;
    if (encoding != "base64") return s.substr(i);
    int slen = s.length();

    int k = i;
    for (; s[k] != '\r'; k++);
    int linelen = k - i;
    string ret = "";
    for (; i < slen; i += linelen + 2) {
        if (i + linelen > slen) {
            int j = i;
            for (; s[j] != '\r' && s[j] != '\n'; j++);
            ret += s.substr(i, j - i);
        }
        else ret += s.substr(i, linelen);
    }
    return ret;
}
/**
 *
 * @param _src
 * @param filename
 * @return
 */
bool DeQuoPri(const string& _src, string filename) {
    FILE* fp = fopen(filename.c_str(), "wb");
    if (fp) {
        int len = _src.length();
        unsigned char* buffer = new unsigned char[len];
        char* src = new char[len];
        memcpy(src, _src.c_str(), len);
        int b = 0;
        int pt = 0;
        auto f = [](char c) ->int { return c >= 'A' && c <= 'F' ? c - 'A' + 10 : c - '0'; };
        auto isUpperAlnum = [](char a) {return (a >= 'A' && a <= 'F') || (a >= '0' && a <= '9') ? true : false; };
        for (int i = 0; i < len;) {
            if (src[i] == '=' && src[i + 1] == '\n') {
                memcpy(buffer + pt, src + b, i - b);
                pt = pt + i - b;
                b = i = i + 2;
                continue;
            }
            if (src[i] == '=' && src[i + 1] == '\r' && src[i + 2] == '\n') {
                memcpy(buffer + pt, src + b, i - b);
                pt = pt + i - b;
                b = i = i + 3;
                continue;
            }
            if (src[i] == '=' && isUpperAlnum(src[i + 1]) && isUpperAlnum(src[i + 2])) {
                memcpy(buffer + pt, src + b, i - b);
                pt = pt + i - b;
                unsigned char n = 0;
                n = f(src[i + 1]) * 16 + f(src[i + 2]);
                buffer[pt] = n;
                pt = pt + 1;
                b = i = i + 3;
                continue;
            }
            i++;
        }
        if (b < len) {
            memcpy(buffer + pt, src + b, len - b);
            pt = pt + len - b;
        }
        fwrite(buffer, 1, pt, fp);
        delete[] buffer;
        delete[] src;
        fclose(fp);
        return true;
    }
    else return false;
}


string GetStringFromFile(string charset) {
    string ret = "";
    if ( charset=="utf-8") {
        FILE* fp = fopen("temp", "rb");
        char buf[3000];
        if (fp) {
            fseek(fp, 0, SEEK_END);
            int size = ftell(fp);
            fseek(fp, 0, SEEK_SET);
            fread(buf, 1, size, fp);
            buf[size] = '\0';
        }
        fclose(fp);
        ret = string(buf);
    }
    else {
        FILE* fp = fopen("temp", "rb");
        char buf[3000];
        if (fp) {
            fseek(fp, 0, SEEK_END);
            int size = ftell(fp);
            fseek(fp, 0, SEEK_SET);
            fread(buf, 1, size, fp);
            buf[size] = '\0';
        }
        fclose(fp);
        ret = string(buf);
    }
    return ret;
}


//Subject: =?UTF-8?B?572R5piT6YKu566x77yM6YKj5Lqb5L2g?=
// =?UTF-8?B?55+l6YGT5ZKM5LiN55+l6YGT55qE5LqL?=

//"=?UTF-8?B?5LqU6YKR5aSn5a2m572R57uc5a6J5YWo5pyf?=
// =?UTF-8?B?5pyr5aSN5Lmg6aKYKDEpLmRvY3g=?="

//filename*=utf-8''%E6%9D%A8zi.jpg
//=?utf-8?B?5oeC5rOV5a6I5rOV55yL5pe26Ze0?=
//=?gb18030?B?zrTD/MP7My5jcHA=?=
//20200610145415zecyab.jpg
//From: "=?gb18030?B?sfnQxMrExsazpNK5zOw=?=" <xjqxz4yth@qq.com>
//To: "=?gb18030?B?MTU4MTk4MjcyMTI=?=" <15819827212@189.cn>


/**
 *
 * @param s
 * @return 编码解码格式
 */
string ParseString(string s) {
    string ret = "";
    if (s.length() > 0) {
        string out = regex_replace(s, regex("[\"\\r\\n\\t]"), " ");
        out = regex_replace(out, regex("(\\s)\\1+"), " ");
        vector<string> res;
        SplitString(res, out, ' ');
        for (int i = 0; i < res.size(); i++) {
            if (res[i].size() > 0 && res[i][0] == '=') {
                vector<string> v;
                SplitString(v, res[i], '?');
                if (v.size() > 1) {
                    if (v[2][0] == 'B' || v[2][0] == 'b') {
                        if (v[1][0] == 'U' || v[1][0] == 'u') {
                            DeCode("temp", v[3], "base64");
                            ret += GetStringFromFile("utf-8");
                        }
                        else {
                            DeCode("temp", v[3], "base64");
                            ret += GetStringFromFile("ansi");
                        }
                    }
                    else {
                        if (v[1][0] == 'U' || v[1][0] == 'u') {
                            DeQuoPri(v[3],"temp");
                            ret += GetStringFromFile("utf-8");
                        }
                        else {
                            DeQuoPri(v[3], "temp");
                            ret += GetStringFromFile("ansi");
                        }
                    }
                }
                else ret += res[i];
            }
            else ret += res[i];
        }
    }
    return ret;
}

/**
 *
 * @param s
 * @param key
 * @return 获取key
 */
string GetValueByKey(string s, string key) {
    int k = s.find(key);
    if (k == string::npos) return "";
    for (; s[k] != ':'; k++);
    k = k + 1;
    smatch sm;
    regex_search(s.cbegin() + k, s.cend(), sm, regex("\\r?\\n[\\w\\r\\n]"));
    return s.substr(k, sm.position());
}


/**
 *
 * @param value
 * @param f
 * @return  获取value
 */
string GetFieldInValue(string value, string f) {
    string ret = "";
    if (value.find(f) != string::npos) {
        int s = value.find(f) + f.length() + 1; // s 指向'=' '/' '*' 后的第一个字符
        int e = s;
        for (; e < value.length() && value[e] != ';'; e++);
        ret = value.substr(s, e - s);
    }
    return ret;
}

/**
 *
 * @return  获取当前时间
 */
string GetLocalCST() {
    time_t rawtime;
    time(&rawtime);
    struct tm* info = localtime(&rawtime);
    //Wed, 10 Jun 2020 14:55:15 +0800 (CST)
    string week[7] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };
    string month[12] = { "Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sept","Oct","Nov","Dec" };
    char buf[50];
    sprintf(buf, "%s, %d %s %d %02d:%02d:%02d\0", week[info->tm_wday].c_str(),
            info->tm_mday, month[info->tm_mon].c_str(), info->tm_year + 1900,
            info->tm_hour, info->tm_min, info->tm_sec);
    return string(buf) + " +0800 (CST)";

}

/**
 * 用户名和密码写入*myemail.conf* 文件
 * @param emailAddress
 * @param password
 */
void SaveInfoToFile(string emailAddress, string password) {

    char buf[100];
    GetModuleFileNameA(NULL, buf, 100);
    string t = string(buf);
    string PATH = t.substr(0, t.rfind('\\'));
    FILE* fp = fopen( (PATH +"\\"+emailAddress+".conf").c_str(), "w");
    if (fp != NULL)
        fprintf(fp, "%s\n%s", emailAddress.c_str(), password.c_str());
    else throw Exception("can't create myemail.conf in " + PATH + "; maybe you don't have permission");
    fclose(fp);
}



/**
 *
 * @param emailAddress
 * @param password
 * @return 从文件 *myemail.conf*中获取用户名和密码
 *
 */
bool GetInfoFromFile(string& emailAddress, string& password) {
    char addr[100];
    char pass[100];
    char buf[100];
    GetModuleFileNameA(NULL, buf, 100);
    string t = string(buf);
    string PATH = t.substr(0, t.rfind('\\'));

    FILE* fp = fopen((PATH +"\\"+emailAddress+".conf").c_str(), "r");
    if (fp != NULL) {
        fscanf(fp, "%s\n%s", addr, pass);
        fclose(fp);
        //emailAddress = addr;
        password = pass;
        return true;
    }
    else return false;
}


void getFiles( string path, vector<string>& files )
{
    //文件句柄
    long   hFile   =   0;
    //文件信息
    struct _finddata_t fileinfo;
    string p;
    if((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) !=  -1)
    {
        do
        {
            //如果是目录,迭代之
            //如果不是,加入列表
//            if((fileinfo.attrib &  _A_SUBDIR))
//            {
//                if(strcmp(fileinfo.name,".") != 0  &&  strcmp(fileinfo.name,"..") != 0)
//                    getFiles( p.assign(path).append("\\").append(fileinfo.name), files );
//            }
//            else
//            {
        string temp = fileinfo.name;
        //cout<<filetype<<endl;
        if(temp.size()>6 ){
            string filetype( temp, temp.size()-4, 4 );
            string emailname( temp, 0, temp.size()-5);
           // cout <<filetype<<endl;
            if(filetype =="conf")files.push_back(emailname);
        }
            //           }
        }while(_findnext(hFile, &fileinfo)  == 0);
        _findclose(hFile);
    }
}

/**
 *
 * @param s
 * @return 返回是否是数字的判断
 */
bool isNumber(string s) {
    if (s.length() == 0) return false;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] < '0' || s[i]>'9') return false;
    }
    return true;
}

std::string string_To_UTF8(const std::string & str)
{
int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);

wchar_t * pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴
ZeroMemory(pwBuf, nwLen * 2 + 2);

::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);

int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

char * pBuf = new char[nLen + 1];
ZeroMemory(pBuf, nLen + 1);

::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

std::string retStr(pBuf);

delete []pwBuf;
delete []pBuf;

pwBuf = NULL;
pBuf = NULL;

return retStr;
}





std::string UTF8_To_string(const std::string & str)
{
int nwLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);

wchar_t * pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴
memset(pwBuf, 0, nwLen * 2 + 2);

MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), pwBuf, nwLen);

int nLen = WideCharToMultiByte(CP_ACP, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

char * pBuf = new char[nLen + 1];
memset(pBuf, 0, nLen + 1);

WideCharToMultiByte(CP_ACP, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

std::string retStr = pBuf;

delete []pBuf;
delete []pwBuf;

pBuf = NULL;
pwBuf = NULL;

return retStr;
}







