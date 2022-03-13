#include "TCPConnector.h"

TCPConnector::TCPConnector(string destIP, int port) {
		try {
			sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			if (sock == INVALID_SOCKET) throw 2;
			sockaddr_in sockad;
			sockad.sin_family = AF_INET;
			sockad.sin_addr.S_un.S_addr = inet_addr(destIP.c_str());
			sockad.sin_port = htons(port);
			if (connect(sock, (sockaddr*)(&sockad), sizeof(sockad)) == SOCKET_ERROR)
				throw 3;
		}
		catch (int e) {
			if (e == 2)
				if (e == 3) {
					int iResult = closesocket(sock);
					if (iResult == SOCKET_ERROR)
						wprintf(L"closesocket function failed with error: %d\n", WSAGetLastError());
				}
			printf("Error Code:%d\n", WSAGetLastError());
			throw Exception("create TCP connection failed");
		}
	}

bool TCPConnector::Send(const string & s) {
		const char* buf = s.c_str();
		int cnt = s.length() / 7000;
		int i = 0;
		int pd = cnt / 50 + 1;
		for (; i < cnt; i++) {
			if (send(sock, buf + i * 7000, 7000, 0) == SOCKET_ERROR) { return false; }
			if (i % pd == 0) printf("#");

		}
		if (s.length() % 7000 != 0) {
			if (send(sock, buf + i * 7000, s.length() % 7000, 0) == SOCKET_ERROR) {
				return false;
			}
		}
		return true;
	}

string TCPConnector::Receive(int charLength , string delimit) { // charLength >= len
		if (charLength < 0) {
			char* buf = new char[7005];
			string s = "";
			int len;
			int i = 0;
			while ((len = recv(sock, buf, 7000, 0)) != SOCKET_ERROR) {
				buf[len] = '\0';
				i++;
				if (i == 50) {
					printf("#");
					i = 0;
				}
				string t = buf;
				s += t;
				if (s.substr(s.length() - 5) == delimit) break;
			}
			delete [] buf;
			return s;
		}
		else {
			char* buf = new char[charLength + 5];
			string s;
			int len;
			if ((len = recv(sock, buf, charLength, 0)) != SOCKET_ERROR) {
				buf[len] = '\0';
				s = buf;
				delete [] buf;
				return s;
			}
		}
	}
	
TCPConnector::~TCPConnector() {
		int iResult = closesocket(sock);
		if (iResult == SOCKET_ERROR)
			wprintf(L"closesocket function failed with error: %d\n", WSAGetLastError());
	}