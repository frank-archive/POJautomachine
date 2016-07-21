#include<WinSock2.h>
#include<iostream>
#include<Windows.h>
using namespace std;
#pragma comment(lib, "ws2_32.lib")
SOCKET sock;
string resultPage;
string request;
char buffer[1024];
string *getPage(string &host, string &directory) {
retry:;
	resultPage = ""; request = "";

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
		closesocket(sock);
		goto retry;
	}

	sockaddr_in address = { AF_INET };

	if (bind(sock, (sockaddr*)&address, sizeof(address)) == SOCKET_ERROR) {
		closesocket(sock);
		goto retry;
	}
	hostent *HostInfo = gethostbyname(host.c_str());
	if (HostInfo == 0) {
		closesocket(sock);
		goto retry;
	}

	address.sin_port = htons(80);
	memcpy(&address.sin_addr, HostInfo->h_addr, 4);

	if (connect(sock, (sockaddr*)&address, sizeof(address)) == SOCKET_ERROR) {
		closesocket(sock);
		goto retry;
	}

	request = "GET " + directory + " HTTP/1.1\r\nHost: " + host + "\r\nConnection:Close\r\n\r\n";

	if (send(sock, request.c_str(), request.size(), 0) == SOCKET_ERROR) {
		closesocket(sock);
		goto retry;
	}

	Sleep(1000);
	int recive;
	while (recive = recv(sock, buffer, sizeof(buffer) - 1, 0))
		resultPage += buffer;

	closesocket(sock);
	return &resultPage;
}
int main() {
	WSADATA word;
	WSAStartup(MAKEWORD(2, 2), &word);

	string suf = "/", hos = "cn.bing.com";
	cout << getPage(hos, suf)->c_str();
}