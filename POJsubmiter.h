#include<string>
#include"Socket.h"
#include"base64.h"
#include"StringMatcher.h"
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
	login();
	cout<<getPageWithJSESSIONID(JSESSIONID,(string)"poj.org", (string)"/")->c_str();
}