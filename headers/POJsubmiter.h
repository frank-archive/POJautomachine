#include<string>
#include"core\Socket.h"
#include"core\StringMatcher.h"
#include"core\Base64OnPOJ.h"
#define Accepted 1
#define Waiting 2
#define WrongAnswer 3

#define GPP "0"
#define GCC "1"
#define Java "2"
#define Pascal "3"
#define CPP "4"
#define C "5"
#define Fortran "6"

using namespace std;

// private property
//lab function
string JSESSIONID;//clearly= =
extern string username, password;
string *Scanner;//used for Scanning JSESSIONID
void login() {
	JSESSIONID = *getJSESSIONID((string)"poj.org");
	PostDataWithJSESSIONID(JSESSIONID,"user_id1="+username+"&password1="+password+"&B1=login&url=%2F",(string)"/login",(string)"poj.org");
}
//
//
//
//TODO post answer
//
//
//
string generateRequest(string &pID, string &code) {
	return (string)"problem_id=" + pID + "&language=" + CPP + "&source=" + encode(code) + "&submit=Submit&encoded=1";
}
void SubmitOnPOJ(string &code,string &pID) {
	login();//可以登录，待提交
	string request = generateRequest(pID, code);
	PostDataWithJSESSIONID(JSESSIONID, request, (string)"/submit", (string)"poj.org");
}
int getStatus(string pID) {
	Scanner = getPage((string)"poj.org", (string)"/status");
	int resultPos = match(*Scanner, (string)"a href=userstatus?user_id=" + username);
	if (resultPos == -1)return 10;//not found
	*Scanner = Scanner->substr(resultPos);
	int pidPos = match(*Scanner, (string)"a href=problem?id=")+18;
	
	resultPos = match(*Scanner, (string)"<font color="); resultPos += 12;
	for (int i = 0; i < 4; i++) {
		if ((*Scanner)[pidPos + i] != pID[i])return 10;
	}
	switch ((*Scanner)[resultPos]) {
	case 'r'://red for WA
		return WrongAnswer;
	case 'g'://green for Waiting or Compile Error
		switch ((*Scanner)[resultPos + 6]) {
		case 'W':
			return Waiting;
		default:
			return WrongAnswer;//Compile Error
		}
	case 'b'://blue for AC
		return Accepted;
	}
	return WrongAnswer;
}