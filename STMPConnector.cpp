#include "STMPConnector.h"
#include "util.h"
SMTPConnector::SMTPConnector(string emailAddress, string password) :TCPConnector(GetEmailServerIP("smtp", emailAddress), port) {
		this->SMTPClientDomain = "myemail-client";
		this->emailAddress = emailAddress;
		this->password = password;
		Receive(100); //
		if (Send("ehlo " + SMTPClientDomain + "\r\n")) {
			string ret = Receive(200);
			if (ret.length() > 0 && ret.substr(0, 3) == "250") {
				AuthLogin();
			}
			else throw Exception(ret);
		}
		else throw Exception("send ehlo failed");
	}
bool SMTPConnector::SendEmail(string destEmailAddress, const string & content) {
		if (Send("mail from: <" + emailAddress + ">\r\n")) {
			string ret = Receive(50);
			if (ret.length() > 0 && ret.substr(0, 3) == "250") {
				if (Send("rcpt to: <" + destEmailAddress + ">\r\n")) {
					ret = Receive(50);
					if (ret.length() > 0 && ret.substr(0, 3) == "250") {
						if (Send("data\r\n")) {
							ret = Receive(50);
							if (ret.length() > 0 && ret.substr(0, 3) == "354") {
								printf("sending...\n");
								if (Send(content)) {
									ret = Receive(200);
									if (ret.length() > 0 && ret.substr(0, 3) == "250") { return true; }
									else throw Exception(ret);
								}
								else throw Exception("send content failed");
							}
							else throw Exception(ret);
						}
						else throw Exception("send data failed");
					}
					else throw Exception(ret);
				}
				else throw Exception("rcpt to failed");
			}
			else throw Exception(ret);
		}
		else throw Exception("mail from failed");
		return false;
	}

void SMTPConnector::AuthLogin() {
		if (Send("auth login\r\n")) {
			string ret = Receive(50);
			if (ret.length() > 0 && ret.substr(0, 3) == "334") {
				string encodeStr;
				FILE* temp = fopen("temp", "w");
				string user = GetUserFromEmailAddress(emailAddress);
				fwrite(user.c_str(), 1, user.length(), temp);
				fclose(temp);
				EnCode(encodeStr, "temp", "Base64");
				if (Send(encodeStr + "\r\n")) {
					ret = Receive(50);
					if (ret.length() > 0 && ret.substr(0, 3) == "334") {
						temp = fopen("temp", "w");
						fwrite(password.c_str(), 1, password.length(), temp);
						fclose(temp);
						EnCode(encodeStr, "temp", "Base64");
						if (Send(encodeStr + "\r\n")) {
							printf("auth login success!\n");
							ret = Receive(50);
							if (!(ret.length() > 0 && ret.substr(0, 3) == "235"))
								throw Exception(ret);
						}
						else throw Exception("send password failed in auth login");
					}
					else throw Exception("a2" + ret);
				}
				else throw Exception("send user failed in auth login");
			}
			else throw Exception("a3" + ret);
		}
		else throw Exception("send auth login failed");
	}