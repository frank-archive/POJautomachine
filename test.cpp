#include<iostream>
#include<WinSock2.h>
using namespace std;
#pragma comment(lib,"ws2_32.lib")
string *getPage(string &host, string &directory) {
	SOCKET sock;
	string resultPage;
	string request;
	char buffer[1024];
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

	

	//request = "POST http://poj.org/login HTTP/1.1\r\nHost: poj.org\r\nConnection: Keep - Alive\r\nCookie: JSESSIONID=95B10CB74D6CB8B6810BB948E5C2D6C8; __utmc=79247125; __utma=79247125.1915142156.1468666850.1469062220.1469069378.7; __utmz=79247125.1468669205.2.2.utmcsr=baidu|utmccn=(organic)|utmcmd=organic; __utmb=79247125.18.10.1469069378; __utmt=1\r\n\r\nuser_id1 = frankli0324&password1 = lixuanzhe0324&B1 = login\r\n";

	if (send(sock, request.c_str(), request.size(), 0) == SOCKET_ERROR) {
		closesocket(sock);
		goto retry;
	}

	Sleep(1000);
	int recive; memset(buffer, 0, sizeof(buffer));
	while (recive = recv(sock, buffer, sizeof(buffer) - 1, 0)) {
		resultPage += buffer;
		if (recive < sizeof(buffer)-1)break;
	}
		

	closesocket(sock);
	cout << resultPage.c_str();
	return &resultPage;
}

int main() {
	WSADATA word;
	WSAStartup(MAKEWORD(2, 2), &word);

	string host = "poj.org", dir = "/submit?problem_id=0";

	getPage(host, dir);
}