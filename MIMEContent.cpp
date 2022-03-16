#include "util.h"
#include"MIMEContent.h"

using namespace std;



MIMEContent::MIMEContent(string contentType, string contentTransferEnCodeing,
string contentFileName , string contentDisposition ) {
		//Content-Type: text/plain;
		//charset="gb18030"
		//Content-Transfer-Encoding: base64

		//Content-Type: image/jpeg;
		//  name="mmexport1590651798523.jpg"
		//Content-Transfer-Encoding: base64
		//Content-Disposition: attachment;
		//  filename="mmexport1590651798523.jpg";
		this->contentType = contentType;
		this->contentTransferEnCodeing = contentTransferEnCodeing;
		this->contentDisposition = contentDisposition;
		this->contentString = "";

		if (contentFileName == "") {
			this->isMultipart = true;
			char buf[50];
			sprintf(buf, "----=_MYEMAIL_Part_%d\0", time(NULL));
			this->contentType = this->contentType + "\r\n\tboundary=\"" + string(buf) + "\"";
			this->boundary = ("--") + string(buf);
		}
		else if (contentDisposition == "") {
			//content
			this->isMultipart = false;
			EnCode(this->contentString, contentFileName, this->contentTransferEnCodeing);
		}
		else {
			//attachment
			this->isMultipart = false;
			//--------
			FILE* fp = fopen("temp", "w");
			fprintf(fp, "%s", contentFileName.c_str());
			fclose(fp);
			string res;
			EnCode(res, "temp", "base64");
			string t = "=?gb18030?B?" + res + "?=";
			//--------
			this->contentDisposition += ("filename=\"" + t + "\";");
			EnCode(this->contentString, contentFileName, this->contentTransferEnCodeing);
		}

	}
MIMEContent::MIMEContent(const string & MIMEString) {
		this->contentType = GetValueByKey(MIMEString, "Content-Type");
		if (this->contentType.find("multipart") == string::npos &&
			this->contentType.find("Multipart") == string::npos) {
			this->contentTransferEnCodeing = GetValueByKey(MIMEString, "Content-Transfer-Encoding");
			this->contentDisposition = GetValueByKey(MIMEString, "Content-Disposition");
			if (contentTransferEnCodeing.find("quoted-printable") != string::npos )
				this->contentString = GetEnCodeContent(MIMEString, "others"); // \r\n\r\n
			else this->contentString = GetEnCodeContent(MIMEString);
			this->isMultipart = false;
		}
		else {
			this->isMultipart = true;
			this->boundary = regex_replace(GetFieldInValue(contentType, "boundary"), regex("\""), "");
			this->contentTransferEnCodeing = GetValueByKey(MIMEString, "Content-Transfer-Encoding");

			vector<int> index;
			MyBoundaryFind(MIMEString, "--" + boundary, index);
			int count = index.size() - 1;
			for (int i = 0; i < count; i++) {
				items.push_back(new MIMEContent(MIMEString.substr(index[i], index[i + 1] - index[i])));
			}
		}
	}


void MIMEContent::SaveToFile(string subject,string email) {
		if (!isMultipart) {
			string filename = GetFieldInValue(contentType, "name");
			filename = ParseString(filename);
			if (filename.empty()) filename = ParseString(GetFieldInValue(contentDisposition, "filename"));
			//如果在 Content-Type找到name字段 或者 Content-Disposition中找到filename字段，

			//则按照给出的名字命名文件
			if (filename.empty()) {      // 是一个邮件内容
				filename = subject;
				string t = GetFieldInValue(contentType, "text");
				if (t.empty()) t = GetFieldInValue(contentType, "Text");
				if (t.empty()) t = "无法识别类型";
				filename += ("." + t);
			}

			if(email.size()>1){
			    filename = email+"\\"+filename;
			}

			if (contentTransferEnCodeing.find("base64") != string::npos
				|| contentTransferEnCodeing.find("Base64") != string::npos) {
			    //closetodo: 要解决路径保存问题
				DeCode(filename, contentString, "base64");
                //printf("had saved %s\n", filename.c_str());
			}
			else {//不是base64，都认为是QuoPri
				DeQuoPri(contentString, filename);
                //printf("had saved %s\n",filename.c_str());
			}
		}
		else {
			for (unsigned int i = 0; i < items.size(); i++) {
				items[i]->SaveToFile(subject,email);
			}
		}
	}
void MIMEContent::AddMIMEContent(MIMEContent* c) {
		items.push_back(c);
	}
string MIMEContent::ToString() {
		string s;
		if (!isMultipart) {
			string add = "";
			if (contentDisposition != "") add = "\r\nContent-Disposition: " + contentDisposition;
			s = "\r\nContent-Type: " + contentType + "\r\n" + "Content-Transfer-Encoding: " +
				contentTransferEnCodeing + add + "\r\n\r\n"
				+ contentString + "\r\n";

		}
		else {
			s = "Content-Type: " + contentType + "\r\n" + "Content-Transfer-Encoding: "
				+ contentTransferEnCodeing + "\r\n\r\n";
			for (int i = 0; i < items.size(); i++) {
				s += boundary;
				s += items[i]->ToString();
			}
			s += boundary + "--\r\n";
		}
		return s;
	}


void MIMEContent::SaveToFileByUIDL(string UIDL, string email) {
    if (!isMultipart) {
        //string filename = GetFieldInValue(contentType, "name");
        //filename = ParseString(filename);
        //if (filename.empty()) filename = ParseString(GetFieldInValue(contentDisposition, "filename"));
        //如果在 Content-Type找到name字段 或者 Content-Disposition中找到filename字段，
        //则按照给出的名字命名文件
//        if (filename.empty()) {      // 是一个邮件内容
//            filename = subject;
//
           string filename;
           string t = GetFieldInValue(contentType, "text");
            if (t.empty()) t =GetFieldInValue(contentType, "Text");
            if (!t.empty()) t = "."+t;


        if(email.size()>1){
            filename = email+"\\"+UIDL+t;
        }

        if (contentTransferEnCodeing.find("base64") != string::npos
            || contentTransferEnCodeing.find("Base64") != string::npos) {
            //closetodo: 要解决路径保存问题
            DeCode(filename, contentString, "base64");
            //printf("had saved %s\n", filename.c_str());
        }
        else {//不是base64，都认为是QuoPri
            DeQuoPri(contentString, filename);
            //printf("had saved %s\n",filename.c_str());
        }
    }
    else {
        for (unsigned int i = 0; i < items.size(); i++) {
            items[i]->SaveToFile(UIDL,email);
        }
    }
}
