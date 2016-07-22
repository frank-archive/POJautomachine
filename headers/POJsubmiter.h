#include<string>
#include"core\Socket.h"
#include"core\base64.h"
#include"core\StringMatcher.h"
#define Accepted 1
#define Waiting 2
#define WrongAnswer 3
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
void SubmitOnPOJ(string &code,string &pID) {
	login();//可以登录，待提交
	cout<<getPageWithJSESSIONID(JSESSIONID,(string)"poj.org", (string)"/submit?problem_id=0")->c_str();
}
int getStatus() {
	Scanner = getPage((string)"poj.org", (string)"/status");
	int resultPos = match(*Scanner, (string)"a href=userstatus?user_id=" + username);
	*Scanner = Scanner->substr(resultPos);
	resultPos = match(*Scanner, (string)"<font color="); resultPos += 12;
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